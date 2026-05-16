//
// Created by hugo2 on 03/05/2026.
//

#include "Graph.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

Graph::Graph() : num_nodes(0), num_edges(0) {}

bool Graph::load_from_file(const std::string& filename) {

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Can't open the file " << filename << std::endl;
    return false;
  }

  std::string line;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == 'c') continue;

    std::istringstream iss(line);
    char type;
    if (line[0] == 'p') {
      std::string dummy;
      iss >> type >> dummy >> num_nodes >> num_edges;

      for (int i = 0; i <= num_nodes; ++i) {
        nodes.emplace_back(i);
      }
    }
    else if (line[0] == 'e') {
      int u, v;
      iss >> type >> u >> v;
      nodes[u].neighbors.push_back(v);
      nodes[v].neighbors.push_back(u);
    }
  }
  file.close();
  return true;
}

int Graph::count_conflicts(int node_id) {
  int count = 0;
  int node_color = nodes[node_id].color;

  for (int neighbor_id : nodes[node_id].neighbors) {
    if (nodes[neighbor_id].color == node_color) {
      count++;
    }
  }
  return count;
}

void Graph::color_graph(std::vector<int> colors) {
  if (colors.size() != num_nodes) {
    std::cerr << "Error: The number of nodes is not equal to the number of colors." << std::endl;
  }

  for (int i=0; i < num_nodes; i++) {
    nodes[i].color = colors[i];
  }
}

int Graph::fitness(std::vector<int> colors) {
  // Calculate and return the fitness.
  // Formula: Sum(err^n_colors)
  this->color_graph(colors);

  float total_errors = 0;
  for (Node& node : nodes) {
    float errors = this->count_conflicts(node.id)/2 ;


    // TODO Change this when having formula
    total_errors += errors;

  }
  int total_fitness = 0;
  if (std::floor(total_errors)==total_errors) {
    total_fitness = total_errors;
  }

  return total_fitness;
}
