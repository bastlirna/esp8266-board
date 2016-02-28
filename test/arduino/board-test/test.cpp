#include "test.h"

#include "Arduino.h"

int test_counter = 0;

int error_counter = 0;
int ok_counter = 0;

void test_section(const char* name)
{
	Serial.print("# ");
	Serial.print(test_counter++);
	Serial.print(" ");
	Serial.println(name);
}

void test_section_end()
{
	Serial.println("\n");
}

void test_name(const char* name)
{
	Serial.print("\n> ");
	Serial.println(name);
}

void test_ok()
{
	Serial.println("  [OK]");
	ok_counter ++;
}

void test_fail()
{
	Serial.println("  [FAIL]");
	error_counter ++;
}


void debug(const char *value)
{
	Serial.print(": ");
	Serial.println(value);

}

void debug(int value)
{
	Serial.print(": ");
	Serial.println(value);
}

void debug(const char* text, int value)
{
	Serial.print(": ");
	Serial.print(text);
	Serial.print(" = ");
	Serial.println(value);
}
