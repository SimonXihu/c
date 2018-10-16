ALL:libvec.so test_main

libvec.so:vector.o
	gcc -shared $< -o $@
vector.o:vector.c
	gcc $^ -c -fPIC
	
test_main:test_main.c
	gcc $< -I./ -L./ -l vec -o $@
	
.PHONY=clean
clean:
	rm -rf vector.o libvec.so test_main