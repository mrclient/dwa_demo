/***************************************************************
 * Name:      dwa_demoMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2021-05-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DWA_DEMOMAIN_H
#define DWA_DEMOMAIN_H

//(*Headers(dwa_demoFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dcclient.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include "Map.h"
#include "Robot.h"

class dwa_demoFrame: public wxFrame
{
    public:

        dwa_demoFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~dwa_demoFrame();

        Map* world_map = nullptr;
        Robot robot;
        void drawMap();
        void drawRobot();
        void drawGoal();
        double angle_error(double px, double py, double ptheta);
        double smallest_distance(double px, double py, double ptheta);
        void stopProcedure();

    private:

        //(*Handlers(dwa_demoFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void Onnew_plan_buttonClick(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnTextCtrl5Text(wxCommandEvent& event);
        void Onnew_map_buttonClick(wxCommandEvent& event);
        void OnTextCtrl6Text(wxCommandEvent& event);
        void OnTextCtrl7Text(wxCommandEvent& event);
        void Onfield_panelPaint(wxPaintEvent& event);
        void OnNewMapButtonClick(wxCommandEvent& event);
        void mainTimerTickEvt(wxTimerEvent& event);
        void OnStartButtonClick(wxCommandEvent& event);
        void controllerTimerTickEvent(wxTimerEvent& event);
        void onGoalXTextEnter(wxCommandEvent& event);
        void onGoalYTextEnter(wxCommandEvent& event);
        //*)

        //(*Identifiers(dwa_demoFrame)
        static const long ID_START_BUTTON;
        static const long ID_NEW_MAP_BUTTON;
        static const long ID_SBS_CHECKBOX;
        static const long ID_ROBOTX_TEXTCTRL;
        static const long ID_ROBOTY_TEXTCTRL;
        static const long ID_ROBOTTH_TEXTCTRL;
        static const long ID_GOALX_TEXTCTRL;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_GOALY_TEXTCTRL;
        static const long ID_CF_TXTCTRL;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL7;
        static const long ID_TEXTCTRL8;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL9;
        static const long ID_CONTROL_PANEL;
        static const long ID_FIELD_DC_CLIENT;
        static const long ID_STATICTEXT8;
        static const long ID_MAP_PANEL;
        static const long ID_DWA_DC_CLIENT;
        static const long ID_DWA_PANEL;
        static const long ID_WORLD_TIMER;
        static const long ID_CONTROLLER_TIMER;
        //*)

        //(*Declarations(dwa_demoFrame)
        wxButton* new_map_button;
        wxButton* start_button;
        wxCheckBox* sbs_checkbox;
        wxClientDC* dwa_dc_client;
        wxClientDC* field_dc_client;
        wxPanel* control_panel;
        wxPanel* dwa_panel;
        wxPanel* map_panel;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxTextCtrl* TextCtrl7;
        wxTextCtrl* TextCtrl8;
        wxTextCtrl* TextCtrl9;
        wxTextCtrl* contr_freq_txt_ctrl;
        wxTextCtrl* goal_x_txt_ctrl;
        wxTextCtrl* goal_y_txt_ctrl;
        wxTextCtrl* robot_th_txt_ctrl;
        wxTextCtrl* robot_x_txt_ctrl;
        wxTextCtrl* robot_y_txt_ctrl;
        wxTimer controller_timer;
        wxTimer world_timer;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DWA_DEMOMAIN_H
