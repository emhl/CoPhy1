#include <stdio.h>
#include <math.h>

#define N 500

main() {
	double start=3.0, end=4.0;
	double dr=(end-start)/(3*N), x0=0.5;

	FILE *LFILE;
	LFILE=fopen("feigel.dat","w+");
	for(double r=start;r<=end;r+=dr) {
		double x=x0,l=0.0;
		for(int i=0;i<2*N;i++) {
			x= r*x*(1-x);
			if(i>N) {
				l += log(fabs(r*(1.0-2.0*x)));
				printf("%g %g\n",r,x);
			}
		}
		fprintf(LFILE,"%g %g\n",r,l/N);
	}
	fclose(LFILE);
}
