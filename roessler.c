// solves Roessler attraktor (Euler)
// \dot X = -Y-Z
// \dot Y = X+aY
// \dot Z = b+(X-c)Z
#include <stdio.h>
#include <zlib.h>

#define A .2
#define B .2
#define C 5.7

#define N 100000
#define H 0.002
#define OUT "roessler.dat.gz"

int main() {
	double x=1.,y=0.,z=0., xn,yn,zn;
	gzFile f=gzopen(OUT,"wb");

	int i;
	for(i=0;i<N;i++) {
		xn = x - H*(y+z);
		yn = y + H*(x+A*y);
		zn = z + H*(B+(x-C)*z);

		x=xn;y=yn;z=zn;

		gzprintf(f,"%g %g %g\n",x,y,z);
	}
	gzclose(f);

	return 0;
}

