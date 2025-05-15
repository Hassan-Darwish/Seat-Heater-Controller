# Seat Heating System using FreeRTOS

## Overview
This project implements a real-time seat heating control system for vehicles using FreeRTOS, a popular RTOS kernel for embedded devices. The system manages multiple concurrent tasks to monitor and adjust seat temperatures, display system states, and measure CPU load and task execution times.

## Features
- **Multi-task Management**: Utilizes FreeRTOS to handle concurrent tasks efficiently.
- **Temperature Control**: Adjusts heater intensity for two seats based on current and desired temperatures.
- **System Monitoring**: Measures CPU load and task execution times for performance analysis.
- **User Interaction**: Monitors and responds to user input for heating level changes.
- **Real-time Display**: Shows system state, including temperatures, heating levels, and heater intensity.

## Task Descriptions
The system includes the following tasks:
- **CPU Load Measurement Task**: Measures system CPU load every 1000 ms.
- **Tasks Time Measurement Task**: Measures task execution times every 1000 ms.
- **Display System State Task**: Displays system state (temperatures, heating levels, etc.) every 1000 ms.
- **Seat 1 & 2 Adjust Heater Tasks**: Adjust heater intensity for each seat every 100 ms.
- **Get Seat 1 & 2 Current Temperature Tasks**: Read seat temperatures every 100 ms.
- **Check Seat 1 & 2 Heating Level Change Tasks**: Monitor user input for heating level changes every 100 ms.

## Example Output
The system provides real-time feedback via UART messages, such as:

```
--- CPU load is 46% ---
Seat1 Temperature: 44°C Seat2 Temperature: 34°C
Seat1 Heating Level: OFF Seat2 Heating Level: OFF
Seat1 Heater Intensity: OFF Seat2 Heater Intensity: OFF
```

## Simulation Results
The project includes simulation results using SimSo, a real-time scheduling simulator, to analyze task performance and CPU load. Key metrics include:
- Task execution times (min, avg, max).
- CPU load and system performance.

## Getting Started
1. **Prerequisites**: 
   - FreeRTOS installed on your embedded system.
   - UART terminal for monitoring output.
2. **Setup**:
   - Clone the repository.
   - Configure the tasks as per your hardware requirements.
   - Upload the code to your embedded device.
3. **Usage**:
   - Monitor the system state via UART.
   - Adjust heating levels using the designated input methods.

## License
This project is open-source. Feel free to modify and distribute it as needed.

## Acknowledgments
- FreeRTOS for providing the RTOS kernel.
- SimSo for real-time scheduling simulation support.
