ALL:list.o liblist.so main

list.o:list.c
	gcc -c $< -fpic
liblist.so:list.o
	gcc -shared $< -o $@
main:main.c
	gcc $< -I./ -L./ -l list -o $@
.PHONY=clean
clean:
	rm -rf list.o liblist.so main
