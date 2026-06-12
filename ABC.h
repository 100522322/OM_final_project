//
// Created by hugo2 on 12/06/2026.
//

#ifndef ABC_H
#define ABC_H

#include <vector>
#include "Graph.h"

struct FoodSource {
  std::vector<int> individual;
  int fitness;
  int trials;

};

class ABC {
  public:
    Graph& graph;

    int num_of_colors;
    int colony_size;
    int limit;
    int iterations;

    std::vector<FoodSource> foods;
    FoodSource best;
    FoodSource worst;

    ABC(Graph& graph, int num_of_colors, int colony_size, int limit, int iterations);
    std::vector<int> run();

    void initialize();
    void employed_phase();
    void onlooker_phase();
    void scout_phase();
    void update_best_and_worst();

    std::vector<int> generate_neighbor(const std::vector<int>& individual);
    std::vector<double> compute_prob();
    double compute_score(int fitness);
    int select_food(const std::vector<double>& probabilities) const;


};



#endif //ABC_H
