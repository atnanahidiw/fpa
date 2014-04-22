#include <iostream>
#include <cstdio>
#include "fpa.h"
using namespace std;

string test_type_name[8] = {"", "De Jong", "eggcrate", "Rosenbrock", "Ackley", "Rastrigin", "Griewank", "Salomon"};
/* Test type choice */
/* 1 : De Jong function    (fmin=0, x[i]=0) */
/* 2 : eggcrate function   (fmin=0, x[i]=0) */
/* 3 : Rosenbrock function (fmin=0, x[i]=1) */
/* 4 : Ackley function     (fmin=0, x[i]=0) */
/* 5 : Rastrigin function  (fmin=0, x[i]=0) */
/* 6 : Griewank function   (fmin=0, x[i]=0) */
/* 7 : Salomon function    (fmin=0, x[i]=0) */  /* still error */
int test_type = 6;

int x        = 50;
double beta  = 1.5;
double gam   = 0.075;
double eps   = 1.0e-5;
int d        = 16;
int n        = 50;
int max_iter = 100000;
double p     = 0.8;

result res;

double mean(double arr[]){
	double sum = 0;
	for(int i=0; i<x; ++i)
		sum += arr[i];
	return (sum / (double)x);
}

double mean(int arr[]){
	int sum = 0;
	for(int i=0; i<x; ++i)
		sum += arr[i];
	return ((double)sum / (double)x);
}

double std_dev(double arr[]){
	double m    = mean(arr);
	double temp = 0;
	for(int i=0; i<x; ++i) temp += (arr[i] - m) * (arr[i] - m);
	return sqrt(temp / (double)(x-1));
}

double std_dev(int arr[]){
	double m    = mean(arr);
	double temp = 0;
	for(int i=0; i<x; ++i) temp += ((double)arr[i] - m) * ((double)arr[i] - m);
	return sqrt(temp / (double)(x-1));
}

void fpa_run(){
//	res = fpa();
	res = fpa(n, max_iter, p);
}

int main(){
	init_acak();
	init_constraint_target();
	int i, j, eval[x], count;
	clock_t start;
	double time[x];

	cout << "/************************************************************************/" << endl;
	cout << "Benchmark fungsi " << test_type_name[test_type] << " " << d << " Dimensi, dengan parameter:" << endl;
	cout << "Populasi          : " << n << endl;
	cout << "Maksimum iterasi  : " << max_iter << endl;
	cout << "Peluang Keputusan : " << p << endl;
	cout << "Stepsize          : " << gam << endl;
	cout << "Toleransi         : " << eps << endl;
	cout << "/************************************************************************/" << endl << endl;

	count = 0;
	for(i=0; i<x; ++i){
		// cout << i+1 << endl;
		start = clock();
		fpa_run();
		time[i] = (double)(clock() - start)/CLOCKS_PER_SEC;
		if(abs(res.fmin - target_val) < eps) ++count;
		else{
			cout << "Fmin            : " << res.fmin << endl;
			cout << "Nilai terbaik   : ";
			for(int j=0; j<d; ++j) cout << res.best[j] << " ";
			cout << endl;
			cout << "Banyak evaluasi : " << res.tot_eval << endl;
		}
		eval[i] = res.tot_eval;
	}
	cout << "Akurasi   : " << (double)count/(double)x*100.0 << "%" << endl;
	cout << "Evaluasi  : " << mean(eval) << " +/- " << std_dev(eval) << endl;
	cout << "Waktu     : " << mean(time) << " +/- " << std_dev(time) << "s" << endl;

	return 0;
}
