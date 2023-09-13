VERSION = '0.1'

import  gpioc._common as _chips 
_now_chip = _chips.detect()
if _now_chip == _chips.CHIP_H616 :
    from gpioc.H616 import *
