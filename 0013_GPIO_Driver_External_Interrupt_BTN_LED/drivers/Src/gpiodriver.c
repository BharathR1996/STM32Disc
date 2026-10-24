/*
 * gpiodriver.c
 *
 *  Created on: 30-Sept-2026
 *      Author: bharathr
 */

#include "gpiodriver.h"

/* ************************************************
 *
 * Common Functions
 *
 * *************************************************/
void resetGPIOPeripheral(uint8_t pos)
{
	GPIO_PERIPHERAL_SET(pos);
	GPIO_PERIPHERAL_RESET(pos);
}

/* **********************************************************************
 *  Func		:	GPIO_CLKControl
 *
 *  brief		:	This function is responsible for enable/disable
 *  				clock for GPIO Peripheral
 *
 *  param[1] 	:	base address of the GPIO port register
 *  param[2] 	:	Enable or Disable value
 *
 *  return		:	None on success
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_CLKControl(GPIO_RegDef_t *pGPIOBaseAddr, bool EnDis)
{
	if (EnDis)
	{
	    if (pGPIOBaseAddr == GPIOA) {
	        GPIOA_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOB) {
	        GPIOB_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOC) {
	        GPIOC_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOD) {
	        GPIOD_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOE) {
	        GPIOE_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOF) {
	        GPIOF_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOG) {
	        GPIOG_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOH) {
	        GPIOH_CLK_EN();
	    } else if (pGPIOBaseAddr == GPIOI) {
	        GPIOI_CLK_EN();
	    }
	} else {
	    if (pGPIOBaseAddr == GPIOA) {
	        GPIOA_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOB) {
	        GPIOB_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOC) {
	        GPIOC_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOD) {
	        GPIOD_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOE) {
	        GPIOE_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOF) {
	        GPIOF_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOG) {
	        GPIOG_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOH) {
	        GPIOH_CLK_DIS();
	    } else if (pGPIOBaseAddr == GPIOI) {
	        GPIOI_CLK_DIS();
	    }
	}

}

/* **********************************************************************
 *  Func		:	GPIO_Init
 *
 *  brief		:	This function is responsible for initialization of
 *  				GPIO Peripheral
 *
 *  param[1] 	:	base address of the GPIO Peripheral and pin configuration
 *  				are passed as part of the GPIO handler
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_Init(GPIO_Handler_t *pGPIOHandle)
{
	// Configure port mode register
	// 2 * pin number because 2 bits represent one GPIO Pin
	// Clear the bits before setting
	if(pGPIOHandle->GPIOPinConfig.pinMode <= GPIO_MODE_ANALOG)
	{
		pGPIOHandle->pGPIOBaseAddr->MODER |= (pGPIOHandle->GPIOPinConfig.pinMode << (2 * pGPIOHandle->GPIOPinConfig.pinNumber));
	}
	else
	{
		if(pGPIOHandle->GPIOPinConfig.pinMode == GPIO_MODE_RET)
		{
			// Enable rising edge and disable falling edge
			EXTI->RTSR |= (1 << pGPIOHandle->GPIOPinConfig.pinNumber);
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIOPinConfig.pinNumber);

		}
		else if (pGPIOHandle->GPIOPinConfig.pinMode == GPIO_MODE_FET)
		{
			// Enable falling edge and disable rising edge
			EXTI->FTSR |= (1 << pGPIOHandle->GPIOPinConfig.pinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIOPinConfig.pinNumber);
		}
		else
		{
			// Enable both rising and falling edge
			EXTI->RTSR |= (1 << pGPIOHandle->GPIOPinConfig.pinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIOPinConfig.pinNumber);
		}

		// Configure the GPIO port selection for INTR
		uint8_t quo = pGPIOHandle->GPIOPinConfig.pinNumber / 4;		// pin number /4 because 4 EXTI Control register available
		uint8_t rem = pGPIOHandle->GPIOPinConfig.pinNumber % 4;		// pin number % 4
		uint8_t portSelect = GPIO_BASE_ADDR_TO_PORT(pGPIOHandle->pGPIOBaseAddr);

		SYSCFG->EXTICR[quo] =  portSelect << (rem * 4);

		// Enable EXTI interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIOPinConfig.pinNumber);
	}
	// Configure output type register
	// 1 bit represent one GPIO Pin
	pGPIOHandle->pGPIOBaseAddr->OTYPER |= (pGPIOHandle->GPIOPinConfig.pinOutputType << (pGPIOHandle->GPIOPinConfig.pinNumber));

	// Configure port output speed register
	pGPIOHandle->pGPIOBaseAddr->OSPEEDR |= (pGPIOHandle->GPIOPinConfig.pinSpeed << (2 * pGPIOHandle->GPIOPinConfig.pinNumber));

	// Configure port pull-up / pull-down register
//	if(pGPIOHandle->GPIOPinConfig.pinOutputType != GPIO_OUTPUT_TYPE_OPENDRAIN && pGPIOHandle->GPIOPinConfig.pinPullUpPullDown != GPIO_NO_PULL_UP_DOWN)
	{
		pGPIOHandle->pGPIOBaseAddr->PUPDR |= (pGPIOHandle->GPIOPinConfig.pinPullUpPullDown << (2 * pGPIOHandle->GPIOPinConfig.pinNumber));
	}

	// Configure Alternate Functionality
	if(pGPIOHandle->pGPIOBaseAddr->MODER == GPIO_MODE_ALTFUN)
	{
		// 9 / 8 = 1 ---> AFR[1];
		// 6 / 8 = 0 ---> AFR[0];
		uint8_t regSel = pGPIOHandle->GPIOPinConfig.pinNumber / 8;
		// 9 % 8 = 1 ---> <<(4 * 1);
		// 6 % 8 = 6 ---> <<(4 * 6);
		uint8_t pinPos = pGPIOHandle->GPIOPinConfig.pinNumber % 8;

		pGPIOHandle->pGPIOBaseAddr->AFR[regSel] |= (pGPIOHandle->GPIOPinConfig.pinAlternateFuncMode << (4 * pinPos));
	}
}

/* **********************************************************************
 *  Func		:	GPIO_DeInit
 *
 *  brief		:	This function is responsible for de-initialization of
 *  				GPIO Peripheral
 *
 *  param[1] 	:	base address of the GPIO port register
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOBaseAddr)
{
	// Identify how to get the bit pos from base address
	// for now hardcoded
    if (pGPIOBaseAddr == GPIOA) {
    	resetGPIOPeripheral(0);
    } else if (pGPIOBaseAddr == GPIOB) {
    	resetGPIOPeripheral(1);
    } else if (pGPIOBaseAddr == GPIOC) {
    	resetGPIOPeripheral(2);
    } else if (pGPIOBaseAddr == GPIOD) {
    	resetGPIOPeripheral(3);
    } else if (pGPIOBaseAddr == GPIOE) {
        resetGPIOPeripheral(4);
    } else if (pGPIOBaseAddr == GPIOF) {
    	resetGPIOPeripheral(5);
    } else if (pGPIOBaseAddr == GPIOG) {
    	resetGPIOPeripheral(6);
    } else if (pGPIOBaseAddr == GPIOH) {
    	resetGPIOPeripheral(7);
    } else if (pGPIOBaseAddr == GPIOI) {
    	resetGPIOPeripheral(8);
    }
}

/* **********************************************************************
 *  Func		:	GPIO_ReadPortPin
 *
 *  brief		:	This function is responsible for reading a particular
 *  				pin value of the GPIO Peripheral
 *
 *  param[1] 	:	base address of the GPIO port register
 *  param[2] 	:	pin number to be read
 *
 *  return		:	value of the pin
 *
 *  note		: 	None
 ************************************************************************ */

