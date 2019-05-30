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



void RouteModel::CreateNodeToRoadHashmap(void)
{
    //For each roads of the model (Note: use reference to store address in map)
    for (const Model::Road &currRoad : Roads())
    {
        //Build reverse map only for non-footway roads
        if (currRoad.type != Model::Road::Type::Footway)
        {
            //Iterate over all nodes of current road's way
            for (int currNodeIdx : Ways()[currRoad.way].nodes)
            {
                //When node index is not yet present in list create an empty vector 
                if (node_to_road.find(currNodeIdx) == node_to_road.end())
                    node_to_road[currNodeIdx] = vector<const Model::Road *> ();

                //Add current Road pointer to node index entry
                node_to_road[currNodeIdx].push_back(&currRoad);
            }
        } 
    }
}

