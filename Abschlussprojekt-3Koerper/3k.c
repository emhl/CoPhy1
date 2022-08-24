#include <math.h>
#include <stdio.h>

#define TMAX 10
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
double epot(double x1, double x2, double x3, double y1, double y2, double y3) {
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
double fg(double r2, double m1, double m2) { return -G * m1 * m2 / r2; }

double fgx(double x1, double y1, double x2, double y2, double m1, double m2) {
  double r = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  return fg(r * r, m1, m2) * (x1 - x2) / r;
}

double fgy(double x1, double y1, double x2, double y2, double m1, double m2) {
  double r = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  return fg(r * r, m1, m2) * (y1 - y2) / r;
}

// Position des Massenzentrums des Systems
double qm(double q1, double q2, double q3, double m1, double m2, double m3) {
  return (q1 * m1 + q2 * m2 + q3 * m3) / (m1 + m2 + m3);
}

#define XM qm(X1, X2, X3, M1, M2, M3)
#define YM qm(Y1, Y2, Y3, M1, M2, M3)

int main() {
  double x1 = X1, y1 = Y1, vx1 = VX1, vy1 = VY1;
  double x2 = X2, y2 = Y2, vx2 = VX2, vy2 = VY2;
  double x3 = X3, y3 = Y3, vx3 = VX3, vy3 = VY3;

  double x1n, y1n, vx1n, vy1n;
  double x2n, y2n, vx2n, vy2n;
  double x3n, y3n, vx3n, vy3n;

  for (double t = 0; t < TMAX; t += H) {

    x1n = x1 + vx1 * H + H * H * fgx(x1, y1, x2, y2, M1, M2) / 2 / M1 +
          H * H * fgx(x1, y1, x3, y3, M1, M3) / 2 / M1;
    x2n = x2 + vx2 * H + H * H * fgx(x2, y2, x1, y1, M2, M1) / 2 / M2 +
          H * H * fgx(x2, y2, x3, y3, M2, M3) / 2 / M2;
    x3n = x3 + vx3 * H + H * H * fgx(x3, y3, x1, y1, M3, M1) / 2 / M3 +
          H * H * fgx(x3, y3, x2, y2, M3, M2) / 2 / M3;

    y1n = y1 + vy1 * H + H * H * fgy(x1, y1, x2, y2, M1, M2) / 2 / M1 +
          H * H * fgy(x1, y1, x3, y3, M1, M3) / 2 / M1;
    y2n = y2 + vy2 * H + H * H * fgy(x2, y2, x1, y1, M2, M1) / 2 / M2 +
          H * H * fgy(x2, y2, x3, y3, M2, M3) / 2 / M2;
    y3n = y3 + vy3 * H + H * H * fgy(x3, y3, x1, y1, M3, M1) / 2 / M3 +
          H * H * fgy(x3, y3, x2, y2, M3, M2) / 2 / M3;

    vx1n =
        vx1 + (fgx(x1, y1, x2, y2, M1, M2) + fgx(x1n, y1n, x2n, y2n, M1, M2) +
               fgx(x1, y1, x3, y3, M1, M3) + fgx(x1n, y1n, x3n, y3n, M1, M3)) /
                  2 / M1 * H;
    vx2n =
        vx2 + (fgx(x2, y2, x1, y1, M2, M1) + fgx(x2n, y2n, x1n, y1n, M2, M1) +
               fgx(x2, y2, x3, y3, M2, M3) + fgx(x2n, y2n, x3n, y3n, M2, M3)) /
                  2 / M2 * H;
    vx3n =
        vx3 + (fgx(x3, y3, x1, y1, M3, M1) + fgx(x3n, y3n, x1n, y1n, M3, M1) +
               fgx(x3, y3, x2, y2, M3, M2) + fgx(x3n, y3n, x2n, y2n, M3, M2)) /
                  2 / M3 * H;

    vy1n =
        vy1 + (fgy(x1, y1, x2, y2, M1, M2) + fgy(x1n, y1n, x2n, y2n, M1, M2) +
               fgy(x1, y1, x3, y3, M1, M3) + fgy(x1n, y1n, x3n, y3n, M1, M3)) /
                  2 / M1 * H;
    vy2n =
        vy2 + (fgy(x2, y2, x1, y1, M2, M1) + fgy(x2n, y2n, x1n, y1n, M2, M1) +
               fgy(x2, y2, x3, y3, M2, M3) + fgy(x2n, y2n, x3n, y3n, M2, M3)) /
                  2 / M2 * H;
    vy3n =
        vy3 + (fgy(x3, y3, x1, y1, M3, M1) + fgy(x3n, y3n, x1n, y1n, M3, M1) +
               fgy(x3, y3, x2, y2, M3, M2) + fgy(x3n, y3n, x2n, y2n, M3, M2)) /
                  2 / M3 * H;

    printf("%g %g %g %g %g %g %g %g %g\n", x1, y1, x2, y2, x3, y3, t,
           sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))),
        ekin(vx1, vy1, vx2, vy2, vx3, vy3) + epot(x1, x2, x3, y1, y2, y3);

    x1 = x1n, x2 = x2n, x3 = x3n;
    y1 = y1n, y2 = y2n, y3 = y3n;
    vx1 = vx1n, vx2 = vx2n, vx3 = vx3n;
    vy1 = vy1n, vy2 = vy2n, vy3 = vy3n;
  }
}