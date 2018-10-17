target:libsort_algorithm.so test_main

libsort_algorithm.so:sort_algorithm.o
	gcc -shared $< -o $@
libsort_algorithm.o:sort_algorithm.c
	gcc $^ -c -fPIC
test_main:test_main.c
	gcc $< -I./ -L./ -l sort_algorithm -o $@
	
.PHONT=clean
clean:libsort_algorithm.so sort_algorithm.o test_main
	rm -rf $^