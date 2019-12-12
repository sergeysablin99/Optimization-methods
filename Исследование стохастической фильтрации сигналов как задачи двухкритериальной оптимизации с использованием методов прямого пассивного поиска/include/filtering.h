#ifndef FILTERING_H
#define FILTERING_H

#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include <iostream>

double signal(const double x);

double noisySignal(const double x, const  double noiseAmplitude);

std::vector<double> noisySignalValues(const double xmin, const double xmax,
                                      const int numberOfPoints, const double noiseAmplitude);

double filteredSignal(const int x, const std::vector<double>& noisySignal,
                      const std::vector<double>& weights, const int sizeOfGap);

double noiseness(const std::vector<double>& noisySignal, const std::vector<double> weights,
                 const int sizeOfGap, const int numberOfPoints);

double discrepancy(const std::vector<double>& noisySignal, const std::vector<double> weights,
                   const int sizeOfGap, const int numberOfPoints);

std::vector<double> randomWeights(const int sizeOfGap);

double linearScalarization(double lambda, const std::vector<double>& noisySignal, const std::vector<double> weights,
                           const int sizeOfGap, const int numberOfPoints);

void findValues(const double xmin, const double xmax, const int numberOfPoints,
                const int sizeOfGap, const double noiseAmplitude, double probability,
                double fallibility, std::string filename, std::string fileForNoise,
                 std::string fileForFilter, std::string fileForWName);
#endif // FILTERING_H
