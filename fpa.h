#ifndef Fpa_H
#define Fpa_H
#include <random>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include "objective.h"
using namespace std;

extern double beta;
extern double sigma;  /* Variance of Levy distribution */
extern double gam;    /* Stepsize of Levy distribution */

struct result{
	double *best, fmin;
	int tot_eval;
};

/* Draw n Levy flight sample */
double* levy(int n);

/* Application of simple constraints */
void simplebounds(double *s, double lb[], double ub[]);

/* Flower pollination algorithm */
/* n        : size of flowers population */
/* max_iter : maximum iteration */
/* p        : switch probability */
result fpa(int n, int max_iter, double p);

/* Flower pollination algorithm */
/* Default parameter */
result fpa();

#endif
