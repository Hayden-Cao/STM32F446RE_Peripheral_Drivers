#include "stm32f446xx.h"
#include "stm32f446xx_GPIO_Driver.h"
#include "stm32f446xx_SPI_Driver.h"
#include <string.h>

// SPI2 MOSI: PB15
// SPI2 MISO: PB14
// SPI2 SCLK: PB13

void SPI2_Pin_Init()
{
    GPIO_Handle_t SPI_Pins;


    SPI_Pins.pGPIOx = GPIOB;
    SPI_Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPI_Pins.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_MODE_IT_RT;
    SPI_Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPI_Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPI_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = 15;
    GPIO_Init(&SPI_Pins);

    SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = 13;
    GPIO_Init(&SPI_Pins);

}

void SPI2_Init()
{
    SPI_Handle_t SPI_NO_2;

    SPI_NO_2.pSPIx = SPI2;
    SPI_NO_2.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI_NO_2.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI_NO_2.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI_NO_2.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI_NO_2.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI_NO_2.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
    SPI_NO_2.SPIConfig.SPI_SSM = SPI_SSM_EN;

    SPI_Init(&SPI_NO_2);

}

int main (void)
{
    SPI2_Pin_Init();
    SPI2_Init();
    SPI_SSIControl(SPI2, ENABLE);
    SPI_PeripheralControl(SPI2, ENABLE);
    char buf[] = "Hello World";

    while(1)
    {
    	while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));
    	SPI_SendData(SPI2, (uint8_t*)buf, strlen(buf));
    }
    return 0;
}

