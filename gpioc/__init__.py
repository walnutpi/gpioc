VERSION = '0.1'

from gpioc._detect import detect as _detect
import  gpioc._common as _chips 
_now_chip = _detect()
if _now_chip == _chips.CHIP_H616 :
    from gpioc.H616 import *
