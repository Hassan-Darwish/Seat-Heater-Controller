/*------------------------------------------------------------------------------
 *  Module      : RGB LED Driver
 *  File        : rgb.c
 *  Description : Source file for RGB LED control using Tiva C GPIO
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/
#include "rgb.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

/*------------------------------------------------------------------------------
 *  Functions Definitions
 *----------------------------------------------------------------------------*/

/**
 * @brief Initializes the RGB LED GPIO pins
 *
 * This function enables the GPIO peripheral and configures the RGB pins as outputs
 */
void RGB_init(void)
{
    /* Enable GPIO peripheral */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    /* Wait for peripheral to be ready */
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {}

    /* Configure pins as outputs */
    GPIOPinTypeGPIOOutput(RED_PORT_BASE, RED_PIN);
    GPIOPinTypeGPIOOutput(GREEN_PORT_BASE, GREEN_PIN);
    GPIOPinTypeGPIOOutput(BLUE_PORT_BASE, BLUE_PIN);
}

/**
 * @brief Turns on the Red LED
 */
void RGB_RedLedOn(void)
{
    GPIOPinWrite(RED_PORT_BASE, RED_PIN, RED_PIN);
}

/**
 * @brief Turns on the Green LED
 */
void RGB_GreenLedOn(void)
{
    GPIOPinWrite(GREEN_PORT_BASE, GREEN_PIN, GREEN_PIN);
}

/**
 * @brief Turns on the Blue LED
 */
void RGB_BlueLedOn(void)
{
    GPIOPinWrite(BLUE_PORT_BASE, BLUE_PIN, BLUE_PIN);
}

/**
 * @brief Turns off the Red LED
 */
void RGB_RedLedOff(void)
{
    GPIOPinWrite(RED_PORT_BASE, RED_PIN, 0x00);
}

/**
 * @brief Turns off the Green LED
 */
void RGB_GreenLedOff(void)
{
    GPIOPinWrite(GREEN_PORT_BASE, GREEN_PIN, 0x00);
}

/**
 * @brief Turns off the Blue LED
 */
void RGB_BlueLedOff(void)
{
    GPIOPinWrite(BLUE_PORT_BASE, BLUE_PIN, 0x00);
}
