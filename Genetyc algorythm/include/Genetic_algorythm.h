#ifndef GENETIC_ALGORYTHM_H
#define GENETIC_ALGORYTHM_H

#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include <iostream>

using namespace std;

struct point
{
  double x;
  double y;
};

double function(double x, double y);
void selection(vector<point>& points);
void mutation(vector<point>& points);
void crossover(vector<point>& points);
void genetic();

#endif // GENETIC_ALGORYTHM_H
