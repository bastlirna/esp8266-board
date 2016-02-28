
#include "ESP8266WiFi.h"


#include "hal.h"
#include "test.h"
#include "tests.h"

#ifdef ESP8266
extern "C" {
	#include "user_interface.h"
}
#endif

#define P(text) Serial.println(text);

bool i2c_mode;

void setup()
{
	Serial.begin(9600);
	Serial.println();
}

void loop()
{
	P("--- INFO -----------------------------------------------------------------------");

	Serial.print("Serial ID: ");
	Serial.println(system_get_chip_id());

	Serial.print("Mac address: ");
	Serial.println(WiFi.macAddress());

	i2c_mode = is_i2c_available();

	Serial.print("Board version: ");

	if (i2c_mode)
	{
		Serial.println("FULL");
	}
	else
	{
		Serial.println("LITE");
	}

	P("");
	P("--- TEST -----------------------------------------------------------------------");

	error_counter = 0;
	ok_counter = 0;

	test_rgb();
	test_beep();
	test_dht();

	if (i2c_mode)
	{
		//test_i2c();
		test_i2c_btn();
		test_i2c_relay();
	}
	else
	{
		test_btn();
	}

	P("--- RESULT ---------------------------------------------------------------------");
	P("")

	if (error_counter == 0)
	{
		Serial.print("PASS (");
		Serial.print(ok_counter);
		Serial.print(" tests ok)");
		
		digitalWrite(PIN_RGB_G, LOW);
		delay(3000);
		digitalWrite(PIN_RGB_G, HIGH);
	}
	else
	{
		Serial.print("FAIL (");
		Serial.print(ok_counter);
		Serial.print(" tests ok, ");
		Serial.print(error_counter);
		Serial.print(" tests fails)");

		digitalWrite(PIN_RGB_R, LOW);
		delay(3000);
		digitalWrite(PIN_RGB_R, HIGH);
	}

	P("")
	
	delay(60000);
}












