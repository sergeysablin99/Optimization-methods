#ifndef INCLUDE_CHANGE_CRITERION_HPP_
#define INCLUDE_CHANGE_CRITERION_HPP_

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <numeric>

struct Alternative
{
  std::string name;
  std::vector<double> criteries;

  Alternative();

  Alternative(const std::string &name_, const double &tr, const double &sr,
              const double &f, const double &dis);
};

Alternative ChangeCriterion(const std::vector<Alternative>& Alternatives, const int& main_cr,const std::vector<double>& part);
Alternative Pareto(const std::vector<Alternative>& Alternatives, const std::pair<int, int>& main_pair);
Alternative Weights(std::vector<Alternative> Alternatives, const std::vector<double>& weights);
Alternative Compare(const std::vector<Alternative>& Alternatives, const std::vector<double>& weights);

std::vector<double> NormalizeMas(const std::vector<double>& vec);
void NormalizeAlternatives(std::vector<Alternative>& opt);
double ManhattanDistance(const double& x1, const double& y1, const double& x2, const double& y2);

std::vector<double> CompareWeights(const std::vector<double>& vec);
std::vector<double> CompareAlternatives(const std::vector<Alternative>& vec, const int& num);

void Print(const std::vector<Alternative>& vec);

#endif // INCLUDE_CHANGE_CRITERION_HPP_
