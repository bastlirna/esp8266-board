#include "hal.h"
#include "Arduino.h"

#define LED_PIN 14

void led_on()
{
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
}

void led_off()
{
	digitalWrite(LED_PIN, HIGH);
}
