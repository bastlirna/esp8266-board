#define pin 15

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  analogWrite(pin, 512);
}

int v;

void loop() {
  v = analogRead(A0);

  int x = (1024 - v) * 10;
  analogWriteFreq(x);
  Serial.println(x);
  delay(50);
}
