#include "tests.h"

#include "Arduino.h"

#include "hal.h"
#include "test.h"

const int measure_count = 5;

int measure()
{
	int v = 0;

	for (int i = 0; i < measure_count; ++i)
	{
		v += analogRead(A0);
	}

	return v / measure_count;
}

void test_led_pin(int pin)
{
	int base = measure();

	debug("Base light level", base);

	digitalWrite(pin, LOW);
	delay(500);
	
	int l = measure();

	if (base - l > 10)
	{
		test_ok();
	}
	else
	{
		debug("On diff", base - l);
		test_fail();
	}

	digitalWrite(pin, HIGH);
	delay(500);

	l = measure();

	if (base - l < 10)
	{
		test_ok();
	}
	else
	{
		debug("Off diff", base - l);
		test_fail();
	}
}



void test_rgb()
{
	test_section("RGB LED & LIGHT");

	// setup pin
	pinMode(PIN_RGB_R, OUTPUT);
	pinMode(PIN_RGB_G, OUTPUT);
	pinMode(PIN_RGB_B, OUTPUT);

	digitalWrite(PIN_RGB_R, HIGH);
	digitalWrite(PIN_RGB_G, HIGH);
	digitalWrite(PIN_RGB_B, HIGH);

	test_name("Red LED");
	test_led_pin(PIN_RGB_R);

	test_name("Green LED");
	test_led_pin(PIN_RGB_G);

	test_name("Blue LED");
	test_led_pin(PIN_RGB_B);

	test_section_end();
}


void test_beep()
{
	test_section("BEEP");

  	// put your setup code here, to run once:
  	pinMode(PIN_BEEP, OUTPUT);

	test_name("500 Hz");
	analogWrite(PIN_BEEP, 512);
	analogWriteFreq(500);
	delay(150);
	analogWrite(PIN_BEEP, 0);
	delay(500);
	test_ok();

	test_name("1 kHz");
	analogWrite(PIN_BEEP, 512);
	analogWriteFreq(1000);
	delay(150);
	analogWrite(PIN_BEEP, 0);
	delay(500);
	test_ok();

	test_name("2 kHz");
	analogWrite(PIN_BEEP, 512);
	analogWriteFreq(2000);
	delay(150);
	analogWrite(PIN_BEEP, 0);
	delay(500);
	test_ok();

	test_section_end();
}

void btn_led_flash(int pin, int time)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(time);
	digitalWrite(pin, HIGH);
	pinMode(pin, INPUT);
	delay(10);
}

void test_btn_pin(int pin)
{
	// test btn
	bool v = digitalRead(pin);

	if (v == LOW){
		debug("Btn is not high in normal state");
		test_fail();
	}
	else
	{
		test_ok();
	}

	debug("Press button");

	for (int i = 0; i < 20; ++i)
	{
		delay(200);
		btn_led_flash(pin, 10);

		v = digitalRead(pin);

		if (v == LOW){
			test_ok();
			break;
		}
	}

	if (v == HIGH)
	{
		btn_led_flash(pin, 1000);
		debug("Btn was not pressed in time");
		test_fail();
	}

}

void test_btn()
{
	test_section("Buttons");

	pinMode(PIN_BTN1, INPUT);
	pinMode(PIN_BTN2, INPUT);

	// Button 1

	test_name("Button 1");
	test_btn_pin(PIN_BTN1);

	test_name("Button 2");
	test_btn_pin(PIN_BTN2);

	test_section_end();
}

void test_dht()
{
	test_section("DHT");

	dht.begin();

	test_name("Temperature");

	float t = dht.readTemperature();
  	debug("Value", t);

  	if (isnan(t))
  	{
  		test_fail();
  	}
  	else
  	{
  		if (t > 10 && t < 40)
  		{
  			test_ok();
  		}
  		else
  		{
  			debug("Out of range");
  			test_fail();
  		}
  	}

	test_name("Humidity");

	float h = dht.readHumidity();
	debug("Value", h);

  	if (isnan(h))
  	{
  		test_fail();
  	}
  	else
  	{
  		if (h > 10 && h < 80)
  		{
  			test_ok();
  		}
  		else
  		{
  			debug("Out of range");
  			test_fail();
  		}
  	}

	test_section_end();
}


void i2c_btn_led_flash(int pin, int time)
{
	pcf8574.write(pin, 0);
	delay(time);
	pcf8574.write(pin, 1);
	delay(10);
}

void test_i2c_btn_pin(int pin)
{
	// test btn
	bool v = pcf8574.read(pin);

	if (v == LOW){
		debug("Btn is not high in normal state");
		test_fail();
	}
	else
	{
		test_ok();
	}

	debug("Press button");

	for (int i = 0; i < 20; ++i)
	{
		delay(200);
		i2c_btn_led_flash(pin, 10);

		v = pcf8574.read(pin);

		if (v == LOW){
			test_ok();
			break;
		}
	}

	if (v == HIGH)
	{
		i2c_btn_led_flash(pin, 1000);
		debug("Btn was not pressed in time");
		test_fail();
	}

}


void test_i2c_btn()
{
	test_section("I2C Buttons");

	test_name("Button 1");
	test_i2c_btn_pin(I2C_BTN1);

	test_name("Button 2");
	test_i2c_btn_pin(I2C_BTN2);

	test_section_end();
}


void test_i2c()
{
	int v = pcf8574.read8();

	Serial.println(v, BIN);

	pcf8574.write(7, 0);

	delay(1000);

	pcf8574.write(7, 1);

}


void test_i2c_relay()
{
	test_section("I2C Buttons");

	test_name("Relay ON");

	pcf8574.write(I2C_RELAY, 0);
	delay(1000);
	pcf8574.write(I2C_RELAY, 1);
	delay(100);

	test_ok();

	test_section_end();
}

bool is_i2c_available()
{
	pcf8574.write8(255);
	int e = pcf8574.lastError();
	return e == 0;
}


