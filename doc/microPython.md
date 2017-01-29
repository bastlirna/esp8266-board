# ESP8266 microPython #

### Documentation ###

GettingStarted Official
[https://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/intro.html](https://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/intro.html)

microPython Firmware
[http://micropython.org/download#esp8266](http://micropython.org/download#esp8266)

esptool.py
[https://github.com/espressif/esptool](https://github.com/espressif/esptool)

### Commands ###

Erase flash (COM4)

    python.exe Scripts\esptool.py -p COM4 erase_flash

Firmware Load (COM4)

    python.exe Scripts\esptool.py -p COM4 -b 460800 write_flash --flash_size=detect 0 C:\Users\Jakub\Desktop\microPython\esp8266-20170108-v1.8.7.bin
    esptool.py v1.3