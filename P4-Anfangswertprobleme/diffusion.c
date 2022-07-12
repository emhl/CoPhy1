#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>


#define T 2
#define DT 5.e-4
#define DX 1.e-3
#define D 1.e-3
#define X0 .5
#define T0 0.
#define N 2*X0/DX
#define SIGMA .02
#define ALPHA (D*DT/DX/DX)

double *phin, *phinm1;

//werte für t = 0
double phi_t0(int i){ return exp(-(i*DX-X0)*(i*DX-X0)/(2*SIGMA*SIGMA));}

//ftcs
double phi_ftcs(double pm1, double p, double pp1){
    return p + ALPHA *(pm1 -2*p + pp1);
}

int main(){
double x=X0,t=T0,phi;
phin=(double *)malloc((int)N * sizeof(double));
printf("x t phi \n");
// t=0

for(int j=0;j<N;j++){
    phi=phi_t0(j);
    phin[j]= phi;
    x = j*DX;
    printf("%g %g %g \n", x, t, phi);
}

//für nächstens schritt implementieren

while(t<=T){
    printf("\n");
    phinm1 = phin;
    t += DT;
    phin[0]= phi_ftcs(phinm1[0],phinm1[1],phinm1[2]);
    phin[(int)(N-1)]= phi_ftcs(phinm1[(int)(N-3)],phinm1[(int)(N-2)],phinm1[(int)(N-1)]);
    // #pragma omp parallel
        for (int k = 1; k < N-1;k++){
            phin[k]= phi_ftcs(phinm1[k-1],phinm1[k],phinm1[k+1]);
        }
    for(int k=0; k < N;k++){
        phi = phin[k];
        x = k*DX;
        printf("%g %g %g \n", x, t, phi);
    }
}
}