#include "../include/simulated_annealing.h"

const double leftPoint = 9.0;
const double rightPoint = 12.0;

int main()
{
  simulated_annealing (unimodalFunction, leftPoint, rightPoint, 10000, 0.01, "unimodalFunction.md");
  simulated_annealing (multimodalFunction, leftPoint, rightPoint, 10000, 0.01, "multimodalFunction.md");
  std::cout << "Job's done";
  return 0;
}
