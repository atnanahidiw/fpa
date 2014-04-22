#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include "acak.h"

/* Dummy */
double beta = 1.5;
double gam = 0.01;

int main()
{
    std::map<int, int> hist;

	// std::mt19937 gen(static_cast<unsigned int>(time(NULL))); 
 //    // values near the mean are the most likely
 //    // standard deviation affects the dispersion of generated values from the mean
 //    std::normal_distribution<> d(0,1);
 
 //    for(int n=0; n<10000; ++n) {
 //        ++hist[std::round(d(gen))];
 //    }

    init_acak();
    for(int n=0; n<10000; ++n) {
        ++hist[std::round(normal())];
    }

    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
}