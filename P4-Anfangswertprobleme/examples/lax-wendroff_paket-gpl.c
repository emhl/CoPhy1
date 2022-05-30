#include <stdio.h>
#include <math.h>

#define N 500
#define S 0.03
#define DX (1.0/N)
#define DT 3.e-3
#define T 3.e0
#define C 1.5	// 1.0:ideal
#define ALPHA (C*DX/DT) 

void init(double *x) {
	int i;
	for(i=0;i<N;i++)
		x[i]=exp(-(i/(double)N-1.0/2.0)*(i/(double)N-1.0/2.0)/(2.0*S*S))*sin(200.0*i/(double)N);
		

}

void print(double *x) {
	int i;
        printf("p [][-1:1] '-' w l\n");
	for(i=0;i<N;i++)
		printf("%d %g\n",i,x[i]);
	printf("e\n");
}

int main() {
	double x[N], tmp[N];

	fprintf(stderr,"ALPHA=%g\n",ALPHA);
	init(x);
	print(x);

	double t;
	int i;
	for(t=0;t<T;t+=DT) {

		for(i=1;i<N-1;i++)
			tmp[i] = x[i] - ALPHA/2.0*( x[i+1]*(1.0-ALPHA) + 2.0*ALPHA*x[i] - x[i-1]*(1.0+ALPHA));
	
		// PBC
		tmp[0] =  0.5*( x[1]*(1.0-ALPHA) + x[N-1]*(1.0+ALPHA));
		tmp[N-1] =  0.5*( x[0]*(1.0-ALPHA) + x[N-2]*(1.0+ALPHA));

		for(i=0;i<N;i++)
			x[i]=tmp[i];	
	
		print(x);
	}
}

