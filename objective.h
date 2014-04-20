#ifndef Objective_H
#define Objective_H
#include <iostream>
#include <cstdio>
#include <cmath>
#define pi acos(-1)
using namespace std;

extern int d;              /* Dimension of the search variables */
extern int test_type;      /* Test type choice */
extern double lb_val;      /* Value of lower bound constraint */
extern double ub_val;      /* Value of upper bound constraint */
extern double target_val;  /* Value of objective function */
extern double eps;         /* Value of tolerance */

/* Initialize objective function constraint */
void init_constraint_target();

/* Evaluate objective function */
double func(double x[]);

#endif
