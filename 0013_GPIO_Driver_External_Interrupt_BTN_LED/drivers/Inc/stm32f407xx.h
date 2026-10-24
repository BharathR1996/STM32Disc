/*
 * stm32f407xx.h
 *
 *  Created on: 29-Sept-2026
 *      Author: bharathr
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stdint.h>
#include<stdbool.h>

/* ************************************* PROCESSOR SPECIFIC DETAILS ************************************* */

/*
 *  ARM CORTEX Mx PROCESSOR NVIC ISERx REGISTER ADDRESSES
 */

#define NVIC_ISER0							(*(volatile uint32_t *) 0xE000E100)
#define NVIC_ISER1							(*(volatile uint32_t *) 0xE000E104)
#define NVIC_ISER2							(*(volatile uint32_t *) 0xE000E108)


#define NVIC_ICER0							(*(volatile uint32_t *) 0xE000E180)
#define NVIC_ICER1							(*(volatile uint32_t *) 0xE000E184)
#define NVIC_ICER2							(*(volatile uint32_t *) 0xE000E188)


#define NVIC_PR_BASE_ADDR					((volatile uint32_t *) 0xE000E400)


#define NO_PR_BITS_IMPLEMENTED				4

/* *************** MEMORY BASE ADDRESS **********************	*/

#define DRV_FLASH_BASEADDR					0x08000000U
#define DRV_SRAM1_BASEADDR					0x20000000U
#define DRV_SRAM2_BASEADDR					0x2001C000U
#define DRV_ROM_BASEADDR					0x1FFF0000U

#define SRAM 								DRV_SRAM1_BASEADDR

/* *************** PERIPHERAL BUS BASE ADDRESS *************** 	*/

#define PERIPH_BASE							0x40000000U
#define DRV_APB1_BASEADDR					PERIPH_BASE
#define DRV_APB2_BASEADDR					0x40010000U
#define DRV_AHB1_BASEADDR					0x40020000U
#define DRV_AHB2_BASEADDR					0x50000000U

/* ************************************************
 * AHB1 PERIPHERALS AHB1_BASEADDR + Offset
 * ************************************************ */


/* ************ GPIO PORTS BASE ADDRESS	****************		*/

#define DRV_GPIOA_BASEADDR					(DRV_AHB1_BASEADDR + 0x00000000U)
#define DRV_GPIOB_BASEADDR					(DRV_AHB1_BASEADDR + 0x00000400U)
#define DRV_GPIOC_BASEADDR					(DRV_AHB1_BASEADDR + 0x00000800U)
#define DRV_GPIOD_BASEADDR					(DRV_AHB1_BASEADDR + 0x00000C00U)
#define DRV_GPIOE_BASEADDR					(DRV_AHB1_BASEADDR + 0x00001000U)
#define DRV_GPIOF_BASEADDR					(DRV_AHB1_BASEADDR + 0x00001400U)
#define DRV_GPIOG_BASEADDR					(DRV_AHB1_BASEADDR + 0x00001800U)
#define DRV_GPIOH_BASEADDR					(DRV_AHB1_BASEADDR + 0x00001C00U)
#define DRV_GPIOI_BASEADDR					(DRV_AHB1_BASEADDR + 0x00002000U)

/* ************ RCC BASE ADDRESS ****************				*/

#define DRV_RCC_BASEADDR					(DRV_AHB1_BASEADDR + 0x00003800U)

/* ************************************************
 * APB1 PERIPHERALS APB1_BASEADDR + Offset ******
 * ************************************************ */

/*	*********** I2C PERIPHERALS	**********************			*/

#define DRV_I2C1_BASEADDR					(DRV_APB1_BASEADDR + 0x00005400U)
#define DRV_I2C2_BASEADDR					(DRV_APB1_BASEADDR + 0x00005800U)
#define DRV_I2C3_BASEADDR					(DRV_APB1_BASEADDR + 0x00005C00U)

/* *********** UART PERIPHERALS **********************			*/

#define DRV_UART4_BASEADDR					(DRV_APB1_BASEADDR + 0x00004C00U)
#define DRV_UART5_BASEADDR					(DRV_APB1_BASEADDR + 0x00005000U)

/* *********** USART PERIPHERALS **********************			*/

#define DRV_USART2_BASEADDR					(DRV_APB1_BASEADDR + 0x00004400U)
#define DRV_USART3_BASEADDR					(DRV_APB1_BASEADDR + 0x00004800U)

/*				SPI PERIPHERALS	**********************			*/

