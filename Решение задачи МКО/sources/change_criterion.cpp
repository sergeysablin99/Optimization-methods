#include "../include/change_criterion.hpp"

Alternative::Alternative()
{
  name = "";
  criteries = {0, 0, 0, 0};
}

Alternative::Alternative(const std::string &name_, const double &quality, const double &service, const double &meal,
                         const double &distance)
{
  name = name_;
  criteries = {quality, service, meal, distance};
}

Alternative ChangeCriterion(const std::vector<Alternative>& Alternatives, const int& main_cr,const std::vector<double>& part)
{
  std::vector<double> max_values = Alternatives[0].criteries;
  std::vector<double> min_values = Alternatives[0].criteries;

  for (size_t j = 0; j < Alternatives[0].criteries.size(); ++j)
    for (size_t i = 1; i < Alternatives.size(); ++i)
      {
        if (max_values[j] < Alternatives[i].criteries[j])
          max_values[j] = Alternatives[i].criteries[j];
        else
          if (min_values[j] > Alternatives[i].criteries[j])
            min_values[j] = Alternatives[i].criteries[j];
      }

  std::vector<Alternative> part_match;
  bool flag = true;

  for (size_t i = 0; i < Alternatives.size(); ++i)
    {
      for (size_t j = 0; j < Alternatives[i].criteries.size(); ++j)
        {
          if (j != main_cr)
            if (Alternatives[i].criteries[j] < max_values[j] * part[j])
              flag = false;
        }

      if (flag)
        part_match.push_back(Alternatives[i]);
      else
        flag = !flag;
    }

  Alternative max = part_match[0];
  if (part_match.size() > 1)
    {
      for (size_t i = 1; i < part_match.size(); i++)
        {
          if (part_match[i].criteries[main_cr] > max.criteries[main_cr])
            max = part_match[i];
        }
    }
  return max;
}

double ManhattanDistance(const double& x1, const double& y1, const double& x2, const double& y2)
{
  return std::abs(x1 - x2) + std::abs(y1 - y2);
}

Alternative Pareto(const std::vector<Alternative>& Alternatives, const std::pair<int, int>& main_pair)
{
  double perf_x = 10;
  double perf_y = 10;
  Alternative max_par = Alternatives[0];
  double min_dis = abs(perf_x - Alternatives[0].criteries[main_pair.first])
      + abs(perf_y - Alternatives[0].criteries[main_pair.second]);
  for (size_t i = 0; i < Alternatives.size(); i++)
    {
      std::cout << "\nFor Alternative " << Alternatives[i].name << " point is: (";
      std::cout << Alternatives[i].criteries[main_pair.first] << "; ";
      std::cout << Alternatives[i].criteries[main_pair.second] << ")\n";

      double dis = ManhattanDistance(perf_x, perf_y,
                                     Alternatives[i].criteries[main_pair.first], Alternatives[i].criteries[main_pair.second]);

      if (dis < min_dis)
        {
          max_par = Alternatives[i];
          min_dis = dis;
        }
    }
  return max_par;
}


void NormalizeAlternatives(std::vector<Alternative>& opt)
{
  for (size_t i = 0; i < opt[0].criteries.size(); i++)
    {
      double sum = 0;

      for (size_t j = 0; j < opt.size(); j++)
        sum += opt[j].criteries[i];

      for (size_t j = 0; j < opt.size(); j++)
        opt[j].criteries[i] /= sum;
    }
  Print(opt);
}

std::vector<double> NormalizeMas(const std::vector<double>& vec)
{
  std::vector<double> temp = vec;
  double sum = std::accumulate(temp.begin(), temp.end(), 0.0);

  for(size_t i = 0; i < temp.size(); i++)
    temp[i] /= sum;

  std::cout << "\n";
  return temp;
}

