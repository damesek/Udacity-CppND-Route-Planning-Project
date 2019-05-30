#pragma once

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // The Node Class 5.7 
        // prev Node
        RouteModel::Node* parent = nullptr;
        // distance
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.f;
        // already visited
        bool visited = false;
        // neighbors nodes
        std::vector<RouteModel::Node *> neighbors;

        
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
      
      private:
        int index;
        RouteModel * parent_model = nullptr;
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);
    //Getter for the private nodes vector
    std::vector<RouteModel::Node> &SNodes() { return m_Nodes; }  
    std::vector<RouteModel::Node> path; // This variable will eventually store the path that is found by the A* search.

  private:
    //The RouteModel Class 
    std::vector<Node> m_Nodes;

};
