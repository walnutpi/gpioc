cc = gcc
target = libgpio
head_file = gpio.h

src = $(wildcard *.c)
src := $(filter-out %_py.c, $(src))
objects = $(patsubst %.c,%.o,$(src))

all: $(target).a $(target).so

$(target).a:  $(objects)
	ar -rc $@ $^

$(target).so:  $(src)
	gcc -fPIC -shared $^ -o $@


install:all
	cp  $(target).a  $(target).so /usr/lib/
	cp  ${head_file} /usr/include

clean:
	-rm /usr/include/${head_file}
	-rm $(objects)
	-rm $(target).a $(target).so 