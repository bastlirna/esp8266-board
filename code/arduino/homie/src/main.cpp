#include <Arduino.h>
#include <Homie.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define HOMIE_LEN 2

#define LED_R 14
#define LED_G 12
#define LED_B 16

#define BTN_A 4
#define BTN_B 5

const int TEMPERATURE_INTERVAL = 60;
const int AD_INTERVAL = 5;

unsigned long lastTemperatureSent = 0;
unsigned long lastAdSent = 0;

int lastBtnA = -1;
int lastBtnB = -1;

Bounce debouncerA = Bounce();
Bounce debouncerB = Bounce();

DHT dht(13, DHT11);

HomieNode rgbNode("rgb", "rgb");
HomieNode buttonsNode("btn", "btn");
HomieNode dhtNode("dht", "dht");
HomieNode adNode("ad", "ad");

void color(byte r, byte g, byte b)
{
    analogWrite(LED_R, 1023 - r * 4);
    analogWrite(LED_G, 1023 - g * 4);
    analogWrite(LED_B, 1023 - b * 4);
}

bool lightOnHandler(String value) {
    unsigned long c = strtoul(value.c_str(), NULL, HEX);

    byte r = (c & 0xFF0000) >> 16;
    byte g = (c & 0x00FF00) >> 8;
    byte b = (c & 0x0000FF);

    Serial.print(r, HEX);
    Serial.print(g, HEX);
    Serial.println(b, HEX);

    color(r, g, b);
    Homie.setNodeProperty(rgbNode, "color", value);

    return true;
}

void setupHandler() {
  //Homie.setNodeProperty(dhtNode, "unit", "c", true);
}

void loopHandler() {

    // temp
    if (millis() - lastTemperatureSent >= TEMPERATURE_INTERVAL * 1000UL || lastTemperatureSent == 0) {
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        if (isnan(h) || isnan(t)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        } else {
            Serial.print("Temperature: ");
            Serial.print(t);
            Serial.print(" °C, Humidity: ");
            Serial.print(h);
            Serial.println(" %");

            if (Homie.setNodeProperty(dhtNode, "temp", String(t), true) &&
                Homie.setNodeProperty(dhtNode, "humi", String(h), true)) {
                lastTemperatureSent = millis();
            } else {
                Serial.println("DHT sending failed");
            }
        }
    }

    // ad
    if (millis() - lastAdSent >= AD_INTERVAL * 1000UL || lastAdSent == 0) {
        int v = analogRead(0);

        Serial.print("AD: ");
        Serial.println(v);

        if (Homie.setNodeProperty(adNode, "value", String(v), true)) {
            lastAdSent = millis();
        } else {
            Serial.println("AD sending failed");
        }
    }

    // btns
    int btnA = debouncerA.read();
    int btnB = debouncerB.read();

    if (btnA != lastBtnA) {
        Serial.print("BtnA change: ");
        Serial.println(btnA ? "open" : "close");

        if (Homie.setNodeProperty(buttonsNode, "a", btnA ? "false" : "true", true)) {
            lastBtnA = btnA;
        } else {
            Serial.println("Sending failed");
        }
    }

    if (btnB != lastBtnB) {
        Serial.print("BtnA change: ");
        Serial.println(btnB ? "open" : "close");

        if (Homie.setNodeProperty(buttonsNode, "b", btnB ? "false" : "true", true)) {
            lastBtnB = btnB;
        } else {
            Serial.println("Sending failed");
        }
    }
}

void setup() {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    color(255,255,255);
    delay(50);
    color(0,0,0);

    debouncerA.attach(BTN_A);
    debouncerA.interval(50);
    debouncerB.attach(BTN_B);
    debouncerB.interval(50);

    dht.begin();

    Homie.setFirmware("esp8266-demo-board", "1.0.0");

    Homie.setLedPin(HOMIE_LEN, LOW);
    //Homie.setBrand("MG");

    rgbNode.subscribe("color", lightOnHandler);

    Homie.registerNode(rgbNode);
    Homie.registerNode(buttonsNode);
    Homie.registerNode(dhtNode);
    Homie.registerNode(adNode);

    Homie.setSetupFunction(setupHandler);
    Homie.setLoopFunction(loopHandler);

    Homie.setup();
}

void loop() {
    Homie.loop();

    debouncerA.update();
    debouncerB.update();
}
