#include <stdio.h>
#include <math.h>

#define H 0.001
#define XMAX 20.0
#define N (XMAX/H)
#define EPS0 1


double F(double x){
    return -x/(8*M_PI*EPS0)*exp(-x);
}

double k2(double x) {
	return 0.0;
}

int main() {
    double x, fnm1=0.0, fn=H, fnp1;
    double y,steig;

    //unkorrigiert
    for(x=H;x <= XMAX;x += H) {
		fnp1 = (H*H/12.0*(F(x+H)+10.0*F(x)+F(x-H)) + fn*(2.0-5.0/6.0*H*H*k2(x))-fnm1*(1.0+H*H/12.0*k2(x-H)))/(1.0+H*H/12.0*k2(x+H));
        // printf("%g %g\n",x,fn);
        fnm1=fn;
	    fn=fnp1;
    }
    steig = (fn-fnm1)/H;

      // nochmal laufen lassen während man den linearen term abzieht
    fnm1=0.0;
    fn=H;
    for(x=H;x <= XMAX;x += H) {
		fnp1 = (H*H/12.0*(F(x+H)+10.0*F(x)+F(x-H)) + fn*(2.0-5.0/6.0*H*H*k2(x))-fnm1*(1.0+H*H/12.0*k2(x-H)))/(1.0+H*H/12.0*k2(x+H));
        y = (fn - x*steig)/.08; //eichung 
        printf("%g %g %g\n",x,y,fnp1);
        fnm1=fn;
	    fn=fnp1;
    } 
}