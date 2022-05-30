#include <stdio.h>
#include <math.h>

#define T 1000
#define H 0.01
#define GAMMA 0.25
#define w0 1
#define A 0.55	// 0.8 : chaos
#define	wT (2.0/3.0)

main() {
	double t=0.0, phialt=M_PI/2.0, phi=phialt, phin;	
	FILE *f;
	f=fopen("pendel.dat","w");
	if(f==NULL)
		return -1;

	while (t<T) {
		phin = 2.0*H*H/(2.0+GAMMA*H)*(A*cos(wT*t)-w0*w0*sin(phi)) + 4.0/(2.0+GAMMA*H)*phi - phialt*(2.0-GAMMA*H)/(2.0+GAMMA*H);

		fprintf(f,"%g %g %g\n",t, phi, (phin-phialt)/H);
		// reduced plot
		//printf("%g %g %g\n",t, fmod(fabs(phi+M_PI),2*M_PI)-M_PI, (phin-phialt)/H);

		phialt = phi;
		phi = phin;

		t+=H;
	}

}
