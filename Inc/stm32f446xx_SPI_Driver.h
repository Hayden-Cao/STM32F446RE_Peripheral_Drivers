/*
 * stm32f446xx_SPI_Driver.h
 *
 *  Created on: May 22, 2024
 *      Author: caoha
 */

#ifndef STM32F446XX_SPI_DRIVER_H_
#define STM32F446XX_SPI_DRIVER_H_

#include "stm32f446xx.h"

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct
{
	SPI_RegDef_t *pSPIx; 		// base addresses of SPIx peripheral registers
	SPI_Config_t SPIConfig;
}SPI_Handle_t;

// Clock Control
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

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


// Other Control Functions


#endif /* STM32F446XX_SPI_DRIVER_H_ */
