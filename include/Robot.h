#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <wx/app.h>


// for simulation of robot motors dynamic
class PID_sim
{
    double desired_value;
    double current_value;
    double diff_val;
    double time;
public:
    double T;

    PID_sim() {T = 0.1;}
    void reset();
    double update(double dt);
    void setDesiredValue(double goal);
};


class Robot
{
    void updateRobotSpeeds();
    void updateGlobalFootprint();

public:

    double x, y, theta;
    double v, omega;
    double wheel_speed_1, wheel_speed_2;
    double max_wheel_speed, max_wheel_accel;
    double wheel_radius, length, robot_wheel_width;
    double controller_period; // in ms
    PID_sim wh1_controller;
    PID_sim wh2_controller;
    std::vector<wxPoint> local_footprint;
    std::vector<wxPoint> global_footprint;

    Robot();
    void stop();
    void updateState(double dt);
    void updateFootprints();
    void getNewPose(double x_, double y_, double theta_);
    void predictState(double new_wh_sp_1, double new_wh_sp_2, double dt,
                      double& px, double& py, double& ptheta, double& pv, double& pomega);
    void transformPoint(double x, double y, double theta, const wxPoint& from, wxPoint& to);
};

#endif // ROBOT_H_INCLUDED
