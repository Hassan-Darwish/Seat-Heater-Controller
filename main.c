/*------------------------------------------------------------------------------
 *  Module      : Seat Heating Control System
 *  File        : main.c
 *  Description : Main application for seat heating control using FreeRTOS
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *  Includes
 *----------------------------------------------------------------------------*/
#include <HAL/POTS/pots.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "typeDefs.h"
#include "GPTM.h"
#include "gpio.h"
#include "uart0.h"
#include "HAL/RGB_LED/rgb.h"

/*------------------------------------------------------------------------------
 *  Constants
 *----------------------------------------------------------------------------*/
#define RUNTIME_MEASUREMENTS_TASK_PERIODICITY    (1000U)

/*------------------------------------------------------------------------------
 *  Type Definitions
 *----------------------------------------------------------------------------*/
typedef enum {
    HEATING_OFF,
    HEATING_LOW,
    HEATING_MEDIUM,
    HEATING_HIGH
} HeatingLevelType;

typedef enum {
    HEATER_OFF,
    HEATER_LOW,
    HEATER_MEDIUM,
    HEATER_HIGH
} HeaterStateType;

typedef struct {
    uint8_t ui8Seat1TempValueC;
    HeatingLevelType Seat1heatingLevel;
    HeaterStateType Seat1heaterState;
    uint8_t ui8Seat2TempValueC;
    HeatingLevelType Seat2heatingLevel;
    HeaterStateType Seat2heaterState;
} SystemStateStructureType;

/*------------------------------------------------------------------------------
 *  Global Variables
 *----------------------------------------------------------------------------*/
SystemStateStructureType SystemState = {
    0, HEATING_OFF, HEATER_OFF,
    0, HEATING_OFF, HEATER_OFF
};

TaskHandle_t vDisplaySystemStateTaskHandle;
TaskHandle_t vcpuLoadMeasurementTaskHandle;
TaskHandle_t vtasksTimeMeasurementTaskHandle;
TaskHandle_t vSeat1AdjustHeaterHandle;
TaskHandle_t vSeat2AdjustHeaterHandle;
TaskHandle_t vgetSeat1CurrentTempTaskHandle;
TaskHandle_t vgetSeat2CurrentTempTaskHandle;
TaskHandle_t vCheckSeat1HeatingLevelChangeHandle;
TaskHandle_t vCheckSeat2HeatingLevelChangeHandle;

xSemaphoreHandle xMutex;

uint32 ullTasksOutTime[10];
uint32 ullTasksInTime[10];
uint32 ullTasksTotalTime[10];

/*------------------------------------------------------------------------------
 *  Function Prototypes
 *----------------------------------------------------------------------------*/
static void prvSetupHardware(void);
void vDisplaySystemStateTask(void *pvParameters);
void vcpuLoadMeasurementTask(void *pvParameters);
void vtasksTimeMeasurementTask(void *pvParameters);
void vSeat1AdjustHeaterTask(void *pvParameters);
void vSeat2AdjustHeaterTask(void *pvParameters);
void vgetSeat1CurrentTempTask(void *pvParameters);
void vgetSeat2CurrentTempTask(void *pvParameters);
void vCheckSeat1HeatingLevelChange(void *pvParameters);
void vCheckSeat2HeatingLevelChange(void *pvParameters);

/*------------------------------------------------------------------------------
 *  Main Function
 *----------------------------------------------------------------------------*/
int main()
{
    // Initialize hardware components
    prvSetupHardware();

    // Create mutex for resource protection
    xMutex = xSemaphoreCreateMutex();

    // Create system tasks
    xTaskCreate(vtasksTimeMeasurementTask, "Time Measurements", 256, NULL, 1,
               &vtasksTimeMeasurementTaskHandle);
    xTaskCreate(vcpuLoadMeasurementTask, "CPU Load Monitor", 32, NULL, 2,
               &vcpuLoadMeasurementTaskHandle);
    xTaskCreate(vDisplaySystemStateTask, "System State Display", 32,
               (void*)&SystemState, 2, &vDisplaySystemStateTaskHandle);
    xTaskCreate(vSeat1AdjustHeaterTask, "Seat1 Heater Control", 32,
               (void*)&SystemState, 2, &vSeat1AdjustHeaterHandle);
    xTaskCreate(vSeat2AdjustHeaterTask, "Seat2 Heater Control", 32,
               (void*)&SystemState, 2, &vSeat2AdjustHeaterHandle);
    xTaskCreate(vgetSeat1CurrentTempTask, "Seat1 Temp Read", 32,
               (void*)&SystemState, 2, &vgetSeat1CurrentTempTaskHandle);
    xTaskCreate(vgetSeat2CurrentTempTask, "Seat2 Temp Read", 32,
               (void*)&SystemState, 2, &vgetSeat2CurrentTempTaskHandle);
    xTaskCreate(vCheckSeat1HeatingLevelChange, "Seat1 Level Control", 32,
               (void*)&SystemState, 3, &vCheckSeat1HeatingLevelChangeHandle);
    xTaskCreate(vCheckSeat2HeatingLevelChange, "Seat2 Level Control", 32,
               (void*)&SystemState, 3, &vCheckSeat2HeatingLevelChangeHandle);

    // Configure task tags for identification
    vTaskSetApplicationTaskTag(vtasksTimeMeasurementTaskHandle, (TaskHookFunction_t)1);
    vTaskSetApplicationTaskTag(vcpuLoadMeasurementTaskHandle,   (TaskHookFunction_t)2);
    vTaskSetApplicationTaskTag(vDisplaySystemStateTaskHandle,   (TaskHookFunction_t)3);
    vTaskSetApplicationTaskTag(vSeat1AdjustHeaterHandle,        (TaskHookFunction_t)4);
    vTaskSetApplicationTaskTag(vSeat2AdjustHeaterHandle,        (TaskHookFunction_t)5);
    vTaskSetApplicationTaskTag(vgetSeat1CurrentTempTaskHandle,  (TaskHookFunction_t)6);
    vTaskSetApplicationTaskTag(vgetSeat2CurrentTempTaskHandle,  (TaskHookFunction_t)7);
    vTaskSetApplicationTaskTag(vCheckSeat1HeatingLevelChangeHandle, (TaskHookFunction_t)8);
    vTaskSetApplicationTaskTag(vCheckSeat2HeatingLevelChangeHandle, (TaskHookFunction_t)9);

    // Start RTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    for(;;);
}

