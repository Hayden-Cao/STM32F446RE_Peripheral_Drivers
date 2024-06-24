/*
 * stm32f446xx_SPI_Driver.c
 *
 *  Created on: May 23, 2024
 *      Author: caoha
 */

#ifndef STM32F446XX_SPI_DRIVER_C_
#define STM32F446XX_SPI_DRIVER_C_

#include "stm32f446xx_SPI_Driver.h"

// Clock Control
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
		if(EnorDi == ENABLE)
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_EN();
			}
			else if (pSPIx == SPI2)
			{
				SPI2_PCLK_EN();
			}
			else if (pSPIx == SPI3)
			{
				SPI3_PCLK_EN();
			}
			else if (pSPIx == SPI4)
			{
				SPI4_PCLK_EN();
			}
		}
		else
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_DI();
			}
			else if (pSPIx == SPI2)
			{
				SPI2_PCLK_DI();
			}
			else if (pSPIx == SPI3)
			{
				SPI3_PCLK_DI();
			}
			else if (pSPIx == SPI4)
			{
				SPI4_PCLK_DI();
			}
		}
}

// Init and Deinit

void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	//peripheral clock enable

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	//first lets configure the SPI_CR1 register

	uint32_t tempreg = 0;

	//1. configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR ;

	//2. Configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIDIMODE);

	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		tempreg |= ( 1 << SPI_CR1_BIDIMODE);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//BIDI mode should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIDIMODE);
		//RXONLY bit must be set
		tempreg |= ( 1 << SPI_CR1_RXONLY);
	}

	// 3. Configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//4.  Configure the DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	//5. configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//6 . configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempreg;

}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	pSPIx->CR1 = 0;
}

// Data send and receive

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t length)
{
	//length is in number of bytes
	while(length > 0)
	{
		// wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == RESET);

		// checking dff bit
		if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit mode therefore we need to typecase the uint8_t *pTxBuffer to 16 bit
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			length--;
			length--;
			(uint16_t*)pTxBuffer++;		// addition to make it point to the next data in the buffer
		}
		else
		{
			pSPIx->DR = *pTxBuffer;
			length--;
			pTxBuffer++;
		}

	}

}


void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t length )
{
	//length is in number of bytes
	while(length > 0)
	{
		// wait until RXNE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == RESET);

		// checking dff bit
		if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit mode therefore we need to typecase the uint8_t *pTxBuffer to 16 bit
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			length--;
			length--;
			(uint16_t*)pRxBuffer++;		// addition to make it point to the next data in the buffer
		}
		else
		{
			*(pRxBuffer) = pSPIx->DR;
			length--;
			pRxBuffer++;
		}
	}
}

// IRQ Config and ISR Handling

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);


void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);


void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp1, temp2;

	// stores value of TXE and if the interuppt for TXE is enabled
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_TXE);
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_TXEIE);

	if (temp1 && temp2)
	{
		SPI_TXE_Interrupt_Handle();
	}

	// stores value of TXE and if the interuppt for TXE is enabled
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_RXNE);
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_RXNEIE);

	if (temp1 && temp2)
	{
		SPI_RXNE_Interrupt_Handle();
	}

	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_OVR);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);


	if (temp1 && temp2)
	{
		SPI_OVR_Err_Interrupt_Handle();
	}

}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if (pSPIx->SR & FlagName)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{

	if (EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

void SPI_SSIControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{

	if (EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}


// Private SPI Interrupt Handling

static void SPI_TXE_Interrupt_Handle(SPI_Handle_t *pSPIHandle)
{
	if ((pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF)))
	{
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}
	else
	{
		pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		pSPIHandle->pTxBuffer++;
	}

	if (!pSPIHandle->TxLen)
	{
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
		pSPIHandle->pTxBuffer = NULL;
		pSPIHandle->TxLen =0;
		pSPIHandle->TxState = SPI_READY;

	}
}


static void SPI_RXNE_Interrupt_Handle(SPI_Handle_t *pSPIHandle)
{
	//do rxing as per the dff
	if(pSPIHandle->pSPIx->CR1 & ( 1 << 11))
	{
		//16 bit
		*((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t) pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen -= 2;
		pSPIHandle->pRxBuffer++;
		pSPIHandle->pRxBuffer++;

	}else
	{
		//8 bit
		*(pSPIHandle->pRxBuffer) = (uint8_t) pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer++;
	}

	if(! pSPIHandle->RxLen)
	{
		//reception is complete
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);
	}

}

static void SPI_OVR_Err_Interrupt_Handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	// clearing OVR Flag
	if (pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{

	}

}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseRecpetion(SPI_Handle_t *pSPIHandle);


#endif /* STM32F446XX_SPI_DRIVER_C_ */
