/*------------------------------------------------------------------------------
 *  Module      : Potentiometer Driver
 *  File        : pots.h
 *  Description : Header file for potentiometer reading interface
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef HAL_POTS_POTS_H_
#define HAL_POTS_POTS_H_

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/
#include <stdint.h>

/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/

/**
 * @defgroup Potentiometer_Max_Values Maximum ADC values for potentiometers
 * @{
 */
#define POT1_MAX_VALUE   4096    /**< Maximum ADC value for POT1 (12-bit resolution) */
#define POT2_MAX_VALUE   4096    /**< Maximum ADC value for POT2 (12-bit resolution) */
/** @} */

/*------------------------------------------------------------------------------
 *  Function Declarations
 *----------------------------------------------------------------------------*/

/**
 * @defgroup Potentiometer_Functions Potentiometer Interface Functions
 * @{
 */

/**
 * @brief Initializes hardware for POT1 (ADC Channel 0)
 */
void POT1_init(void);

/**
 * @brief Reads current value from POT1
 * @return Raw ADC value (0-4095)
 */
uint32_t POT1_getValue(void);

/**
 * @brief Initializes hardware for POT2 (ADC Channel 1)
 */
void POT2_init(void);

/**
 * @brief Reads current value from POT2
 * @return Raw ADC value (0-4095)
 */
uint32_t POT2_getValue(void);

/** @} */

#endif /* HAL_POTS_POTS_H_ */
