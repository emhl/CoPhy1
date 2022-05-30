// solving time-dependent Schroedinger eqn using Thomas algorithm
#include <stdio.h>
#include <math.h>
#include <complex.h>

#define N 1000		// x steps
#define T 2.e-2		// run time
#define DT 1.e-5
#define DX 1.e-3
#define K 100.0

// simplified Thomas algorithm for diffusion problem
void solveThomas(complex *b, complex *d, complex *psi) {
	int i;
        for (i = 1; i < N; i++) {
                complex m = 1.0/b[i-1];
                b[i] = b[i] - m;
                d[i] = d[i] - m*d[i-1];
        }
 
        psi[N-1] = d[N-1]/b[N-1];
 
        for (i = N - 2; i >= 0; i--)
                psi[i]=(d[i]-psi[i+1])/b[i];
}


void init(complex *psi) {
	int i;

	double S=0.02;
	for(i=0;i<N;i++) {
		// gaussian
		psi[i]=cexp(I*K*(i/(double)N-0.5))*exp(-(i/(double)N-0.5)*(i/(double)N-0.5)/2./S/S);
	}
}

double V(i) {
	// harmonic
	return 0.2*(i-N/2.)*(i-N/2.);
}

int main() {
	complex psi[N], b[N], d[N];
	init(psi);

	int i;
	double t;
	for(t=0;t<T;t+=DT) {
		// print out
	        printf("p [][0:1] '-' w l\n");
		for(i=0;i<N;i++)
			printf("%d %g\n",i,sqrt(creal(psi[i])*creal(psi[i]) + cimag(psi[i])*cimag(psi[i])));
		printf("e\n");
		// delay
		for(i=0;i<5000000;i++);


		// initialize coefficients
		for(i=0;i<N;i++) 
			b[i]=2.*(DX*DX*(2.0*I/DT - V(i)) - 1.0);
		for(i=1;i<N-1;i++)
			d[i]= - psi[i-1] - psi[i+1] + 2.*(DX*DX*(2.*I/DT + V(i)) + 1.0)*psi[i];
		d[0]=2.*(DX*DX*(2.0*I/DT + V(i)) + 1.0)*psi[0] - psi[1];
		d[N-1]=2.*(DX*DX*(2.0*I/DT + V(i)) + 1.0)*psi[N-1] - psi[N-2];
		
		solveThomas(b,d,psi);
	}
	
	return 0;
}
