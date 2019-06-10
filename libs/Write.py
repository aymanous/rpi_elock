#!/usr/bin/env python

import RPi.GPIO as GPIO
import mfrc522

reader = mfrc522.SimpleMFRC522()

try:
        text = raw_input('New data:')
        print("Now place your tag to write")
        reader.write(text)
        print("Written")
finally:
        GPIO.cleanup()
