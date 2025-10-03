/**
 * @brief a pins configuration file for the BigTreeTech SKR MINI E3 V3.0 board
 * https://github.com/bigtreetech/BIGTREETECH-SKR-mini-E3/tree/master/hardware/BTT%20SKR%20MINI%20E3%20V3.0/Hardware
 */
#pragma once

#define SW_SERIAL_UART 0

// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - X axis
#ifndef RA_STEP_PIN
    #define RA_STEP_PIN PB_13  // STEP
#endif
#ifndef RA_DIR_PIN
    #define RA_DIR_PIN PB_12  // DIR
#endif
#ifndef RA_EN_PIN
    #define RA_EN_PIN PB_14  // Enable
#endif
#ifndef RA_DIAG_PIN
    #define RA_DIAG_PIN PC_0  // only if jumper P2 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define RA_SERIAL_PORT Serial4
#ifndef RA_DRIVER_ADDRESS
    #define RA_DRIVER_ADDRESS 0
#endif
#define RA_MOTOR_CURRENT_RATING 1500
#define RA_OPERATING_CURRENT_SETTING 75


// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - Y Axis
#ifndef DEC_STEP_PIN
    #define DEC_STEP_PIN PB_10  // STEP
#endif
#ifndef DEC_DIR_PIN
    #define DEC_DIR_PIN PB_2  // DIR
#endif
#ifndef DEC_EN_PIN
    #define DEC_EN_PIN PB_11  // Enable
#endif
#ifndef DEC_DIAG_PIN
    #define DEC_DIAG_PIN PC_1  // only if jumper P4 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define DEC_SERIAL_PORT Serial4
#ifndef DEC_DRIVER_ADDRESS
    #define DEC_DRIVER_ADDRESS 2
#endif
#define DEC_MOTOR_CURRENT_RATING 1500
#define DEC_OPERATING_CURRENT_SETTING 75

// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - Z Axis
#ifndef AZ_STEP_PIN
    #define AZ_STEP_PIN PB_0  // STEP
#endif
#ifndef AZ_DIR_PIN
    #define AZ_DIR_PIN PC_5  // DIR
#endif
#ifndef AZ_EN_PIN
    #define AZ_EN_PIN PB_1  // Enable
#endif
#ifndef AZ_DIAG_PIN
    #define AZ_DIAG_PIN PC_2  // only if jumper P5 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define AZ_SERIAL_PORT Serial4
#ifndef AZ_DRIVER_ADDRESS
    #define AZ_DRIVER_ADDRESS 1
#endif

// DRIVER_TYPE_TMC2209_UART requires 4 digital pins in Arduino pin numbering - E0 port
#ifndef ALT_STEP_PIN
    #define ALT_STEP_PIN PB_3  // STEP
#endif
#ifndef ALT_DIR_PIN
    #define ALT_DIR_PIN PB_4  // DIR
#endif
#ifndef ALT_EN_PIN
    #define ALT_EN_PIN PD_1  // Enable
#endif
#ifndef ALT_DIAG_PIN
    #define ALT_DIAG_PIN PC_15  // only if jumper P1 is set
#endif
// DRIVER_TYPE_TMC2209_UART requires 2 additional digital pins for SoftwareSerial, can be shared across all drivers
#define ALT_SERIAL_PORT Serial4
#ifndef ALT_DRIVER_ADDRESS
    #define ALT_DRIVER_ADDRESS 3
#endif

// Board only has 4 stepper drivers, so no focus motor support

// RA Homing pin for TMC2209 stall
#ifndef RA_HOMING_SENSOR_PIN
    #define RA_HOMING_SENSOR_PIN PC_0 // TMC2209 Diag when jumper P2 is set
#endif

// DEC Homing pin for TMC2209 stall
#ifndef DEC_HOMING_SENSOR_PIN
    #define DEC_HOMING_SENSOR_PIN PC_1 // TMC2209 Diag when jumper P4 is set
#endif

//GPS pin configuration
#ifndef GPS_SERIAL_PORT
    #define GPS_SERIAL_PORT Serial2 // Port P3
#endif

// DISPLAY_TYPE_LCD_KEYPAD requires 6 digital & 1 analog output in Arduino pin numbering
// This type of display not supported by hardware - see schematic for port J10

//Pin to turn on dew heater MOSFET
#ifndef DEW_HEATER_1_PIN
    #define DEW_HEATER_1_PIN PC_9 // Bed PWM
#endif
#ifndef DEW_HEATER_2_PIN
    #define DEW_HEATER_2_PIN PC_8 // Hot End 0 PWM
#endif

//Serial port for external debugging
// Use SWD (J11) for debugging
