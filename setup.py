from setuptools import setup, Extension
from setuptools.command.install import install
import subprocess

classifiers = [
    'Development Status :: 3 - Alpha',
    'Intended Audience :: Developers',
    'Topic :: Software Development :: Build Tools',
    'License :: OSI Approved :: MIT License',
    'Programming Language :: Python :: 3',
]

class CustomInstall(install):
    """自定义安装命令"""
    def run(self):
        # 在安装前编译C代码
        print("Running pre-installation tasks...")
        subprocess.check_call(['make'])
        subprocess.check_call(['make', 'install'])
        super().run()

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
                #    Extension('gpioc._h616', ['chips/h616.c', 'chips/h616_py.c']),
                   Extension('gpioc._softpwm', ['src/softpwm.c', 'src/softpwm_py.c',  'chips/h616.c']),
                #    Extension('gpioc._common', ['src/common.c', 'src/common_py.c']),
                   Extension('gpioc._gpioc', ['src/gpioc_py.c'], libraries=['gpioc']),
                   ],
    cmdclass={
        'install': CustomInstall,
    }
)
