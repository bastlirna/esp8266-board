/*
 Basic MQTT example 
 
  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char *ssid =	"SH_IF";		// cannot be longer than 32 characters!
const char *pass =	"InstallFest16";		//

// Update these with values suitable for your network.
IPAddress server(147, 32, 30, 132);

#define PIN_DHT 13
#define DHT_TYPE DHT11

#define PIN_RGB_R 14
#define PIN_RGB_G 12
#define PIN_RGB_B 16

DHT dht(PIN_DHT, DHT_TYPE);

String topic;

void callback(const MQTT::Publish& pub) {
  // handle message arrived
}


unsigned long sendtime;
unsigned long counter = 0;

WiFiClient wclient;
PubSubClient client(wclient, server);

void flash()
{
  digitalWrite(PIN_RGB_G, LOW);
  delay(100);
  digitalWrite(PIN_RGB_G, HIGH);
}

void setup() {

  pinMode(PIN_RGB_G, OUTPUT);
  digitalWrite(PIN_RGB_G, HIGH);

  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  client.set_callback(callback);

  topic = "/if/esp" + WiFi.macAddress() + "/";

  sendtime = millis();
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("WiFi connected");
  }

  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect("c" + WiFi.macAddress())) {
	       //client.subscribe("inTopic");
      }
    }

    if (millis() - sendtime > 5000)
    {
      flash();

      float h = dht.readHumidity();
      float t = dht.readTemperature();

      Serial.print("T: ");
      Serial.println(t);
      Serial.print("H: ");
      Serial.println(h);

      client.publish(topic + "t", String(t));
      client.publish(topic + "h", String(h));
      client.publish(topic + "counter", String(counter));
      //client.publish(topic + "uptime", String(sendtime));

      sendtime = millis();
      counter++;
    }

    if (client.connected())
      client.loop();
    }
}
