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
 * 	EXERCISE 2: Set a bit in a GPIOD register
 *
 * 	1. Check to which bus is GPIOD is connected in STM32 reference manual
 * 	2. Configure the respective RCC register to enable the clock for the module
 * 	3. Set the bit of a particular register
 *
 */


#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
// Always consider address as an unsigned integer

#define RCC_BASE_ADDR				0x40023800UL	// Base address of RCC
#define RCC_AHB1ENR_OFFSET			0x30UL			// AHB1 clock enable offset
// AHB1 clock enable register address
#define RCC_AHB1ENR_ADDR			(RCC_AHB1ENR_OFFSET + RCC_BASE_ADDR)

#define GPIOD_BASE_ADDR				0x40020C00UL	// Base address of GPIOD
#define GPIOD_ODR_OFFSET			0x14UL			// GPIOD out register offset
// GPIO Port D output register address
#define GPIOD_ODR_ADDR				(GPIOD_ODR_OFFSET + GPIOD_BASE_ADDR)

int main(void)
{

/* pointer to store the address of GPIOD output register and typecast mandatory
 * from unsigned long to uint32_t* */

	// Assign the Clock Enable address of AHB1 to pointer
	uint32_t *pRccAHB1EnAddr = (uint32_t *)RCC_AHB1ENR_ADDR;

	// Assign the GPIOD output register address to pointer
	uint32_t *pGpiodOdrAddr = (uint32_t *)GPIOD_ODR_ADDR;

	// Set bit 3 to enable clock for GPIOD
	*pRccAHB1EnAddr |= (1<<3);

	// Set bit 2 to get output on GPIOD pin 2
	*pGpiodOdrAddr |= (1<<2);

    /* Loop forever */
	for(;;);
}
