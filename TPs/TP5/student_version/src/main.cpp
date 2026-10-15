#include <iostream>
#include <string>
#include <iomanip>
#include <functional>
#include <random>
#include <chrono>

#include "DualNumber.hpp"


// g++ -Wall -O2 -std=c++14 main.cpp -o dualNum


///////////////////////////////////////////////////////////////////////////////////////
/// standard numerical central derivalitve for dual numbers
/// input is the fuction of dual number already defined and a dual numnber.
/// this is just for commodity, this central derivative fuction should only use the 'real' part of the dual numbers
// template<typename T>
// T centralDerivative(std::function<DualNumber<T>(const DualNumber<T>&)> f, const DualNumber<T> &x, const T &dx){
//     return f(x).real(); 
// }





///////////////////////////////////////////////////////////////////////////////////////
int main(){

    // function to evaluate using dual numbers
    std::function<DualNumber<double>(const DualNumber<double>&)> f;

    // its derivative formula, to compare our result with the good result
    std::function<double(const double&)> df;

    // easy test
    f  = [](const DualNumber<double> &x){return x*x;}; // f(x)  = x*x
    df = [](const double &x){return 2*x;};             // f'(x) = 2x

    // badass test
    // f(x) = log(2|x|) + exp(x) + sin(x^3)
    // f  = [](const DualNumber<double>&x){return DualNumber<double>::log(DualNumber<double>::abs(x)*2) + DualNumber<double>::exp(x) +  DualNumber<double>::sin(DualNumber<double>::pow(x,3));};
    // df = [](const double&x){return 1.0/x + std::exp(x) + (std::pow(x,2)*3.0)*std::cos(std::pow(x,3));};


    const unsigned int precision = 20;

    // select seed from time and some random distribution
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::cout << "seed : " << seed << std::endl;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> uniformRealDistribution(-20,20);
    DualNumber<double> x(0,1);  // f(x) = x  => sa dérivée est 1, et x prendra des valeurs dans la boucle for

    // make some tests
    for(unsigned int i=0; i< 10; ++i){
        // select a value for x over the selected distribution
        x.real() = uniformRealDistribution(gen);
        // f(x) via dual numbers
        std::cout << std::setprecision(5) << "function : f (" << x.real() << ") = " << std::setprecision(precision) << f(x).real() << std::endl;
        // f'(x) via computer algebra or derivative function
        std::cout << std::setprecision(5) << "comp alg : f'(" << x.real() << ") = " << std::setprecision(precision) << df(x.real()) << std::endl;
        // f'(x) via dual numbers
        std::cout << std::setprecision(5) << "dual nb  : f'(" << x.real() << ") = " << std::setprecision(precision) << f(x).dual() << std::endl;
        // f'(x) via regular numerical differentiation
        //std::cout << std::setprecision(5) << "numerical: f'(" << x.real() << ") = " << std::setprecision(precision) << centralDerivative<double>(f,x,1.0e-10) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
