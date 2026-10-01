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

void GPIO_CLKControl(void);

/*
 *  GPIO Initialization and De-Initialization
 */

void GPIO_Init(void);
void GPIO_DeInit(void);

/*
 *  GPIO Read and Write
 */

void GPIO_ReadPortPin(void);
void GPIO_ReadPort(void);
void GPIO_WritePortPin(void);
void GPIO_WritePort(void);
void GPIO_TogglePin(void);

/*
 *  GPIO Interrupt config and Handler
 */

void GPIO_INTRConfig(void);
void GPIO_INTRHandler(void);

#endif /* INC_GPIODRIVER_H_ */
