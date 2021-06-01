#include "DWAplanner.h"


DWAplanner::DWAplanner()
{
    robot = nullptr;
    goal = nullptr;
    world_map = nullptr;
}


double DWAplanner::angle_error(double px, double py, double ptheta)
{
    double delta = (std::atan2(goal->y - py, goal->x - px) - ptheta);
    if(delta > M_PI) delta = -(2*M_PI - delta);
    if(delta < -M_PI) delta = 2*M_PI + delta;
    return delta;
}


double DWAplanner::max_free_distance(double new_wh_sp_1, double new_wh_sp_2, double dt)
{
    double px, py, ptheta, pvel, pomega;
    double safe_distance = 1000.0;

    if(world_map == nullptr)
        return 1000.0;

    int i;
    for(i = 5; i >= 1; i--)
    {
        robot->predictState(new_wh_sp_1, new_wh_sp_2, i*dt, px, py, ptheta, pvel, pomega);
        if(collision_check(true, px, py, ptheta))
        {
            safe_distance = 0.0;
            continue;
        }
        else
        {
            if(pomega == 0.0)
                safe_distance = std::sqrt(std::pow(robot->x - px, 2) + std::pow(robot->y - py, 2));
            else
                safe_distance = pvel / pomega * (ptheta - robot->theta);
            break;
        }
    }

    return (i == 5) ? 1000.0 : std::abs(safe_distance);
}


int DWAplanner::leftTurn(const wxPoint& a, const wxPoint& b, const wxPoint& c)
{
    int v = (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
    return (v > 0) ? 1 : (v < 0 ? -1 : 0);
}


bool DWAplanner::collision_check(bool safe, double px, double py, double ptheta)
{
    wxPoint robot_pt1, robot_pt2;
    if(world_map==nullptr)
        return false;

    std::vector<std::vector<wxPoint>>& obstacles = safe ? world_map->bigger_obstacles : world_map->obstacles;
    for(int j = 0; j < obstacles.size(); j++)
    {
        int sz = obstacles[j].size();
        for(int k = 0; k < sz; k++)
        {
            wxPoint obst_pt1 = obstacles[j][k];
            wxPoint obst_pt2 = obstacles[j][(k + 1) % sz];
            for(int i = 0; i < 4; i++)
            {
                robot->transformPoint(px, py, ptheta, robot->local_footprint[i], robot_pt1);
                robot->transformPoint(px, py, ptheta, robot->local_footprint[(i+1)%4], robot_pt2);
                bool is_in_collision = (leftTurn(robot_pt1, robot_pt2, obst_pt1) != leftTurn(robot_pt1, robot_pt2, obst_pt2))
                                        && ((leftTurn(obst_pt1, obst_pt2, robot_pt1) != leftTurn(obst_pt1, obst_pt2, robot_pt2)));
                if(is_in_collision)
                    return true;
            }
        }
    }
    return false;
}


bool DWAplanner::checkAchievment()
{
    if(std::pow(robot->x - goal->x, 2) + std::pow(robot->y - goal->y, 2) < 100.0)
        return true;
    return false;
}


void DWAplanner::updateControl(double dt)
{
    double best_wh1 = 0.0, best_wh2 = 0.0;
    double cost, best_cost = 0.0;

    double px, py, ptheta, pvel, pomega;

    for(double wh1 = -4.0; wh1 <= 4.0; wh1 += 0.8)
    {
        for(double wh2 = -4.0; wh2 <= 4.0; wh2 += 0.8)
        {
            robot->predictState(wh1, wh2, dt, px, py, ptheta, pvel, pomega);
            if(collision_check(true, px, py, ptheta))
                continue;
            cost = 0.1 * std::cos(angle_error(px, py, ptheta)) +  0.02 * max_free_distance(wh1, wh2, dt) +
                   0.002 * pvel * std::cos(angle_error(px, py, ptheta));
            if(cost > best_cost)
            {
                best_cost = cost;
                best_wh1 = wh1;
                best_wh2 = wh2;
            }
        }
    }
//        robot.predictState(best_wh1, best_wh2, 5*dt, px, py, ptheta, pvel, pomega);
//        field_dc_client->DrawCircle(px, py, 10);
    robot->wh1_controller.setDesiredValue(best_wh1);
    robot->wh2_controller.setDesiredValue(best_wh2);
}