#define DRV_SPI2_BASEADDR					(DRV_APB1_BASEADDR + 0x00003800U)
#define DRV_SPI3_BASEADDR					(DRV_APB1_BASEADDR + 0x00003C00U)

/* ************************************************
 * 				APB2 PERIPHERALS APB2_BASEADDR + Offset
 * ************************************************ */

/* *********** USART PERIPHERALS **********************			*/

#define DRV_USART1_BASEADDR					(DRV_APB2_BASEADDR + 0x00001000U)
#define DRV_USART6_BASEADDR					(DRV_APB2_BASEADDR + 0x00001400U)

/* *********** SPI PERIPHERAL **********************			*/

#define DRV_SPI1_BASEADDR					(DRV_APB2_BASEADDR + 0x00003000U)

/* *********** SYSCFG PERIPHERAL **********************			*/

#define DRV_SYSCFG_BASEADDR					(DRV_APB2_BASEADDR + 0x00003800U)

/* *********** EXT INTERRUPT PERIPHERAL	**********************	*/

#define DRV_EXTI_BASEADDR					(DRV_APB2_BASEADDR + 0x00003C00U)


/* ************************************************
 *
 * PERIPHERAL REGISTER STRUCTURES
 *
 * *************************************************/

typedef struct {
	volatile uint32_t MODER;			/* ***** GPIO port mode register, 									offset = 0x00 ***** */
	volatile uint32_t OTYPER;			/* ***** GPIO port output type register, 							offset = 0x04 ***** */
	volatile uint32_t OSPEEDR;			/* ***** GPIO port output speed register, 							offset = 0x08 ***** */
	volatile uint32_t PUPDR;			/* ***** GPIO port Pull-up/down register, 							offset = 0x0C ***** */
	volatile uint32_t IDR;				/* ***** GPIO port input data register, 							offset = 0x10 ***** */
	volatile uint32_t ODR;				/* ***** GPIO port output data register, 							offset = 0x14 ***** */
	volatile uint32_t BSRR;				/* ***** GPIO port bit set/reset register, 							offset = 0x18 ***** */
	volatile uint32_t LCKR;				/* ***** GPIO port config lock register, 							offset = 0x1C ***** */
	volatile uint32_t AFR[2];			/* ***** AFR[0]: GPIO port Alternate Low register, 					offset = 0x20 ***** */
	 	 	 	 	 	 	 			/* ***** AFR[1]: GPIO port Alternate High register, 				offset = 0x40 ***** */
}GPIO_RegDef_t;

typedef struct {
	volatile uint32_t RCC_CR;			/* ***** RCC clock control register, 								offset = 0x00 ***** */
	volatile uint32_t RCC_PLLCFGR;		/* ***** RCC PLL config register, 									offset = 0x04 ***** */
	volatile uint32_t RCC_CFGR;			/* ***** RCC clock config register, 								offset = 0x08 ***** */
	volatile uint32_t RCC_CIR;			/* ***** RCC clock interrupt register, 								offset = 0x0C ***** */
	volatile uint32_t RCC_AHB1RSTR;		/* RCC AHB1 periph reset register, 									offset = 0x10 ***** */
	volatile uint32_t RCC_AHB2RSTR;		/* RCC AHB2 periph reset register, 									offset = 0x14 ***** */
	volatile uint32_t RCC_AHB3RSTR;		/* RCC AHB3 periph reset register, 									offset = 0x18 ***** */
	volatile uint32_t reserved0;		/* ***** Reserved 													offset = 0x1C ***** */
	volatile uint32_t RCC_APB1RSTR;		/* RCC APB1 periph reset register, 									offset = 0x20 ***** */
	volatile uint32_t RCC_APB2RSTR;   	/* RCC APB2 periph reset register, 									offset = 0x24 ***** */
	volatile uint32_t reserved1;		/* ***** Reserved 													offset = 0x28 ***** */
	volatile uint32_t reserved2;		/* ***** Reserved 													offset = 0x2C ***** */
	volatile uint32_t RCC_AHB1ENR;		/* RCC AHB1 clock enable register, 									offset = 0x30 ***** */
	volatile uint32_t RCC_AHB2ENR;  	/* RCC AHB2 clock enable register, 									offset = 0x34 ***** */
	volatile uint32_t RCC_AHB3ENR;   	/* RCC AHB3 clock enable register, 									offset = 0x38 ***** */
	volatile uint32_t reserved3;		/* ***** Reserved 													offset = 0x3C ***** */
	volatile uint32_t RCC_APB1ENR;		/* RCC_APBxENR[0]: RCC APB1 clock enable register, 					offset = 0x40 ***** */
	volatile uint32_t RCC_APB2ENR;		/* RCC_APBxENR[1]: RCC APB2 clock enable register, 					offset = 0x44 ***** */
	volatile uint32_t reserved4;		/* ***** Reserved 													offset = 0x48 ***** */
	volatile uint32_t reserved5;		/* ***** Reserved 													offset = 0x4C ***** */
	volatile uint32_t AHB1LPENR;		/* RCC AHB1 low power clock enable register, 						offset = 0x50 ***** */
	volatile uint32_t AHB2LPENR;		/* RCC AHB2 low power clock enable register, 						offset = 0x54 ***** */
	volatile uint32_t AHB3LPENR;		/* RCC AHB3 low power clock enable register, 						offset = 0x58 ***** */
	volatile uint32_t reserved6;		/* ***** Reserved 													offset = 0x5C ***** */
	volatile uint32_t APB1LPENR;		/* RCC APB1 low power clock enable register, 						offset = 0x60 ***** */
	volatile uint32_t APB2LPENR;		/* RCC APB1 low power clock enable register, 						offset = 0x64 ***** */
	volatile uint32_t reserved7;		/* ***** Reserved 													offset = 0x68 ***** */
	volatile uint32_t reserved8;		/* ***** Reserved 													offset = 0x6C ***** */
	volatile uint32_t RCC_BCDR;			/* ***** RCC backup domain control register,						offset = 0x70 ***** */
	volatile uint32_t RCC_CSR;			/* ***** RCC clock control & status register,						offset = 0x74 ***** */
	volatile uint32_t reserved9;		/* ***** Reserved 													offset = 0x78 ***** */
	volatile uint32_t reserved10;		/* ***** Reserved 													offset = 0x7C ***** */
	volatile uint32_t RCC_SSCGR;		/* ***** RCC spread spectrum clock generation register,				offset = 0x80 ***** */
	volatile uint32_t RCC_PLLI2SCFGR;	/* ***** RCC PLLI2S configuration register,							offset = 0x84 ***** */

}RCC_RegDef_t;

