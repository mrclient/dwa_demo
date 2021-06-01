#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include <wx/app.h>
#include <random>
#include <ctime>

class Map
{
public:
    int obstacle_num;
    std::vector<std::vector<wxPoint>> obstacles;
    std::vector<std::vector<wxPoint>> bigger_obstacles;
    void create(wxSize map_size);
};

#endif // MAP_H_INCLUDED
