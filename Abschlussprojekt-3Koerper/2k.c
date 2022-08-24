#include <math.h>
#include <stdio.h>

#define TMAX 10
#define H 1.e-3
#define G 1.

// Anfangsbedingungen für Körper 1
#define X1 1.
#define Y1 2.
#define VX1 0.
#define VY1 0.
#define M1 5.

// Anfangsbedingungen für Körper 2
#define X2 2.
#define Y2 -1.
#define VX2 0.
#define VY2 0.
#define M2 4.

// potentielle Energie des Systems
double epot(double x1, double x2, double y1, double y2) {
  return -G * M1 * M2 / sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// kinetische Energie des Systems
double ekin(double vx1, double vy1, double vx2, double vy2) {
  return (M1 * (vx1 * vx1 + vy1 * vy1) + M2 * (vx2 * vx2 + vy2 * vy2)) / 2;
}

#define E epot(X1, X2, Y1, Y2) + ekin(VX1, VY1, VX2, VY2)

// Gravitationskraft zwischen zwei Körpern
double fg(double r2, double m1, double m2) {
  return -G * m1 * m2 /r2;
}

double fgx(double x1, double y1, double x2, double y2, double m1, double m2) {
  double r = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  return fg(r*r, m1, m2) * (x1 - x2) / r;
}

double fgy(double x1, double y1, double x2, double y2, double m1, double m2) {
  double r = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  return fg(r*r, m1, m2) * (y1 - y2) / r;
}

// Position des Massenzentums des Systems
double qm(double q1, double q2, double m1, double m2) {
  return (q1 * m1 + q2 * m2) / (m1 + m2);
}

#define XM qm(X1, X2, M1, M2)
#define YM qm(Y1, Y2, M1, M2)

int main() {

double x1 = X1, x2 = X2, y1 = Y1, y2 = Y2, vx1 = VX1, vx2 = VX2, vy1 = VY1, vy2 = VY2;
double x1n, x2n, y1n, y2n, vx1n, vx2n, vy1n, vy2n;

//double x1v = X1, x2v = X2, y1v = Y1, y2v = Y2, vx1v = VX1, vx2v = VX2, vy1v = VY1, vy2v = VY2;



for (double t = 0; t < TMAX; t += H)
{
  
x1n = x1 + vx1*H + H*H*fgx(x1,y1,x2,y2,M1,M2)/2/M1;
x2n = x2 + vx2*H + H*H*fgx(x2,y2,x1,y1,M2,M1)/2/M2;
y1n = y1 + vy1*H + H*H*fgy(x1,y1,x2,y2,M1,M2)/2/M1;
y2n = y2 + vy2*H + H*H*fgy(x2,y2,x1,y1,M2,M1)/2/M2;

vx1n = vx1 + (fgx(x1,y1,x2,y2,M1,M2)+fgx(x1n,y1n,x2n,y2n,M1,M2))*H/2/M1;
vx2n = vx2 + (fgx(x2,y2,x1,y1,M2,M1)+fgx(x2n,y2n,x1n,y1n,M2,M1))*H/2/M2;
vy1n = vy1 + (fgy(x1,y1,x2,y2,M1,M2)+fgy(x1n,y1n,x2n,y2n,M1,M2))*H/2/M1;
vy2n = vy2 + (fgy(x2,y2,x1,y1,M2,M1)+fgy(x2n,y2n,x1n,y1n,M2,M1))*H/2/M2;


printf("%g %g %g %g %g %g %g\n", x1, y1, x2, y2, t, sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))), ekin(vx1, vy1, vx2, vy2) + epot(x1, x2, y1, y2);

x1 = x1n;
x2 = x2n;
y1 = y1n;
y2 = y2n;
vx1 = vx1n;
vx2 = vx2n;
vy1 = vy1n;
vy2 = vy2n;

}



}