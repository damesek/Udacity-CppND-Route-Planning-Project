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
    
    start_node->visited = true;
    start_node->g_value = 0;
    start_node->h_value = start_node->distance(*end_node); 

    open_list.push_back(start_node);

    RouteModel::Node *current_node = nullptr;
    while (open_list.size() > 0) {
        current_node = NextNode();
        if (current_node->distance(*end_node) == 0) {
            m_Model.path = ConstructFinalPath(current_node);
            return;
        }
        AddNeighbors(current_node);
    }

    return;
}


RouteModel::Node * RoutePlanner::NextNode() {
    std::sort(open_list.begin(), open_list.end(), [](const auto &_1st, const auto &_2nd) {
        return _1st->h_value + _1st->g_value < _2nd->h_value + _2nd->g_value;
    });

    RouteModel::Node *result = open_list.front();
    open_list.erase(open_list.begin());
    return result;
}

float RoutePlanner::CalculateHValue(const RouteModel::Node node) //maybe not needed the start here
{
    return node.distance(*end_node);
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

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();

    for (auto thisNeighbors : current_node->neighbors) {
        thisNeighbors->parent = current_node; 
        thisNeighbors->g_value = current_node->g_value + current_node->distance(*thisNeighbors);
        thisNeighbors->h_value = CalculateHValue(*thisNeighbors);
        open_list.push_back(thisNeighbors);
        thisNeighbors->visited = true;
    }
}