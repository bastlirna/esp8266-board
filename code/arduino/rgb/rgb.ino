#define LED_R 14
#define LED_G 12
#define LED_B 16


void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  //Serial.begin(9600);
  color(0,0,0);
}

void loop()
{
  for (int i = 0; i <= 359; i++)
  {
      colorHSV(i, 255, 150);
      delay(20);
  }
}

void color(byte r, byte g, byte b)
{
  analogWrite(LED_R, 1023 - r * 4);
  analogWrite(LED_G, 1023 - g * 4);
  analogWrite(LED_B, 1023 - b * 4);
}

void colorHSV(int hue, int sat, int val) { 
  
  // http://www.kasperkamperman.com/blog/arduino/arduino-programming-hsb-to-rgb/
  
  int colors[3];
  int r;
  int g;
  int b;

  int base;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    colors[0]=val;
    colors[1]=val;
    colors[2]=val;  
  } else  { 
    base = ((255 - sat) * val)>>8;

    switch(hue/60) {
    case 0:
        r = val;
        g = (((val-base)*hue)/60)+base;
        b = base;
    break;
    case 1:
        r = (((val-base)*(60-(hue%60)))/60)+base;
        g = val;
        b = base;
    break;
    case 2:
        r = base;
        g = val;
        b = (((val-base)*(hue%60))/60)+base;
    break;
    case 3:
        r = base;
        g = (((val-base)*(60-(hue%60)))/60)+base;
        b = val;
    break;
    case 4:
        r = (((val-base)*(hue%60))/60)+base;
        g = base;
        b = val;
    break;
    case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(hue%60)))/60)+base;
    break;
    }

    colors[0]=r;
    colors[1]=g;
    colors[2]=b; 
  }   
  
  color( (byte)colors[0], (byte)colors[1], (byte)colors[2]);
}
