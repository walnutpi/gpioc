from setuptools import setup, Extension, find_packages
import glob
classifiers = [
    'Development Status :: 3 - Alpha',
    'Intended Audience :: Developers',
    'Topic :: Software Development :: Build Tools',
    'License :: OSI Approved :: MIT License',
    'Programming Language :: Python :: 3',
]

pinctrl_files = glob.glob('libgpio/pinctrl*.c')
softpwm_files = glob.glob('libgpio/*.c')

setup(
    name="gpioc",
    version="1.0",
    author="sc-bin",
    author_email="3335447573@qq.com",
    description="A module to control GPIO",
    long_description = open('README.md').read(),
    license          = 'MIT',
    url="https://github.com/sc-bin/gpioc", 
    packages=find_packages(),

    ext_modules = [
                   Extension('gpioc._softpwm', sources=softpwm_files),
                   Extension('gpioc._pinctrl', sources=pinctrl_files),
                   ],

)
