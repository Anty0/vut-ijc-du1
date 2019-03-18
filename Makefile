# Makefile
# Řešení IJC-DU1, příklad a), 9.3.2019
# Autor: Jiří Kuchyňka, xkuchy02, FIT
# Přeloženo: gcc (GCC) 8.2.1 20181127

OPTIMIZATION=-O2
CC = gcc $(OPTIMIZATION)
#ARCH = -m32
#CFLAGS = -g -std=c11 -pedantic $(ARCH) -Wall -Wextra # Debugging flags
CFLAGS = -std=c11 -Wall -pedantic
LIBS = -lm

.PHONY: all
all: primes primes-i steg-decode

.PHONY: everything
everything: primes-everything steg-decode-everything array-test-everything

.PHONY: run
run: primes primes-i
	bash -c "ulimit -s 131072 && time ./primes"
	bash -c "ulimit -s 131072 && time ./primes-i"

.PHONY: clean
clean:
	rm -f *.o primes-alloc primes primes-alloc-i primes-i \
		steg-decode-alloc steg-decode steg-decode-alloc-i steg-decode-i \
		array-test-alloc array-test array-test-alloc-i array-test-i

pack:
	zip xkuchy02.zip *.c *.h Makefile


primes-everything: primes-alloc primes primes-alloc-i primes-i

steg-decode-everything: steg-decode-alloc steg-decode steg-decode-alloc-i steg-decode-i

array-test-everything: array-test-alloc array-test array-test-alloc-i array-test-i


primes: primes.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

primes-alloc: primes-alloc.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

primes-i: primes-i.o bit_array-i.o eratosthenes-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

primes-alloc-i: primes-alloc-i.o bit_array-i.o eratosthenes-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


steg-decode: steg-decode.o ppm.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

steg-decode-alloc: steg-decode-alloc.o ppm.o bit_array.o eratosthenes.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

steg-decode-i: steg-decode-i.o ppm.o bit_array-i.o eratosthenes-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

steg-decode-alloc-i: steg-decode-alloc-i.o ppm.o bit_array-i.o eratosthenes-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


array-test: array-test.o bit_array.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

array-test-alloc: array-test-alloc.o bit_array.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

array-test-i: array-test-i.o bit_array-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

array-test-alloc-i: array-test-alloc-i.o bit_array-i.o error.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


primes.o: primes.c bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ $(CFLAGS)

primes-alloc.o: primes.c bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC $(CFLAGS)

primes-i.o: primes.c bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_INLINE $(CFLAGS)

primes-alloc-i.o: primes.c bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC -DUSE_INLINE $(CFLAGS)


steg-decode.o: steg-decode.c ppm.h bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ $(CFLAGS)

steg-decode-alloc.o: steg-decode.c ppm.h bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC $(CFLAGS)

steg-decode-i.o: steg-decode.c ppm.h bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_INLINE $(CFLAGS)

steg-decode-alloc-i.o: steg-decode.c ppm.h bit_array.h eratosthenes.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC -DUSE_INLINE $(CFLAGS)


array-test.o: array-test.c bit_array.h error.h
	$(CC) -c $< -o $@ $(CFLAGS)

array-test-alloc.o: array-test.c bit_array.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC $(CFLAGS)

array-test-i.o: array-test.c bit_array.h error.h
	$(CC) -c $< -o $@ -DUSE_INLINE $(CFLAGS)

array-test-alloc-i.o: array-test.c bit_array.h error.h
	$(CC) -c $< -o $@ -DUSE_ALLOC -DUSE_INLINE $(CFLAGS)


bit_array.o: bit_array.c bit_array.h error.h
	$(CC) -c $< -o $@ $(CFLAGS)

bit_array-i.o: bit_array.c bit_array.h error.h
	$(CC) -c $< -o $@ -DUSE_INLINE $(CFLAGS)


eratosthenes.o: eratosthenes.c eratosthenes.h bit_array.h error.h
	$(CC) -c $< -o $@ $(CFLAGS)

eratosthenes-i.o: eratosthenes.c eratosthenes.h bit_array.h error.h
	$(CC) -c $< -o $@ -DUSE_INLINE $(CFLAGS)


error.o: error.c error.h
	$(CC) -c $< -o $@ $(CFLAGS)


ppm.o: ppm.c ppm.h error.h
	$(CC) -c $< -o $@ $(CFLAGS)
