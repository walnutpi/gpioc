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
with open('version', 'r') as file:
    version_str = file.read().strip()
setup(
    name="gpioc",
    version=version_str,
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
