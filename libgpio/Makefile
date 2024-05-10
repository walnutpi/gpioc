cc = gcc

src = $(wildcard *.c)
src := $(filter-out %_py.c, $(src))
target = libgpio.so
head_file = gpio.h
all: 
	gcc -shared -fPIC $(src) -o $(target)
install:
	cp  ${target} /usr/lib/
	cp  ${head_file} /usr/include

clean:
	-rm $(target)