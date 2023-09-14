cc = gcc

src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src) )

%:%.c
	$(cc)  $< -o $@   -L../  -lproject -static

all:$(target)

clean:
	-rm $(target)