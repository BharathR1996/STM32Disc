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
 * GPIO MODE VALUES
 *
 * *************************************************/

#define GPIO_MODE_IN						0
#define GPIO_MODE_OUT						1
#define GPIO_MODE_ALTFUN					2
#define GPIO_MODE_ANALOG					3

/* ************************************************
 *
 * GPIO OUTPUT TYPE VALUES
 *
 * *************************************************/

#define GPIO_OUTPUT_TYPE_PUSHPULL			0
#define GPIO_OUTPUT_TYPE_OPENDRAIN			1

/* ************************************************
 *
 * GPIO OUTPUT SPEED VALUES
 *
 * *************************************************/

#define GPIO_OUTPUT_SPEED_LOW				0
#define GPIO_OUTPUT_SPEED_MEDIUM			1
#define GPIO_OUTPUT_SPEED_HIGH				2
#define GPIO_OUTPUT_SPEED_VERYHIGH			3

/* ************************************************
 *
 * GPIO PULL-UP / PULL-DOWN VALUES
 *
 * *************************************************/

#define GPIO_NO_PULL_UP_DOWN				0
#define GPIO_PULL_UP						1
#define GPIO_PULL_DOWN						2

/* ************************************************
 *
 * GPIO PIN NUMBERS
 *
 * *************************************************/

#define GPIO_PIN_1				1
#define GPIO_PIN_2				2
#define GPIO_PIN_3				3
#define GPIO_PIN_4				4
#define GPIO_PIN_5				5
#define GPIO_PIN_6				6
#define GPIO_PIN_7				7
#define GPIO_PIN_8				8
#define GPIO_PIN_9				9
#define GPIO_PIN_10				10
#define GPIO_PIN_11				11
#define GPIO_PIN_12				12
#define GPIO_PIN_13				13
#define GPIO_PIN_14				14
#define GPIO_PIN_15				15
#define GPIO_PIN_16				16

/* ************************************************
 *
 * API's Supported by this driver
 *
 * *************************************************/

/*
 *  GPIO Clock Control
 */

void GPIO_CLKControl(GPIO_RegDef_t *pGPIOBaseAddr, bool EnDis);

/*
 *  GPIO Initialization and De-Initialization
 */

void GPIO_Init(GPIO_Handler_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOBaseAddr);

/*
 *  GPIO Read and Write
 */

uint8_t GPIO_ReadPortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOBaseAddr);
void GPIO_WritePortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber, bool value);
void GPIO_WritePort(GPIO_RegDef_t *pGPIOBaseAddr, uint16_t value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber);

/*
 *  GPIO Interrupt config and Handler
 */

void GPIO_INTRConfig(uint8_t pinNumber, uint8_t IRQPriority, bool EnDis);
void GPIO_INTRHandler(uint8_t pinNumber);

#endif /* INC_GPIODRIVER_H_ */