Alternative Weights(std::vector<Alternative> Alternatives, const std::vector<double>& weights)
{
  std::vector<double> norm_weights = NormalizeMas(weights);
  std::cout << "Normalized weights massive: ";

  for (size_t i =0; i < norm_weights.size(); i++)
    std::cout << norm_weights[i] << " ";

  std::cout << "\n\n";

  NormalizeAlternatives(Alternatives);
  std::vector<double> ideal(norm_weights.size());
  Alternative max_weights;

  double max_val = 0;
  std::cout << "\nResult vector: ";

  for (size_t i = 0; i < Alternatives.size(); i++)
    {
      for (size_t j = 0; j < norm_weights.size(); j++)
        ideal[i] += norm_weights[j] * Alternatives[i].criteries[j];

      std::cout << ideal[i] << " ";

      if (i == 0 || ideal[i] > max_val)
        {
          max_weights = Alternatives[i];
          max_val = ideal[i];
        }
    }
  std::cout << "\n";
  return max_weights;
}

std::vector<double> CompareWeights(const std::vector<double>& vec)
{
  std::vector<double> rowSum(vec.size());
  std::vector<double> colSum(vec.size());
  std::vector<double> result(vec.size());

  std::cout << "|  | ";
  for (size_t i = 1 ; i <= vec.size(); i++)
    {
      std::cout << i << " | ";
    }
  std::cout << " Sum|\n";
  std::cout << "| ";

  for (size_t i = 0 ; i <= vec.size() + 2; i++)
    std::cout << " --- | ";

  std::cout << "\n";
  for (size_t i = 0; i < vec.size(); i++)
    {
      std::cout << "| " << i + 1 << " | ";
      for (size_t j = 0; j < vec.size(); j++)
        {
          if (vec[i] == vec[j])
            {
              std::cout << "1 | ";
              result[i] += 1;
              colSum[i] += 1;
            } else
            if (vec[i] > vec[j])
              {
                if (vec[i] - vec[j] == 1)
                  {
                    result[i] += 3;
                    colSum[i] += 0.333;
                    std::cout << "3 | ";
                  } else if (vec[i] - vec[j] == 2)
                  {
                    result[i] += 5;
                    colSum[i] += 0.2;
                    std::cout << "5 | ";
                  } else
                  {
                    std::cout << "7 | ";
                    result[i] += 7;
                    colSum[i] += 0.142;
                  }
              } else {
                if (vec[j] - vec[i] == 1)
                  {
                    std::cout << "1 / 3 | ";
                    result[i] += 0.333;
                    colSum[i] += 3;
                  } else if (vec[j] - vec[i] == 2)
                  {
                    std::cout << "1 / 5 | ";
                    result[i] += 0.2;
                    colSum[i] += 5;
                  } else
                  {
                    std::cout << "1 / 7 | ";
                    result[i] += 0.142;
                    colSum[i] += 7;
                  }
              }
          rowSum[i] = result[i];
        }
      std::cout << result[i] << " |\n";
    }

  double sum = 0.0;
  double consistencyRatio = 0.0;
  std::vector<double> normalizedCriteries(vec.size());
  normalizedCriteries = NormalizeMas(rowSum);

  for (size_t k = 0 ; k < colSum.size(); k++)
    {
      sum += normalizedCriteries[k];
    }

  for (size_t k = 0 ; k < colSum.size(); k++)
    {
      consistencyRatio += normalizedCriteries[k]*colSum[k]/sum;
    }

  consistencyRatio = (consistencyRatio - 4)/(3*0.9);

  std::cout << "For weights matrix the consistency ratio is: ";
  std::cout << consistencyRatio << " \n";


  result = NormalizeMas(result);
  return result;
}

