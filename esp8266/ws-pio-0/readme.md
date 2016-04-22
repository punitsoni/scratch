

# Commands for windows

## upload program via serial
/c/Users/punits/.platformio/packages/tool-esptool/esptool -vv -cd nodemcu -cb 115200 -cp COM14 -cf .pioenvs/nodemcuv2/firmware.bin

## Monitor the serial port
pio -f -c atom serialports monitor --port COM14 --baud 115200
