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
 * 	EXERCISE 1: Set a bit in a peripheral register
 *
 * 	Consider ADC1 in this test
 *
 * 	1. Check to which bus is ADC 1 connected in STM32 reference manual
 * 	2. Configure the respective RCC register to enable the clock for the module
 * 	3. Set the bit of a particular register
 *
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define RCC_BASE_ADDR			0x40023800UL	// Base address of RCC
#define RCC_APB2ENR_OFFSET		0x44UL			// APB2 clock enable offset
// APB2 clock enable register address
#define RCC_APB2ENR_ADDR		(RCC_APB2ENR_OFFSET + RCC_BASE_ADDR)

// Always consider address as an unsigned integer
#define ADC_BASE_ADDR			0x40012000UL	// Base address of ADC
#define ADC_CR1_OFFSET			0x04UL			// ADC control register 1 offset
// ADC control register 1 address
#define ADC_CR1_ADDR			(ADC_CR1_OFFSET + ADC_BASE_ADDR)

int main(void)
{
/* pointer to store the address of ADC1 control register 1
 * Typecasting mandatory from unsigned long to uint32_t* */

	// Set the Clock for ADC1 module (APB2)
	uint32_t* pRccAPB2EnAddr = (uint32_t*)RCC_APB2ENR_ADDR;

	// Set bit 8 to enable clock for ADC1
	*pRccAPB2EnAddr |= (1<<8);

	uint32_t* pAdcCtlReg1Addr = (uint32_t*)ADC_CR1_ADDR;

	// Set bit 8 in control register
	*pAdcCtlReg1Addr |= (1<<8);

	for(;;);
}
