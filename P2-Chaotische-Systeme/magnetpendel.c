#include <stdio.h>
#include <math.h>

#define T 300.0	// Laufzeit
#define H 0.01	// Zeitschritt/m
#define X0 1. //Startwert x
#define Y0 0. // Startwert y
#define Z0 .25 // Startwert z
#define K .5	// federkonstante k
#define G .1 // Dämpfung gamma
#define V0 0. //Startgeschwindigkeit
#define M 1. //masse

//magnet koordinaten
#define PX1 1.
#define PY1 0.
#define PX2 -0.5
#define PY2 0.5/sin(3.)
#define PX3 -0.5
#define PY3 -0.5/sin(3.)



int main() {
    double t,xl=X0,yl=Y0, x,y, vx,vy,xn,yn,fx=0,fy=0, E;
    double dx1,dy1,dx2,dy2,dx3,dy3,fx1,fy1,fx2,fy2,fx3,fy3;
    x = xl + H*V0;
    y = yl + H*V0;
    vx = V0 - K/M*H*x; 
    vy = V0 - K/M*H*x; // Euler metheode für ersten schritt
    // E = (v*v + K/M*x*x)/2.0;
	for (t = H; t <= T; t += H){
        printf("%g %g %g\n",t,x,y);

        dx1 = x - PX1;//first magnet
        dy1 = y - PY1;
        fx1 = dx1 / pow((fabs(dx1) + fabs(dy1) + Z0),3);
        fy1 = dy1 / pow((fabs(dx1) + fabs(dy1) + Z0),3);

        dx2 = x - PX2;//seccond magnet
        dy2 = y - PY2;
        fx2 = dx2 / pow((fabs(dx2) + fabs(dy2) + Z0),3);
        fy2 = dy2 / pow((fabs(dx2) + fabs(dy2) + Z0),3);

        dx3 = x - PX3;//third magnet
        dy3 = y - PY3;
        fx3 = dx3 / pow((fabs(dx3) + fabs(dy3) + Z0),3);
        fy3 = dy3 / pow((fabs(dx3) + fabs(dy3) + Z0),3);

        fx = fx1 + fx2 + fx3;
        fy = fy1 + fy2 + fy3;


        xn = 1./(2.+G/M*H) * (2.*H*H*fx + 2.*x*(2. - H*H*K/M) + xl*(G/M*H-2.));
        yn = 1./(2.+G/M*H) * (2.*H*H*fy + 2.*y*(2. - H*H*K/M) + yl*(G/M*H-2.));


        xl = x;
        x = xn;
        yl = y;
        y = yn;

	}
}
