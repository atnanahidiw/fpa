#include <iostream>
#include <cstdio>
#include <ctime>
#include "fpa.h"
using namespace std;

result res;
int d         = 3;
double beta   = 1.5;
int count     = 0;

/* Test type choice */
/* 1 : De Jong function    (fmin=0, x[i]=0) */
/* 2 : eggcrate function   (fmin=0, x[i]=0) */
/* 3 : Rosenbrock function (fmin=0, x[i]=1) */
/* 4 : Ackley function     (fmin=0, x[i]=0) */
/* 5 : Rastrigin function  (fmin=0, x[i]=0) */
/* 6 : Griewank function   (fmin=0, x[i]=0) */
/* 7 : Salomon function    (fmin=0, x[i]=0) */  /* still error */
int test_type = 3;

void fpa_run(){
	res = fpa(45, 2500, 0.8);
}

void eval(){
	clock_t t_start = clock();
	fpa_run();

	printf("Waktu           : %.2lfs\n", (double)(clock() - t_start)/CLOCKS_PER_SEC);
	printf("Fmin            : %.5lf\n", res.fmin);
	printf("Nilai terbaik   : ");
	for(int i=0; i<d; ++i)  printf("%.2lf ", res.best[i]);
	printf("\n");
	printf("Banyak evaluasi : %d\n", res.tot_eval);
}

void accurate_test(){
	int i, j, max_eval = 0;
	clock_t start, t_start = clock();
	double time, slowest = 0.0;

	for(i=0; i<1000; ++i){
		start    = clock();
		fpa_run();
		if(abs(res.fmin - target_val) < eps) ++count;
		else{
			printf("Fmin            : %.5lf\n", res.fmin);
			printf("Nilai terbaik   : ");
			for(j=0; j<d; ++j)  printf("%.2lf ", res.best[j]);
			printf("\n");
			printf("Banyak evaluasi : %d\n", res.tot_eval);
		}
		time = (double)(clock() - start)/CLOCKS_PER_SEC;
		if(time>slowest) slowest = time;
		if(res.tot_eval>max_eval) max_eval = res.tot_eval;
	}

	printf("Akurasi                    : %.2lf\%\n", (double)count/10.0);
	printf("Evaluasi Paling Banyak     : %d\n", max_eval);
	printf("Waktu Evaluasi Paling Lama : %.2lfs\n", slowest);
	printf("Waktu Total                : %.2lfs\n", (double)(clock() - t_start)/CLOCKS_PER_SEC);
}

int main(){
	init_constraint_target();
//	eval();
	accurate_test();

	/* simplebounds check */
//	double ub[2] = {1.0, 1.0}, lb[2] = {-1.0, -1.0}, s[2] = {-10.0, 2.0};
//	simplebounds(2, s, lb, ub);
//	printf("%.5lf %.5lf\n", s[0], s[1]);

	/* func check */
//	double x[3] = {1.19, 1.41, 2.0};
//	printf("%.2lf\n", func(x));

    return 0;
}
