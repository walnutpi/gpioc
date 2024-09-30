cc = gcc

src = $(wildcard *.c)
target = gpioc-server


all:$(src)
	gcc $(src) -lgpio  -o $(target) 
	chown root:root $(target) 
	chmod 4755 $(target) 
	chmod +s $(target) 
clean:
	-rm $(target)