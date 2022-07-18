all: diff cnv

diff: diffusion.c
	gcc diffusion.c -lm -o diff
	./diff > diff.dat
	ipython diff-plot.ipynb

cnv: examples/diffusion-gpl.c
	gcc examples/diffusion-gpl.c -lm -o cnv
	./cnv > cnv.dat
	ipython cnv-plot.ipynb

	