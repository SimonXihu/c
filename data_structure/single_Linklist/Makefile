ALL:liblinklist.so test_main

liblinklist.so:linklist.o
	gcc -shared $< -o $@
linklist.o:linklist.c
	gcc $< -c -fPIC
test_main:test_main.c
	gcc $< -I./ -L./ -l linklist -o $@
.PHONY=clean
clean:
	rm -rf test_main liblinklist.so linklist.o