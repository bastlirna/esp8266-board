#ifndef HAL_H_ 
#define HAL_H_

// ----------------------------------------------------------------------------

#include <DHT.h>
#include <pcf8574_esp.h>

// settings 

#define PIN_RGB_R 14
#define PIN_RGB_G 12
#define PIN_RGB_B 16

#define PIN_BEEP 15

#define PIN_BTN1 4
#define PIN_BTN2 5

#define PIN_DHT 13

#define DHT_TYPE DHT11

#define I2C_BTN1 4
#define I2C_BTN2 5
#define I2C_RELAY 7

// periferal 

extern DHT dht;

extern TwoWire testWire;
extern PCF8574 pcf8574;

// ----------------------------------------------------------------------------

#endif