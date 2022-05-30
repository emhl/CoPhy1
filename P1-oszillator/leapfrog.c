#include <stdio.h>
#include <stdlib.h>


#define H 0.01 // Zeitschritt
#define Omega 1 // Frequenz
#define T 30.0
    
    /*Harmonischer Oszillator m a(t) + k x(t) = 0 */
    int main() {
        double t = 0;
        double x = 0;
        double v = 1.0;
        double E0 = (v * v + Omega * Omega * x * x) / 2.0;
        double xn, vn, E, Ediff;
        
        for(t = 0; t < T; t += H){
        vn = v - Omega * Omega * H * x;
        xn = x + H * vn;
        E = (v * v + Omega * Omega * x * x) / 2.0;
        Ediff = E - E0;
        
        printf("%g %g %g %g\n" ,t,x,v,Ediff);
        x = xn;
        v = vn;
        }
        
        
        

    return 0;
    }
