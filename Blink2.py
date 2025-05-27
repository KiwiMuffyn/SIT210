import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setup(7,GPIO.OUT)
count =0
while count < 7:
    GPIO.output(7,GPIO.HIGH)
    time.sleep(0.25)
    GPIO.output(7,GPIO.LOW)
    count = count +1
    time.sleep(0.25)
GPIO.cleanup()