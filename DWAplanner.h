#ifndef DWAPLANNER_H_INCLUDED
#define DWAPLANNER_H_INCLUDED

#include <wx/app.h>
#include "Map.h"
#include "Robot.h"

class DWAplanner
{
    double angle_error(double px, double py, double ptheta);
    double max_free_distance(double new_wh_sp_1, double new_wh_sp_2, double dt);
    int leftTurn(const wxPoint& a, const wxPoint& b, const wxPoint& c);

public:

    Map* world_map;
    Goal* goal;
    Robot* robot;

    DWAplanner();
    void updateControl(double dt);
    bool checkAchievment();
    bool collision_check(bool safe, double px, double py, double ptheta);
};

#endif // DWAPLANNER_H_INCLUDED
