/***************************************************************
 * Name:      dwa_demoMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2021-05-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "dwa_demoMain.h"

//(*InternalHeaders(dwa_demoFrame)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(dwa_demoFrame)
const long dwa_demoFrame::ID_START_BUTTON = wxNewId();
const long dwa_demoFrame::ID_NEW_MAP_BUTTON = wxNewId();
const long dwa_demoFrame::ID_ROBOTX_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_ROBOTY_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_ROBOTTH_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_GOALX_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT1 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT2 = wxNewId();
const long dwa_demoFrame::ID_GOALY_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT3 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT6 = wxNewId();
const long dwa_demoFrame::ID_CYCLE_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_PRED_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT7 = wxNewId();
const long dwa_demoFrame::ID_TRAJQNT_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT9 = wxNewId();
const long dwa_demoFrame::ID_ROBOTL_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_ROBOTW_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_ROBOTR_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT10 = wxNewId();
const long dwa_demoFrame::ID_MAXSPEED_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_MAXACC_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_PID_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL10 = wxNewId();
const long dwa_demoFrame::ID_DWA_KD_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_DWA_KS_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_ACCUR_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_BORD_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT4 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT5 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT11 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT12 = wxNewId();
const long dwa_demoFrame::ID_CONTROL_PANEL = wxNewId();
const long dwa_demoFrame::ID_FIELD_DC_CLIENT = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT8 = wxNewId();
const long dwa_demoFrame::ID_MAP_PANEL = wxNewId();
const long dwa_demoFrame::ID_DWA_DC_CLIENT = wxNewId();
const long dwa_demoFrame::ID_DWA_PANEL = wxNewId();
const long dwa_demoFrame::ID_WORLD_TIMER = wxNewId();
const long dwa_demoFrame::ID_CONTROLLER_TIMER = wxNewId();
//*)

BEGIN_EVENT_TABLE(dwa_demoFrame,wxFrame)
    //(*EventTable(dwa_demoFrame)
    //*)
END_EVENT_TABLE()

dwa_demoFrame::dwa_demoFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(dwa_demoFrame)
    Create(parent, wxID_ANY, _("DWA planner work demonstration program"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
    SetClientSize(wxSize(960,700));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    control_panel = new wxPanel(this, ID_CONTROL_PANEL, wxPoint(530,10), wxSize(420,460), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_CONTROL_PANEL"));
    control_panel->SetMaxSize(wxSize(210,600));
    start_button = new wxButton(control_panel, ID_START_BUTTON, _("Start"), wxPoint(80,425), wxSize(80,30), 0, wxDefaultValidator, _T("ID_START_BUTTON"));
    new_map_button = new wxButton(control_panel, ID_NEW_MAP_BUTTON, _("New map"), wxPoint(250,425), wxSize(80,30), 0, wxDefaultValidator, _T("ID_NEW_MAP_BUTTON"));
    new_map_button->SetFocus();
    robot_x_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTX_TEXTCTRL, _("1.0"), wxPoint(8,56), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_ROBOTX_TEXTCTRL"));
    robot_y_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTY_TEXTCTRL, _("1.0"), wxPoint(72,56), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_ROBOTY_TEXTCTRL"));
    robot_th_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTTH_TEXTCTRL, _("0.0"), wxPoint(136,56), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_ROBOTTH_TEXTCTRL"));
    goal_x_txt_ctrl = new wxTextCtrl(control_panel, ID_GOALX_TEXTCTRL, _("4.0"), wxPoint(8,184), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_GOALX_TEXTCTRL"));
    goal_x_txt_ctrl->SetToolTip(_("Press Enter after input"));
    StaticText1 = new wxStaticText(control_panel, ID_STATICTEXT1, _("x (m), y(m), theta (rad)"), wxPoint(32,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(control_panel, ID_STATICTEXT2, _("x(m), y(m)"), wxPoint(40,160), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    goal_y_txt_ctrl = new wxTextCtrl(control_panel, ID_GOALY_TEXTCTRL, _("4.0"), wxPoint(80,184), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_GOALY_TEXTCTRL"));
    goal_y_txt_ctrl->SetToolTip(_("Press Enter after input"));
    StaticText3 = new wxStaticText(control_panel, ID_STATICTEXT3, _("Accuracy (m), safety border (m)"), wxPoint(8,296), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText6 = new wxStaticText(control_panel, ID_STATICTEXT6, _("Cycle period T (s)"), wxPoint(256,240), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    cycle_txt_ctrl = new wxTextCtrl(control_panel, ID_CYCLE_TEXTCTRL, _("0.5"), wxPoint(280,264), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_CYCLE_TEXTCTRL"));
    pr_steps_txt_ctrl = new wxTextCtrl(control_panel, ID_PRED_TEXTCTRL, _("5"), wxPoint(8,376), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_PRED_TEXTCTRL"));
    pr_steps_txt_ctrl->SetToolTip(_("Each trajectory is checked for collisions for T*the_number seconds."));
    StaticText7 = new wxStaticText(control_panel, ID_STATICTEXT7, _("K angle, K distance, K speed:"), wxPoint(8,240), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    traj_qnt_txt_ctrl = new wxTextCtrl(control_panel, ID_TRAJQNT_TEXTCTRL, _("3"), wxPoint(80,376), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TRAJQNT_TEXTCTRL"));
    traj_qnt_txt_ctrl->SetToolTip(_("Check N*N trajectories"));
    StaticText9 = new wxStaticText(control_panel, ID_STATICTEXT9, _("L (m), W (m),  wheel radius (m):"), wxPoint(208,32), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    robot_l_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTL_TEXTCTRL, _("0.4"), wxPoint(208,56), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_ROBOTL_TEXTCTRL"));
    robot_w_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTW_TEXTCTRL, _("0.3"), wxPoint(280,56), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_ROBOTW_TEXTCTRL"));
    robot_r_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTR_TEXTCTRL, _("0.1"), wxPoint(352,56), wxSize(60,20), 0, wxDefaultValidator, _T("ID_ROBOTR_TEXTCTRL"));
    robot_r_txt_ctrl->Disable();
    StaticText10 = new wxStaticText(control_panel, ID_STATICTEXT10, _("Motor max. speed (1/s), max. accel (1/s^2), PID time (s):"), wxPoint(8,80), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    m_max_sp_txt_ctrl = new wxTextCtrl(control_panel, ID_MAXSPEED_TEXTCTRL, _("4.0"), wxPoint(8,104), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_MAXSPEED_TEXTCTRL"));
    m_max_ac_txt_ctrl = new wxTextCtrl(control_panel, ID_MAXACC_TEXTCTRL, _("1.0"), wxPoint(80,104), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_MAXACC_TEXTCTRL"));
    pid_t_txt_ctrl = new wxTextCtrl(control_panel, ID_PID_TEXTCTRL, _("0.1"), wxPoint(152,104), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_PID_TEXTCTRL"));
    dwa_ka_txt_ctrl = new wxTextCtrl(control_panel, ID_TEXTCTRL10, _("0.1"), wxPoint(8,264), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL10"));
    dwa_kd_txt_ctrl = new wxTextCtrl(control_panel, ID_DWA_KD_TEXTCTRL, _("0.02"), wxPoint(80,264), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_DWA_KD_TEXTCTRL"));
    dwa_ks_txt_ctrl = new wxTextCtrl(control_panel, ID_DWA_KS_TEXTCTRL, _("0.002"), wxPoint(152,264), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_DWA_KS_TEXTCTRL"));
    accur_txt_ctrl = new wxTextCtrl(control_panel, ID_ACCUR_TEXTCTRL, _("0.1"), wxPoint(8,320), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_ACCUR_TEXTCTRL"));
    accur_txt_ctrl->SetToolTip(_("Goal achievement accuracy"));
    bord_txt_ctrl = new wxTextCtrl(control_panel, ID_BORD_TEXTCTRL, _("0.05"), wxPoint(80,320), wxSize(60,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_BORD_TEXTCTRL"));
    StaticText4 = new wxStaticText(control_panel, ID_STATICTEXT4, _("ROBOT"), wxPoint(184,8), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(control_panel, ID_STATICTEXT5, _("DWA PLANNER"), wxPoint(168,216), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText11 = new wxStaticText(control_panel, ID_STATICTEXT11, _("Prediction steps number, N param"), wxPoint(8,352), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    StaticText12 = new wxStaticText(control_panel, ID_STATICTEXT12, _("GOAL"), wxPoint(192,144), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    map_panel = new wxPanel(this, ID_MAP_PANEL, wxPoint(10,10), wxSize(510,680), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_MAP_PANEL"));
    map_panel->SetBackgroundColour(wxColour(255,255,255));
    field_dc_client = new wxClientDC(map_panel);
    StaticText8 = new wxStaticText(map_panel, ID_STATICTEXT8, _("(5.1 m; 6.8 m)"), wxPoint(410,648), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    dwa_panel = new wxPanel(this, ID_DWA_PANEL, wxPoint(530,480), wxSize(210,210), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_DWA_PANEL"));
    dwa_dc_client = new wxClientDC(dwa_panel);
    world_timer.SetOwner(this, ID_WORLD_TIMER);
    world_timer.Start(25, false);
    controller_timer.SetOwner(this, ID_CONTROLLER_TIMER);
    controller_timer.Start(500, false);
    Center();

    Connect(ID_START_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dwa_demoFrame::OnStartButtonClick);
    Connect(ID_NEW_MAP_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dwa_demoFrame::OnNewMapButtonClick);
    Connect(ID_ROBOTX_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_ROBOTY_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_ROBOTTH_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_GOALX_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_GOALY_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_CYCLE_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_PRED_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_TRAJQNT_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_ROBOTL_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_ROBOTW_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_MAXSPEED_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_MAXACC_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_PID_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_TEXTCTRL10,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_DWA_KD_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_DWA_KS_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_ACCUR_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    Connect(ID_BORD_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onTextEnter);
    map_panel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&dwa_demoFrame::Onfield_panelPaint,0,this);
    Connect(ID_WORLD_TIMER,wxEVT_TIMER,(wxObjectEventFunction)&dwa_demoFrame::mainTimerTickEvt);
    Connect(ID_CONTROLLER_TIMER,wxEVT_TIMER,(wxObjectEventFunction)&dwa_demoFrame::controllerTimerTickEvent);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&dwa_demoFrame::OnClose);
    //*)

    world_map = nullptr;
    program_stopped = true;
    dwa_planner.robot = &robot;
    dwa_planner.goal = &goal;
}

dwa_demoFrame::~dwa_demoFrame()
{
    //(*Destroy(dwa_demoFrame)
    //*)
}

void dwa_demoFrame::drawMap()
{
    wxPen orig_pen = field_dc_client->GetPen();
    field_dc_client->SetPen(wxPen(wxColour(0, 255, 0))); // green color
    for(int i = 0; i < world_map->obstacle_num; i++)
    {
        field_dc_client->DrawPolygon(world_map->bigger_obstacles[i].size(), world_map->bigger_obstacles[i].data());
    }

    field_dc_client->SetPen(orig_pen);
    for(int i = 0; i < world_map->obstacle_num; i++)
    {
        field_dc_client->DrawPolygon(world_map->obstacles[i].size(), world_map->obstacles[i].data());
    }

}


void dwa_demoFrame::drawRobot()
{
    wxPen orig_pen = field_dc_client->GetPen();
    static std::vector<wxPoint> last_footprint;
    if(last_footprint.size() == robot.global_footprint.size())
    {
        field_dc_client->SetPen(wxPen(wxColour(255, 255, 255), 2)); // white color with width = 2
        field_dc_client->DrawPolygon(last_footprint.size(), last_footprint.data());
    }
    field_dc_client->SetPen(orig_pen);
    field_dc_client->DrawPolygon(robot.global_footprint.size(), robot.global_footprint.data());
    last_footprint = robot.global_footprint;
}


void dwa_demoFrame::drawGoal()
{
    static int last_x = -1, last_y = -1;
    wxPen orig_pen = field_dc_client->GetPen();

    if(last_x != -1 && last_y != -1)
    {
        field_dc_client->SetPen(wxPen(wxColour(255, 255, 255))); // white color
        field_dc_client->DrawCircle(last_x, last_y, goal.graph_radius + 1);
    }

    last_x = goal.x;
    last_y = goal.y;
    field_dc_client->SetPen(wxPen(wxColour(255, 0, 0))); // red color
    field_dc_client->DrawCircle(last_x, last_y, goal.graph_radius);
    field_dc_client->SetPen(orig_pen);
}


void dwa_demoFrame::stopProcedure()
{
    if(program_stopped)
    {
        start_button->SetLabel("Stop");
    }
    else
    {
        start_button->SetLabel("Start");
        robot.stop();
    }
    program_stopped = !program_stopped;
    new_map_button->Enable(program_stopped);
    robot_x_txt_ctrl->Enable(program_stopped);
    robot_y_txt_ctrl->Enable(program_stopped);
    robot_th_txt_ctrl->Enable(program_stopped);
}


void dwa_demoFrame::readTextFields()
{
    // *100 -- from m to cm
    goal_x_txt_ctrl->GetValue().ToDouble(&goal.x);
    goal_y_txt_ctrl->GetValue().ToDouble(&goal.y);
    goal.x *= 100.0;
    goal.y *= 100.0;

    double x, y, theta;
    robot_x_txt_ctrl->GetValue().ToDouble(&x);
    robot_y_txt_ctrl->GetValue().ToDouble(&y);
    robot_th_txt_ctrl->GetValue().ToDouble(&theta);
    robot.getNewPose(x*100.0, y*100.0, theta);

    robot_l_txt_ctrl->GetValue().ToDouble(&robot.length);
    robot.length *= 100;
    robot_w_txt_ctrl->GetValue().ToDouble(&robot.robot_wheel_width);
    robot.robot_wheel_width *= 100;
    robot.updateFootprints();

    m_max_sp_txt_ctrl->GetValue().ToDouble(&robot.max_wheel_speed);
    m_max_ac_txt_ctrl->GetValue().ToDouble(&robot.max_wheel_accel);

    pid_t_txt_ctrl->GetValue().ToDouble(&robot.wh1_controller.T);
    robot.wh2_controller.T = robot.wh1_controller.T;

    dwa_ka_txt_ctrl->GetValue().ToDouble(&dwa_planner.k_angle);
    dwa_kd_txt_ctrl->GetValue().ToDouble(&dwa_planner.k_dist);
    dwa_ks_txt_ctrl->GetValue().ToDouble(&dwa_planner.k_vel);

    double aux;
    cycle_txt_ctrl->GetValue().ToDouble(&aux);
    controller_timer.Stop();
    controller_timer.Start(aux*1000.0, false);

    accur_txt_ctrl->GetValue().ToDouble(&dwa_planner.accuracy);
    dwa_planner.accuracy *= 100;
    pr_steps_txt_ctrl->GetValue().ToDouble(&aux);
    dwa_planner.prediction_steps = aux;
    traj_qnt_txt_ctrl->GetValue().ToDouble(&aux);
    dwa_planner.wheel_speed_step = aux;


    field_dc_client->Clear();
    bord_txt_ctrl->GetValue().ToDouble(&aux);
    if(world_map != nullptr){
        world_map->safety_adding = aux * 100;
        world_map->updateSafetyContours();
        drawMap();
    }

    drawGoal();
    drawRobot();
}


void dwa_demoFrame::OnClose(wxCloseEvent& event)
{
    Destroy();
}


void dwa_demoFrame::Onfield_panelPaint(wxPaintEvent& event)
{
    readTextFields();
    if(world_map != nullptr)
        drawMap();
}


void dwa_demoFrame::OnNewMapButtonClick(wxCommandEvent& event)
{
    if(world_map != nullptr)
        delete world_map;
    world_map = new Map;
    world_map->create(map_panel->GetSize());
    dwa_planner.world_map = world_map;

    field_dc_client->Clear();
    readTextFields();

}


void dwa_demoFrame::mainTimerTickEvt(wxTimerEvent& event)
{
    if(!program_stopped)
    {
        robot_x_txt_ctrl->SetValue(std::to_string(robot.x / 100.0)); // from cm to m
        robot_y_txt_ctrl->SetValue(std::to_string(robot.y / 100.0)); // from cm to m
        robot_th_txt_ctrl->SetValue(std::to_string(robot.theta));
        robot.updateState(world_timer.GetInterval() / 1000.0); // from ms to s
        if(dwa_planner.collision_check(false, robot.x, robot.y, robot.theta))
        {
            stopProcedure();
            wxMessageBox("Collision detected");
        }
        drawRobot();
    }
}


void dwa_demoFrame::OnStartButtonClick(wxCommandEvent& event)
{
    stopProcedure();
}


void dwa_demoFrame::controllerTimerTickEvent(wxTimerEvent& event)
{
    if(!program_stopped)
    {
        if(world_map != nullptr)
            drawMap();
        if(dwa_planner.checkAchievment())
            stopProcedure();
        else
            dwa_planner.updateControl(controller_timer.GetInterval() / 1000.0); // from ms to s
    }
}


void dwa_demoFrame::onTextEnter(wxCommandEvent& event)
{
    readTextFields();
}
