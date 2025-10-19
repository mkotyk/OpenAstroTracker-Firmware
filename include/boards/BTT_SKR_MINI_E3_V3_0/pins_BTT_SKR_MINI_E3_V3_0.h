/**
 * @brief a pins configuration file for the BigTreeTech SKR MINI E3 V3.0 board
 * https://github.com/bigtreetech/BIGTREETECH-SKR-mini-E3/tree/master/hardware/BTT%20SKR%20MINI%20E3%20V3.0/Hardware
 */
#pragma once

#include <HardwareSerial.h>

#define SW_SERIAL_UART 0
#define UART_CONNECTION_TEST_TXRX 1

extern HardwareSerial DriverSerial;
#define DRIVER_SERIAL_PORT_DECLARATION HardwareSerial DriverSerial(PC11, PC10);


// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - X axis
#ifndef RA_STEP_PIN
    #define RA_STEP_PIN PB13  // STEP
#endif
#ifndef RA_DIR_PIN
    #define RA_DIR_PIN PB12  // DIR
#endif
#ifndef RA_EN_PIN
    #define RA_EN_PIN PB14  // Enable
#endif
#ifndef RA_DIAG_PIN
    #define RA_DIAG_PIN PC0  // only if jumper P2 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define RA_SERIAL_PORT DriverSerial
#ifndef RA_DRIVER_ADDRESS
    #define RA_DRIVER_ADDRESS 0
#endif


// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - Y Axis
#ifndef DEC_STEP_PIN
    #define DEC_STEP_PIN PB10  // STEP
#endif
#ifndef DEC_DIR_PIN
    #define DEC_DIR_PIN PB2  // DIR
#endif
#ifndef DEC_EN_PIN
    #define DEC_EN_PIN PB11  // Enable
#endif
#ifndef DEC_DIAG_PIN
    #define DEC_DIAG_PIN PC1  // only if jumper P4 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define DEC_SERIAL_PORT DriverSerial
#ifndef DEC_DRIVER_ADDRESS
    #define DEC_DRIVER_ADDRESS 2
#endif

// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - Z Axis
#ifndef AZ_STEP_PIN
    #define AZ_STEP_PIN PB0  // STEP
#endif
#ifndef AZ_DIR_PIN
    #define AZ_DIR_PIN PC5  // DIR
#endif
#ifndef AZ_EN_PIN
    #define AZ_EN_PIN PB1  // Enable
#endif
#ifndef AZ_DIAG_PIN
    #define AZ_DIAG_PIN PC2  // only if jumper P5 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define AZ_SERIAL_PORT DriverSerial
#ifndef AZ_DRIVER_ADDRESS
    #define AZ_DRIVER_ADDRESS 1
#endif

// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - E0 port
#ifndef ALT_STEP_PIN
    #define ALT_STEP_PIN PB3  // STEP
#endif
#ifndef ALT_DIR_PIN
    #define ALT_DIR_PIN PB4  // DIR
#endif
#ifndef ALT_EN_PIN
    #define ALT_EN_PIN PD1  // Enable
#endif
#ifndef ALT_DIAG_PIN
    #define ALT_DIAG_PIN PC15  // only if jumper P1 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define ALT_SERIAL_PORT DriverSerial
#ifndef ALT_DRIVER_ADDRESS
    #define ALT_DRIVER_ADDRESS 3
#endif

// Board only has 4 stepper drivers, so no focus motor support, or reconfigure focus from above

// Enable RA TMC2209 stall homing
#define RA_STALL_HOMING 1

// Enable DEC TMC2209 stall homing
#define DEC_STALL_HOMING 1

//GPS pin configuration
//#define USE_GPS 1
#ifndef GPS_SERIAL_PORT
    #define GPS_SERIAL_PORT Serial2 // Port P3 for TFT Display
#endif

// DISPLAY_TYPE_LCD_KEYPAD requires 6 digital & 1 analog output in Arduino pin numbering
// This type of display not supported by hardware - see schematic for port J10

//Pin to turn on dew heater MOSFET
#ifndef DEW_HEATER_1_PIN
    #define DEW_HEATER_1_PIN PC9 // Bed PWM
#endif
#ifndef DEW_HEATER_2_PIN
    #define DEW_HEATER_2_PIN PC8 // Hot End 0 PWM
#endif

//Serial port for external debugging
// USART5 PD2(RX), PD3(TX)
#if DEBUG_LEVEL > 0
    extern HardwareSerial DebugSerial;
    #define DEBUG_SERIAL_PORT_DECLARATION	HardwareSerial DebugSerial(PD2, PD3);
    #define DEBUG_SERIAL_PORT DebugSerial
    #define DEBUG_SEPARATE_SERIAL 1
    #define DEBUG_SERIAL_BAUDRATE 115200
#endif
