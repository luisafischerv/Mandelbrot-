mandelbrot: main.o mandelbrot_common.o
	gcc main.o mandelbrot_common.o -o mandelbrot -lm

main.o: main.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -c main.c

mandelbrot_common.o: mandelbrot_common.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -c mandelbrot_common.c

mandelbrot_serial.o: mandelbrot_serial.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -c mandelbrot_serial.c

run: mandelbrot
	./mandelbrot 800 800 1000 4

clean:
	rm -f *.o mandelbrot *.pgm times.txt

.PHONY: run clean