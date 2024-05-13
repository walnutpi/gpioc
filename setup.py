from setuptools import setup, Extension, find_packages
import glob
import datetime

classifiers = [
    'Development Status :: 3 - Alpha',
    'Intended Audience :: Developers',
    'Topic :: Software Development :: Build Tools',
    'License :: OSI Approved :: MIT License',
    'Programming Language :: Python :: 3',
]

pinctrl_files = glob.glob('libgpio/pinctrl*.c')
softpwm_files = glob.glob('libgpio/*.c')

# 获取当前时间并格式化
now = datetime.datetime.now()
time_str = now.strftime("%y%m%d%H%M")

setup(
    name="gpioc",
    version="1.0_rc7-" + time_str,  # 将时间字符串添加到版本号中，为了自动上传到test.pypi时不用过来改
    author="sc-bin",
    author_email="3335447573@qq.com",
    description="A module to control GPIO",
    platforms=['manylinux'],
    long_description = open('README_PY.md').read(),
    long_description_content_type='text/markdown',
    license          = 'MIT',
    url="https://github.com/sc-bin/gpioc", 
    packages=find_packages(),

    ext_modules = [
                   Extension('gpioc._softpwm', sources=softpwm_files),
                   Extension('gpioc._pinctrl', sources=pinctrl_files),
                   ],
)
