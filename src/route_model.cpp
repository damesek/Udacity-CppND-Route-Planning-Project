#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  // Create RouteModel Nodes 
  int counter = 0;
  for (Model::Node node : this->Nodes()) 
    this->m_Nodes.push_back(RouteModel::Node(counter++, this, node));
  
}