# Makefile
# Řešení IJC-DU1, příklad a), 9.3.2019
# Autor: Jiří Kuchyňka, xkuchy02, FIT
# Přeloženo: gcc (GCC) 8.2.1 20181127

OPTIMIZATION=-O2
CC = gcc $(OPTIMIZATION)
ARCH = #-m32 # 64 native
CFLAGS = -std=c11 -pedantic $(ARCH) -Wall -Wextra
#CFLAGS = -std=c11 -Wall -pedantic
LIBS = -lm

.PHONY: all
all: primes primes-i steg-decode

.PHONY: everything
everything: primes-everything steg-decode-everything array-test-everything

.PHONY: run
run: primes primes-i
	bash -c "time ./primes"
	bash -c "time ./primes-i"

.PHONY: clean
clean:
	rm -f *.o primes primes-local primes-i primes-local-i \
		steg-decode steg-decode-local steg-decode-i steg-decode-local-i \
		array-test array-test-local array-test-i array-test-local-i


primes-everything: primes primes-local primes-i primes-local-i

steg-decode-everything: steg-decode steg-decode-local steg-decode-i steg-decode-local-i

array-test-everything: array-test array-test-local array-test-i array-test-local-i


primes: primes-alloc.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

primes-local: primes.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

primes-i: primes-alloc.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

primes-local-i: primes.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)


steg-decode: steg-decode-alloc.o ppm.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

steg-decode-local: steg-decode.o ppm.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

steg-decode-i: steg-decode-alloc.o ppm.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

steg-decode-local-i: steg-decode.o ppm.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS)


array-test: array-test-alloc.o bit_array.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

array-test-local: array-test.o bit_array.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

array-test-i: array-test-alloc.o bit_array-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS)

array-test-local-i: array-test.o bit_array-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS)


primes.o: primes.c bit_array.h eratosthenes.h error.h
	$(CC) -c $< $(CFLAGS)

primes-alloc.o: primes.c bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC $(CFLAGS)


steg-decode.o: steg-decode.c ppm.h bit_array.h eratosthenes.h error.h
	$(CC) -c $< $(CFLAGS)

steg-decode-alloc.o: steg-decode.c ppm.h bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC $(CFLAGS)


array-test.o: array-test.c bit_array.h error.h
	$(CC) -c $< $(CFLAGS)

array-test-alloc.o: array-test.c bit_array.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC $(CFLAGS)


bit_array.o: bit_array.c bit_array.h error.h
	$(CC) -c $< $(CFLAGS)

bit_array-i.o: bit_array.c bit_array.h error.h
	$(CC) -c $< -o $@ -DUSE_INLINE $(CFLAGS)


eratosthenes.o: eratosthenes.c eratosthenes.h bit_array.h error.h
	$(CC) -c $< $(CFLAGS)


error.o: error.c error.h
	$(CC) -c $< $(CFLAGS)


ppm.o: ppm.c ppm.h error.h
	$(CC) -c $< $(CFLAGS)
