#include "../include/Genetic_algorythm.h"


double function(double x, double y)
{
  return cos(x)*cos(y)*exp(y/2);
}

void selection(vector<point>& points)
{
  double sum = 0;
  double min = 9999;
  size_t minIndex = 0;

  for (size_t point = 0; point < points.size(); point++)
    {
      sum += function(points[point].x, points[point].y);
      if (function(points[point].x, points[point].y) < min)
        {
          min = function(points[point].x, points[point].y);
          minIndex = point;
        }
    }

  random_device random;
  uniform_real_distribution<double> distribution(0, 1);

  for (size_t point = 0; point < points.size(); point++)
    {
      if (distribution(random) <= function(points[point].x, points[point].y)/sum)
      {
        points.erase(points.begin() + point);
        break;
      }
    }

  if (points.size() == 4)
    points.erase(points.begin() + minIndex);
}

void mutation(vector<point>& points)
{
  const double mutationProbability = 0.25;
  random_device random;
  uniform_real_distribution<double> distribution(0, 1);
  uniform_real_distribution<double> mutationDistribution(0.01, 0.1);

  for (size_t point = 0; point < points.size(); point++)
    {
      if (distribution(random) < mutationProbability)
        {
          double mutationValue = mutationDistribution(random);
          if (distribution(random) < 0.5)
            {
              if (points[point].x + mutationValue > 2)
                {
                  points[point].x -= mutationValue;
                }
              else
                {
                  points[point].x += mutationValue;
                }
            }
          else
              if (points[point].x - mutationValue < -2)
                {
                  points[point].x += mutationValue;
                }
              else
                {
                  points[point].x -= mutationValue;
                }


          mutationValue = mutationDistribution(random);

          if (distribution(random) < mutationProbability)
            {
              if (points[point].y + mutationValue > 2)
                {
                  points[point].y -= mutationValue;
                }
              else
                {
                  points[point].y += mutationValue;
                }
            }
          else
              if (points[point].y - mutationValue < -2)
                {
                  points[point].y += mutationValue;
                }
              else
                {
                  points[point].y -= mutationValue;
                }
        }
    }
}

void crossover(vector<point>& points)
{
  for (size_t i = 0; i < points.size(); i++)
    {
      for (size_t j = 0; j < points.size() - i - 1; j++)
        {
          if (function(points[j].x, points[j].y) <
              function(points[j + 1].x, points[j + 1].y))
            {
              std::swap(points[j], points[j + 1]);
            }
        }
    }

  point child1;
  child1.x = points[0].x;
  child1.y = points[1].y;

  point child2;
  child2.x = points[1].x;
  child2.y = points[0].y;

  point child3;
  child3.x = points[0].x;
  child3.y = points[2].y;

  point child4;
  child4.x = points[2].x;
  child4.y = points[0].y;

  points[0] = child1;
  points[1] = child2;
  points[2] = child3;
  points.push_back(child4);
}

void genetic()
{
  ofstream f("results.md", 'w');
  f << "| № | X | Y | FIT | Max result | Average result |\n";
  f << "| --- | --- | --- | --- | --- | --- |\n";


  random_device random;
  uniform_real_distribution<double> distribution(-2, 2);

  vector<point> points(4);

  for (size_t i = 0; i < 4; i++)
    {
      points[i].x = distribution(random);
      points[i].y = distribution(random);
    }

  double max = 0;
  double sredn = 0;

  for (size_t i = 0; i <= 100; i++)
    {
      max = 0;
      sredn = 0;
      // Найдем максимум
      for (size_t j = 0; j < points.size(); j++)
        {
          if (function(points[j].x, points[j].y) > max)
            max = function(points[j].x, points[j].y);
        }
      //Найдем среднее
      for (size_t j = 0; j < points.size(); j++)
        {
          sredn += function(points[j].x, points[j].y);
        }
      sredn = sredn/points.size();

      for (size_t j = 0; j < points.size(); j++)
        {
          if ((j + 4)%4 == 0)
            f << "| " << i;
          else
            f << " | ";

          f << " | " << points[j].x << " | " << points[j].y << " | " <<
               function(points[j].x, points[j].y) << " | " ;
          if ((j + 4)%4 == 0)
            f << max << " | " << sredn << " |\n";
          else
            f << " | |\n";
        }

      selection(points);
      crossover(points);
      mutation(points);
    }
}
