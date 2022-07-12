all: diffusion

diffusion: diffusion.c
	gcc diffusion.c -lm -o diff
	./diff > diff.dat
	ipython diff-plot.ipynb
