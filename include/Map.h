#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include <wx/app.h>
#include <random>
#include <ctime>

class Goal
{
public:
    Goal() {graph_radius = 10;}
    int graph_radius;
    double x;
    double y;
};

class Map
{
public:
    int safety_adding;
    int obstacle_num;
    std::vector<std::vector<wxPoint>> obstacles;
    std::vector<std::vector<wxPoint>> bigger_obstacles;
    Map(){ safety_adding = 5;}
    void create(wxSize map_size);
    void updateSafetyContours();
};

#endif // MAP_H_INCLUDED
