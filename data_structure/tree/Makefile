ALL:libtree.so test_main
libtree.so:tree.o
	gcc -shared $^ -o $@
tree.o:tree.c
	gcc $< -c -fpic
test_main:test_main.c
	gcc $< -I./ -L./ -l tree -o $@
.PHONY=clean
clean:
	rm -rf test_main libtree.so tree.o