#ifndef _ADAFRUIT_VL6180X_H
#define _ADAFRUIT_VL6180X_H

#include <stdbool.h> //de ser necesario
#include <stdint.h>  //de ser necesario
#include <stdio.h>   //de ser necesario
#include "stm32fxxx_hal.h" // incluye la biblioteca HAL 

//direccion i2c
#define VL6180X_DEFAULT_I2C_ADDR 0x29 

#define VL6180X_ALS_GAIN_1 0x06    
#define VL6180X_ALS_GAIN_1_25 0x05 
#define VL6180X_ALS_GAIN_1_67 0x04
#define VL6180X_ALS_GAIN_2_5 0x03  
#define VL6180X_ALS_GAIN_5 0x02    
#define VL6180X_ALS_GAIN_10 0x01   
#define VL6180X_ALS_GAIN_20 0x00   
#define VL6180X_ALS_GAIN_40 0x07  

#define VL6180X_ERROR_NONE 0       
#define VL6180X_ERROR_SYSERR_1 1    
#define VL6180X_ERROR_SYSERR_5 5    
#define VL6180X_ERROR_ECEFAIL 6     
#define VL6180X_ERROR_NOCONVERGE 7  
#define VL6180X_ERROR_RANGEIGNORE 8 
#define VL6180X_ERROR_SNR 11         
#define VL6180X_ERROR_RAWUFLOW 12   
#define VL6180X_ERROR_RAWOFLOW 13   
#define VL6180X_ERROR_RANGEUFLOW 14 
#define VL6180X_ERROR_RANGEOFLOW 15 

typedef struct VL6180X {
  I2C_HandleTypeDef *i2cHandler;
  uint8_t i2cAddress;
  uint8_t rxBuffer[128];
  uint8_t txBuffer[128];
  // revisar tamaño de los buffer en librería wire.h
  //tambien revisar I2C control interface pag 42 
} VL6180X;

void VL6180X_Init(VL6180X *vl6180x, I2C_HandleTypeDef *i2cHandler, uint8_t i2cAddress);
//void Adafruit_VL6180X_Begin(VL6180X *vl6180x);
//void Adafruit_VL6180X_SetAddress(VL6180X *vl6180x, uint8_t newAddr);
uint8_t VL6180X_GetAddress(VL6180X *vl6180x);
uint8_t VL6180X_ReadRange(VL6180X *vl6180x);
float VL6180X_ReadLux(VL6180X *vl6180x, uint8_t gain);
uint8_t VL6180X_ReadRangeStatus(VL6180X *vl6180x);
boolean VL6180X_StartRange(VL6180X *vl6180x);
boolean VL6180X_IsRangeComplete(VL6180X *vl6180x);
boolean VL6180X_WaitRangeComplete(VL6180X *vl6180x);
uint8_t VL6180X_ReadRangeResult(VL6180X *vl6180x);
void VL6180X_StartRangeContinuous(VL6180X *vl6180x, uint16_t period_ms);
void VL6180X_StopRangeContinuous(VL6180X *vl6180x);
void VL6180X_SetOffset(VL6180X *vl6180x, uint8_t offset);
void VL6180X_GetID(VL6180X *vl6180x, uint8_t *id_ptr);

#endif