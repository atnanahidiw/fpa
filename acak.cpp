#include "acak.h"

// normal_distribution<> normal_dist(0.0, 0.1);
// uniform_real_distribution<> uniform_dist(0.0, 1.0);

/* Variance x of Levy distribution */
static double sigma = pow(tgamma(1.0+beta)*sin(pi*beta/2.0)/(tgamma((1.0+beta)/2.0)*beta*pow(2.0, (beta-1.0)/2.0)), 1.0/beta);

static float fn[128];
static int i;
static int j;
static uint32_t kn[128];
static uint32_t seed;
static float value;
static float wn[128];

void init_acak(){
	seed = static_cast<unsigned int>(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count());
	r4_nor_setup (kn, fn, wn);
}

/* Return random sampling following uniform distribution */
double uniform(){
	// return uniform_dist(gen);
	return r4_uni(seed);
}

/* Return discrete random sampling following uniform distribution */
int uniform_int(int begin, int end){
	// return (int)(uniform_dist(gen)*(end-begin+1)+begin);
	return (int)(r4_uni(seed)*(end-begin+1)+begin);
}

/* Return random sampling following normal distribution */
double normal(){
	// return normal_dist(gen);
	return r4_nor(seed, kn, fn, wn);
}

/* Draw n Levy flight sample */
double* levy(int n){
	double *step = new double[n];
	for(int i=0; i<n; ++i){
		step[i] = gam*normal()*sigma/pow(abs(normal()), 1.0/beta);
//		cout << step[i] << " ";
	}
//	cout << "| ";
	return step;
}
