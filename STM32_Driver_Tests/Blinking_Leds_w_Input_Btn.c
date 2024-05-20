#include <stdint.h>
#include "stm32f446xx.h"
#include "stm32f446xx_GPIO_Driver.h"

// quick software delay
void Delay(void)
{
	for(int i = 0; i < 500000; i++);
}


int main(void)
{
	GPIO_Handle_t GPIO_LED1;

	GPIO_LED1.pGPIOx = GPIOA;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinNumber = 9;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	GPIO_Init(&GPIO_LED1);

	GPIO_Handle_t GPIO_LED2;

	GPIO_LED2.pGPIOx = GPIOA;
	GPIO_LED2.GPIO_PinConfig.GPIO_PinNumber = 8;
	GPIO_LED2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_LED2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_LED2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_LED2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	GPIO_Init(&GPIO_LED2);

	GPIO_Handle_t GPIO_LED3;

	GPIO_LED3.pGPIOx = GPIOC;
	GPIO_LED3.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_LED3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_LED3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_LED3.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_LED3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	GPIO_Init(&GPIO_LED3);

	GPIO_Handle_t GPIO_Switch;

	GPIO_Switch.pGPIOx = GPIOB;
	GPIO_Switch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIO_Switch.GPIO_PinConfig.GPIO_PinNumber = 10;
	GPIO_Switch.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_Switch.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Switch.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&GPIO_Switch);

	GPIO_WriteToOutputPin(GPIOA, 9, 0);
	GPIO_WriteToOutputPin(GPIOA, 8, 0);
	GPIO_WriteToOutputPin(GPIOC, 7, 0);

    /* Loop forever */
	for(;;)
	{
		if (GPIO_ReadFromInputPin(GPIOB, 10))
		{
			 GPIO_ToggleOutputPin(GPIOA, 9);
			 Delay();
			 GPIO_ToggleOutputPin(GPIOA, 8);
			 Delay();
			 GPIO_ToggleOutputPin(GPIOC, 7);
			 Delay();
		}

	}
}
