from gpioc.chips.K230 import *
import time
key = IO21
led = IO52
key.init(key.IN,key.PULL_UP)
led.init(led.OUT)


while True:
    time.sleep(0.1)
    if key.value() == 0:
        led.value(1)
    else:
        led.value(0)