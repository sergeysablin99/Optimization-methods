#include <iostream>
#include "../include/change_criterion.hpp"
#include <cmath>

int main()
{
    std::vector<Alternative> Alternatives(4);
    Alternatives[0] = Alternative("Lipeck", 5, 2, 2, 5);
    Alternatives[1] = Alternative("Sosnoviy Bor", 2, 5, 2, 4);
    Alternatives[2] = Alternative("Lesnaya Zhemchuzhina", 3, 2, 4, 4);
    Alternatives[3] = Alternative("Sosny", 4, 4, 5, 2);
    freopen("RESULTS.md", "w", stdout);
    Print(Alternatives);

    int main_cr = 0;
    std::vector<double> part = {1, 0.4, 0.2, 0.3};
    Alternative max_ch =  ChangeCriterion(Alternatives, main_cr, part);

    std::pair<int, int> main_pair = {0, 1};
    Alternative max_par = Pareto(Alternatives, main_pair);

    std::vector<double> weights = {5, 4, 4, 1};
    Alternative max_weights = Weights(Alternatives, weights);
    Alternative max_compare = Compare(Alternatives, weights);

    std::cout << "\nСhange criterion method results: " << max_ch.name << "\n";
    std::cout << "\nPareto method results: " << max_par.name << "\n";
    std::cout << "\nWeights method results: " << max_weights.name << "\n";
    std::cout << "\nHierarchy analysis method results: " << max_compare.name << "\n";
    return 0;
}
