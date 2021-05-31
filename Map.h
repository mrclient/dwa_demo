#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include <wx/app.h>

class Map
{
public:
    int obstacle_num;
    std::vector<int> obstacles;
    void create(wxPoint robot_position);
};

#endif // MAP_H_INCLUDED
