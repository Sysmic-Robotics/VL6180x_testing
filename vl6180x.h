#define _ADAFRUIT_VL6180X_H

//#include "Arduino.h"
//#include <Adafruit_I2CDevice.h>

#define VL6180X_DEFAULT_I2C_ADDR 0x29
///< The fixed I2C addres

///! Device model identification number
#define VL6180X_REG_IDENTIFICATION_MODEL_ID 0x000
///! Interrupt configuration
#define VL6180X_REG_SYSTEM_INTERRUPT_CONFIG 0x014
///! Interrupt clear bits
#define VL6180X_REG_SYSTEM_INTERRUPT_CLEAR 0x015
///! Fresh out of reset bit
#define VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET 0x016
///! Trigger Ranging
#define VL6180X_REG_SYSRANGE_START 0x018
///! Part to part range offset
#define VL6180X_REG_SYSRANGE_PART_TO_PART_RANGE_OFFSET 0x024
///! Trigger Lux Reading
#define VL6180X_REG_SYSALS_START 0x038
///! Lux reading gain
#define VL6180X_REG_SYSALS_ANALOGUE_GAIN 0x03F
///! Integration period for ALS mode, high byte
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_HI 0x040
///! Integration period for ALS mode, low byte
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_LO 0x041
///! Specific error codes
#define VL6180X_REG_RESULT_RANGE_STATUS 0x04d
///! Interrupt status
#define VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO 0x04f
///! Light reading value
#define VL6180X_REG_RESULT_ALS_VAL 0x050
///! Ranging reading value
#define VL6180X_REG_RESULT_RANGE_VAL 0x062
///! I2C Slave Device Address
#define VL6180X_REG_SLAVE_DEVICE_ADDRESS 0x212

#define VL6180X_ALS_GAIN_1 0x06
///< 1x gain
#define VL6180X_ALS_GAIN_1_25 0x05
///< 1.25x gain
#define VL6180X_ALS_GAIN_1_67 0x04
///< 1.67x gain
#define VL6180X_ALS_GAIN_2_5 0x03
///< 2.5x gain
#define VL6180X_ALS_GAIN_5 0x02
///< 5x gain
#define VL6180X_ALS_GAIN_10 0x01
///< 10x gain
#define VL6180X_ALS_GAIN_20 0x00
///< 20x gain
#define VL6180X_ALS_GAIN_40 0x07
///< 40x gain

#define VL6180X_ERROR_NONE 0
///< Success!
#define VL6180X_ERROR_SYSERR_1 1
///< System error
#define VL6180X_ERROR_SYSERR_5 5
///< Sysem error
#define VL6180X_ERROR_ECEFAIL 6
///< Early convergence estimate fail
#define VL6180X_ERROR_NOCONVERGE 7
///< No target detected
#define VL6180X_ERROR_RANGEIGNORE 8
///< Ignore threshold check failed
#define VL6180X_ERROR_SNR 11
//< Ambient conditions too high
#define VL6180X_ERROR_RAWUFLOW 12
///< Raw range algo underflow
#define VL6180X_ERROR_RAWOFLOW 13
///< Raw range algo overflow
#define VL6180X_ERROR_RANGEUFLOW 14
///< Raw range algo underflow
#define VL6180X_ERROR_RANGEOFLOW 15
///< Raw range algo overflow

///! Class for managing connection and state to a VL6180X sensor

#include <stdbool.h> //de ser necesario
#include <stdint.h>  //de ser necesario
#include <stdio.h>   //de ser necesario
#include "stm32fxxx_hal.h" 

#define VL6180X_DEFAULT_I2C_ADDR 0x29

typedef struct VL6180X {
  I2C_HandleTypeDef *i2cHandler;
  // TwoWire *_i2c;
  uint8_t i2cAddress;
  uint8_t rxBuffer[128];
  uint8_t txBuffer[128];
  // revisar tamaño de los buffer en librería wire.h
  //tambien revisar I2C control interface pag 42 
} VL6180X;

VL6180X* Adafruit_VL6180X_create(uint8_t i2caddr);
void Adafruit_VL6180X_destroy(VL6180X* vl6180x);
int Adafruit_VL6180X_begin(VL6180X* vl6180x);
int Adafruit_VL6180X_setAddress(VL6180X *vl6180x, uint8_t newAddr);
uint8_t Adafruit_VL6180X_getAddress(VL6180X *vl6180x);

uint8_t Adafruit_VL6180X_readRange(VL6180X *vl6180x);
float Adafruit_VL6180X_readLux(VL6180X *vl6180x, uint8_t gain);
uint8_t Adafruit_VL6180X_readRangeStatus(VL6180X *vl6180x);

int Adafruit_VL6180X_startRange(VL6180X *vl6180x);
int Adafruit_VL6180X_isRangeComplete(VL6180X *vl6180x);
int Adafruit_VL6180X_waitRangeComplete(VL6180X *vl6180x);
uint8_t Adafruit_VL6180X_readRangeResult(VL6180X *vl6180x);

void Adafruit_VL6180X_startRangeContinuous(VL6180X *vl6180x,
                                           uint16_t period_ms);
void Adafruit_VL6180X_stopRangeContinuous(VL6180X *vl6180x);

void Adafruit_VL6180X_setOffset(VL6180X *vl6180x, uint8_t offset);
void Adafruit_VL6180X_getID(VL6180X *vl6180x, uint8_t *id_ptr);

void Adafruit_VL6180X_loadSettings(VL6180X *vl6180x);
// void Adafruit_VL6180X_write8(Adafruit* vl6180x, uint16_t address, uint8_t
// data); void Adafruit_VL6180X_write16(Adafruit* vl6180x, uint16_t address,
// uint16_t data);
uint16_t Adafruit_VL6180X_read16(VL6180X *vl6180x, uint16_t address);
uint8_t Adafruit_VL6180X_read8(VL6180X *vl6180x, uint16_t address);
