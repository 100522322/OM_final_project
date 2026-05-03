//
// Created by hugo2 on 03/05/2026.
//

#ifndef OM_FINAL_PROJECT_NODE_H
#define OM_FINAL_PROJECT_NODE_H
#include <vector>


class Node {
  public:
    int id;
    int color;
    std::vector<int> neighbors;

    Node(int _id);
};


#endif //OM_FINAL_PROJECT_NODE_H
