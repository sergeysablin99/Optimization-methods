#include <iostream>
#include <vector>

using namespace std;

const double epsilon = 0.1;
const int leftBorder = 9;
const int rightBorder = 12;

double f(double x)
{
  return std::exp(-0.2*x)*std::sin(x) + 1;
}

void PassiveSearch(double leftPoint, double rightPoint)
{
  freopen("../OptimalPassive.md" , "w", stdout);
  std::cout << "|Порядковый номер (N)| X  |Значение f(x)|  " << std::endl <<
               "| --- | ----- | --------- |" << std::endl;

  int number = 2*(rightPoint - leftPoint)/epsilon + 1;
  double min = leftPoint;
  double fmin = f(min);

  for (int i = 1; i < number; i++)
    {
      double temp = (rightPoint - leftPoint)*(i + 1)/(number + 1) + leftPoint;
      double ftemp = f(temp);
      if(f(temp) < fmin)
        {
          min = (rightPoint - leftPoint)*i/(number + 1) + leftPoint;
          fmin = f(min);
        }

      std::cout.precision(4);
      std::cout.setf(std::ios::fixed);
      std::cout << "|   " << i << "     | " <<
                   temp << "  | " << f(temp) << " |" << std::endl;
    }

  std::cout << std::endl << "Xmin = " << min << " +- " << (rightPoint - leftPoint)/(number + 1)  << " Fmin = " << f(min);
}//void passiveSerach

unsigned int FindFibonacci(unsigned int number)
{
  if (number <= 2)
    return 1;
  else
    {
      unsigned int number1 = 1;
      unsigned int number2 = 1;

      for (unsigned int counter = 0; counter < number - 2; counter++)
        {
          number2 = number1 + number2;
          number1 = number2 - number1;
        }//for

      return number2;
    }//else
}

void FibonacciSearch(double leftPoint, double rightPoint, unsigned int number)
{
  freopen("../Fibonacci.md" , "w", stdout);

  double xmin = leftPoint;
  double fxmin = f(xmin);

  int fibonacciMaxNumber = 0;

  while(true)
    {
      fibonacciMaxNumber++;
      if (FindFibonacci(fibonacciMaxNumber) >  (rightPoint - leftPoint)/epsilon)
        break;
    }

  double fibonacciPoint = leftPoint + double(FindFibonacci(fibonacciMaxNumber))*
      (rightPoint - leftPoint)/FindFibonacci(fibonacciMaxNumber + 1);
  double fibonacciPointNext = leftPoint + double(FindFibonacci(fibonacciMaxNumber - 1))*
      (rightPoint - leftPoint)/FindFibonacci(fibonacciMaxNumber + 1); //точки Хn и X(n-1)

  std::cout << "| Номер итерации | Начало интервала (аk) |   Конец интервала (bk)  |   Длина интервала (l)  |      x1     |     x2      |   f(X1)      |    f(X2)     |" <<
               std::endl << "| --- | --- | --- | --- | --- | --- | --- | --- |" <<
               std::endl;


  for (unsigned int counter = 1; counter <= fibonacciMaxNumber; counter++)
    {
      std::cout.precision(4);
      std::cout.setf(std::ios::fixed);

      std::cout << "| "  << counter << "|   " << leftPoint << "  |   " <<
                   rightPoint << "  |   " <<
                   rightPoint - leftPoint <<  "  |   "  << fibonacciPoint <<  "  |   "
                << fibonacciPointNext <<  "  |   " <<
                   f(fibonacciPoint) <<  "  |   " <<
                   f(fibonacciPointNext) <<  "    |"  << std::endl;


      if (f(fibonacciPoint) > f(fibonacciPointNext))
        {
          rightPoint = fibonacciPoint;
          fibonacciPoint = fibonacciPointNext;
          fibonacciPointNext = leftPoint + double(FindFibonacci(fibonacciMaxNumber - 1 - counter))*
              (rightPoint - leftPoint)/FindFibonacci(fibonacciMaxNumber + 1);

          xmin = fibonacciPointNext;
          fxmin = f(xmin);
        } else
        {
          leftPoint = fibonacciPointNext;
          fibonacciPointNext = leftPoint + double(FindFibonacci(fibonacciMaxNumber - 1 - counter))*
              (rightPoint - leftPoint)/FindFibonacci(fibonacciMaxNumber + 1);

          xmin = fibonacciPoint;
          fxmin = f(xmin);
        }//else
    }//for

  std::cout << std::endl << "Xmin = " << xmin << " Fmin = " << f(xmin);
}// void FibonacciSearch

int main()
{
  setlocale(LC_ALL, "Rus");

  PassiveSearch(leftBorder, rightBorder);

  std::cout << std::endl;

  FibonacciSearch (leftBorder, rightBorder, 25);

  return 0;
}
