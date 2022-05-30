#include <stdio.h>

#define T 30.0	// Laufzeit
#define H 0.01	// Zeitschritt
#define OMEGA2 1	// Frequenz

int main() {
    double t, k1, k2, x=0.0, v=1.0,xn,vn,c, E0,Ediff=0;
    E0 = (v*v + OMEGA2*x*x)/2.0;
	for (t = 0; t <= T; t += H){
        printf("%g %g %g %g\n",t,x,v,Ediff);
        c = 1 - (H*H*OMEGA2)/2.0;
        xn = x*c + v*H;
        vn = v*c - x*H*OMEGA2;
        x = xn;
        v = vn;
        Ediff = (v*v + OMEGA2*x*x)/2.0 - E0;
	}

}
