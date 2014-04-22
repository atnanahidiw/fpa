#include <iostream>
#include <cstdio>
#include "fpa.h"
using namespace std;

/* Test type choice */
/* 1 : De Jong function    (fmin=0, x[i]=0) */
/* 2 : eggcrate function   (fmin=0, x[i]=0) */
/* 3 : Rosenbrock function (fmin=0, x[i]=1) */
/* 4 : Ackley function     (fmin=0, x[i]=0) */
/* 5 : Rastrigin function  (fmin=0, x[i]=0) */
/* 6 : Griewank function   (fmin=0, x[i]=0) */
/* 7 : Salomon function    (fmin=0, x[i]=0) */  /* still error */
int test_type = 1;

int d        = 20;
double eps   = 1.0e-5;
double beta  = 1.5;
double gam   = 0.075;
int n        = 25;
int max_iter = 300000;
double p     = 0.8;

result res;

void fpa_run(){
//	res = fpa();
	res = fpa(n, max_iter, p);
}

int main(){
	init_acak();
	init_constraint_target();
	clock_t t_start = clock();
	fpa_run();

	cout << "Waktu           : " << (double)(clock() - t_start)/CLOCKS_PER_SEC << "s" << endl;
	cout << "Fmin            : " << res.fmin << endl;
	cout << "Nilai terbaik   : ";
	for(int i=0; i<d; ++i) cout << res.best[i] << " ";
	cout << endl;
	cout << "Banyak evaluasi : " << res.tot_eval << endl;

	/* simplebounds check */
//	double ub[2] = {1.0, 1.0}, lb[2] = {-1.0, -1.0}, s[1][2] = {-10.0, 0.5};
//	simplebounds(s[0], lb, ub);
//	cout << s[0][0] << " " << s[0][1] << endl;

	/* func check */
//	double x[3] = {1.19, 1.41, 2.0};
//	cout << func(x) << endl;

    return 0;
}
