all: numerov shooting

numerov: numerov.c
	gcc numerov.c -lm -o numerov
	./numerov > numerov.dat
	ipython numerov-plot.ipynb

shooting: shooting.c
	gcc shooting.c -lm -o shooting
	./shooting > shooting.dat
