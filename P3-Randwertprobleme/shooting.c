#include <stdio.h>
#include <math.h>

#define H 0.001
#define XMAX 20.0
#define N (XMAX/H)

double *psi;
double F(double x){
    return 0.0;
}

double k2(double E,double x) {
	return x-2*E;
}

double numerov(double E,int save) {
    double x, fnm1=0.0, fn=H, fnp1;
    double y,df;
    int i = 0;

    //rechte seite
    for(x=H;x <= XMAX;x += H) {
		fnp1 = (H*H/12.0*(F(x+H)+10.0*F(x)+F(x-H)) + fn*(2.0-5.0/6.0*H*H*k2(E,x))-fnm1*(1.0+H*H/12.0*k2(E,x-H)))/(1.0+H*H/12.0*k2(E,x+H));
        printf("%g %g\n",x,fn);
        fnm1=fn;
	    fn=fnp1;
    }

    if (save == 1){
        psi[i++] = fn;
    }

}

int main(){
    double E1 = 1.;
    numerov(E1,1);
}