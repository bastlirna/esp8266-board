#ifndef TEST_H_ 
#define TEST_H_

extern int error_counter;
extern int ok_counter;

void test_section(const char* name);
void test_section_end();
void test_name(const char* name);
void test_ok();
void test_fail();

void debug(const char *value);
void debug(int value);
void debug(const char* text, int value);

#endif
