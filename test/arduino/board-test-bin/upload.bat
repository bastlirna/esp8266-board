set esptool="c:\Users\adam\AppData\Local\Arduino15\packages\esp8266\tools\esptool\0.4.6\esptool.exe"

%esptool% -vv -cd nodemcu -cb 921600 -cp COM%1% -ca 0x00000 -cf board-test.ino.bin 
