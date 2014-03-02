#include <iostream>
#include <cstdio>
#include <ctime>
#include "fpa.h"
#define epsilon 0.000000001
using namespace std;

int d         = 3;
double beta   = 1.5;
int count     = 0;

/* Test type choice */
/* 1 : De Jong function    (fmin=0, x[i]=0) */
/* 2 : eggcrate function   (fmin=0, x[i]=0) */
/* 3 : Rosenbrock function (fmin=0, x[i]=1) */
/* 4 : Ackley function     (fmin=0, x[i]=0) */
/* 5 : Rastrigin function  (fmin=0, x[i]=0) */
/* 6 : Griewank function   (fmin=0, x[i]=0) */  /* still error */
/* 7 : Salomon function    (fmin=0, x[i]=0) */  /* still error */
int test_type = 0;

int main(){
	clock_t t_start;
	init_constraint();
	t_start     = clock();
//	for(int a=0; a<100; ++a){
	result res  = fpa(5, 20000, 0.8);

	printf("Waktu: %.2lfs\n", (double)(clock() - t_start)/CLOCKS_PER_SEC);
	printf("Fmin: %.2lf\n", res.fmin);
	printf("Nilai terbaik: ");
	for(int i=0; i<d; ++i)  printf("%.2f ", res.best[i]);
	printf("\n");
//	printf("Banyak iterasi: %d\n", res.iteration);
//	printf("Banyak evaluasi: %d\n", res.tot_eval);

//	if(abs(res.fmin) < epsilon) ++count;
//	else{
//		printf("Fmin: %.2lf\n", res.fmin);
//		printf("Nilai terbaik: ");
//		for(int i=0; i<d; ++i)  printf("%.2f ", res.best[i]);
//		printf("\n");
//	}
//	}
//	printf("Akurasi : %d\%\n", count);
//	printf("Waktu: %.2lfs\n", (double)(clock() - t_start)/CLOCKS_PER_SEC);

	/* simplebounds check */
//	double ub[2] = {1.0, 1.0}, lb[2] = {-1.0, -1.0}, s[2] = {-10.0, 2.0};
//	simplebounds(2, s, lb, ub);
//	printf("%.5lf %.5lf\n", s[0], s[1]);

	/* func check */
//	double x[3] = {1.19, 1.41, 2.0};
//	printf("%.2lf\n", func(x));

    return 0;
}
