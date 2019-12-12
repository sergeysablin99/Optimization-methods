#include "../include/filtering.h"


double signal(const double x)
{
  return (sin(x) + 0.5);
}

double noisySignal(const double x, const  double noiseAmplitude)
{
  std::random_device random;
  std::uniform_real_distribution<> distribution( -noiseAmplitude/2, noiseAmplitude/2);

  return signal(x) + distribution(random);
}

std::vector<double> noisySignalValues(const double xmin, const double xmax,
                                      const int numberOfPoints, const double noiseAmplitude)
{
  std::vector<double> values(numberOfPoints);

  for (size_t i = 0; i < numberOfPoints; i++)
    {
      values[i] = noisySignal(xmin + i*(xmax - xmin)/numberOfPoints, noiseAmplitude);
    }

  return values;
}

double filteredSignal(const int x, const std::vector<double>& noisySignal,
                      const std::vector<double>& weights, const int sizeOfGap)
{
  double multiplication = 1;
  int middle = (sizeOfGap - 1)/2;

  if (x <= middle)
    {
      for (size_t j = 0; j < x + middle; j++)
        {
          multiplication *= pow(noisySignal[j], weights[j]);
        }
    }
  else if (x >= noisySignal.size() - middle)
    {
      for (size_t j = x - middle; j < noisySignal.size(); j++)
        {
          multiplication *= pow(noisySignal[j], weights[j + middle - x]);
        }
    }
  else
    {
      for (size_t j = x - middle; j <= x + middle; j++)
        {
          multiplication *= pow(noisySignal[j], weights[j + middle - x]);
        }
    }

  return multiplication;
}

double noiseness(const std::vector<double>& noisySignal, const std::vector<double> weights,
                 const int sizeOfGap, const int numberOfPoints)
{
  double max = 0;
  double delta = 0;

  for (int k = 1; k < numberOfPoints; k++)
    {
      delta = abs(filteredSignal(k, noisySignal, weights, sizeOfGap)
                  - filteredSignal(k - 1, noisySignal, weights, sizeOfGap));
      if (delta > max)
        max = delta;
    }

  return max;
}

double discrepancy(const std::vector<double>& noisySignal, const std::vector<double> weights,
                   const int sizeOfGap, const int numberOfPoints)
{
  double max = 0;
  double delta = 0;
  for (int k = 0; k < numberOfPoints; k++)
    {
      delta = abs(filteredSignal(k, noisySignal, weights, sizeOfGap) -
                  noisySignal[k]);
      if (delta > max)
        max = delta;
    }
  return max;
}

std::vector<double> randomWeights(const int sizeOfGap)
{
  std::random_device random;
  double sum = 1;
  std::uniform_real_distribution<> distribution(0, sum);

  std::vector<double> weights;
  for (size_t weight = 0; weight < sizeOfGap; weight++)
    weights.push_back(0);

  weights[static_cast<int>((sizeOfGap - 1)/2)] = distribution(random);

  for (size_t i = 1; i < static_cast<int>((sizeOfGap - 1)/2) ; i++)
    {
      sum = 0;
      for (size_t j = i + 1; j <= sizeOfGap - i; j++)
        sum += weights[j];
      sum = 1 - sum;

      weights[i] = 0.5*distribution(random);
      weights[sizeOfGap - i - 1] = weights[i];
    }

  sum = 0;
  for (size_t s = 1; s <= sizeOfGap - 2; s++)
    {
      sum += weights[s];
    }

  sum = 1 - sum;
  weights[0] = 0.5*sum;
  weights[sizeOfGap - 1] = weights[0];

  return weights;
}


double linearScalarization(double lambda, const std::vector<double>& noisySignal, const std::vector<double> weights,
                           const int sizeOfGap, const int numberOfPoints)
{
  return lambda*noiseness(noisySignal, weights, sizeOfGap, numberOfPoints) +
      (1 - lambda)*discrepancy(noisySignal, weights, sizeOfGap, numberOfPoints);
}

void findValues(const double xmin, const double xmax, const int numberOfPoints,
                const int sizeOfGap, const double noiseAmplitude, double probability,
                double fallibility, std::string filename, std::string fileForNoise,
                 std::string fileForFilter, std::string fileForWName)
{
  std::ofstream file(filename, 'w');
  std::ofstream fileForW(fileForWName, 'w');
  file << "| h | dis | alpha | w | d |\n";
  file << "| --- | --- | --- | --- | --- |\n";

  double numberOfExpriments = log(1 - probability)/log(1 - fallibility/(xmax - xmin));

  std::vector<double> currentWeights;
  std::vector<double> currentBestWeights;
  std::vector<double> bestWeights;
  std::vector<double> noisySignal = noisySignalValues(xmin, xmax, numberOfPoints, noiseAmplitude);
  std::ofstream noise(fileForNoise, 'w');
  for (size_t t = 0; t < noisySignal.size(); t++)
    {
      noise << "(" << xmin + t*(xmax - xmin)/numberOfPoints << ";" << noisySignal[t] << ")\n";
    }

  double JlocalMin = 9999;
  double Jmin = 999;
  double Jcurrent = 0;
  double dist = 9999;
  double bestLambda = 0;

  double currentW = 0;
  double currentD = 0;

  double minW = 99999;
  double minD = 99999;
  double minDist = 9999;

  for (double lambda = 0.0; lambda <= 1; lambda += 0.1)
    {
      JlocalMin = 9999;
      currentWeights.clear();
      for (int counter = 0; counter < numberOfExpriments; counter++)
        {
          currentWeights = randomWeights(sizeOfGap);
          Jcurrent = linearScalarization(lambda, noisySignal, currentWeights, sizeOfGap, numberOfPoints);

          if (Jcurrent < JlocalMin)
            {
              currentBestWeights = currentWeights;
              JlocalMin = Jcurrent;
            }
        }
//      for (auto t:currentWeights)
//        std::cout << t << " ";
//      std::cout << "\n";
      currentW = noiseness(noisySignal, currentWeights, sizeOfGap, numberOfPoints);
      currentD = discrepancy(noisySignal, currentWeights, sizeOfGap, numberOfPoints);
      dist = std::max(currentW, currentD);

      file << "| " << lambda << " | " << dist << " | [ ";
      for (auto weight:currentBestWeights)
        file << weight << ", ";
      file << " ] | " << currentW << " | " << currentD << " |\n";

      if (dist < minDist || (dist == minDist && (currentW < minW || currentD < minD)))
        {
          Jmin = lambda*currentW + (1 - lambda)*currentD;
          minDist = dist;
          minW = currentW;
          minD = currentD;
          bestLambda = lambda;
          bestWeights = currentWeights;
        }
      fileForW << char(65 + lambda*10) << " = (" << currentW << ", " << currentD << ")\n";

    }

  file << "\n\n| h* | J | w | d|\n | - | - | - | - |\n" << "|" <<
          bestLambda << " | " << Jmin << " | " << minW << " | " << minD << " |";

  std::ofstream fileForFilteredSignal(fileForFilter, 'w');
  for (size_t k= 0; k < numberOfPoints; k++)
    {
      fileForFilteredSignal << "(" << xmin + k*(xmax - xmin)/numberOfPoints << ";" <<
                               filteredSignal(k, noisySignal, bestWeights, sizeOfGap) << ")\n";
    }
}
