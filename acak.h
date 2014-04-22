#ifndef Acak_H
#define Acak_H
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#define pi acos(-1)
using namespace std;

extern double beta;
extern double sigma;  /* Variance of Levy distribution */
extern double gam;    /* Stepsize of Levy distribution */

/* Used on Unix */
static random_device rd;
static mt19937 gen;

/* Used on Windows */
// static mt19937 gen(static_cast<unsigned int>(time(NULL)));

/* Return random sampling following uniform distribution */
double uniform();

/* Return discrete random sampling following uniform distribution */
int uniform_int(int begin, int end);

/* Return random sampling following normal distribution */
double normal();

/* Draw n Levy flight sample */
double* levy(int n);

#endif
