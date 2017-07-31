# ESP8266 Demo Board

> If you are loking for **workshop material** go to **[esp8266-workshop](https://github.com/bastlirna/esp8266-workshop) repository** (in czech only).

## Description

*At the begining of 2016 we organized workshop focused on programming of the ESP8266 modules at linux conference [InstallFest 2016](http://installfest.cz/if16/) in Prague. We were looking for some demoboard that we could use during the workshop. There are a lot of handy boards like NodeMcu or WeMos D1 mini available. However, we were unable to find any board with basic peripheries that would suit our needs. So we decided to build our own…*

### Main Goal

Main goal was to create demo board focused for SW part of the thing (InstallFest is SW conference after all). That way, users can jump straight to programming and they don’t need to bother with connecting serial port, thermometer or even LED to ESP. On the other hand, we wanted universal board suitable for advanced users as well (I mean someone who is not afraid of soldering iron). All pins of ESP-12E module are brake out on pin headers and all on-board peripheries are connected to ESP via soldering jumpers.

### Key features

-	On board module ESP-12E
-	USB to serial interface, compatible programming with NodeMcu
-	USB or external power supply (on board 3.3V regulator)
-	Reset and boot manual switch
-	One RGB LED
-	Two tactile switches (with indication LED)
-	Beeper
-	Photoresistor connected to ADC input
-	DHT11 temperature and humidity sensor *)
-	I2C extender PCF8574 (optional)
-	Relay connected to I2C extender (optional)
-	I2C external connector (optional)

All I2C stuff are optional. There are two possible assemblies with (full version) or without I2C (lite version). The main difference is in the use of 2 ESP pins. They are either used as inputs for user switches or as I2C bus and switches are connected to I2C extender.
