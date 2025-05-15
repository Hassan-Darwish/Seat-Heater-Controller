/*------------------------------------------------------------------------------
 *  Module      : RGB LED Driver
 *  File        : rgb.h
 *  Description : Header file for RGB LED control using Tiva C GPIO
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef HAL_RGB_LED_RGB_H_
#define HAL_RGB_LED_RGB_H_

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/

/** @defgroup RGB_Port_Definitions RGB LED Port Base Addresses
  * @{
  */
#define RED_PORT_BASE           GPIO_PORTB_BASE    /**< Red LED port base address */
#define GREEN_PORT_BASE         GPIO_PORTB_BASE    /**< Green LED port base address */
#define BLUE_PORT_BASE          GPIO_PORTB_BASE    /**< Blue LED port base address */
/**
  * @}
  */

/** @defgroup RGB_Pin_Definitions RGB LED Pin Numbers
  * @{
  */
#define RED_PIN                 GPIO_PIN_1         /**< Red LED pin number */
#define GREEN_PIN               GPIO_PIN_2         /**< Green LED pin number */
#define BLUE_PIN                GPIO_PIN_3         /**< Blue LED pin number */
/**
  * @}
  */

/*------------------------------------------------------------------------------
 *  Function Declarations
 *----------------------------------------------------------------------------*/

/** @defgroup RGB_Functions RGB LED Control Functions
  * @{
  */

/**
 * @brief Initializes RGB LED GPIO pins
 */
void RGB_init(void);

/**
 * @brief Turns on the Red LED
 */
void RGB_RedLedOn(void);

/**
 * @brief Turns on the Green LED
 */
void RGB_GreenLedOn(void);

/**
 * @brief Turns on the Blue LED
 */
void RGB_BlueLedOn(void);

/**
 * @brief Turns off the Red LED
 */
void RGB_RedLedOff(void);

/**
 * @brief Turns off the Green LED
 */
void RGB_GreenLedOff(void);

/**
 * @brief Turns off the Blue LED
 */
void RGB_BlueLedOff(void);

/**
  * @}
  */

#endif /* HAL_RGB_LED_RGB_H_ */