typedef struct {
	volatile uint32_t IMR;				/* ***** EXTI Interrupt Mask Register,								offset = 0x00 ***** */
	volatile uint32_t EMR;				/* ***** EXTI Event Mask Register,									offset = 0x04 ***** */
	volatile uint32_t RTSR;				/* ***** EXTI Rising Edge Selection Register,						offset = 0x08 ***** */
	volatile uint32_t FTSR;				/* ***** EXTI Falling Edge Selection Register,						offset = 0x0C ***** */
	volatile uint32_t SWIER;			/* ***** EXTI Software Interrupt Event Register,					offset = 0x10 ***** */
	volatile uint32_t PR;				/* ***** EXTI Pending Register,										offset = 0x14 ***** */
}EXTI_RegDef_t;

typedef struct {
	volatile uint32_t MEMRMP;			/* ***** SYSCFG Memory remap register,								offset = 0x00 ***** */
	volatile uint32_t PMC;				/* ***** SYSCFG Peripheral mode config register,					offset = 0x04 ***** */
	volatile uint32_t EXTICR[4];		/* ***** SYSCFG External interrupt config1 register,				offset = 0x08 ***** */
										/* ***** SYSCFG External interrupt config2 register,				offset = 0x0C ***** */
										/* ***** SYSCFG External interrupt config3 register,				offset = 0x10 ***** */
										/* ***** SYSCFG External interrupt config4 register,				offset = 0x14 ***** */
	volatile uint32_t reserved[2];		/* ***** Reserved 													offset = 0x18 ***** */
										/* ***** Reserved 													offset = 0x1C ***** */
	volatile uint32_t CMPCR;			/* ***** SYSCFG compensation cell control register,					offset = 0x20 ***** */
}SYSCFG_RegDef_t;


/* ************************************************
 *
 * PERIPHERAL DEFINITIONS
 *
 * ************************************************ */

/* ************************************************
 * GPIO DEFINITIONS
 * *********************************************** */

#define GPIOA								((GPIO_RegDef_t *)DRV_GPIOA_BASEADDR)
#define GPIOB								((GPIO_RegDef_t *)DRV_GPIOB_BASEADDR)
#define GPIOC								((GPIO_RegDef_t *)DRV_GPIOC_BASEADDR)
#define GPIOD								((GPIO_RegDef_t *)DRV_GPIOD_BASEADDR)
#define GPIOE								((GPIO_RegDef_t *)DRV_GPIOE_BASEADDR)
#define GPIOF								((GPIO_RegDef_t *)DRV_GPIOF_BASEADDR)
#define GPIOG								((GPIO_RegDef_t *)DRV_GPIOG_BASEADDR)
#define GPIOH								((GPIO_RegDef_t *)DRV_GPIOH_BASEADDR)
#define GPIOI								((GPIO_RegDef_t *)DRV_GPIOI_BASEADDR)

