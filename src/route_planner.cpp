#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {

    // shorter version convert inputs to percentage from dbecad
    start_node = &m_Model.FindClosestNode(start_x * 0.01, start_y * 0.01);
    end_node   = &m_Model.FindClosestNode(end_x * 0.01, end_y * 0.01);

}

//A* Search
void RoutePlanner::AStarSearch()
{
    
    end_node->parent = start_node;
    m_Model.path = ConstructFinalPath(end_node); 
    return;
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node ){
    std::vector<RouteModel::Node> pathFound;
    distance = 0.f;
    RouteModel::Node parent;
    
    while (current_node->parent != nullptr) {
        pathFound.push_back(*current_node);
        parent = *(current_node->parent);
        distance += current_node->distance(parent);
        current_node = current_node->parent;
    }
    pathFound.push_back(*current_node);
    distance *= m_Model.MetricScale();
    return pathFound;
}