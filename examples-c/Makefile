cc = gcc

src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src) )

%:%.c
	$(cc)  $< -o $@     -lproject 

all:$(target)

clean:
	-rm $(target)