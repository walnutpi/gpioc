from setuptools import setup, Extension, find_packages
import glob
import datetime

classifiers = [
    "Development Status :: 3 - Alpha",
    "Intended Audience :: Developers",
    "Topic :: Software Development :: Build Tools",
    "License :: OSI Approved :: MIT License",
    "Programming Language :: Python :: 3",
]

# 获取所有源文件
all_source_files = glob.glob("libgpio/pinctrl/**/*.c", recursive=True)

pinctrl_main_file = ["libgpio/pinctrl/pinctrl_py.c"]
softpwm_main_file = ["libgpio/pinctrl/softpwm_py.c"]

other_files = [
    f
    for f in all_source_files
    if f not in pinctrl_main_file and f not in softpwm_main_file
]

pinctrl_files = glob.glob("libgpio/pinctrl/**/*.c", recursive=True)
softpwm_files = glob.glob("libgpio/pinctrl/**/*.c", recursive=True)
with open("version", "r") as file:
    version_str = file.read().strip()
setup(
    name="gpioc",
    version=version_str,
    author="sc-bin",
    author_email="3335447573@qq.com",
    description="A module to control GPIO",
    platforms=["manylinux"],
    long_description=open("README_PY.md").read(),
    long_description_content_type="text/markdown",
    license="MIT",
    url="https://github.com/sc-bin/gpioc",
    packages=find_packages(),
    ext_modules=[
        Extension("gpioc._pinctrl", sources=pinctrl_main_file + other_files),
        Extension("gpioc._softpwm", sources=softpwm_main_file + other_files),
    ],
)
