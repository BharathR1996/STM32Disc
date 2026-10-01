/*
 * gpiodriver.c
 *
 *  Created on: 30-Sept-2026
 *      Author: bharathr
 */

#include "gpiodriver.h"


/* **********************************************************************
 *  Func		:	GPIO_CLKControl
 *
 *  brief		:	This function is responsible for enable/disable
 *  				clock for GPIO Peripheral
 *
 *  param[1] 	:	base address of the GPIO port register
 *  param[2] 	:	Enable or Disable value
 *
 *  return		:	ERR_OK on success
 *
 *  note		: 	None
 ************************************************************************ */

ut_Status GPIO_CLKControl(GPIO_RegDef_t *pGPIOBaseAddr, bool EnDis)
{

	return ERR_OK;
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
 *  return		:	ERR_OK on success
 *
 *  note		: 	None
 ************************************************************************ */

ut_Status GPIO_Init(GPIO_Handler_t *pGPIOHandle)
{

	return ERR_OK;
}

/* **********************************************************************
 *  Func		:	GPIO_DeInit
 *
 *  brief		:	This function is responsible for de-initialization of
 *  				GPIO Peripheral
 *
 *  param[1] 	:	base address of the GPIO port register
 *
 *  return		:	ERR_OK on success
 *
 *  note		: 	None
 ************************************************************************ */

ut_Status GPIO_DeInit(GPIO_RegDef_t *pGPIOBaseAddr)
{

	return ERR_OK;
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

	return 0;
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

	return ERR_OK;
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
 *  return		:	ERR_OK on successful execution of API
 *
 *  note		: 	None
 ************************************************************************ */

ut_Status GPIO_WritePortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber, bool value)
{

	return ERR_OK;
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
 *  return		:	ERR_OK on successful execution of API
 *
 *  note		: 	None
 ************************************************************************ */

ut_Status GPIO_WritePort(GPIO_RegDef_t *pGPIOBaseAddr, uint16_t value)
{

	return ERR_OK;
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
 *  return		:	ERR_OK on successful execution of API
 *
 *  note		: 	None
 ************************************************************************ */

ut_Status GPIO_TogglePin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber)
{

	return ERR_OK;
}

/* **********************************************************************
 *  Func		:	GPIO_INTRConfig
 *
 *  brief		:	This function is responsible for enable/disable
 *  				interrupt for a particular pin of GPIO Peripheral
 *
 *  param[1] 	:	pin number
 *  param[2] 	:	interrupt priority
 *  param[3]	:	enable or disable
 *
 *  return		:	ERR_OK on successful execution of API
 *
 *  note		: 	None
 ************************************************************************ */

ut_Status GPIO_INTRConfig(uint8_t pinNumber, uint8_t IRQPriority, bool EnDis)
{

	return ERR_OK;
}

/* **********************************************************************
 *  Func		:	GPIO_INTRHandler
 *
 *  brief		:	This function is GPIO interrupt handler
 *
 *  param[1] 	:	pin number
 *
 *  return		:	None
 *
 *  note		: 	None
 ************************************************************************ */

void GPIO_INTRHandler(uint8_t pinNumber)
{

}
