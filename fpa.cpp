#include "fpa.h"

/* Application of simple constraints */
/* s  : target to be constrained */
/* lb : lower bound constraint */
/* ub : upper bound constraint */
void simplebounds(double *s, double lb[], double ub[]){
	for(int i=0; i<d; ++i){
		/* Apply the lower bound */
		if(s[i]<lb[i]) s[i] = lb[i];

		/* Apply the upper bounds */
		if(s[i]>ub[i]) s[i] = ub[i];

//		cout << s[i] << " ";
	}
//	cout << endl;
}

/* Flower pollination algorithm */
/* n        : size of flowers population */
/* max_iter : maximum iteration */
/* p        : switch probability */
result fpa(int n, int max_iter, double p){
	int i, j;

	double ub[d], lb[d], sol[n][d], s[n][d], fitness[n];
	for(i=0; i<d; ++i){
		lb[i] = lb_val;
		ub[i] = ub_val;
	}

	/* Initialize the population (solutions) */
	for(i=0; i<n; ++i){
		for(j=0; j<d; ++j) s[i][j] = sol[i][j] = lb[j] + (ub[j] - lb[j]) * uniform();
		fitness[i] = func(sol[i]);
	}

	/* Find the current best */
	j = 0;
	for(i=1; i<n; ++i) if(fitness[i] < fitness[j]) j = i;
	double fmin = fitness[j];
	double best[d];
	for(i=0; i<d; ++i) best[i] = sol[j][i];

//	for(i=0; i<n; ++i){
//		cout << "Solution " << i+1 << " -> " << fitness[i] << " | ";
//		for(j=0; j<d; ++j) cout << sol[i][j] << " ";
//		cout << endl;
//	}

//	for(i=0; i<d; ++i) cout << best[i] << " ";
//	cout << endl;

	/* Main algorithm */
	bool stop = false;
	int tot_eval, i_rand, j_rand, iter = 0;
	double epsilon, fnew, *l;
	while((iter < max_iter) && !stop){
//		cout << "Iteration " << iter+1 << endl;

        /* Loop over all flower (solutions) */
        for(i=0; (i<n) && !stop; ++i){
			/* Pollens are carried by insects and thus can move in large scale, large distance. */
			/* Formula: x[t+1][i] = x[t][i] + l*(best-x[t][i]) */
			if(uniform()<p){
				l = levy(d);
//				for(j=0; j<d; ++j) cout << l[j] << " ";
//				cout << endl;
				for(j=0; j<d; ++j)
					s[i][j] = sol[i][j] + l[j] * (best[j] - sol[i][j]);
//				for(j=0; j<d; ++j) cout << s[i][j] << " ";
//				cout << endl;
				free(l);
			}
			/* If not, then local pollination of neighbor flowers */
			/* Formula: x[t+1][i] + epsilon*(x[t][irand]-x[t][jrand]) */
			else{
				/* Find random flowers in the neighbourhood */
				do{ i_rand = uniform_int(0,n-1); } while(i_rand==i);
				do{ j_rand = uniform_int(0,n-1); } while((j_rand==i) || (j_rand==i_rand));

				epsilon = uniform();
				for(j=0; j<d; ++j) s[i][j] += epsilon * (sol[i_rand][j] - sol[j_rand][j]);
			}

			simplebounds(s[i], lb, ub);  /* Check if the simple limits/bounds are OK */
			fnew = func(s[i]);           /* Evaluate new solutions */

			/* If fitness improves (better solutions found), update then */
			if (fnew<fitness[i]){
				fitness[i] = fnew;
				for(j=0; j<d; ++j) sol[i][j] = s[i][j];
			}

			/* Update the current global best */
			if (fnew<fmin){
				fmin = fnew;
				for(j=0; j<d; ++j) best[j] = s[i][j];
			}

			/* Stop function */
			/* Check if the the difference of fnew and solution less than eps */
			if((abs(fmin-target_val)<eps)){
				stop     = true;
				tot_eval = iter*n+i+1;
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
