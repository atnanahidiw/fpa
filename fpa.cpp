#include "fpa.h"

/* Used on Unix */
//random_device rd;
//mt19937 gen(rd());

/* Used on Windows */
mt19937 gen(static_cast<unsigned int>(time(NULL)));

normal_distribution<double> normal(0.0, 0.1);
uniform_real_distribution<double> uniform(0.0, 1.0);

/* Variance of Levy distribution */
double sigma = pow(tgamma(1.0+beta)*sin(pi*beta/2.0)/(tgamma((1.0+beta)/2.0)*beta*pow(2.0, (beta-1.0)/2.0)), 1.0/beta);

/* Draw n Levy flight sample */
double* levy(int n){
	double *step = new double[n];
	for(int i=0; i<n; ++i){
		step[i] = normal(gen)*sigma/pow(abs(normal(gen)), 1.0/beta);
//		cout << step[i] << " ";
//		step[i] *= 0.01;
	}
//	cout << "| ";
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

//	for(int i=0; i<d; ++i) cout << best[i] << " ";
//	cout << endl;

//	for(i=0; i<n; ++i){
//		cout << "Solution " << i+1 << " -> " << fitness[i] << " | ";
//		for(j=0; j<d; ++j) cout << sol[i][j] << " ";
//		cout << endl;
//	}

	/* Main algorithm */
	bool stop = false;
	int tot_eval, i_rand, j_rand, iter = 0;
	double epsilon, fnew, norm, s[d], *l;
	uniform_int_distribution<int> uniform_i(0, n-1);
	while((iter < max_iter) && !stop){
//		cout << "Iteration " << iter+1 << endl;
        /* Loop over all flower (solutions) */
        for(i=0; (i<n) && !stop; ++i){
			double rand =  uniform(gen);
			/* Pollens are carried by insects and thus can move in large scale, large distance. */
			/* Formula: x[t+1][i] = x[t][i] + l*(x[t][i]-best) */
			if(rand<p){
				l = levy(d);
//				for(j=0; j<d; ++j) cout << l[j] << " ";
//				cout << endl;
				for(j=0; j<d; ++j)
					s[j] = sol[i][j] + l[j] * (sol[i][j] - best[j]);
				simplebounds(d, s, lb, ub);  /* Check if the simple limits/bounds are OK */
//				for(j=0; j<d; ++j) cout << s[j] << " ";
//				cout << endl;
			}
			/* If not, then local pollination of neighbor flowers */
			/* Formula: x[t+1][i] = x[t][i] + eps*(x[t][irand]-x[t][jrand]) */
			else{
				/* Find random flowers in the neighbourhood */
				do{ i_rand = uniform_i(gen); } while(i_rand==i);
				do{ j_rand = uniform_i(gen); } while((j_rand==i) || (j_rand==i_rand));

				epsilon = uniform(gen);
				for(j=0; j<d; ++j) s[j] = sol[i][j] + epsilon * (sol[i_rand][j] - sol[j_rand][j]);
				simplebounds(d, s, lb, ub);  /* Check if the simple limits/bounds are OK */
			}

			fnew = func(s);  /* Evaluate new solutions */

	        /* Stop function */
	        /* Check if the the diffence of fnew and solution less than eps */
//		    norm = 0.0;
//		    for(j=0; j<d; ++j) norm += pow(s[j]-sol[i][j], 2.0);
//		    norm = sqrt(norm);
//		    if((abs((fnew-fmin))<eps) && (norm<eps)){
		    if((abs(fmin-target_val)<eps)){
		    	stop     = true;
		    	tot_eval = iter*n+i+1;
		    }

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

//			cout << "Solution " << i+1 << " -> " << fitness[i] << " | ";
//			for(j=0; j<d; ++j) cout << s[j] << " ";
//			cout << endl;
		}
		++iter;
	}
	if(!stop) tot_eval = max_iter*n;

//	cout << "Fmin          : " << fmin << endl;
//	cout << "Nilai terbaik : ";
//	for(int i=0; i<d; ++i)  cout << best[i]) << " ";
//	cout << endl;

	/* Return the result */
	result res;
	res.fmin      = fmin;
	res.best      = new double[d];
	for (int i=0; i<d; ++i) res.best[i] = best[i];
	res.tot_eval  = tot_eval;

	return res;
}

/* Flower pollination algorithm */
/* Default parameter */
result fpa(){
	return fpa(20, 2000, 0.8);
}
