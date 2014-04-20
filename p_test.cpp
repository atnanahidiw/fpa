#include <iostream>
#include <cstdio>
#include "fpa.h"
using namespace std;

string test_type_name[8] = {"", "De Jong function", "eggcrate function", "Rosenbrock function", "Ackley function", "Rastrigin function", "Griewank function", "Salomon function"};
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
double eps   = 1.0e-10;
double beta  = 1.5;
double gamma = 0.075;
int n        = 25;
int max_iter = 300000;
double p     = 0.2;

result res;

void fpa_run(){
//	res = fpa();
	res = fpa(n, max_iter, p);
}

int main(){
	init_constraint_target();

	cout << "/*******************************************/" << endl;
	cout << "Tes P " << endl;
	cout << test_type_name[test_type] << " " << d << " Dimensi, dengan parameter:" << endl;
	cout << "Populasi          : " << n << endl;
	cout << "Maksimum iterasi  : " << max_iter << endl;
	cout << "Stepsize          : " << gamma << endl;
	cout << "Presisi           : " << eps << endl;
	cout << "/*******************************************/" << endl << endl;
	
	int count;
	clock_t t_start;
	p = 0.1;
	while((p-0.9)<eps){
		count   = 0;
		t_start = clock();
		fpa_run();

		cout.precision(2);
		cout << fixed;
		cout << "p = " << p << endl;
		cout << "Waktu           : " << (double)(clock() - t_start)/CLOCKS_PER_SEC << "s" << endl;
		cout << "Fmin            : " << res.fmin << endl;
		cout << "Nilai terbaik   : ";
		for(int i=0; i<d; ++i) cout << res.best[i] << " ";
		cout << endl;
		cout << "Banyak evaluasi : " << res.tot_eval << endl;
		p += 0.1;
		if((p-0.9)<eps) cout << endl;
	}

    return 0;
}
