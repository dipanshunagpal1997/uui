
import Adafruit_BBIO.GPIO as GPIO
import Adafruit_BBIO.PWM as PWM
import time

GPIO.setup("P8_7",GPIO.IN)
GPIO.setup("P8_8",GPIO.IN)
GPIO.setup("P8_9",GPIO.IN)
GPIO.setup("P8_10",GPIO.IN)

#PWM.start(channel, duty, freq=2000, polarity=0)
PWM.start("P8_13")

#optionally, you can set the frequency as well as the polarity from their defaults: 
#PWM.start("P8_13", 50, 1000, 1)

while True:
	if (GPIO.input("P8_8")==0):
		PWM.set_duty_cycle("P8_13", 20)
	elif (GPIO.input("P8_7")==0):
		PWM.set_duty_cycle("P8_13", 90)
	elif (GPIO.input("P8_10")==0):
		PWM.set_duty_cycle("P8_13", 50)
	elif (GPIO.input("P8_9")==0):
		PWM.set_duty_cycle("P8_13", 0)

PWM.stop("P8_13") 
PWM.cleanup()



