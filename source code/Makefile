INC="./inc"
FLAGS=-I$(INC)
OMPFLAG=-fopenmp
MATH=-lm
CC=gcc

all: main


main: main.c quick_sort.c merge_sort.c bitonic_sort.c metrics.c Run.c alloc.c
	$(CC) main.c quick_sort.c merge_sort.c bitonic_sort.c metrics.c -o main Run.c alloc.c $(OMPFLAG) $(MATH)
	
clean:
	rm main
	
