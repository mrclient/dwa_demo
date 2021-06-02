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
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include "Map.h"
#include "Robot.h"
#include "DWAplanner.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>

class dwa_demoFrame: public wxFrame
{
    public:

        dwa_demoFrame(wxWindow* parent, wxWindowID id = -1);
        virtual ~dwa_demoFrame();

        Map* world_map;
        Robot robot;
        Goal goal;
        DWAplanner dwa_planner;
        bool program_stopped;
        bool redraw_required;
        bool redraw_allowed;

        void clearMap();
        void drawMap();
        void drawRobot();
        void drawGoal();
        void drawDWAwindow();
        void stopProcedure();
        void readTextFields();


    private:

        //(*Handlers(dwa_demoFrame)
        void OnClose(wxCloseEvent& event);
        void OnRepaint(wxPaintEvent& event);
        void OnNewMapButtonClick(wxCommandEvent& event);
        void mainTimerTickEvt(wxTimerEvent& event);
        void OnStartButtonClick(wxCommandEvent& event);
        void controllerTimerTickEvent(wxTimerEvent& event);
        void onTextEnter(wxCommandEvent& event);
        void redrawTimerTickEvt(wxTimerEvent& event);
        //*)

        //(*Identifiers(dwa_demoFrame)
        static const long ID_STATICTEXT8;
        static const long ID_MAP_PANEL;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT14;
        static const long ID_DWA_PANEL;
        static const long ID_START_BUTTON;
        static const long ID_NEW_MAP_BUTTON;
        static const long ID_ROBOTX_TEXTCTRL;
        static const long ID_ROBOTY_TEXTCTRL;
        static const long ID_ROBOTTH_TEXTCTRL;
        static const long ID_GOALX_TEXTCTRL;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_GOALY_TEXTCTRL;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT6;
        static const long ID_CYCLE_TEXTCTRL;
        static const long ID_PRED_TEXTCTRL;
        static const long ID_STATICTEXT7;
        static const long ID_TRAJQNT_TEXTCTRL;
        static const long ID_STATICTEXT9;
        static const long ID_ROBOTL_TEXTCTRL;
        static const long ID_ROBOTW_TEXTCTRL;
        static const long ID_ROBOTR_TEXTCTRL;
        static const long ID_STATICTEXT10;
        static const long ID_MAXSPEED_TEXTCTRL;
        static const long ID_MAXACC_TEXTCTRL;
        static const long ID_PID_TEXTCTRL;
        static const long ID_TEXTCTRL10;
        static const long ID_DWA_KD_TEXTCTRL;
        static const long ID_DWA_KS_TEXTCTRL;
        static const long ID_ACCUR_TEXTCTRL;
        static const long ID_BORD_TEXTCTRL;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT11;
        static const long ID_STATICTEXT12;
        static const long ID_CONTROL_PANEL;
        static const long ID_STATICTEXT15;
        static const long ID_WORLD_TIMER;
        static const long ID_CONTROLLER_TIMER;
        static const long ID_REDRAW_TIMER;
        //*)

        //(*Declarations(dwa_demoFrame)
        wxButton* new_map_button;
        wxButton* start_button;
        wxPanel* control_panel;
        wxPanel* dwa_panel;
        wxPanel* map_panel;
        wxStaticText* StaticText10;
        wxStaticText* StaticText11;
        wxStaticText* StaticText12;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxStaticText* StaticText15;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxTextCtrl* accur_txt_ctrl;
        wxTextCtrl* bord_txt_ctrl;
        wxTextCtrl* cycle_txt_ctrl;
        wxTextCtrl* dwa_ka_txt_ctrl;
        wxTextCtrl* dwa_kd_txt_ctrl;
        wxTextCtrl* dwa_ks_txt_ctrl;
        wxTextCtrl* goal_x_txt_ctrl;
        wxTextCtrl* goal_y_txt_ctrl;
        wxTextCtrl* m_max_ac_txt_ctrl;
        wxTextCtrl* m_max_sp_txt_ctrl;
        wxTextCtrl* pid_t_txt_ctrl;
        wxTextCtrl* pr_steps_txt_ctrl;
        wxTextCtrl* robot_l_txt_ctrl;
        wxTextCtrl* robot_r_txt_ctrl;
        wxTextCtrl* robot_th_txt_ctrl;
        wxTextCtrl* robot_w_txt_ctrl;
        wxTextCtrl* robot_x_txt_ctrl;
        wxTextCtrl* robot_y_txt_ctrl;
        wxTextCtrl* traj_qnt_txt_ctrl;
        wxTimer controller_timer;
        wxTimer redraw_timer;
        wxTimer world_timer;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DWA_DEMOMAIN_H
