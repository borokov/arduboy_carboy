# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

USER_LIB_PATH=~/Arduino/libraries/
BOARD_TAG    = leonardo
MONITOR_PORT = /dev/ttyACM0
MCU = atmega32u4
F_CPU = 8000000L
ARDUINO_LIBS = Arduboy SPI EEPROM

AVRDUDE_ARD_PROGRAMMER = avr109
AVRDUDE_ARD_BAUDRATE = 57600


# ------------------------------------------------------------------ #

# Path to the Arduino Makefile
include ../Arduino-Makefile/Arduino.mk

