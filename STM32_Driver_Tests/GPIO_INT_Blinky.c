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
	// All Pins are push pull with no pull up resistors
	// Only resistors needed are external current limiting resistors for external leds
	GPIO_Handle_t GPIO_LED1, GPIO_BTN;

	GPIO_LED1.pGPIOx = GPIOB;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_LED1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	GPIO_Init(&GPIO_LED1);

	GPIO_BTN.pGPIOx = GPIOA;
	GPIO_BTN.GPIO_PinConfig.GPIO_PinNumber = 9;
	GPIO_BTN.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
	GPIO_BTN.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_BTN.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_BTN.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	GPIO_Init(&GPIO_BTN);

	GPIO_IRQInterruptConfig(IRQ_EXTI9_5, ENABLE);

	GPIO_WriteToOutputPin(GPIOB, 5, 0);
	/* Loop forever */
	for(;;)
	{

	}

}

void EXTI9_5_IRQHandler(void)   // <----- The ISR Function We're Looking For!
{
   GPIO_IRQHandling(9);
   // software delay for debouncing
   Delay();
   GPIO_ToggleOutputPin(GPIOB, 5);
}
