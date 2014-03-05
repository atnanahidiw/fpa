#include <iostream>
#include <cstdio>
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
int test_type = 1;

void fpa_run(){
//	res = fpa();
	res = fpa(45, 2500, 0.8);
}

void eval(){
	clock_t t_start = clock();
	fpa_run();

	cout << "Waktu           : " << (double)(clock() - t_start)/CLOCKS_PER_SEC << "s" << endl;
	cout << "Fmin            : " << res.fmin << endl;
	cout << "Nilai terbaik   : ";
	for(int i=0; i<d; ++i) cout << res.best[i] << " ";
	cout << endl;
	cout << "Banyak evaluasi : " << res.tot_eval << endl;
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

	cout << "Akurasi                    : " << (double)count/10.0 << "%" << endl;
	cout << "Evaluasi Paling Banyak     : " << max_eval << endl;
	cout << "Waktu Evaluasi Paling Lama : " << slowest << "s" << endl;
	cout << "Waktu Total                : " << (double)(clock() - t_start)/CLOCKS_PER_SEC << "s" << endl;
}

int main(){
	init_constraint_target();
//	eval();
	accurate_test();

	/* simplebounds check */
//	double ub[2] = {1.0, 1.0}, lb[2] = {-1.0, -1.0}, s[2] = {-10.0, 2.0};
//	simplebounds(2, s, lb, ub);
//	cout << s[0] << " " << s[1] << endl;

	/* func check */
//	double x[3] = {1.19, 1.41, 2.0};
//	cout << func(x) << endl;

    return 0;
}
