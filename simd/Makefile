.PHONY: all check check2 clean

all: test1 test1a test1b test2 test3

test1: test1.c
	gcc -o $@ test1.c -lm

test1a: test1.c
	gcc -o $@ -O3 test1.c -lm

#This -ffast-math enables sse optimization
#prepare, test1 codes works in similar speed.
test1b: test1.c
	gcc -o $@ -O3 -ffast-math test1.c -lm

test2: test2.c
	gcc -o $@ test2.c -mavx -lm

test3: test3.c
	gcc -o $@ test3.c -mavx512f -lm

check: test1 test1a test1b
	./test1
	./test2
	./test3

check2: test1a test1b
	./test1a
	./test1b

clean:
	rm -f test1 test1a test1b test2 test3
