from gpioc.pwm import Pwm
from gpioc.chips.K230 import *
import time
led = Pwm(IO52)
led.frequency = 1000
while 1:
    for i in range(1,100,5):
        led.duty_cycle = i
        time.sleep(0.1)