#include "objective.h"

double lb_val;  /* Value of lower bound constraint */
double ub_val;  /* Value of upper bound constraint */

/* Initialize objective function constraint */
void init_constraint(){
	switch(test_type){
		case 1 : lb_val = -5.12;    ub_val = 5.12;    break;  /* De Jong function */
		case 2 : lb_val = -5.12;    ub_val = 5.12;    break;  /* eggcrate function */
		case 3 : lb_val = -9.87;    ub_val = 9.87;    break;  /* Rosenbrock function */
		case 4 : lb_val = -32.768;  ub_val = 32.768;  break;  /* Ackley function */
		case 5 : lb_val = -5.12;    ub_val = 5.12;    break;  /* Rastrigin function */
		case 6 : lb_val = -600.0;   ub_val = 600.0;   break;  /* Griewank function */
		case 7 : lb_val = -5.12;    ub_val = 5.12;    break;  /* Salomon function */
	}
}

/* Evaluate objective function */
double func(double x[]){
	switch(test_type){
		case 1 : {
			/* De Jong function */
			double total = 0.0;
			for(int i=0; i<d; ++i) total += pow(x[i], 2.0);
			return total;
		}

		case 2 : {
			/* eggcrate function */
			double total = 0.0, total_sin = 0.0;
			for(int i=0; i<d; ++i){
				total     += pow(x[i], 2.0);
				total_sin += sin(x[i]);
			}
			return total+25.0*pow(total_sin, 2.0);
		}

		case 3 : {
			/* Rosenbrock function */
			double total = 0.0;
			for(int i=0; i<(d-1); ++i) total += (100.0*pow(x[i+1]-pow(x[i], 2.0), 2.0)+pow(x[i]-1.0, 2.0));
			return total;
		}

		case 4 : {
			/* Ackley function */
			double total_cos = 0.0, total_sqr = 0.0;
			for(int i=0; i<d; ++i){
				total_cos += cos(2*pi*x[i]);
				total_sqr += pow(x[i], 2.0);
			}
			return 20.0+exp(1.0)-20.0*exp(-0.2*sqrt(1.0*total_sqr/d))-exp(1.0*total_cos/d);
		}

		case 5 : {
			/* Rastrigin function */
			double total = 0.0;
			for(int i=0; i<d; ++i) total += pow(x[i], 2.0)-10.0*cos(2*pi*x[i]);
			return 10.0*d+total;
		}

		case 6 : {
			/* Griewank function */
			/* Still error */
			double total_cos = 0.0, total_sqr = 0.0;
			for(int i=0; i<d; ++i){
				total_cos *= cos(x[i]/sqrt(i));
				total_sqr += pow(x[i], 2.0);
			}
			return 1.0+1.0*total_sqr/4000.0-total_cos;
		}

		case 7 : {
			/* Salomon function */
			double total = 0.0;
			for(int i=0; i<d; ++i) total += pow(x[i], 2.0);
			return 1.0+0.1*sqrt(total)-cos(2.0*pi*sqrt(total));
		}
	}
}

/* Application of simple constraints */
void simplebounds(int n, double *s, double lb[], double ub[]){
	for(int i=0; i<n; ++i){
		/* Apply the lower bound */
		if(s[i]<lb[i]) s[i] = lb[i];

		/* Apply the upper bounds */
		if(s[i]>ub[i]) s[i] = ub[i];

//		printf("%.5lf ", s[i]);
	}
//	printf("\n");
}
