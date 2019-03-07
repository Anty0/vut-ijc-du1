# Makefile
# Řešení IJC-DU1, příklad a), 9.3.2019
# Autor: Jiří Kuchyňka, xkuchy02, FIT
# Přeloženo: gcc (GCC) 8.2.1 20181127

OPTIMIZATION=-O2
CC = gcc $(OPTIMIZATION)
ARCH = #-m32 # 64 native # TODO: test 32bit
CFLAGS = -g -std=c11 -pedantic $(ARCH) -Wall -Wextra # Debug flags
#CFLAGS = -std=c11 -Wall -pedantic # TODO: Switch to this flags
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
	rm -f *.o primes-alloc primes primes-alloc-i primes-i \
		steg-decode-alloc steg-decode steg-decode-alloc-i steg-decode-i \
		array-test-alloc array-test array-test-alloc-i array-test-i

pack:
	zip xkuchy02.zip *.c *.h .gitignore Makefile


primes-everything: primes-alloc primes primes-alloc-i primes-i

steg-decode-everything: steg-decode-alloc steg-decode steg-decode-alloc-i steg-decode-i

array-test-everything: array-test-alloc array-test array-test-alloc-i array-test-i


primes-alloc: primes-alloc.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

primes: primes.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

primes-alloc-i: primes-alloc.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

primes-i: primes.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


steg-decode-alloc: steg-decode-alloc.o ppm.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

steg-decode: steg-decode.o ppm.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

steg-decode-alloc-i: steg-decode-alloc.o ppm.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

steg-decode-i: steg-decode.o ppm.o bit_array-i.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


array-test-alloc: array-test-alloc.o bit_array.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

array-test: array-test.o bit_array.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

array-test-alloc-i: array-test-alloc.o bit_array-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

array-test-i: array-test.o bit_array-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


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
