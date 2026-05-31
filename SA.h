//
// Created by hugo2 on 30/05/2026.
//

#ifndef SA_H
#define SA_H

#include <vector>
#include "Graph.h"


class SA {
  public:
    int num_of_colors;
    Graph& graph;
    int iterations;
    float temperature;
    float alpha;



    SA(int num_of_colors, Graph& graph, int iterations, float temperature, float alpha);
    std::vector<int> run();
    std::vector<int> mutate(std::vector<int> individual);
};



#endif //SA_H
