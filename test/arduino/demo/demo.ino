#include "hal.h"

void setup()
{
	Serial.begin(9600);
	Serial.println();
}

void loop()
{
	Serial.println("Ahoj");
	led_on();
	delay(1000);
	led_off();
	delay(1000);


}












