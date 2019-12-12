#include "../include/simulated_annealing.h"

double unimodalFunction(double x)
{
  return std::exp(-0.2*x)*sin(x) + 1;
}

double multimodalFunction(double x)
{
  return (std::exp(-0.2*x)*sin(x) + 1)*sin(5*x);
}

double jump(double delta, double current_temperature)
{
  return exp(-delta/current_temperature);
}


double simulated_annealing(double (*function)(double x), double left,
                           double right, double maxTemperature, double minTemterature, std::string filename)
{
  std::ofstream file_for_function(filename, *"w");
  file_for_function.precision(7);
  file_for_function.setf(std::ios::fixed);

  file_for_function << "| N | T | x | f(x) | P | +- |\n";
  file_for_function << "| --- | --- | --- | --- | --- | ---| \n";

  std::random_device random;
  std::uniform_real_distribution<> distribution(left, right);
  std::uniform_real_distribution<> normalyzed_distribution(0.0, 1.0);

  double probability = 1;
  bool change = false;
  double point = distribution(random);
  double current_function = function(point);
  double min = current_function;

  double next_point;
  double next_function;
  unsigned int number = 1;

  while(maxTemperature > minTemterature)
    {
      next_point = distribution(random);
      next_function = function(next_point);
      probability = jump(next_function - current_function, maxTemperature);

      if(next_function - current_function < 0)
        {
          current_function = next_function;
          min = next_function;
          point = next_point;
          change = true;
          probability = 1;
        }
      else if (normalyzed_distribution(random) <
               probability)
        {	
          change = true;
          current_function = next_function;
          min = next_function;
          point = next_point;
        }// if
      else {
          change = false;
        }

      file_for_function << "| " << number << " | " << maxTemperature << " | "
                        << point << " | " << current_function;

      file_for_function  << " | " << probability << " | " << change << " |\n";

      maxTemperature = 0.95*maxTemperature;
      number++;

    }// while

  file_for_function << "\nResult: Xmin = " << point << " Fmin = " << min;

  return min;
}
