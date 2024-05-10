from gpioc.chips.H616 import *
import time
key = PC12
led = PC13
key.init(key.IN,key.PULL_UP)
led.init(led.OUT)

PC12.init(PC12.IN,PC12.PULL_UP)
PC13.init(PC13.OUT)

while True:
    time.sleep(0.1)
    if key.value() == 0:
        led.value(1)
    else:
        led.value(0)