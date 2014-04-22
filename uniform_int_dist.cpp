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

    init_acak();
    for(int n=0; n<100000; ++n) {
        // std::cout << uniform_int(1,10) << ' ';
        ++hist[uniform_int(2,8)];
    }

    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
}