/* ************************************************
 * Reset and clock control (RCC) DEFINITIONS
 * *********************************************** */

#define RCC									((RCC_RegDef_t *)DRV_RCC_BASEADDR)

/* ************************************************
 * Reset and clock control (RCC) DEFINITIONS
 * *********************************************** */

#define EXTI								((EXTI_RegDef_t *)DRV_EXTI_BASEADDR)

/* ************************************************
 * System configuration controller (SYSCFG) DEFINITIONS
 * *********************************************** */

#define SYSCFG								((SYSCFG_RegDef_t *)DRV_SYSCFG_BASEADDR)

/* ************************************************
 * GPIO CLOCK ENABLE DEFINITIONS
 * *********************************************** */

#define GPIOA_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 0))
#define GPIOB_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 1))
#define GPIOC_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 2))
#define GPIOD_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 3))
#define GPIOE_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 4))
#define GPIOF_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 5))
#define GPIOG_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 6))
#define GPIOH_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 7))
#define GPIOI_CLK_EN()						(RCC->RCC_AHB1ENR |= (1 << 8))

/* ************************************************
 * SPI CLOCK ENABLE DEFINITIONS
 * *********************************************** */

/* ************************************************
 * I2C CLOCK ENABLE DEFINITIONS
 * *********************************************** */

/* ************************************************
 * UART CLOCK ENABLE DEFINITIONS
 * *********************************************** */

/* ************************************************
 * USART CLOCK ENABLE DEFINITIONS
 * *********************************************** */

/* ************************************************
 * SYSCFG CLOCK ENABLE DEFINITIONS
 * *********************************************** */

#define SYSCFG_CLK_EN()						(RCC->RCC_APB2ENR |= (1 << 14))


/* ************************************************
 * GPIO CLOCK DISABLE DEFINITIONS
 * *********************************************** */

#define GPIOA_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 0))
#define GPIOB_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 1))
#define GPIOC_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 2))
#define GPIOD_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 3))
#define GPIOE_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 4))
#define GPIOF_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 5))
#define GPIOG_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 6))
#define GPIOH_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 7))
#define GPIOI_CLK_DIS()						(RCC->RCC_AHB1ENR &= ~(1 << 8))

/* ************************************************
 * GPIO MODULE RESET DEFINITIONS
 * *********************************************** */
#define GPIO_PERIPHERAL_RESET(pos)				(RCC->RCC_APB1RSTR &= ~(1 << pos))
#define GPIO_PERIPHERAL_SET(pos)				(RCC->RCC_APB1RSTR |= (1 << pos))

/* ************************************************
 * GPIO BASE ADDRESS TO PORT SELECTION VALUE
 * *********************************************** */
#define GPIO_BASE_ADDR_TO_PORT(baseAddr)		(((baseAddr) == GPIOA)? 0 :\
												((baseAddr) == GPIOB) ? 1 :\
												((baseAddr) == GPIOC) ? 2 :\
												((baseAddr) == GPIOD) ? 3 :\
												((baseAddr) == GPIOE) ? 4 :\
												((baseAddr) == GPIOF) ? 5 :\
												((baseAddr) == GPIOG) ? 6 :\
												((baseAddr) == GPIOH) ? 7 :\
												((baseAddr) == GPIOI) ? 8 : 0)


/* ************************************************
 * SYSCFG CLOCK DISABLE DEFINITIONS
 * *********************************************** */

#define SYSCFG_CLK_DIS()						(RCC->RCC_APB2ENR &= ~(1 << 14))


/* ************************************************
 *  DEFINITIONS
 * *********************************************** */

#define ENABLE 								1
#define DISABLE								0

#define SET									ENABLE
#define RESET								DISABLE

#define GPIO_SET_PIN						SET
#define GPIO_CLEAR_PIN						RESET

/* ************************************************
 *  IRQ NO for EXT INTERRUPT
 * *********************************************** */
#define IRQ_NO_EXTI0						6
#define IRQ_NO_EXTI1						7
#define IRQ_NO_EXTI2						8
#define IRQ_NO_EXTI3						9
#define IRQ_NO_EXTI4						19
#define IRQ_NO_EXTI9_5						23
#define IRQ_NO_EXTI15_10					40

/* ************************************************
 *  RETURN STATUS STRUCTURE
 * *********************************************** */

#endif /* INC_STM32F407XX_H_ */
