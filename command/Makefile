cc = gcc

src = $(wildcard *.c)
target = _gpiocommand


all:$(src)
	gcc $(src) -lgpio -o $(target) 
	chown root:root $(target) 
	chmod 4755 $(target) 
	chmod +s $(target) 
	mv ${target} /usr/bin/${target}

clean:
	-rm $(target)