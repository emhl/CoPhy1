// solving diffusion problem using Thomas algorithm
#include <stdio.h>
#include <math.h>

#define N 1000		// x steps
#define T 2.0		// run time
#define DT 5.e-4
#define DX 1.e-3
#define D 1.e-3	// diffusion constant
#define ALPHA (D*DT/DX/DX)

// simplified Thomas algorithm for diffusion problem
void solveThomas(double *b, double *d, double *x) {
	int i;
        for (i = 1; i < N; i++) {
                double m = 1.0/b[i-1];
                b[i] = b[i] - m;
                d[i] = d[i] - m*d[i-1];
        }
 
        x[N-1] = d[N-1]/b[N-1];
 
        for (i = N - 2; i >= 0; i--)
                x[i]=(d[i]-x[i+1])/b[i];
}


void init(double *x) {
	int i;

	double S=0.02;
	for(i=0;i<N;i++) {
		// gaussian
		x[i]=exp(-(i/(double)N-0.5)*(i/(double)N-0.5)/2./S/S);
	
		// step
		/*if(i<N/2)
			x[i]=0;
		else
			x[i]=S;
		*/
		// barrier
		/*if(i>N/3.0 && i< 2.0*N/3.0)
			x[i]=S;
		else
			x[i]=0;
		*/
	}
}

int main() {
	double x[N], b[N], d[N];
	init(x);

	int i;
	double t=0;
	for(t=0;t<T;t+=DT) {
		// print out
	        // printf("p [][0:1] '-' w l t ''\n");
			printf("x t phi \n");
	
		for(i=0;i<N;i++)
			printf("%g %g %g\n",i*DX,t,x[i]);
		// printf("e\n");

		// initialize coefficients
		for(i=0;i<N;i++) 
			b[i]=-2.*(1.+1./ALPHA);
		for(i=1;i<N-1;i++)
			d[i]= - x[i-1] - x[i+1] + 2.*(1.-1./ALPHA)*x[i];
		d[0]=2.*(1.-1./ALPHA)*x[0]-x[1];
		d[N-1]=2.*(1.-1./ALPHA)*x[N-1]-x[N-2];
		
		solveThomas(b,d,x);
	}
	
	return 0;
}
