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
        // distance and cost
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.f;
        // already visited
        bool visited = false;
        // neighbors nodes
        std::vector<RouteModel::Node *> neighbors;

        // distance declaration for the RouteModel:Node class
        float distance(const Model::Node &other) const {
          return std::sqrt(std::pow(this->x - other.x, 2.f) + std::pow(this->y - other.y, 2.f));
        }

        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
      
        void FindNeighbors();

      private:
        int index;
        RouteModel * parent_model = nullptr;

        // the Neighbor declaration > find the closest node in each Road
        RouteModel::Node* FindNeighbor(std::vector<int> node_indices);
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);
    // Create Node to Road hashmap getter function
    auto &GetNodeToRoadMap() { return node_to_road; }
    // Getter for the private nodes vector
    std::vector<RouteModel::Node> &SNodes() { return m_Nodes; }  
    std::vector<RouteModel::Node> path; 

  private:

    // reverse hashmap
    void CreateNodeToRoadHashmap(void);
 
    // The RouteModel Class 
    std::vector<Node> m_Nodes;

    // NodeID (reverse map) > Road
    std::unordered_map <int, std::vector<const Model::Road *>> node_to_road;

};
