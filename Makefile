# https://blog.conduitlabs.com/arduino-command-line/

ARDUINO=/Applications/Arduino.app/Contents/MacOS/Arduino
PORT=/dev/cu.usbmodemFA131

install:
	#arduino --board package:architecture:board[:parameters] --port /dev/deviceFileName --upload rgb_led/rgb_led.ino
	$(ARDUINO) --board arduino:avr:uno --port $(PORT) --upload ./planet_lamp.ino
