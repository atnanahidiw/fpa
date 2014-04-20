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
int test_type = 3;

int d        = 16;
double beta  = 1.5;
int n        = 30;
int max_iter = 300000;
double p     = 0.2; 

result res;

void fpa_run(){
//	res = fpa();
	res = fpa(n, max_iter, p);
}

int main(){
	init_constraint_target();
	int i, j, max_eval = 0, count = 0;
	clock_t start, t_start = clock();
	double time, slowest = 0.0;

	for(i=0; i<50; ++i){
		start    = clock();
		fpa_run();
		if(abs(res.fmin - target_val) < eps) ++count;
		else{
			cout << "Fmin            : " << res.fmin << endl;
			cout << "Nilai terbaik   : ";
			for(int j=0; j<d; ++j) cout << res.best[j] << " ";
			cout << endl;
			cout << "Banyak evaluasi : " << res.tot_eval << endl;
		}
		time = (double)(clock() - start)/CLOCKS_PER_SEC;
		if(time>slowest) slowest = time;
		if(res.tot_eval>max_eval) max_eval = res.tot_eval;
	}

	cout << "Akurasi                    : " << (double)count*2 << "%" << endl;
	cout << "Evaluasi Paling Banyak     : " << max_eval << endl;
	cout << "Waktu Evaluasi Paling Lama : " << slowest << "s" << endl;
	cout << "Waktu Total                : " << (double)(clock() - t_start)/CLOCKS_PER_SEC << "s" << endl;

    return 0;
}
