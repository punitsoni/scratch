#git clone https://github.com/arduino/Arduino.git -b ide-1.5.x arduino-ide

if [ ! -e arduino-1.5 ]; then
    #wget https://github.com/arduino/Arduino/archive/ide-1.5.x.zip
    #unzip ide-1.5.x.zip
    mv Arduino-ide-1.5.x arduino-1.5
    rm ide-1.5.x.zip
else
    echo "arduino ide exists."
fi


