#include <stdio.h>

#define T 30.0    // Laufzeit
#define H 0.005   // Zeitschritt
#define OMEGA2 1. // Frequenz
#define D 4.      // Dämpfung
#define X0 0.     // Startwert x
#define V0 1.     // Startwert

int main() {
  double t, xl = X0, x, v, xn, c, E;
  x = xl + H * V0;
  v = V0 - OMEGA2 * H * x; // Euler metheode für ersten schritt
  E = (v * v + OMEGA2 * x * x) / 2.0;
  for (t = H; t <= T; t += H) {
    printf("%g %g %g %g\n", t, x, v, E);
    xn =
        1. / (2. + D * H) * (4 * x - 2 * x * H * H * OMEGA2 + xl * (D * H - 2));
    v = (xn - xl) / (2 * H);
    xl = x;
    x = xn;
    E = (v * v + OMEGA2 * x * x) / 2.0;
  }
}
