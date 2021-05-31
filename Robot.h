#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <wx/app.h>
#include <wx/msgdlg.h> // MUST BE DELETED

class PID_sim
{
    double desired_value;
    double current_value;
    double diff_val;
    double time;
public:
    double T;
    void reset();
    double update(double dt);
    void setDesiredValue(double goal);
};


class Robot
{
    void updateRobotSpeeds();

public:

    double x, y, theta;
    double v, omega;
    double wheel_speed_1, wheel_speed_2;
    double wheel_radius, robot_wheel_width;
    double controller_frequency;
    PID_sim wh1_controller;
    PID_sim wh2_controller;
    std::vector<wxPoint> local_footprint;
    std::vector<wxPoint> global_footprint;

    Robot();
    void stop();
    void updateState(double dt);
    void predictState(double new_wh_sp_1, double new_wh_sp_2, double dt,
                      double& px, double& py, double& ptheta, double& pv);
    void transformPoint(const wxPoint& from, wxPoint& to);
    void updateGlobalFootprint();
};

#endif // ROBOT_H_INCLUDED