uint8_t GPIO_ReadPortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOBaseAddr->IDR >> pinNumber) & 0x01);
	return value;
}

/* **********************************************************************
 *  Func		:	GPIO_ReadPort
 *
 *  brief		:	This function is responsible for reading the entire
 *  				GPIO peripheral register
 *
 *  param[1] 	:	base address of the GPIO port register
 *
 *  return		:	value of the entire register
 *
 *  note		: 	None
 ************************************************************************ */

uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOBaseAddr)
{
	uint16_t value;
	value = (uint16_t)((pGPIOBaseAddr->IDR) & 0xFFFF);
	return value;
}

/* **********************************************************************
 *  Func		:	GPIO_WritePortPin
 *
 *  brief		:	This function is responsible for writing value on a
 *  				particular pin of a GPIO port register
 *
 *  param[1] 	:	base address of the GPIO port register
 *  param[2] 	:	pin number to be modified
 *  param[3]	:	value to be written
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_WritePortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber, bool value)
{
	if(value != GPIO_SET_PIN)
	{
		pGPIOBaseAddr->ODR &= ~(0x01 << pinNumber);
	}
	else
	{
		pGPIOBaseAddr->ODR |= (0x01 << pinNumber);
	}
}

/* **********************************************************************
 *  Func		:	GPIO_WritePort
 *
 *  brief		:	This function is responsible for writing value on an
 *  				entire GPIO port register
 *
 *  param[1] 	:	base address of the GPIO port register
 *  param[2] 	:	value to be written
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_WritePort(GPIO_RegDef_t *pGPIOBaseAddr, uint16_t value)
{
	pGPIOBaseAddr->ODR = (value & 0xFFFF);
}

/* **********************************************************************
 *  Func		:	GPIO_TogglePin
 *
 *  brief		:	This function is responsible for Toggling a pin
 *  				of a particular GPIO port register
 *
 *  param[1] 	:	base address of the GPIO port register
 *  param[2] 	:	pin number to be toggled
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber)
{
	pGPIOBaseAddr->ODR ^= (0x01 << pinNumber);
}

/* **********************************************************************
 *  Func		:	GPIO_IRQInterruptConfig
 *
 *  brief		:	This function is responsible for enable/disable
 *  				interrupt for a particular pin of GPIO Peripheral
 *
 *  param[1] 	:	Interrupt IRQ number
 *  param[2]	:	enable or disable
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, bool EnDis)
{
	if(EnDis == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber <= 63)
		{
			NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if (IRQNumber > 63 && IRQNumber <= 96)
		{
			NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
		else
		{
			// DO NOTHING
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber <= 63)
		{
			NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if (IRQNumber > 63 && IRQNumber <= 96)
		{
			NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}

}

/* **********************************************************************
 *  Func		:	GPIO_IRQPriority
 *
 *  brief		:	This function is responsible for configuring the
 *  				interrupt priority of the GPIO peripheral
 *
 *  param[1] 	:	Interrupt IRQ number
 *  param[2]	:	IRQ Priority
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_IRQPriority(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR  + (iprx * 4)) |= (IRQPriority << shift);
}

/* **********************************************************************
 *  Func		:	GPIO_Handler
 *
 *  brief		:	This function is GPIO interrupt handler
 *
 *  param[1] 	:	pin number
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_Handler(uint8_t pinNumber)
{
	// clear the EXTI PR register corresponding to the pin number
	if(EXTI->PR & (1 << pinNumber))
	{
		EXTI->PR |= (1 << pinNumber);
	}

}
