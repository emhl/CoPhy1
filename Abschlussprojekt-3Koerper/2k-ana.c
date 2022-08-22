#include <math.h>
#include <stdio.h>

#define DPHI 1.e-2

// Anfangsbedingungen für Körper 1
#define X1 0.
#define Y1 0.
#define VX1 0.
#define VY1 0.
#define M1 2.

// Anfangsbedingungen für Körper 2
#define X2 .2
#define Y2 0.
#define VX2 0.
#define VY2 1.
#define M2 .5

#define M M1 + M2
#define M_RED M1 *M2 / M

#define L2                                                                     \
  2 * M1 *(X1 * VY1 - Y1 * VX1) * (X1 * VY1 - Y1 * VX1) +                      \
      2 * M2 *(X2 * VY2 - Y2 * VX2) * (X2 * VY2 - Y2 * VX2)

#define G 1.

#define P1 L2 / M1 / M1 / G / M
#define P2 L2 / M2 / M2 / G / M

// potentielle Energie des Systems
double epot(double x1, double x2, double y1, double y2) {
  return -G * M * M_RED / sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// kinetische Energie des Systems
double ekin(double vx1, double vy1, double vx2, double vy2) {
  return (M_RED / 2) * (vx1 * vx1 + vy1 * vy1 + vx2 * vx2 + vy2 * vy2);
}

#define E epot(X1, X2, Y1, Y2) + ekin(VX1, VY1, VX2, VY2)

#define EPSILON1 sqrt(1. + 2. * E * P1 / (M1 * G * M))
#define EPSILON2 sqrt(1. + 2. * E * P2 / (M2 * G * M))

// transformationen zwischen polar und kartesischen koordinaten
double r_transf(double x, double y) { return sqrt(x * x + y * y); }
double phi_transf(double x, double y) { return atan2(y, x); }
double x_transf(double r, double phi) { return r * cos(phi); }
double y_transf(double r, double phi) { return r * sin(phi); }

// erstes Keplersches Gesetz
double r(double phi, double p, double epsilon) {
  return p / (1 + epsilon * cos(phi));
}

// startwerte in karthesischen koordinaten
#define R1 r_transf(X1, Y1)
#define R2 r_transf(X2, Y2)
#define PHI1 phi_transf(X1, Y1)
#define PHI2 phi_transf(X2, Y2)

int main() {
  if (!(0 < EPSILON1 < 1 || 0 < EPSILON2 < 1)) {
    printf("Keine stabile Umlaufbahn möglich");
    printf("Eps1: %g  Eps2: %g", EPSILON1, EPSILON2);
    return 0;
  }
  // printf("%g %g\n", EPSILON1, E);
  for (double k = 0; k < 2 * M_PI; k += DPHI) {
    printf("%g %g %g %g \n", x_transf(r(k, P1, EPSILON1), k),
           y_transf(r(k, P1, EPSILON1), k), x_transf(r(k, P2, EPSILON2), k),
           y_transf(r(k, P2, EPSILON2), k));
    // printf("%g %g %g \n", k, r(k, P1, EPSILON1), r(k, P2, EPSILON2));
  }
}