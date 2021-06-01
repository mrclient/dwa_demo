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
const long dwa_demoFrame::ID_SBS_CHECKBOX = wxNewId();
const long dwa_demoFrame::ID_ROBOTX_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_ROBOTY_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_ROBOTTH_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_GOALX_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT1 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT2 = wxNewId();
const long dwa_demoFrame::ID_GOALY_TEXTCTRL = wxNewId();
const long dwa_demoFrame::ID_CF_TXTCTRL = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT3 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT4 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT5 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT6 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL7 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL8 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT7 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL9 = wxNewId();
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
    control_panel = new wxPanel(this, ID_CONTROL_PANEL, wxPoint(740,10), wxSize(210,460), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_CONTROL_PANEL"));
    start_button = new wxButton(control_panel, ID_START_BUTTON, _("Start"), wxPoint(10,425), wxSize(80,30), 0, wxDefaultValidator, _T("ID_START_BUTTON"));
    new_map_button = new wxButton(control_panel, ID_NEW_MAP_BUTTON, _("New map"), wxPoint(120,425), wxSize(80,30), 0, wxDefaultValidator, _T("ID_NEW_MAP_BUTTON"));
    new_map_button->SetFocus();
    sbs_checkbox = new wxCheckBox(control_panel, ID_SBS_CHECKBOX, _("\"Step by step\" mode"), wxPoint(8,390), wxDefaultSize, 0, wxDefaultValidator, _T("ID_SBS_CHECKBOX"));
    sbs_checkbox->SetValue(false);
    robot_x_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTX_TEXTCTRL, _("1.0"), wxPoint(5,35), wxSize(60,30), 0, wxDefaultValidator, _T("ID_ROBOTX_TEXTCTRL"));
    robot_y_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTY_TEXTCTRL, _("1.0"), wxPoint(70,35), wxSize(60,30), 0, wxDefaultValidator, _T("ID_ROBOTY_TEXTCTRL"));
    robot_th_txt_ctrl = new wxTextCtrl(control_panel, ID_ROBOTTH_TEXTCTRL, _("0.0"), wxPoint(135,35), wxSize(60,30), 0, wxDefaultValidator, _T("ID_ROBOTTH_TEXTCTRL"));
    goal_x_txt_ctrl = new wxTextCtrl(control_panel, ID_GOALX_TEXTCTRL, _("5.0"), wxPoint(5,110), wxSize(60,30), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_GOALX_TEXTCTRL"));
    goal_x_txt_ctrl->SetToolTip(_("Press Enter after input"));
    StaticText1 = new wxStaticText(control_panel, ID_STATICTEXT1, _("Robot pose (x,y,theta):"), wxPoint(5,5), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(control_panel, ID_STATICTEXT2, _("Goal position (x,y):"), wxPoint(8,80), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    goal_y_txt_ctrl = new wxTextCtrl(control_panel, ID_GOALY_TEXTCTRL, _("5.0"), wxPoint(80,110), wxSize(60,30), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_GOALY_TEXTCTRL"));
    goal_y_txt_ctrl->SetToolTip(_("Press Enter after input"));
    contr_freq_txt_ctrl = new wxTextCtrl(control_panel, ID_CF_TXTCTRL, _("0.5"), wxPoint(5,350), wxSize(50,30), 0, wxDefaultValidator, _T("ID_CF_TXTCTRL"));
    StaticText3 = new wxStaticText(control_panel, ID_STATICTEXT3, _("Controller\nfrequency (Hz):"), wxPoint(5,300), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(control_panel, ID_STATICTEXT4, _("World\ntime (s):"), wxPoint(135,300), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(control_panel, ID_STATICTEXT5, _("0.000"), wxPoint(135,355), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(control_panel, ID_STATICTEXT6, _("Motor max. speed and\nacceleration (1/s, 1/s^2):"), wxPoint(5,152), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    TextCtrl7 = new wxTextCtrl(control_panel, ID_TEXTCTRL7, _("5.0"), wxPoint(5,200), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    TextCtrl8 = new wxTextCtrl(control_panel, ID_TEXTCTRL8, _("2.5"), wxPoint(80,200), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    StaticText7 = new wxStaticText(control_panel, ID_STATICTEXT7, _("Braking distance (m):"), wxPoint(5,240), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    TextCtrl9 = new wxTextCtrl(control_panel, ID_TEXTCTRL9, _("0.1"), wxPoint(5,265), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    map_panel = new wxPanel(this, ID_MAP_PANEL, wxPoint(10,10), wxSize(720,680), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_MAP_PANEL"));
    map_panel->SetBackgroundColour(wxColour(255,255,255));
    field_dc_client = new wxClientDC(map_panel);
    StaticText8 = new wxStaticText(map_panel, ID_STATICTEXT8, _("(7.2 m; 6.8 m)"), wxPoint(624,648), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    dwa_panel = new wxPanel(this, ID_DWA_PANEL, wxPoint(740,480), wxSize(210,210), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_DWA_PANEL"));
    dwa_dc_client = new wxClientDC(dwa_panel);
    world_timer.SetOwner(this, ID_WORLD_TIMER);
    world_timer.Start(25, false);
    controller_timer.SetOwner(this, ID_CONTROLLER_TIMER);
    controller_timer.Start(500, false);
    Center();

    Connect(ID_START_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dwa_demoFrame::OnStartButtonClick);
    Connect(ID_NEW_MAP_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dwa_demoFrame::OnNewMapButtonClick);
    Connect(ID_GOALX_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onGoalTextEnter);
    Connect(ID_GOALY_TEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dwa_demoFrame::onGoalTextEnter);
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
    field_dc_client->SetPen(wxPen(wxColour(0, 255, 0)));
    for(int i = 0; i < world_map->obstacle_num; i++)
    {
        field_dc_client->DrawPolygon(4, world_map->bigger_obstacles[i].data());
    }

    field_dc_client->SetPen(orig_pen);
    for(int i = 0; i < world_map->obstacle_num; i++)
    {
        field_dc_client->DrawPolygon(4, world_map->obstacles[i].data());
    }

}


void dwa_demoFrame::drawRobot()
{
    static std::vector<wxPoint> last_footprint(2);
    if(last_footprint.size() == 4 )
    {
        field_dc_client->SetPen(wxPen(wxColour(255, 255, 255), 2));
        field_dc_client->DrawPolygon(4, last_footprint.data());
    }
    field_dc_client->SetPen(wxPen(wxColour(0, 0, 0)));
    field_dc_client->DrawPolygon(4, robot.global_footprint.data());
    last_footprint = robot.global_footprint;
}


void dwa_demoFrame::drawGoal()
{
    static int last_x = -1, last_y = -1;
    double x, y;

    wxPen orig_pen = field_dc_client->GetPen();
    if(last_x != -1 && last_y != -1)
    {
        field_dc_client->SetPen(wxPen(wxColour(255, 255, 255)));
        field_dc_client->DrawCircle(last_x, last_y, 11);
    }
    last_x = goal.x;
    last_y = goal.y;
    field_dc_client->SetPen(wxPen(wxColour(255, 0, 0)));
    field_dc_client->DrawCircle(last_x, last_y, 10);
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


void dwa_demoFrame::OnClose(wxCloseEvent& event)
{
    Destroy();
}


void dwa_demoFrame::Onfield_panelPaint(wxPaintEvent& event)
{
    drawRobot();
    drawGoal();
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

    field_dc_client -> Clear();
    drawMap();
    drawRobot();
    drawGoal();

}


void dwa_demoFrame::mainTimerTickEvt(wxTimerEvent& event)
{
    if(!program_stopped)
    {
        robot_x_txt_ctrl->SetValue(std::to_string(robot.x / 100.0));
        robot_y_txt_ctrl->SetValue(std::to_string(robot.y / 100.0));
        robot_th_txt_ctrl->SetValue(std::to_string(robot.theta));
        robot.updateState(world_timer.GetInterval()/1000.0);
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
        if(dwa_planner.checkAchievment())
            stopProcedure();
        else
            dwa_planner.updateControl(controller_timer.GetInterval()/1000.0);
}


void dwa_demoFrame::onGoalTextEnter(wxCommandEvent& event)
{
    //Add beautiful formatting of fields text
    goal_x_txt_ctrl->GetValue().ToDouble(&goal.x);
    goal_y_txt_ctrl->GetValue().ToDouble(&goal.y);
    goal.x = std::round(goal.x*100.0);
    goal.y = std::round(goal.y*100.0);
    drawGoal();
    drawRobot();
}
