/*
 * stm32f407xx_gpiodriver.h
 *
 *  Created on: 30-Sept-2026
 *      Author: bharathr
 */

#ifndef INC_GPIODRIVER_H_
#define INC_GPIODRIVER_H_

#include "stm32f407xx.h"

/* ************************************************
 *
 * CONFIGURATION STRUCTURES
 *
 * *************************************************/

typedef struct {
	uint8_t pinNumber;
	uint8_t pinMode;
	uint8_t pinSpeed;
	uint8_t pinOutputType;
	uint8_t pinPullUpPullDown;
	uint8_t pinAlternateFuncMode;
}GPIO_PinConfig_t;

/* ************************************************
 *
 * HANDLER STRUCTURES
 *
 * *************************************************/

typedef struct {
	GPIO_RegDef_t 		*pGPIOBaseAddr;						/* pointer to hold the base address of GPIO peripheral */
	GPIO_PinConfig_t 	GPIOPinConfig;						/* GPIO pin configuration */
}GPIO_Handler_t;

/* ************************************************
 *
 * API's Supported by this driver
 *
 * *************************************************/

/*
 *  GPIO Clock Control
 */

ut_Status GPIO_CLKControl(GPIO_RegDef_t *pGPIOBaseAddr, bool EnDis);

/*
 *  GPIO Initialization and De-Initialization
 */

ut_Status GPIO_Init(GPIO_Handler_t *pGPIOHandle);
ut_Status GPIO_DeInit(GPIO_RegDef_t *pGPIOBaseAddr);

/*
 *  GPIO Read and Write
 */

uint8_t GPIO_ReadPortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOBaseAddr);
ut_Status GPIO_WritePortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber, bool value);
ut_Status GPIO_WritePort(GPIO_RegDef_t *pGPIOBaseAddr, uint16_t value);
ut_Status GPIO_TogglePin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber);

/*
 *  GPIO Interrupt config and Handler
 */

ut_Status GPIO_INTRConfig(uint8_t pinNumber, uint8_t IRQPriority, bool EnDis);
void GPIO_INTRHandler(uint8_t pinNumber);

#endif /* INC_GPIODRIVER_H_ */
