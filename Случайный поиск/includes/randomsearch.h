#ifndef RANDOMSEARCH_H
#define RANDOMSEARCH_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

double unimodalFunction(double x)
{
  return std::exp(-0.2*x)*sin(x) + 1;
}

double multimodalFunction(double x)
{
  return (std::exp(-0.2*x)*sin(x) + 1)*sin(5*x);
}

double findMin(double (*function)(double x), int number,
               double left, double right)
{
  std::random_device random;
  std::uniform_real_distribution<> distribution(left, right);
  double min = function(distribution(random));
  double temp;
  for (int counter = 1; counter < number; counter++)
  {
      temp = function(distribution(random));
      if (temp < min)
        min = temp;
  }//for
  return min;
}

void Analyze(double leftPoint, double rightPoint)
{
  std::ofstream file_for_N("file_for_N_1.txt");
  file_for_N.precision(6);
  file_for_N.setf(std::ios::fixed);

  std::ofstream file_for_Functions_1("file_for_Functions_1.txt");
  file_for_Functions_1.precision(6);
  file_for_Functions_1.setf(std::ios::fixed);

  std::ofstream file_for_Functions_2("file_for_Functions_2.txt");
  file_for_Functions_2.precision(6);
  file_for_Functions_2.setf(std::ios::fixed);

  file_for_N << "+-------+-------+-------+-------+"
               "-------+-------+-------+-------+"
               "-------+-------+-------+" << std::endl;

  file_for_N << "|  q\\P  |  0.90  | 0.91  | 0.92  |"
               " 0.93  | 0.94  | 0.95  | 0.96  |"
               " 0.97  | 0.98  | 0.99  |" << std::endl;

  file_for_N << "+-------+-------+-------+-------+"
               "-------+-------+-------+-------+"
               "-------+-------+-------+" << std::endl;

  file_for_Functions_1 << "+----------+----------+----------+----------+"
               "----------+----------+----------+----------+"
               "----------+----------+----------+" << std::endl;

  file_for_Functions_1 << "|  q\\P     |  0.90    |  0.91    |  0.92    |"
               "  0.93    |  0.94    |  0.95    |  0.96    |"
               "  0.97    |  0.98    |  0.99    |" << std::endl;

  file_for_Functions_1 << "+----------+----------+----------+----------+"
               "----------+----------+----------+----------+"
               "----------+----------+----------+" << std::endl;

  file_for_Functions_2 << "+----------+-----------+-----------+-----------+"
               "-----------+-----------+-----------+-----------+"
               "-----------+-----------+-----------+" << std::endl;

  file_for_Functions_2 << "|  q\\P     |  0.90     |  0.91     |  0.92     |"
               "  0.93     |  0.94     |  0.95     |  0.96     |"
               "  0.97     |  0.98     |  0.99     |" << std::endl;

  file_for_Functions_2 << "+----------+-----------+-----------+-----------+"
               "-----------+-----------+-----------+-----------+"
               "-----------+-----------+-----------+" << std::endl;

  for (double q = 0.005; q <= 0.1; q += 0.005)
  {
      file_for_N << "| " << q;
      file_for_Functions_1 << "| " << q;
      file_for_Functions_2 << "| " << q;

      for(double P = 0.90; P < 1; P += 0.01)
      {

        int N = static_cast<int>(std::log(1 - P)/std::log(1-q));

        if (N/10 > 10)
          file_for_N << " |  " << N;
        else
          file_for_N << " |   " << N;
        file_for_Functions_1 << " | " << findMin(unimodalFunction, N, leftPoint, rightPoint);
        file_for_Functions_2 << " | " << findMin(multimodalFunction, N, leftPoint, rightPoint);
      }//for

      file_for_N << std::endl;
      file_for_Functions_1 << " |" << std::endl;
      file_for_Functions_2 << " |"  << std::endl;
  }

  file_for_N << "+----------+---------+---------+---------+"
               "---------+---------+---------+---------+"
               "---------+---------+---------+";

  file_for_Functions_1 << "+----------+----------+----------+----------+"
               "----------+----------+----------+----------+"
               "----------+----------+----------+";

  file_for_Functions_2 << "+----------+-----------+-----------+-----------+"
               "-----------+-----------+-----------+-----------+"
               "-----------+-----------+-----------+" << std::endl;

  file_for_N.close();
  file_for_Functions_1.close();
  file_for_Functions_2.close();
}

#endif // RANDOMSEARCH_H