std::vector<double> CompareAlternatives(const std::vector<Alternative>& vec, const int& num)
{
  std::vector<double> rowSum(vec.size());
  std::vector<double> colSum(vec.size());
  std::vector<double> result(vec.size());

  for (size_t i = 0; i < vec.size(); i++)
    {
      std::cout << "| " << vec[i].name << " | ";
      for (size_t j = 0; j < vec.size(); j++)
        {
          if (vec[i].criteries[num] == vec[j].criteries[num])
            {
              std::cout << "1 | ";
              result[i] += 1;
              colSum[i] += 1;
            }
          else if (vec[i].criteries[num] > vec[j].criteries[num])
            {
              if (vec[i].criteries[num] - vec[j].criteries[num] == 1)
                {
                  std::cout << "3 | ";
                  result[i] += 3;
                  colSum[i] += 0.333;
                } else if (vec[i].criteries[num] - vec[j].criteries[num] == 2) {
                  std::cout << "5 | ";
                  result[i] += 5;
                  colSum[i] += 0.2;
                } else {
                  std::cout << "7 | ";
                  result[i] += 7;
                  colSum[i] += 0.142;
                }
            } else {
              if (vec[j].criteries[num] - vec[i].criteries[num] == 1)
                {
                  std::cout << "1 / 3 | ";
                  result[i] += 0.333;
                  colSum[i] += 3;
                } else if (vec[j].criteries[num] - vec[i].criteries[num] == 2) {
                  std::cout << "1 / 5 | ";
                  result[i] += 0.2;
                  colSum[i] += 5;
                } else {
                  std::cout << "1 / 7 | ";
                  result[i] += 0.142;
                  colSum[i] += 7;
                }
            }
        }
      std::cout << result[i] << " |\n";
      rowSum[i] = result[i];
    }

  double sum = 0.0;
  double consistencyRatio = 0.0;
  std::vector<double> normalizedCriteries(vec.size());
  normalizedCriteries = NormalizeMas(rowSum);

  for (size_t k = 0 ; k < colSum.size(); k++)
    {
      sum += normalizedCriteries[k];
    }

  for (size_t k = 0 ; k < colSum.size(); k++)
    {
      consistencyRatio += normalizedCriteries[k]*colSum[k]/sum;
    }

  consistencyRatio = (consistencyRatio - 4)/(3*0.9);

  std::cout << "For ";
  switch(num) {
        case 0:
          std::cout << "Quality";
          break;
        case 1:
          std::cout << "Service";
          break;
        case 2:
          std::cout << "Food";
          break;
        case 3:
          std::cout << "Distance";
          break;
        }
  std::cout << " matrix the consistency ratio is: ";
  std::cout << consistencyRatio << " \n";

  result = NormalizeMas(result);
  return result;
}

Alternative Compare(const std::vector<Alternative>& Alternatives, const std::vector<double>& weights)
{
  std::vector<std::vector<double>> Comparison(Alternatives[0].criteries.size());
  for (size_t k = 0 ; k < Alternatives[0].criteries.size(); k++)
    {
      switch(k) {
        case 0:
          std::cout << "Quality:\n";
          break;
        case 1:
          std::cout << "Service:\n";
          break;
        case 2:
          std::cout << "Food:\n";
          break;
        case 3:
          std::cout << "Distance:\n";
          break;
        }
      std::cout << "|  | ";
      for (size_t i = 0; i < Alternatives.size(); i++)
        {
          std::cout << Alternatives[i].name << " | ";
        }
      std::cout << "Sum |\n";
      std::cout << "| --- | --- | --- | --- | --- | --- | --- |\n";
      Comparison[k] = CompareAlternatives(Alternatives, k);
    }

  std::cout << "Weights:\n";
  std::vector<double> weights_compare = CompareWeights(weights);
  std::vector<double> result_mas(weights_compare.size());
  Alternative max_compare;
  double max_val = 0;
  std::cout << "Result vector: ";

  for (size_t i = 0; i < Comparison.size(); i++)
    {
      for (size_t j = 0; j < weights_compare.size(); j++)
        {
          result_mas[i] += weights_compare[j] * Comparison[i][j];
        }
      std::cout << result_mas[i] << " ";
      if (i == 0 || result_mas[i] > max_val)
        {
          max_compare = Alternatives[i];
          max_val = result_mas[i];
        }
    }
  return max_compare;
}

void Print(const std::vector<Alternative>& vec)
{
  std::cout << "| Name | Quality | Service | Meal | Distance |";
  std::cout << "\n| --- | ";
  for (size_t i = 0; i < vec[0].criteries.size(); i++)
    {
      std::cout << "--- | ";
    }
  for (size_t j = 0; j < vec.size(); j++)
    {
      std::cout << "\n";
      std::cout << "| " << vec[j].name << " | ";
      for (size_t i = 0; i < vec[j].criteries.size(); i++)
        {
          std::cout << vec[j].criteries[i] << " | ";
        }
    }
}

