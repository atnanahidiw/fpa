#ifndef Fpa_H
#define Fpa_H
#include <iostream>
#include <cstdio>
#include <cmath>
#include "acak.h"
#include "objective.h"
using namespace std;

struct result{
	double *best, fmin;
	int tot_eval;
};

/* Application of simple constraints */
/* s  : target to be constrained */
/* lb : lower bound constraint */
/* ub : upper bound constraint */
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
