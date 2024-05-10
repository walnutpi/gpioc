cc = gcc

src = $(wildcard *.c)
target = libgpio.so

all: 
	gcc -shared -fPIC $(src) -o $(target)
install:
	cp  ${target} /usr/lib/

clean:
	-rm $(target)