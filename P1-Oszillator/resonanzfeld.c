#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define H 0.01  // Zeitschritt
#define Omega 1 // Frequenz
#define T 500.0
#define dwt 0.1
#define wmax 10
#define EINSCHWINGZEIT 150
#define dd 0.1
#define dmax 5

int main() {
  double xn2, xn1, xn, fn;
  // double wt = 1;
  double t = 0;
  double x0 = 0;
  double v = 1.0;
  double amplitude = 0;

  xn1 = x0 + H * v;
  t = t + H;

  for (double d = 0.1; d < dmax; d = d + dd) {
    for (double wt = 0.1; wt < wmax; wt = wt + dwt) {
      amplitude = 0;
      for (t = 2 * H; t < T; t += H) {
        fn = sin(wt * t);
        xn2 = 1. / (2. + d * H) *
              (2 * H * H * fn + 2. * xn1 * (2. - H * H * Omega * Omega) +
               xn * (d * H - 2.));
        xn = xn1;
        xn1 = xn2;
        if (t > EINSCHWINGZEIT) {
          if (xn > amplitude) {
            amplitude = xn;
          }
        }
      }
      printf("%g %g %g\n", wt, d, amplitude);
    }
  }
  return 0;
}
