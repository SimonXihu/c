src=$(wildcard ./*.c)
target=$(patsubst %.c,%,$(src))

all:$(target)

%:%.c
	gcc -lpthread $< -o $@

.PHONY=clean
clean:$(target)
	rm -rf $(target)

