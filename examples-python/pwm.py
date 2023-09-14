from gpioc import * 
import time

led = Pwm(PC13)
led.frequency = 1000
while 1:
    for i in range(1,65535,500):
        led.duty_cycle = i
        time.sleep(0.01)