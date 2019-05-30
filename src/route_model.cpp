#include "route_model.h"
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  // Create RouteModel Nodes 
  int counter = 0;
  for (Model::Node node : this->Nodes()) 
    this->m_Nodes.push_back(RouteModel::Node(counter++, this, node));

  CreateNodeToRoadHashmap(); 
  
}




// FindNeighBor method > Find closest Node
RouteModel::Node* RouteModel::Node::FindNeighbor(vector<int> node_indices){
    RouteModel::Node* closestNode = nullptr;
    float minDistance = std::numeric_limits<float>::max(); 

    // *solution from dbecad, sounds clearer than official 
    vector<RouteModel::Node> &nodeList = parent_model->SNodes();

    for (int node_index : node_indices)
    {
        if (nodeList[node_index].visited == false)
        {
            float currDistance = distance(nodeList[node_index]);
            if (currDistance < minDistance && currDistance != 0)
            {
                minDistance = currDistance;
                closestNode = &nodeList[node_index];
            }
        }
    }

    return closestNode;
}


void RouteModel::Node::FindNeighbors() {
    for (auto road : parent_model->node_to_road[this->index]) {
        RouteModel::Node *new_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
        if (new_neighbor) {
            this->neighbors.emplace_back(new_neighbor);
        }
    }
}

RouteModel::Node &RouteModel::FindClosestNode(float x, float y) {
    Model::Node userNode {x, y}; 
    float minDistance = std::numeric_limits<float>::max(); 
    int minNodeIndex = std::numeric_limits<int>::max();
    for(auto i : node_to_road) {
        float thisDistance = SNodes()[i.first].distance(userNode);
        if (thisDistance < minDistance) {
            minNodeIndex = i.first;
            minDistance = thisDistance;
        }
    }
    return SNodes()[minNodeIndex];
}

// Create reverse map
void RouteModel::CreateNodeToRoadHashmap(void)
{
    for (const Model::Road &thisRoad : Roads())
    { // just footway
        if (thisRoad.type != Model::Road::Type::Footway){
          for (int curr_index : Ways()[thisRoad.way].nodes){ 
                if (node_to_road.find(curr_index) == node_to_road.end())
                    node_to_road[curr_index] = vector<const Model::Road *> ();

                //Add current Road pointer to node index entry
                node_to_road[curr_index].push_back(&thisRoad);
            }
        } 
    }
}
