/*------------------------------------------------------------------------------
 *  Module      : Potentiometer Driver
 *  File        : pots.c
 *  Description : Driver for reading potentiometer values using ADC on Tiva C
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/
#include "HAL/POTS/pots.h"
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

/*------------------------------------------------------------------------------
 *  LOCAL DEFINITIONS
 *----------------------------------------------------------------------------*/
#define ADC_SEQUENCE_NUM       3   /**< ADC sequence number to use */
#define ADC_SAMPLE_WAIT        false /**< Don't wait for samples when checking status */

/*------------------------------------------------------------------------------
 *  FUNCTIONS DEFINITIONS
 *----------------------------------------------------------------------------*/

/**
 * @brief Initializes POT1 hardware (ADC channel 0 on PE3)
 */
void POT1_init(void)
{
    /* Enable required peripherals */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    /* Configure PE3 as ADC input */
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
}

/**
 * @brief Gets current value from POT1
 * @return Raw ADC value (0-4095)
 */
uint32_t POT1_getValue(void)
{
    uint32_t pui32ADC0Value[1];

    /* Configure ADC sequence */
    ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_NUM, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_NUM, 0,
                           ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    /* Enable and clear interrupt */
    ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_NUM);
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_NUM);

    /* Trigger conversion and wait for completion */
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQUENCE_NUM);
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQUENCE_NUM, ADC_SAMPLE_WAIT));

    /* Clear interrupt and read value */
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_NUM);
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQUENCE_NUM, pui32ADC0Value);

    return pui32ADC0Value[0];
}

/**
 * @brief Initializes POT2 hardware (ADC channel 1 on PE2)
 */
void POT2_init(void)
{
    /* Enable required peripherals */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    /* Configure PE2 as ADC input */
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);
}

/**
 * @brief Gets current value from POT2
 * @return Raw ADC value (0-4095)
 */
uint32_t POT2_getValue(void)
{
    uint32_t pui32ADC0Value[1];

    /* Configure ADC sequence */
    ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_NUM, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_NUM, 0,
                           ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);

    /* Enable and clear interrupt */
    ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_NUM);
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_NUM);

    /* Trigger conversion and wait for completion */
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQUENCE_NUM);
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQUENCE_NUM, ADC_SAMPLE_WAIT));

    /* Clear interrupt and read value */
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_NUM);
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQUENCE_NUM, pui32ADC0Value);

    return pui32ADC0Value[0];
}
