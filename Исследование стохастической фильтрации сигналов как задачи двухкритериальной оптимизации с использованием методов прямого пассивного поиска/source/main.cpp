#include "../include/filtering.h"
#include <iostream>


int main()
{
  findValues(0, 3.14, 100, 3, 0.5, 0.95, 0.01, "file_for_3.md", "file_for_noise_3.md",
             "file_for_filter_3.md", "fole_for_w_3.md");
  findValues(0, 3.14, 100, 5, 0.5, 0.95, 0.01, "file_for_5.md", "file_for_noise_5.md",
             "file_for_filter_5.md", "fole_for_w_5.md");

  std::cout << "Job's done";

  return 0;
}
