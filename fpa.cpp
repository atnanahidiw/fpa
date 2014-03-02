#include "fpa.h"

random_device rd;
mt19937 gen(rd());
normal_distribution<double> normal(0.0, 0.1);
uniform_real_distribution<double> uniform(0.0, 1.0);

/* Variance of Levy distribution */
double sigma = pow(tgamma(1.0+beta)*sin(pi*beta/2.0)/(tgamma((1.0+beta)/2.0)*beta*pow(2.0, (beta-1.0)/2.0)), 1.0/beta);

/* Draw n Levy flight sample */
double* levy(int n){
	double *step = new double[n];
	for(int i=0; i<n; ++i){
		step[i] = normal(gen)*sigma/pow(abs(normal(gen)), 1.0/beta);
//		printf("%.2lf ", step[i]);
//		step[i] *= 0.01;
	}
//	printf("| ");
	return step;
}

/* Flower pollination algorithm */
/* n        : size of flowers population */
/* max_iter : maximum iteration */
/* p        : switch probability */
result fpa(int n, int max_iter, double p){
	int i, j;

	/* Initialize the population (solutions) */
	double ub[d], lb[d], sol[n][d], fitness[n];
	for(i=0; i<d; ++i){
		lb[i] = lb_val;
		ub[i] = ub_val;
	}
	for(i=0; i<n; ++i){
		for(j=0; j<d; ++j) sol[i][j] = lb[j] + (ub[j] - lb[j]) * uniform(gen);
		fitness[i] = func(sol[i]);
	}

	/* Find the current best */
	double best[d];
	double fmin = fitness[0];
	int imin    = 0;
	for(i=1; i<n; ++i)
		if(fitness[i] < fmin){
			fmin = fitness[i];
			imin = i;
		}
	for(i=0; i<d; ++i) best[i] = sol[imin][i];

//	for(int i=0; i<d; ++i)  printf("%.2lf ", best[i]);
//	printf("\n");

	/* Main algorithm */
	double s[d], *l;
	int iter = 0;
	while(iter < max_iter){
//		printf("Iteration %d\n", iter+1);
        /* Loop over all flower (solutions) */
        for(i=0; i<n; ++i){
			double rand =  uniform(gen);
			/* Pollens are carried by insects and thus can move in large scale, large distance. */
			/* Formula: x[t+1][i] = x[t][i] + l*(x[t][i]-best) */
			if(rand<p){
			l = levy(d);
//			for(j=0; j<d; ++j) printf("%.10lf ", l[j]);
//			printf("\n");
				for(j=0; j<d; ++j)
					s[j] = sol[i][j] + l[j] * (sol[i][j] - best[j]);
				simplebounds(d, s, lb, ub);  /* Check if the simple limits/bounds are OK */
//				for(j=0; j<d; ++j) printf("%.10lf ", s[j]);
//				printf("\n");
			}
			/* If not, then local pollination of neighbor flowers */
			/* Formula: x[t+1][i] = x[t][i] + eps*(x[t][irand]-x[t][jrand]) */
			else{
				int irand, jrand;
				double eps = uniform(gen);
				
				/* Find random flowers in the neighbourhood */
				uniform_int_distribution<int> uniform_i(0, n-1);
				do{ irand = uniform_i(gen); } while(irand==i);
				do{ jrand = uniform_i(gen); } while((jrand==i) || (jrand==irand));
				for(j=0; j<d; ++j) s[j] = sol[i][j] + eps * (sol[irand][j] - sol[jrand][j]);
				simplebounds(d, s, lb, ub);  /* Check if the simple limits/bounds are OK */
			}

//			printf("Solution %d -> %.2lf | ", i+1, fitness[i]);
//			for(j=0; j<d; ++j) printf("%.2lf ", s[j]);
//			printf("\n");
//			printf("%.2lf\n", rand);

			double fnew = func(s);  /* Evaluate new solutions */

			/* If fitness improves (better solutions found), update then */
			if (fnew<=fitness[i]){
				fitness[i] = fnew;
				for(j=0; j<d; ++j) sol[i][j] = s[j];
			}

			/* Update the current global best */
			if (fnew<=fmin){
				fmin = fnew;
				for(j=0; j<d; ++j) best[j] = s[j];
			}
		}
		++iter;
	}

//	printf("Fmin: %.2lf\n", fmin);
//	printf("Nilai terbaik: ");
//	for(int i=0; i<d; ++i)  printf("%.2lf ", best[i]);
//	printf("\n");

	/* Return the result */
	result res;
	res.fmin      = fmin;
	res.best      = new double[d];
	for (int i=0; i<d; ++i) res.best[i] = best[i];
	res.iteration = iter;

	return res;
}

/* Flower pollination algorithm */
/* Default parameter */
result fpa(){
	return fpa(5, 20000, 0.8);
}
