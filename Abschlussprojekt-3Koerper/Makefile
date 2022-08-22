all: analytisch 2-koerper 3-koerper

analytisch: 2k-ana.c
	gcc 2k-ana.c -lm -o 2k-ana
	./2k-ana > 2k-ana.dat
2-koerper: 2k.c
	gcc 2k.c -lm -o 2k
	./2k > 2k.dat
3-koerper: 3k.c
	gcc 3k.c -lm -o 3k
	./3k > 3k.dat