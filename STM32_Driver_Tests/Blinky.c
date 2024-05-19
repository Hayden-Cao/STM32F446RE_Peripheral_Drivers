#include <stdint.h>
#include "stm32f446xx_GPIO_Driver.h"
#include "stm32f446xx.h"

// quick software delay
void delay()
{
	for(int i = 0; i < 500000; i++);
}

int main(void)
{
	GPIO_Handle_t GPIO_LED;

	GPIO_LED.pGPIOx = GPIOA;

	GPIO_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_LED.GPIO_PinConfig.GPIO_PinNumber = 9;
	GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIO_LED);
	GPIO_WriteToOutputPin(GPIOA, 9, SET);
    /* Loop forever */
	for(;;)
	{
		GPIO_ToggleOutputPin(GPIOA, 9);
		delay();
	}

}
