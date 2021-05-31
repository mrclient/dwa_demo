/***************************************************************
 * Name:      dwa_demoMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2021-05-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "dwa_demoMain.h"
#include <wx/msgdlg.h>

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
const long dwa_demoFrame::ID_TEXTCTRL1 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL2 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL3 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL4 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT1 = wxNewId();
const long dwa_demoFrame::ID_STATICTEXT2 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL5 = wxNewId();
const long dwa_demoFrame::ID_TEXTCTRL6 = wxNewId();
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
    TextCtrl1 = new wxTextCtrl(control_panel, ID_TEXTCTRL1, _("1.0"), wxPoint(5,35), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl2 = new wxTextCtrl(control_panel, ID_TEXTCTRL2, _("1.0"), wxPoint(70,35), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl3 = new wxTextCtrl(control_panel, ID_TEXTCTRL3, _("0.0"), wxPoint(135,35), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl4 = new wxTextCtrl(control_panel, ID_TEXTCTRL4, _("5.0"), wxPoint(5,110), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    StaticText1 = new wxStaticText(control_panel, ID_STATICTEXT1, _("Robot pose (x,y,theta):"), wxPoint(5,5), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(control_panel, ID_STATICTEXT2, _("Goal position (x,y):"), wxPoint(8,80), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    TextCtrl5 = new wxTextCtrl(control_panel, ID_TEXTCTRL5, _("5.0"), wxPoint(80,110), wxSize(60,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    TextCtrl6 = new wxTextCtrl(control_panel, ID_TEXTCTRL6, _("0.5"), wxPoint(5,350), wxSize(50,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
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
    Center();

    Connect(ID_NEW_MAP_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dwa_demoFrame::OnNewMapButtonClick);
    Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dwa_demoFrame::OnTextCtrl6Text);
    Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dwa_demoFrame::OnTextCtrl7Text);
    map_panel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&dwa_demoFrame::Onfield_panelPaint,0,this);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&dwa_demoFrame::OnClose);
    //*)
}

dwa_demoFrame::~dwa_demoFrame()
{
    //(*Destroy(dwa_demoFrame)
    //*)
}

void dwa_demoFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void dwa_demoFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void dwa_demoFrame::OnClose(wxCloseEvent& event)
{
    Destroy();
}


void dwa_demoFrame::OnTextCtrl6Text(wxCommandEvent& event)
{
}

void dwa_demoFrame::OnTextCtrl7Text(wxCommandEvent& event)
{
}

void dwa_demoFrame::Onfield_panelPaint(wxPaintEvent& event)
{
}

void dwa_demoFrame::OnNewMapButtonClick(wxCommandEvent& event)
{
    world_map->create(wxPoint(0, 0));
}
