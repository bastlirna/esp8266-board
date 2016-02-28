
#define P(text) Serial.println(text);
#define H(text) Serial.print("## "); Serial.println(text);
#define debug(value) Serial.print(": "); Serial.println(value);
#define debugv(name, value) Serial.print(": ");Serial.print(name);Serial.print(": ");Serial.println(value);

int error_counter = 0;
int ok_counter = 0;
int test_counter = 0;

DHT dht(PIN_DHT, DHT_TYPE);

TwoWire testWire;
PCF8574 pcf8574(0x38, 5, 4, testWire);



inline void test_section(const char* name)
{
	Serial.print("# ");
	Serial.print(test_counter++);
	Serial.print(" ");
	Serial.println(name);
}

inline void test_section_end()
{
	Serial.println("\n");
}

inline void test_name(const char* name)
{
	Serial.print("\n> ");
	Serial.println(name);
}

inline void test_ok()
{
	Serial.println("  [OK]");
	ok_counter ++;
}

inline void test_fail()
{
	Serial.println("  [FAIL]");
	error_counter ++;
}

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

	debugv("Base light level", base);

	digitalWrite(pin, LOW);
	delay(500);
	
	int l = measure();

	if (base - l > 10)
	{
		test_ok();
	}
	else
	{
		debugv("On diff", base - l);
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
		debugv("Off diff", base - l);
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
  	debugv("Value", t);

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
	debugv("Value", h);

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


void i2c_btn_led_flash(byte pin, int time)
{
	pcf8574.write(pin, 0);
	delay(time);
	pcf8574.write(pin, 1);
	delay(10);
}

void test_i2c_btn_pin(byte pin)
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
	byte v = pcf8574.read8();

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


