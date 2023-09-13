from setuptools import setup, Extension

classifiers = [
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
    ]

setup(
    name="gpioc",
    version="0.1",
    author="sc-bin",
    author_email="3335447573@qq.com",
    description="A module to control GPIO",
    long_description = open('README.md').read(),
    license          = 'MIT',
    url="https://github.com/sc-bin/gpioc", 
    packages=['gpioc'],
    ext_modules = [
                   Extension('gpioc._h616', ['chips/h616.c', 'chips/h616_py.c', 'src/common.c']),
                   Extension('gpioc._softpwm', ['src/softpwm.c', 'src/softpwm_py.c',  'chips/h616.c']),
                   Extension('gpioc._common', ['src/common.c']),
                   ],


)