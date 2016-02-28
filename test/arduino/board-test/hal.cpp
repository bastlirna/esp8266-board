#include "hal.h"

DHT dht(PIN_DHT, DHT_TYPE);

TwoWire testWire;
PCF8574 pcf8574(0x38, 5, 4, testWire);
