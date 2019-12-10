#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <string>

double unimodalFunction(double x);

double multimodalFunction(double x);

double jump(double delta, double current_temperature);

double simulated_annealing(double (*function)(double x), double left,
                           double right, double maxTemperature, double minTemterature, std::string filename);

#endif // SIMULATED_ANNEALING_H