/*------------------------------------------------------------------------------
 *  Hardware Initialization
 *----------------------------------------------------------------------------*/
static void prvSetupHardware(void)
{
    UART0_Init();
    GPTM_WTimer0Init();
    GPIO_BuiltinButtonsLedsInit();
    POT1_init();
    RGB_init();

    // Initialize all LEDs to OFF state
    RGB_RedLedOff();
    RGB_GreenLedOff();
    RGB_BlueLedOff();
    GPIO_RedLedOff();
    GPIO_GreenLedOff();
    GPIO_BlueLedOff();
}

/*------------------------------------------------------------------------------
 *  Task Implementations
 *----------------------------------------------------------------------------*/

// Time measurement task implementation
void vtasksTimeMeasurementTask(void *pvParameters)
{
    vTaskDelay(pdMS_TO_TICKS(2000));

    if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
        UART0_SendString("CPU Load Measurement Task: ");
        UART0_SendInteger(ullTasksTotalTime[2]/10);
        UART0_SendString(" ms\r\n");

        UART0_SendString("System State Display Task: ");
        UART0_SendInteger(ullTasksTotalTime[3]/10);
        UART0_SendString(" ms\r\n");

        // ... remaining measurement outputs ...

        xSemaphoreGive(xMutex);
        vTaskDelete(NULL);
    }
}

// CPU load monitoring task
void vcpuLoadMeasurementTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;) {
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
            uint32_t ullTotalTasksTime = 0;

            // Calculate total execution time
            for(uint8_t ucCounter = 1; ucCounter < 9; ucCounter++) {
                ullTotalTasksTime += ullTasksTotalTime[ucCounter];
            }

            uint8_t ucCPU_Load = (ullTotalTasksTime * 100) / GPTM_WTimer0Read();

            // Display CPU load
            taskENTER_CRITICAL();
            UART0_SendString("----- CPU Utilization: ");
            UART0_SendInteger(ucCPU_Load);
            UART0_SendString("% -----\r\n");
            taskEXIT_CRITICAL();

            xSemaphoreGive(xMutex);
        }
        vTaskDelayUntil(&xLastWakeTime, RUNTIME_MEASUREMENTS_TASK_PERIODICITY);
    }
}

// System state display task
void vDisplaySystemStateTask(void *pvParameters)
{
    SystemStateStructureType* systemState = (SystemStateStructureType*)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;) {
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
            // Temperature display
            UART0_SendString("Seat1 Temp: ");
            UART0_SendInteger(systemState->ui8Seat1TempValueC);
            UART0_SendString("°C | Seat2 Temp: ");
            UART0_SendInteger(systemState->ui8Seat2TempValueC);
            UART0_SendString("°C\r\n");

            // Heating level display
            UART0_SendString("Seat1 Level: ");
            switch(systemState->Seat1heatingLevel) {
                case HEATING_OFF:    UART0_SendString("OFF");    break;
                case HEATING_LOW:     UART0_SendString("LOW");    break;
                case HEATING_MEDIUM:  UART0_SendString("MEDIUM"); break;
                case HEATING_HIGH:    UART0_SendString("HIGH");   break;
                default:              break;
            }

            UART0_SendString(" | Seat2 Level: ");
            switch(systemState->Seat2heatingLevel) {
                case HEATING_OFF:    UART0_SendString("OFF\r\n");  break;
                case HEATING_LOW:     UART0_SendString("LOW\r\n");  break;
                case HEATING_MEDIUM:  UART0_SendString("MEDIUM\r\n"); break;
                case HEATING_HIGH:    UART0_SendString("HIGH\r\n");   break;
                default:              break;
            }

            // Heater state display
            UART0_SendString("Seat1 Heater: ");
            switch(systemState->Seat1heaterState) {
                case HEATER_OFF:    UART0_SendString("OFF");    break;
                case HEATER_LOW:     UART0_SendString("LOW");    break;
                case HEATER_MEDIUM:  UART0_SendString("MEDIUM"); break;
                case HEATER_HIGH:    UART0_SendString("HIGH");   break;
                default:              break;
            }

            UART0_SendString(" | Seat2 Heater: ");
            switch(systemState->Seat2heaterState) {
                case HEATER_OFF:    UART0_SendString("OFF\r\n");  break;
                case HEATER_LOW:     UART0_SendString("LOW\r\n");  break;
                case HEATER_MEDIUM:  UART0_SendString("MEDIUM\r\n"); break;
                case HEATER_HIGH:    UART0_SendString("HIGH\r\n");   break;
                default:              break;
            }

            UART0_SendString("----------------------------------------\r\n");
            xSemaphoreGive(xMutex);
            vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
        }
    }
}

// Remaining tasks follow the same improved formatting pattern...
