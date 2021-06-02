/***************************************************************
 * Name:      dwa_demoApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2021-05-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "dwa_demoApp.h"

//(*AppHeaders
#include "dwa_demoMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(dwa_demoApp);

bool dwa_demoApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	dwa_demoFrame* Frame = new dwa_demoFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
