#include "objective.h"

double lb_val;      /* Value of lower bound constraint */
double ub_val;      /* Value of upper bound constraint */
double target_val;  /* Value of objective function */

/* Initialize objective function constraint */
void init_constraint_target(){
	switch(test_type){
		case 1 : target_val = 0.0;  lb_val = -5.12;    ub_val = 5.12;    break;  /* De Jong function */
		case 2 : target_val = 0.0;  lb_val = -2*pi;    ub_val = 2*pi;    break;  /* eggcrate function */
		case 3 : target_val = 0.0;  lb_val = -9.87;    ub_val = 9.87;    break;  /* Rosenbrock function */
		case 4 : target_val = 0.0;  lb_val = -32.768;  ub_val = 32.768;  break;  /* Ackley function */
		case 5 : target_val = 0.0;  lb_val = -5.12;    ub_val = 5.12;    break;  /* Rastrigin function */
		case 6 : target_val = 0.0;  lb_val = -600.0;   ub_val = 600.0;   break;  /* Griewank function */
		case 7 : target_val = 0.0;  lb_val = -5.0;     ub_val = 5.0;     break;  /* Salomon function */
	}
}

/* Evaluate objective function */
double func(double x[]){
	switch(test_type){
		case 1 : {
			/* De Jong function */
			double total = 0.0;
			for(int i=0; i<d; ++i) total += x[i]*x[i];
			return total;
		}

		case 2 : {
			/* eggcrate function */
			double total = 0.0, total_sin = 0.0;
			for(int i=0; i<d; ++i){
				total     += x[i]*x[i];
				total_sin += sin(x[i]);
			}
			return total+25.0*pow(total_sin, 2.0);
		}

		case 3 : {
			/* Rosenbrock function */
			double tempa, tempb, total = 0.0;
			for(int i=0; i<(d-1); ++i){
				tempa = x[i+1]-x[i]*x[i];
				tempb = x[i]-1.0;
				total += (100.0*(tempa*tempa)+(tempb*tempb));
			}
			return total;
		}

		case 4 : {
			/* Ackley function */
			double total_cos = 0.0, total_sqr = 0.0;
			for(int i=0; i<d; ++i){
				total_cos += cos(2*pi*x[i]);
				total_sqr += x[i]*x[i];
			}
			return 20.0+exp(1.0)-20.0*exp(-0.2*sqrt(total_sqr/d))-exp(total_cos/d);
		}

		case 5 : {
			/* Rastrigin function */
			double total = 0.0;
			for(int i=0; i<d; ++i) total += pow(x[i], 2.0)-10.0*cos(2*pi*x[i]);
			return 10.0*d+total;
		}

		case 6 : {
			/* Griewank function */
			double total_cos = 1.0, total_sqr = 0.0;
			for(int i=0; i<d; ++i){
				total_cos *= cos(x[i]/sqrt(i+1));
				total_sqr += x[i]*x[i];
			}
			return 1.0+total_sqr/4000.0-total_cos;
		}

		case 7 : {
			/* Salomon function */
			/* Still error */
			double total = 0.0;
			for(int i=0; i<d; ++i) total += x[i]*x[i];
			return 1.0+0.1*sqrt(total)-cos(2.0*pi*sqrt(total));
		}
	}
}
