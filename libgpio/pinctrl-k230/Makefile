cc = gcc
target = exe

src = $(wildcard *.c)
src := $(filter-out %_py.c, $(src))
objects = $(patsubst %.c,%.o,$(src))

all: $(target)

$(target):  $(objects)
	gcc -fPIC  $^ -o $@


clean:
	-rm $(target) $(objects)