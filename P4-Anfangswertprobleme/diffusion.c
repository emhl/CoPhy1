#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>


#define N 500
#define T 20	
#define DT 5.e-3
#define DX 5.e-3
#define D 5.e-3
#define X0 .5
#define T0 0.
#define SIGMA .02
#define ALPHA (D*DT/DX/DX)

double *phin, *phinm1;

//werte für t = 0
double phi_t0(int i){ return exp(-(i*i*DX*DX)/(2*SIGMA*SIGMA));}

//ftcs
double phi_ftcs(double pm1, double p, double pp1){
    return p + ALPHA *(pm1 -2*p + pp1);
}

int main(){
double x=X0,t=T0,phi;
phin=(double *)malloc(2 * (int)N * sizeof(double));
printf("x t phi \n");
// t=0
int j=0;
while(j<2*N){
    phi=phi_t0(j-N);
    phin[j]= phi;
    x = X0 + (j-N)*DX;
    printf("%g %g %g \n", x, t, phi);
    j++;
}

//für nächstens schritt implementieren

while(t<=T){
    printf("\n");
    phinm1 = phin;
    t += DT;
    phin[0]= phi_ftcs(phinm1[0],phinm1[1],phinm1[2]);
    phin[2*N-1]= phi_ftcs(phinm1[2*N-3],phinm1[2*N-2],phinm1[2*N-1]);
    #pragma omp parallel
        for (int k = 1; k < 2*N-1;k++){
            phin[k]= phi_ftcs(phinm1[k-1],phinm1[k],phinm1[k+1]);
        }
    for(int k=0; k < 2*N;k++){
        phi = phin[k];
        x = X0 + (k-N)*DX;
        printf("%g %g %g \n", x, t, phi);
    }
}
}