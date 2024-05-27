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

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

// Data send and receive

void SPI_SendData(SPI_RegDef_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t length);
void SPI_ReceiveData(SPI_RegDef_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t length );

// IRQ Config and ISR Handling

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_RegDef_t *pSPIHandle);


#endif /* STM32F446XX_SPI_DRIVER_C_ */
