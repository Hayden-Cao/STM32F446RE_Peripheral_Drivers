/*
 * stm32f446xx.h
 *
 *  Created on: May 18, 2024
 *      Author: haydencao
 */

#ifndef STM32F446XX_H_
#define STM32F446XX_H_


#include <stdint.h>

#define __vo volatile


//some generic macros

#define ENABLE 				1
#define DISABLE 			0
#define SET 				ENABLE
#define RESET 				DISABLE
#define FLAG_RESET          RESET
#define FLAG_SET 			SET

/*
 * AHBx and APBx Bus Peripheral Addresses
 */

#define PERI_BASE_ADDR 		0x40000000U
#define APB1_ADDR			PERI_BASE_ADDR
#define	APB2_ADDR			0x40010000U
#define AHB1_ADDR			0x40020000U
#define AHB2_ADDR			0x50000000U

/*
 * Register Base Addresses
 */

// GPIO
#define GPIOA_ADDR 			AHB1_ADDR
#define GPIOB_ADDR 			(AHB1_ADDR + 0x0400)
#define GPIOC_ADDR			(AHB1_ADDR + 0x0800)
#define GPIOD_ADDR			(AHB1_ADDR + 0x0C00)
#define GPIOE_ADDR 			(AHB1_ADDR + 0x1000)
#define GPIOF_ADDR 			(AHB1_ADDR + 0x1400)
#define GPIOG_ADDR 			(AHB1_ADDR + 0x1800)
#define GPIOH_ADDR 			(AHB1_ADDR + 0x1C00)

// Interrupts
#define RCC_ADDR			(AHB1_ADDR + 0x3800)
#define SYSCFG_ADDR			(APB2_ADDR + 0x3800)
#define EXTI_ADDR			(APB2_ADDR + 0x3C00)

// SPI
#define SPI1_ADDR			(APB2_ADDR + 0x3000)
#define SPI2_ADDR			(APB1_ADDR + 0x3800)
#define SPI3_ADDR			(APB1_ADDR + 0x3C00)
#define SPI4_ADDR			(APB2_ADDR + 0x3400)


/*
 * GPIOx Register Struct
 */

typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];				/*!< AFR[0] : GPIO alternate function low register, AF[1] : GPIO alternate function high register    	Address offset: 0x20-0x24 */
}	GPIO_RegDef_t;


/*
 * RCC Register Struct
 */

typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	  	 uint32_t RESERVED0;			// Offset 0x1C - 0x20 is reserved
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
		 uint32_t RESERVED1[2]; 		// Offset 0x28 - 0x30 is reserved
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	   	 uint32_t RESERVED2;			// Offset 0x3C - 0x40 is reserved
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
		 uint32_t RESERVED3[2]; 		// Offset 0x48 - 0x50 is reserved
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	__vo uint32_t RESERVED4; 			// Offset 0x5C - 0x60 is reserved
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
		 uint32_t RESERVED5[2]; 		// Offset 0x68 - 0x70 is reserved
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
		 uint32_t RESERVED6[2]; 		// Offset 0x78 - 0x80 is reserved
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	__vo uint32_t PLLSAICFGR;
	__vo uint32_t DCKCFGR;
	__vo uint32_t CKGATEENR;
	__vo uint32_t DCKCFGR2;

} RCC_RegDef_t;

/*
 * EXTI Register Struct
 */

typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;


} EXTI_RegDef_t;

/*
 * SYSCFG Register Struct
 */

typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
		 uint32_t RESERVED0[2];		// offset 0x18 - 0x20 is reserved
	__vo uint32_t CMPCR;			// offset 0x20
		 uint32_t RESERVED1[2];		// offset 0x24 - 0x2C is reserved
	__vo uint32_t CFGR;


} SYSCFG_RegDef_t;


/*
 * SPI Register Struct
 */

typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;

}SPI_RegDef_t;


/*
 * Peripheral Definitions
 */


#define GPIOA  							((GPIO_RegDef_t*)GPIOA_ADDR)
#define GPIOB  							((GPIO_RegDef_t*)GPIOB_ADDR)
#define GPIOC  							((GPIO_RegDef_t*)GPIOC_ADDR)
#define GPIOD  							((GPIO_RegDef_t*)GPIOD_ADDR)
#define GPIOE  							((GPIO_RegDef_t*)GPIOE_ADDR)
#define GPIOF  							((GPIO_RegDef_t*)GPIOF_ADDR)
#define GPIOG  							((GPIO_RegDef_t*)GPIOG_ADDR)
#define GPIOH  							((GPIO_RegDef_t*)GPIOH_ADDR)

