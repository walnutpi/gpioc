cc = gcc

src = $(wildcard *.c)
src := $(filter-out %_py.c, $(src))
target = libgpio.so

all: 
	gcc -shared -fPIC $(src) -o $(target)
install:
	cp  ${target} /usr/lib/

clean:
	-rm $(target)