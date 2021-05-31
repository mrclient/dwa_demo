#include "Robot.h"


void PID_sim::reset()
{
    current_value = 0.0;
    desired_value = 0.0;
    time = 0.0;
}


double PID_sim::update(double dt)
{
    time += dt;
    return current_value = desired_value - diff_val * std::exp(-time / T);
}

void PID_sim::setDesiredValue(double goal)
{
    time = 0.0;
    diff_val = goal - current_value;
    desired_value = goal;
}


Robot::Robot(){

    x = 100.0;
    y = 100.0;
    theta = 0.75;
    robot_wheel_width = 30.0;
    wheel_radius = 10.0;

    local_footprint.resize(4);
    local_footprint[0].x = 10;
    local_footprint[0].y = robot_wheel_width / 2.0;
    local_footprint[1].x = 10;
    local_footprint[1].y = - robot_wheel_width / 2.0;
    local_footprint[2].x = -30;
    local_footprint[2].y = - robot_wheel_width / 2.0;
    local_footprint[3].x = -30;
    local_footprint[3].y = robot_wheel_width / 2.0;

    global_footprint.resize(4);
    updateGlobalFootprint();
    wh1_controller.T = 1.0;
    wh2_controller.T = 1.0;
}


void Robot::transformPoint(const wxPoint& from, wxPoint& to)
{
    to.x = x + std::round(from.x * std::cos(theta) - from.y * std::sin(theta));
    to.y = y + std::round(from.x * std::sin(theta) + from.y * std::cos(theta));
}

void Robot::updateGlobalFootprint()
{
    for(int i = 0; i < 4; i++)
        transformPoint(local_footprint[i], global_footprint[i]);
}

void Robot::stop()
{
    wh1_controller.reset();
    wh2_controller.reset();
    wheel_speed_1 = 0.0;
    wheel_speed_2 = 0.0;
    updateRobotSpeeds();
}


void Robot::updateRobotSpeeds()
{
    v = 0.5 * (wheel_speed_1 + wheel_speed_2) * wheel_radius;
    omega = (wheel_speed_1 - wheel_speed_2) * wheel_radius / robot_wheel_width;
}


void Robot::updateState(double dt)
{
    x += v * std::cos(theta) * dt;
    y += v * std::sin(theta) * dt;
    theta += omega * dt;
    if(theta > M_PI) theta -= 2*M_PI;
    if(theta < -M_PI) theta += 2*M_PI;
    wheel_speed_1 = wh1_controller.update(dt);
    wheel_speed_2 = wh2_controller.update(dt);
    updateRobotSpeeds();
    updateGlobalFootprint();
}


void Robot::predictState(double new_wh_sp_1, double new_wh_sp_2, double dt,
                         double& px, double& py, double& ptheta, double& pv)
{
    pv = 0.25 * (wheel_speed_1 + wheel_speed_2 + new_wh_sp_1 + new_wh_sp_2) * wheel_radius;
    double pomega = 0.5 * (wheel_speed_1 + new_wh_sp_1 - wheel_speed_2 - new_wh_sp_2) * wheel_radius / robot_wheel_width;
    px = x + pv * std::cos(theta) * dt;
    py = y + pv * std::sin(theta) * dt;
    ptheta = theta + pomega * dt;
}
