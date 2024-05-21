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

#define GPIOA_ADDR 			AHB1_ADDR
#define GPIOB_ADDR 			(AHB1_ADDR + 0x0400)
#define GPIOC_ADDR			(AHB1_ADDR + 0x0800)
#define GPIOD_ADDR			(AHB1_ADDR + 0x0C00)
#define GPIOE_ADDR 			(AHB1_ADDR + 0x1000)
#define GPIOF_ADDR 			(AHB1_ADDR + 0x1400)
#define GPIOG_ADDR 			(AHB1_ADDR + 0x1800)
#define GPIOH_ADDR 			(AHB1_ADDR + 0x1C00)
#define RCC_ADDR			(AHB1_ADDR + 0x3800)
#define SYSCFG_ADDR			(APB2_ADDR + 0x3800)
#define EXTI_ADDR			(APB2_ADDR + 0x3C00)


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
										(x == GPIOB) ? 2 : \
										(x == GPIOB) ? 3 : \
										(x == GPIOB) ? 4 : \
										(x == GPIOB) ? 5 : \
										(x == GPIOB) ? 6 : \
										(x == GPIOB) ? 7 : 0)


#define SYSCFG_PCLK_EN() 				(RCC->APB2ENR |= (1 << 14))



#endif /* STM32F446XX_H_ */
