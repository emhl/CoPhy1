#include <stdio.h>

#define T 30.0	// Laufzeit
#define H 0.01	// Zeitschritt
#define OMEGA 1	// Frequenz

int main() {
    double t, x = 0.0, v = 1.0, xp, vp;

    for (t = 0; t <= T; t += H) {
        printf("%g %g %g\n",t,x,v);
        xp = x + H*v;
        vp = v - OMEGA*OMEGA*H*x; 

        x = xp;
        v = vp;
    }
}
