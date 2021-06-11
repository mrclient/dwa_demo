#include "Robot.h"


void PID_sim::reset()
{
    current_value = 0.0;
    desired_value = 0.0;
    diff_val = 0.0;
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

    // some initialization values just in case
    x = 100.0;
    y = 100.0;
    theta = 0.75;
    length = 40;
    robot_wheel_width = 30.0;
    wheel_radius = 10.0;
    max_wheel_speed = 4.0;
    max_wheel_accel = 1.0;
    controller_period = 500; // in ms

    updateFootprints();
}


void Robot::updateFootprints()
{
    // robot form is a rectangle with specified sizes
    local_footprint.resize(4);
    local_footprint[0].x = length / 2;
    local_footprint[0].y = robot_wheel_width / 2.0;
    local_footprint[1].x = length / 2;
    local_footprint[1].y = - robot_wheel_width / 2.0;
    local_footprint[2].x = -length / 2;
    local_footprint[2].y = - robot_wheel_width / 2.0;
    local_footprint[3].x = -length / 2;
    local_footprint[3].y = robot_wheel_width / 2.0;

    global_footprint.resize(local_footprint.size());
    updateGlobalFootprint();
}

void Robot::transformPoint(double x, double y, double theta, const wxPoint& from, wxPoint& to)
{
    to.x = x + std::round(from.x * std::cos(theta) - from.y * std::sin(theta));
    to.y = y + std::round(from.x * std::sin(theta) + from.y * std::cos(theta));
}

void Robot::updateGlobalFootprint()
{
    for(int i = 0; i < local_footprint.size(); i++)
        transformPoint(x, y, theta, local_footprint[i], global_footprint[i]);
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


// precise only with small dt
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


void Robot::getNewPose(double x_, double y_, double theta_)
{
    x = x_;
    y = y_;
    theta = (theta_ > M_PI) ? (theta_ - 2 * M_PI) : ((theta_ < -M_PI) ? (theta_ + 2 * M_PI) : theta_);
    updateGlobalFootprint();
}


// precise with arbitrary dt when wheels speeds are constant
void Robot::predictState(double new_wh_sp_1, double new_wh_sp_2, double dt,
                         double& px, double& py, double& ptheta, double& pv, double& pomega)
{
    pv = 0.5 * (new_wh_sp_1 + new_wh_sp_2) * wheel_radius;
    pomega = (new_wh_sp_1 - new_wh_sp_2) * wheel_radius / robot_wheel_width;
// commented code also works well
//    px = x;
//    py = y;
//    ptheta = theta;
//    for(double t = 0.01; t < dt; t+=0.01)
//    {
//        px = px + pv * std::cos(ptheta) * 0.01;
//        py = py + pv * std::sin(ptheta) * 0.01;
//        ptheta = ptheta + pomega * 0.01;
//    }
    if(pomega <= 0.01 && pomega >= -0.01) // to prevent division by almost zero
    {
        px = x + pv * std::cos(theta) * dt;
        py = y + pv * std::sin(theta) * dt;
    }
    else
    {
        px = x - pv / pomega * (std::sin(theta) - std::sin(pomega * dt + theta));
        py = y + pv / pomega * (std::cos(theta) - std::cos(pomega * dt + theta));
    }
    ptheta = theta + pomega * dt;
    ptheta = (ptheta > M_PI) ? (ptheta - 2 * M_PI) : ((ptheta < -M_PI) ? (ptheta + 2 * M_PI) : ptheta);
}
