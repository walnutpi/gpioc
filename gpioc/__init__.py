VERSION = '0.1'

import   gpioc._gpioc   as _de
_now_chip = _de.detect()
if _now_chip == _de.CHIP_H616 :
    from gpioc.H616 import *
