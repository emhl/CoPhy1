all: diff cnv

diff: diffusion.c
	gcc diffusion.c -lm -o diff
	./diff > diff.dat
	ipython diff-plot.ipynb
	# gnuplot: plot "diff.dat" u 1:2:3 lc pal
cnv: examples/diffusion-gpl.c
	gcc examples/diffusion-gpl.c -lm -o cnv
	./cnv > cnv.dat
	ipython cnv-plot.ipynb
	# gnuplot: plot "cnv.dat" u 1:2:3 lc pal
