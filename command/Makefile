cc = gcc

src = $(wildcard *.c)
target = gpioc


all:$(src)
	gcc $(src) -lgpio -o $(target) 
	chown root:root $(target) 
	chmod 4755 $(target) 

clean:
	-rm $(target)