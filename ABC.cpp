//
// Created by hugo2 on 12/06/2026.
//

#include "ABC.h"

#include <iostream>
#include <ostream>
#include <vector>

ABC::ABC(Graph& graph, int num_of_colors, int colony_size, int limit, int iterations)
    : graph(graph),
      num_of_colors(num_of_colors),
      colony_size(colony_size),
      limit(limit),
      iterations(iterations) {}


std::vector<int> ABC::run(){
  initialize();

  for (int iter = 0; iter < iterations; iter++) {
    employed_phase();
    onlooker_phase();
    scout_phase();

    update_best_and_worst();
    if (best.fitness == 0) {
      break;
    }

  }
  std::vector<int> result;
  result.push_back(best.fitness);
  result.push_back(worst.fitness);
  return result;
};


void ABC::initialize(){
  foods.clear();

  for (int i=0; i < colony_size; i++){

    FoodSource food;
    food.individual = graph.random_color_graph(num_of_colors);
    food.fitness = graph.fitness(food.individual);
    food.trials = 0;

    foods.push_back(food);
  }
  best = foods[0];
  worst = foods[0];
  update_best_and_worst();
}

void ABC::employed_phase() {
  for (int i=0; i < colony_size; i++) {
    std::vector<int> candidate = generate_neighbor(foods[i].individual);
    int candidate_fitness = graph.fitness(candidate);

    if (candidate_fitness < foods[i].fitness) {
      foods[i].fitness = candidate_fitness;
      foods[i].individual = candidate;
      foods[i].trials = 0;
    } else {
      foods[i].trials++;
    }
  }
}

void ABC::onlooker_phase() {
  std::vector<double> probabilities = compute_prob();
  for (int i=0; i < colony_size; i++) {
    int idx = select_food(probabilities);

    std::vector<int> candidate = generate_neighbor(foods[idx].individual);
    int candidate_fitness = graph.fitness(candidate);

    if (candidate_fitness < foods[idx].fitness) {
      foods[idx].fitness = candidate_fitness;
      foods[idx].individual = candidate;
      foods[idx].trials = 0;
    }else {
      foods[idx].trials++;
    }
  }
}
void ABC::scout_phase() {
  for (int i=0; i < colony_size; i++) {
    if (foods[i].trials >= limit) {
      foods[i].individual = graph.random_color_graph(num_of_colors);
      foods[i].fitness = graph.fitness(foods[i].individual);
      foods[i].trials = 0;
    }
  }
}

void ABC::update_best_and_worst(){
  for (const auto& food : foods){
    if (food.fitness < best.fitness){
      best = food;
    }
    if (food.fitness > worst.fitness) {
      worst = food;
    }
  }
}



std::vector<int> ABC::generate_neighbor(const std::vector<int>& individual) {
  std::vector<int> neighbor = individual;

  int vertex = rand() % graph.num_nodes;
  int old_color = neighbor[vertex];
  int new_color = old_color;
  while (new_color == old_color) {
    new_color = rand() % num_of_colors;
  }

  neighbor[vertex] = new_color;
  return neighbor;
}

double ABC::compute_score(int fitness) {
  return 1.0 / (1.0 + fitness);

}

std::vector<double> ABC::compute_prob() {
  std::vector<double> probabilities(colony_size);
  double total_score = 0.0;

  for (const auto& food: foods) {
    total_score += compute_score(food.fitness);
  }

  for (int i = 0; i < colony_size; i++) {
    probabilities[i] = compute_score(foods[i].fitness)/total_score;
  }
  return probabilities;
}

int ABC::select_food(const std::vector<double>& probabilities) const {
  double r = (double) rand() / RAND_MAX;
  double cumulative = 0.0;

  for (int i = 0; i < probabilities.size(); i++) {
    cumulative += probabilities[i];
    if (r <= cumulative) {
      return i;
    }
  }

  return probabilities.size() - 1;
}