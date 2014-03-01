#include <iostream>
#include <cstdio>
#include <ctime>
#include "fpa.h"
using namespace std;

int d         = 3;
double lb_val = -5.12;
double ub_val = 5.12;
double beta   = 1.5;

int main(){
	
	clock_t t_start;
//	for(int a=0; a<100; ++a){
	t_start     = clock();
	result res  = fpa(5, 20000, 0.8);

	printf("Waktu: %.2lfs\n", (double)(clock() - t_start)/CLOCKS_PER_SEC);
	printf("Fmin: %.2lf\n", res.fmin);
	printf("Nilai terbaik: ");
	for(int i=0; i<d; ++i)  printf("%.2f ", res.best[i]);
	printf("\n");
//	printf("Banyak iterasi: %d\n", res.iteration);
//	printf("Banyak evaluasi: %d\n", res.tot_eval);
//	}

	/* simplebounds check */
//	double ub[2] = {1.0, 1.0}, lb[2] = {-1.0, -1.0}, s[2] = {-10.0, 2.0};
//	simplebounds(2, s, lb, ub);
//	printf("%.5lf %.5lf\n", s[0], s[1]);

	/* func check */
//	double x[3] = {1.19, 1.41, 2.0};
//	printf("%.2lf\n", func(x));

    return 0;
}

/* Evaluate function */
double func(double x[]){
	// Rosenbrock's 3D function
	return pow(1.0-x[0],2.0)+100.0*pow(x[1]-pow(x[0],2.0),2.0)+100.0*pow(x[2]-pow(x[1],2.0),2.0);
}
