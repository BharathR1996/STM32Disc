/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Bharath R
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/*
 * 	EXERCISE 3: Configure HSE clock on microcontroller pin and measure the clock
 *
 * 	1. Select the desired clock for MCO1 signal (microcontroller output)
 * 	2. Output the MCO1 signal on the MCU pin
 * 	3. Check for which pin we can be configure as MCO1 in the pinout of STM32 (PA8)
 * 	4. Configure MCO1 and set prescaler to 4 so 16 MHz / 4
 * 	5. Enable clock for GPIO Port A
 * 	2. Configure GPIO A pin 8 for alternate function
 * 	3. Configure PA8 for MCO1 i.e. Alternate function 0
 *
 */


#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#define RCC_BASE_ADDR			0x40023800UL	// Base address of RCC
#define RCC_AHB1ENR_OFFSET		0x30UL			// AHB1 clock enable offset
#define RCC_CFGR_OFFSET			0x08UL			// Clock configuration register offset
#define GPIOA_BASE_ADDR			0x40020000UL	// Base address of GPIOA
#define GPIOA_AFRL_OFFSET		0x24UL			// GPIO alternate function register offset


// clock configuration register address
#define RCC_CFGR_ADDR		(RCC_CFGR_OFFSET + RCC_BASE_ADDR)
// APB2 clock enable register address
#define RCC_AHB1ENR_ADDR	(RCC_AHB1ENR_OFFSET + RCC_BASE_ADDR)
// GPIO alternate function register
#define GPIOA_AFRL_ADDR		(GPIOA_AFRL_OFFSET + GPIOA_BASE_ADDR)
// GPIO mode select register address is same as GPIO Port A base address
#define GPIOA_MODER			GPIOA_BASE_ADDR // GPIO port mode register
// RCC control register address is same as RCC base address
#define RCC_CR_ADDR			RCC_BASE_ADDR

int main(void)
{
	/* pointer to store the address of ADC1 control register 1
	 * Typecasting mandatory from unsigned long to uint32_t* */

	// Store address in pointer
	uint32_t *pRccCfgAddr = (uint32_t*)RCC_CFGR_ADDR;
	uint32_t *pRccCRAddr = (uint32_t *)RCC_CR_ADDR;
	uint32_t *pRccAPB1EnAddr = (uint32_t*)RCC_AHB1ENR_ADDR;
	uint32_t *pGPIOAModeRegAddr	= (uint32_t*)GPIOA_MODER;
	uint32_t *pGPIOAModePinAddr = (uint32_t*)GPIOA_AFRL_ADDR;

	// Enable HSE ON
	*pRccCRAddr |= (0x01<<16);

	// Check for HSERDY bit if set by hardware
	while(*pRccCRAddr & (0x01<<17));

	// Enable MCO1 for HSE
	*pRccCfgAddr |= (0x02<<21);	// Set bit 22 and clear 21 bit

	// Configure System clock as HSE
	*pRccCfgAddr |= (0x01<<0);	// Set bit 0 and clear bit 1

	// Set prescaler value to 4. Clock will be 8Mhz / 4
	*pRccCfgAddr |= (0x06<<24);

	// Enable clock for GPIO A
	*pRccAPB1EnAddr |= (0x01<<0);

	// Configure GPIO A pin 8 mode for alternate function
	*pGPIOAModeRegAddr &= ~(0x03<<16); // clear bits
	*pGPIOAModeRegAddr |= (0x02<<16);  // set bits

	// Configure PA8 for MCO1 i.e. Alternate function 0
	*pGPIOAModePinAddr &= ~(0x0F<<4);

	for(;;);
}
