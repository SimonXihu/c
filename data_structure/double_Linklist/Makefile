ALL:libdouble_linklist.so test_main

libdouble_linklist.so:double_linklist.o
	gcc -shared $^ -o $@
double_linklist.o:double_linklist.c
	gcc $< -c -fpic
test_main:test_main.c
	gcc $< -I./ -L./ -l double_linklist -o $@
.PHONY=clean
clean:
	rm -rf test_main libdouble_linklist.so double_linklist.o