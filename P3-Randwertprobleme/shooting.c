#include <stdio.h>
#include <math.h>
#include <stdlib.h>


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

double numerov(double E, int save) {
    double x, fnm1=0.0, fn=H, fnp1, ret=0;
    double y,df;
    int i = 0;

    //rechte seite
    for(x=H;x <= XMAX;x += H) {
		fnp1 = (H*H/12.0*(F(x+H)+10.0*F(x)+F(x-H)) + fn*(2.0-5.0/6.0*H*H*k2(E,x))-fnm1*(1.0+H*H/12.0*k2(E,x-H)))/(1.0+H*H/12.0*k2(E,x+H));
        if (save ==1){
            printf("%g %g\n",x,fn);
        }

        fnm1=fn;
	    fn=fnp1;
        psi[i++] = fn;
    }

    
    for(int x=N - 100 ;x < N;x++) {
        // ret += fabs(psi[x]);
        ret += psi[x];
        
    }

    return ret;
}

int main(){
    psi = (double *)malloc(2*(int)N*sizeof(double));
    double E0=0,E1 = 2.,Ex,tmp;
    // numerov(E1);
    // printf("%g %g\n", numerov(E1),0.);
    do {
		Ex = (E1+E0)/2.0;
		// bisection (non continous !)
		tmp = numerov(Ex,0);
	    if(tmp*numerov(E0,0)>0)
			E0=Ex;
	    else
		    E1=Ex;
	} while (fabs((E1-E0)/E0)>1.e-14);
    numerov(Ex,1);

}