#define RCC 							((RCC_RegDef_t*)RCC_ADDR)
#define EXTI							((EXTI_RegDef_t*)EXTI_ADDR)
#define SYSCFG							((SYSCFG_RegDef_t*)SYSCFG_ADDR)

#define SPI1							((SPI_RegDef_t*)SPI1_ADDR)
#define SPI2							((SPI_RegDef_t*)SPI2_ADDR)
#define SPI3							((SPI_RegDef_t*)SPI3_ADDR)
#define SPI4							((SPI_RegDef_t*)SPI4_ADDR)


/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()    				(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()					(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()					(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()					(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()					(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()					(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()					(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()					(RCC->AHB1ENR |= (1 << 7))

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()    				(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 7))

/*
 *  Macros to reset GPIOx peripherals
 *
 *  do {} while(0) lets us run 2 lines of code in a single macro
 *  We need to set and reset the bit in the AHB1RSTR register to reset GPIOx Port
 */
#define GPIOA_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)
#define GPIOI_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8)); }while(0)

#define GPIO_BASEADDR_TO_CODE(x)	  (	(x == GPIOA) ? 0 : \
										(x == GPIOB) ? 1 : \
										(x == GPIOC) ? 2 : \
										(x == GPIOD) ? 3 : \
										(x == GPIOE) ? 4 : \
										(x == GPIOF) ? 5 : \
										(x == GPIOG) ? 6 : 0 )


#define GPIO_PIN_NUM_0					0
#define GPIO_PIN_NUM_1					1
#define GPIO_PIN_NUM_2					2
#define GPIO_PIN_NUM_3					3
#define GPIO_PIN_NUM_4					4
#define GPIO_PIN_NUM_5					5
#define GPIO_PIN_NUM_6					6
#define GPIO_PIN_NUM_7					7
#define GPIO_PIN_NUM_8					8
#define GPIO_PIN_NUM_9					9
#define GPIO_PIN_NUM_10					10
#define GPIO_PIN_NUM_11					11
#define GPIO_PIN_NUM_12					12
#define GPIO_PIN_NUM_13					13
#define GPIO_PIN_NUM_14					14
#define GPIO_PIN_NUM_15					15


/*
 * SYSCFG Clock Enable
 */

#define SYSCFG_PCLK_EN() 				(RCC->APB2ENR |= (1 << 14))

/*
 * SPI Clock Enable and Disable
 */
#define SPI1_PCLK_EN()					(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()					(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()					(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()					(RCC->APB2ENR |= (1 << 13))


#define SPI1_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()					(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()					(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 13))


/*
 * Interrupt Request Positions from Table 38 of reference manual
 */

#define IRQ_EXTI0 						6
#define IRQ_EXTI1						7
#define IRQ_EXTI2 						8
#define IRQ_EXTI3 						9
#define IRQ_EXTI4 						10
#define IRQ_EXTI9_5 					23
#define IRQ_EXTI15_10					40

/*
 * NVIC ISERx and ICERx Register Addresses
 * ISER = Set Reg, ICER = Clear Reg
 * Register Addresses from ARM Cortex M4 Generic User Guide
 */

#define NVIC_ISER0						((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1						((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2						((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3						((__vo uint32_t*)0xE000E10C)

#define NVIC_ICER0						((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1						((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2						((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3						((__vo uint32_t*)0xE000E18C)

#define NVIC_IRQ_PRIO0					0
#define NVIC_IRQ_PRIO1					1
#define NVIC_IRQ_PRIO2					2
#define NVIC_IRQ_PRIO3					3
#define NVIC_IRQ_PRIO4					4
#define NVIC_IRQ_PRIO5					5
#define NVIC_IRQ_PRIO6					6
#define NVIC_IRQ_PRIO7					7
#define NVIC_IRQ_PRIO8					8
#define NVIC_IRQ_PRIO9					9
#define NVIC_IRQ_PRIO10					10
#define NVIC_IRQ_PRIO11					11
#define NVIC_IRQ_PRIO12					12
#define NVIC_IRQ_PRIO13					13
#define NVIC_IRQ_PRIO14					14
#define NVIC_IRQ_PRIO15					15

/*
 * Priority Interrupt Register Addresses
 */

// only defining the base addr because there are 59 priority registers
#define NVIC_PR_BASEADDR				((__vo uint32_t*)0xE000E400)
// last 4 bits of each register is not used
#define NUM_NOT_USED_PR_BITS			4



/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA     				 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     				 2
#define SPI_CR1_BR   					 3
#define SPI_CR1_SPE     				 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     				 8
#define SPI_CR1_SSM      				 9
#define SPI_CR1_RXONLY      		 	10
#define SPI_CR1_DFF     			 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   			 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE      			15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE				 	2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE					7


/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8


/*
*	SPI Flags
*/




#endif /* STM32F446XX_H_ */



