#include <math.h>
#include <stdio.h>

#define H 1.e-2
#define G 1.

// Anfangsbedingungen für Körper 1
#define X1 0.
#define Y1 0.
#define VX1 0.
#define VY1 0.
#define M1 10

// Anfangsbedingungen für Körper 2
#define X2 10
#define Y2 0.
#define VX2 0.
#define VY2 1
#define M2 1

// Anfangsbedingungen für Körper 3
#define X3 0.
#define Y3 10.
#define VX3 1
#define VY3 0
#define M3 1

// potentielle Energie des Systems
double epot(double x1, double x2, double y1, double y2, double x3, double y3) {
  return -G * M1 * M2 / sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) -
         G * M1 * M3 / sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) -
         G * M2 * M3 / sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
}

// kinetische Energie des Systems
double ekin(double vx1, double vy1, double vx2, double vy2, double vx3,
            double vy3) {
  return (M1 * (vx1 * vx1 + vy1 * vy1) + M2 * (vx2 * vx2 + vy2 * vy2) +
          M3 * (vx3 * vx3 + vy3 * vy3)) /
         2;
}

#define E epot(X1, X2, Y1, Y2, X3, Y3) + ekin(VX1, VY1, VX2, VY2, VX3, VY3)

// Gravitationskraft zwischen zwei Körpern
double fg(double q1, double q2, double m1, double m2) {
  return -G * m1 * m2 / ((q1 - q2) * (q1 - q2));
}

// Position des Massenzentums des Systems
double qm(double q1, double q2, double q3, double m1, double m2, double m3) {
  return (q1 * m1 + q2 * m2 + q3 * m3) / (m1 + m2 + m3);
}

#define XM qm(X1, X2, X3, M1, M2, M3)
#define YM qm(Y1, Y2, Y3, M1, M2, M3)

int main() {}