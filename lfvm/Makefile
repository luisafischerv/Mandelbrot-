mandelbrot: main.o mandelbrot_common.o mandelbrot_serial.o mandelbrot_openmp.o mandelbrot_pthreads1.o
	gcc main.o mandelbrot_common.o mandelbrot_serial.o mandelbrot_openmp.o mandelbrot_pthreads1.o -o mandelbrot -lm -fopenmp -pthread

main.o: main.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -c main.c

mandelbrot_common.o: mandelbrot_common.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -c mandelbrot_common.c

mandelbrot_serial.o: mandelbrot_serial.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -c mandelbrot_serial.c

mandelbrot_openmp.o: mandelbrot_openmp.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -fopenmp -c mandelbrot_openmp.c

mandelbrot_pthreads1.o: mandelbrot_pthreads1.c mandelbrot_common.h
	gcc -Wall -Wextra -O2 -pthread -c mandelbrot_pthreads1.c

run: mandelbrot
	./mandelbrot 800 800 1000 4

clean:
	rm -f *.o mandelbrot *.pgm times.txt

.PHONY: run clean