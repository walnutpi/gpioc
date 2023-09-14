import gpioc._softpwm as _pwm
import gpioc as _gpio

class PWMOut_father:
    """Base Pulse Width Modulation Output Class"""
    _gpio_num = 0
    _chip = 0 
    def __init__(self, pin, *, frequency=500, duty_cycle=0, variable_frequency=False):
        self._gpio_num = pin.id

        pin.init(pin.OUT)
        _pwm.switch_chip(self._chip)
        _pwm.set_frequency(self._gpio_num, frequency)
        _pwm.set_duty_cycle(self._gpio_num, duty_cycle)
        _pwm.start(self._gpio_num)
        

    def __del__(self):
        self.deinit()

    def __enter__(self):
        return self

    def __exit__(self, t, value, traceback):
        self.deinit()

    def deinit(self):
        _pwm.stop(self._gpio_num)

    @property
    def duty_cycle(self):
        """The PWM's output duty cycle, 16-bit."""
        return _pwm.get_duty_cycle(self._gpio_num)
        
    @duty_cycle.setter
    def duty_cycle(self, duty_cycle):
        _pwm.set_duty_cycle(self._gpio_num, int(duty_cycle))

    @property
    def frequency(self):
        return _pwm.get_frequency(self._gpio_num)

    @frequency.setter
    def frequency(self, frequency):
        _pwm.set_frequency(self._gpio_num, int(frequency))

