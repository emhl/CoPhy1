// solves Lorenz attraktor (Euler)
// \dot X = a(Y-X)
// \dot Y = X(b-Z)+Y
// \dot Z = XY-cZ
#include <stdio.h>

#define A 10.
#define B 28.
#define C (8./3.)

#define N 10000
#define H 0.01

int main() {
	double x=1.,y=0.,z=0., xn,yn,zn;

	int i;
	for(i=0;i<N;i++) {
		xn = x + H*A*(y-x);
		yn = y + H*(x*(B-z)+y);
		zn = z + H*(x*y-C*z);

		x=xn;y=yn;z=zn;

		printf("%g %g %g\n",x,y,z);
	}
}

