#ifndef Fpa_H
#define Fpa_H
#include <iostream>
#include <random>
#include <cstdio>
#include <cmath>
#define pi acos(-1)
using namespace std;

extern int d;                        /* Dimension of the search variables */
extern double ub_val, lb_val, beta;
extern double sigma;                 /* Variance of Levy distribution */

struct result{
	double *best, fmin;
	int iteration, tot_eval;
};

/* Evaluate function */
double func(double x[]);

/* Application of simple constraints */
void simplebounds(int n, double *s, double lb[], double ub[]);

/* Draw n Levy flight sample */
double* levy(int n);

/* Flower pollination algorithm */
/* n        : size of flowers population */
/* max_iter : maximum iteration */
/* p        : switch probability */
result fpa(int n, int max_iter, double p);

/* Flower pollination algorithm */
/* Default parameter */
result fpa();

#endif
