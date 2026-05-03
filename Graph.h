//
// Created by hugo2 on 03/05/2026.
//

#ifndef OM_FINAL_PROJECT_GRAPH_H
#define OM_FINAL_PROJECT_GRAPH_H
#include <string>
#include <vector>

#include "Node.h"


class Graph {
  public:
    int num_nodes;
    int num_edges;
    std::vector<Node> nodes;

    Graph();

    bool loadFromFile(const std::string& filename);

};


#endif //OM_FINAL_PROJECT_GRAPH_H
