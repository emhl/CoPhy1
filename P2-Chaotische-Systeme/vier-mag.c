#include <math.h>
#include <omp.h>
#include <stdio.h>

#define T 300.0 // Laufzeit
#define H 0.01  // Zeitschritt/m
#define Z0 .25  // Startwert z
#define K .5    // federkonstante k
#define G .1    // Dämpfung gamma
#define V0 0.   // Startgeschwindigkeit
#define M 1.    // masse

// magnet koordinaten
#define PX1 .5
#define PY1 .5
#define PX2 .5
#define PY2 -0.5
#define PX3 -0.5
#define PY3 -0.5
#define PX4 -0.5
#define PY4 .5

#define XMIN -1.5 // Startwert x
#define XMAX 1.5  // Endwert x
#define YMIN -1.5 // Startwert y
#define YMAX 1.5  // Endwert y
#define RES .005  // Sweep Resolution

int pendel(double x0, double y0);

int main() {
  double x, y;
#pragma omp parallel
  for (x = XMIN; x <= XMAX; x += RES) {
    for (y = YMIN; y <= YMAX; y += RES) {
      pendel(x, y);
    }
  }
}

int pendel(double x0, double y0) {
  double t, xl = x0, yl = y0, x, y, vx, vy, xn, yn, fx = 0, fy = 0, E;
  double dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4, fx1, fy1, fx2, fy2, fx3, fy3,
      fx4, fy4;
  int pos;
  x = xl + H * V0;
  y = yl + H * V0;
  vx = V0 - K / M * H * x;
  vy = V0 - K / M * H * x; // Euler metheode für ersten schritt
  for (t = H; t <= T; t += H) {

    dx1 = x - PX1; // first magnet
    dy1 = y - PY1;
    fx1 = -dx1 / pow((pow(dx1, 2) + pow(dy1, 2) + pow(Z0, 2)), 1.5);
    fy1 = -dy1 / pow((pow(dx1, 2) + pow(dy1, 2) + pow(Z0, 2)), 1.5);

    dx2 = x - PX2; // seccond magnet
    dy2 = y - PY2;
    fx2 = -dx2 / pow((pow(dx2, 2) + pow(dy2, 2) + pow(Z0, 2)), 1.5);
    fy2 = -dy2 / pow((pow(dx2, 2) + pow(dy2, 2) + pow(Z0, 2)), 1.5);

    dx3 = x - PX3; // third magnet
    dy3 = y - PY3;
    fx3 = -dx3 / pow((pow(dx3, 2) + pow(dy3, 2) + pow(Z0, 2)), 1.5);
    fy3 = -dy3 / pow((pow(dx3, 2) + pow(dy3, 2) + pow(Z0, 2)), 1.5);

    dx4 = x - PX4; // fourth magnet
    dy4 = y - PY4;
    fx4 = -dx4 / pow((pow(dx4, 2) + pow(dy4, 2) + pow(Z0, 2)), 1.5);
    fy4 = -dy4 / pow((pow(dx4, 2) + pow(dy4, 2) + pow(Z0, 2)), 1.5);

    fx = fx1 + fx2 + fx3 + fx4;
    fy = fy1 + fy2 + fy3 + fy4;

    xn = 1. / (2. + G / M * H) *
         (2. * H * H * fx + 2. * x * (2. - H * H * K / M) +
          xl * (G / M * H - 2.));
    yn = 1. / (2. + G / M * H) *
         (2. * H * H * fy + 2. * y * (2. - H * H * K / M) +
          yl * (G / M * H - 2.));

    xl = x;
    x = xn;
    yl = y;
    y = yn;
  }
  if (x > 0) {
    if (y > 0) {
      pos = 1;
    } else {
      pos = 2;
    }

  } else {
    if (y < 0) {
      pos = 3;
    } else {
      pos = 4;
    }
  }
  printf("%g %g %d\n", x0, y0, pos);
}
