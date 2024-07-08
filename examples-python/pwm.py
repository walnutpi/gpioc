from gpioc.pwm import Pwm
from gpioc.chips.H616 import *
import time
led = Pwm(PC13)
led.frequency = 1000
while 1:
    for i in range(1,100,5):
        led.duty_cycle = i
        time.sleep(0.1)