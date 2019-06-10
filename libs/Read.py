#!/usr/bin/env python
# -*-coding:UTF-8 -*

import RPi.GPIO as GPIO
import mfrc522

reader = mfrc522.SimpleMFRC522()

try:
        id, text = reader.read()
        #print(id)
        #print(text)
        file = open("temp/rfid_code.txt","w") 
        file.write(str(id))
        file.close() 
finally:
        GPIO.cleanup()
