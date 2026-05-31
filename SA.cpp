//
// Created by hugo2 on 30/05/2026.
//

#include "SA.h"
#include "Graph.h"
#include <cmath>


SA::SA(int num_of_colors, Graph& graph, int iterations, float temperature, float alpha)
: num_of_colors(num_of_colors),
  graph(graph),
  iterations(iterations),
  temperature(temperature),
  alpha(alpha){}

std::vector<int> SA::run(){

   std::vector<int> current_individual = graph.random_color_graph(num_of_colors);

   int current_fitness = graph.fitness(current_individual);
   int best_fitness = current_fitness;
   int worst_fitness = current_fitness;


   for(int i = 0; i < iterations; i++){
        std::vector<int> candidate = mutate(current_individual);
        int cand_fitness = graph.fitness(candidate);

        int delta = cand_fitness - current_fitness;

        if (delta < 0){
          current_fitness = cand_fitness;
          current_individual = candidate;

          if (cand_fitness < best_fitness){
            best_fitness = cand_fitness;
          }

        }else{

          if (worst_fitness < cand_fitness){
            worst_fitness = cand_fitness;
          }

          float probability = exp((-delta)/temperature);
          float acceptance = rand()/ (float)RAND_MAX;

          if (acceptance < probability){
            current_fitness = cand_fitness;
            current_individual = candidate;
          }
        }
       temperature *= alpha;
   }
   std::vector<int> result;
   result.push_back(best_fitness);
   result.push_back(worst_fitness);

   return result;
}

std::vector<int> SA::mutate(std::vector<int>  individual){
  std::vector<int> neighbour = individual;

  int node = rand() % neighbour.size();

  int old_color = individual[node];
  int new_color = old_color;

  if (num_of_colors > 1){
    while(new_color == old_color){
      new_color = rand() % num_of_colors;
    }
  }
  neighbour[node] = new_color;
  return neighbour;
}