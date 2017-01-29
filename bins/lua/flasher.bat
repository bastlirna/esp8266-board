
::esptool.py --port %1 erase_flash

esptool.py --port %1 write_flash 0x00000 %2