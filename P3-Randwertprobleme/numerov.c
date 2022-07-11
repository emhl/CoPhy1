#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>


#define H 0.001
#define XMAX 20.0
#define N (XMAX / H)
#define EPS0 1.

double F(double x) { return -x / (8 * M_PI * EPS0) * exp(-x); }

double k2(double x) { return 0.0; }

double numerov(double x, double fnm1, double fn) {
  return (H * H / 12.0 * (F(x + H) + 10.0 * F(x) + F(x - H)) +
          fn * (2.0 - 5.0 / 6.0 * H * H * k2(x)) -
          fnm1 * (1.0 + H * H / 12.0 * k2(x - H))) /
         (1.0 + H * H / 12.0 * k2(x + H));
}

double chi(double x) { // analytische lösung von chi(r)
  return (-(1 + x / 2.) / (4. * M_PI * EPS0) * exp(-x) +
          1 / (4. * M_PI * EPS0)) /
         .08;
}

int main() {
  double x, fnm1 = 0.0, fn = H, fnp1;
  double y, steig;

  // unkorrigiert
  for (x = H; x <= XMAX; x += H) {
    fnp1 = numerov(x, fnm1, fn);
    fnm1 = fn; // letzter und aktueller wert werden zwischengespeichert
    fn = fnp1;
  }
  steig = (fn - fnm1) /
          H; // berechnung des linearen terms aus den letzten zwei werten

  // nochmal laufen lassen während man den linearen term abzieht
  fnm1 = 0.0;
  fn = H;
  for (x = H; x <= XMAX; x += H) {
    fnp1 = numerov(x, fnm1, fn);

    y = (fn - x * steig) / .08; // eichung
    printf("%g %g %g %g %g\n", x, y, y / x, chi(x),
           chi(x) /
               x); // x , Chi_num(x), phi_num(x), chi analytisch, phi analytisch

    fnm1 = fn;
    fn = fnp1;
  }
}