test1: test1.c
	gcc -o $@ test1.c -lm

test1a: test1.c
	gcc -o $@ -O3 test1.c -lm

test1b: test1.c
	#This -ffast-math enables sse optimization
	#prepare, test1 codes works in similar speed.
	gcc -o $@ -O3 -ffast-math test1.c -lm

check: test1 test1a test1b
	./test1
	./test1a
	./test1b

clean:
	rm -f test1 test1a test1b
