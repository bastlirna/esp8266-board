#define pin 15

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  analogWrite(pin, 512);
}

int i = 100;

void loop() {
  // put your main code here, to run repeatedly:

  analogWriteFreq(i);
  i+= 10;

  if (i > 15000) i = 1;
  
  delay(100);
  
}
