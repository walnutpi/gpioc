cc = gcc

src = $(wildcard *.c)
target = exe


all:$(src)
	gcc $(src) -lgpio -o $(target) 

clean:
	-rm $(target)