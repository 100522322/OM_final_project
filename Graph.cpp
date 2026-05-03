//
// Created by hugo2 on 03/05/2026.
//

#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

Graph::Graph() : num_nodes(0), num_edges(0) {}

bool Graph::loadFromFile(const std::string& filename) {

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Can't open the file" << filename << std::endl;
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