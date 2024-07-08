import gpioc._softpwm as _pwm
from gpioc.pin import Pin

class Pwm:
    """Base Pulse Width Modulation Output Class"""
    gpio_num = 0
    def __init__(self, gpio:int, *, frequency=500, duty_cycle=0, variable_frequency=False):

        self.gpio_num = gpio
        Pin(gpio).init(Pin.OUT)
        _pwm.set_frequency(self.gpio_num, frequency)
        _pwm.set_duty_cycle(self.gpio_num, duty_cycle)
        _pwm.start(self.gpio_num)
        
    def __init__(self, gpio:Pin, *, frequency=500, duty_cycle=0, variable_frequency=False):

        self.gpio_num = gpio.id
        gpio.init(Pin.OUT)
        _pwm.set_frequency(self.gpio_num, frequency)
        _pwm.set_duty_cycle(self.gpio_num, duty_cycle)
        _pwm.start(self.gpio_num)
        

    def __del__(self):
        self.deinit()

    def __enter__(self):
        return self

    def __exit__(self, t, value, traceback):
        self.deinit()

    def deinit(self):
        _pwm.stop(self.gpio_num)

    @property
    def duty_cycle(self):
        """The PWM's output duty cycle, 16-bit."""
        return _pwm.get_duty_cycle(self.gpio_num)
        
    @duty_cycle.setter
    def duty_cycle(self, duty_cycle):
        _pwm.set_duty_cycle(self.gpio_num, int(duty_cycle))

    @property
    def frequency(self):
        return _pwm.get_frequency(self.gpio_num)

    @frequency.setter
    def frequency(self, frequency):
        _pwm.set_frequency(self.gpio_num, int(frequency))

