#include <stdio.h>
#include <complex.h>

#define MAX 1000
#define N 100

int punkt(complex c) {
	complex z=0;
	int i=0;

	while (cabs(z) < MAX && i < N) {
		z = z*z + c;
		i++;
	}
	
	return i;
}

int main() {
	double a,b;

	for(a=-2;a<1;a+=0.002) {
	for(b=-1;b<1;b+=0.002) {
		complex c=a+I*b;
		int i=punkt(c);
		printf("%g %g %d\n",a,b,i);
	}
	printf("\n");
	}
}
