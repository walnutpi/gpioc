cc = gcc

src = $(wildcard *.c)
target = _gpiocommand


all:$(src)
	gcc $(src) -lgpio -o $(target) 
	chown root:root $(target) 
	chmod 4755 $(target) 
	chmod +s $(target) 
	cp ${target} /usr/bin

clean:
	-rm $(target)