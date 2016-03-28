@echo off

set esptool=h:\Dev\esp8266\sw\esptool\esptool.py
set port=COM3

echo Chip ID:
python %esptool% --port %port% chip_id

echo.
echo Flash ID:
python %esptool% --port %port% flash_id

echo.
echo Mac Address:
python %esptool% --port %port% read_mac
