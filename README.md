# simple-tachometer
A simple Arduino-based tachometer, based on [the design by Great Scott](https://www.instructables.com/DIY-Tachometer-RPM-Meter/)

##Components
1x Arduino (any should do, I used Nano)
1x HW201 infrared (IR) proximity sensor
1x breadboard (optional)
Wires/solder as needed

##Assembly
1. Connect VCC and GND on the sensor to 5V and GND on the Arduino
2. Connect the OUT pin on the sensor to pin D8 on the Arduino
  -  If you use a different Arduino, you may need to use a differnt pin for this
  -  This is selected as the ATmega328P ICP1 (Timer/Counter1 Input Capture Input) pin

##Use
1. Apply a reflective marker to the object you wish to measure the RPM of
2. The Arduino outputs timestamped measurements to the USB serial port, so use the IDE serial monitor or another connected terminal to read it

##Caveats
1. Because of the specific use-case I built this for, the code assumes the measured object is slowing down and ignores measurements that are faster than the previous one

##Possible improvements
1. Rechargable battery power
2. LCD display
3. Storage to removable media
