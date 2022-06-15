all: magnetpendel feld vier

magnetpendel: magnetpendel.c
	gcc magnetpendel.c -lm -o magnetpendel
	./magnetpendel > magnetpendel.dat

feld: mp-field.c
	gcc mp-field.c -lm -fopenmp -o mp-field -O3
	./mp-field > mp-field.dat

vier: vier-mag.c
	gcc vier-mag.c -lm -fopenmp -o vier-mag -O3
	./vier-mag > vier.dat
