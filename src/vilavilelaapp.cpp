/////////////////////////////////////////////////////////////////////////////
// Name:        vilavilelaapp.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     08/05/2012 09:52:28
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/cmdline.h"


////@begin includes
////@end includes

#include "vilavilelaapp.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( VilavilelaApp )
////@end implement app


/*
 * VilavilelaApp type definition
 */

IMPLEMENT_CLASS( VilavilelaApp, wxApp )


/*
 * VilavilelaApp event table definition
 */

BEGIN_EVENT_TABLE( VilavilelaApp, wxApp )

////@begin VilavilelaApp event table entries
////@end VilavilelaApp event table entries

END_EVENT_TABLE()


/*
 * Constructor for VilavilelaApp
 */

VilavilelaApp::VilavilelaApp()
{
    Init();
}


/*
 * Member initialisation
 */

void VilavilelaApp::Init()
{
	

////@begin VilavilelaApp member initialisation
////@end VilavilelaApp member initialisation
}

/*
 * Initialisation for VilavilelaApp
 */

bool VilavilelaApp::OnInit(){   
		if (this->argc > 0){
wxString cmdFilename = this->argv[0];
// Under Windows when invoking via a document
// in Explorer, we are passed the short form.
// So normalize and make the long form.
wxFileName fName(cmdFilename);
fName.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
cmdFilename = fName.GetPath();
fName.SetCwd(cmdFilename);
printf("exepath=%s\n",cmdFilename.ToAscii().data());
}

	wxString curdir=wxGetCwd();
	printf("curdir=%s\n",curdir.ToAscii().data());
	//while(!getchar());
	wxInitAllImageHandlers();
	VilaVilela* mainWindow = new VilaVilela( NULL );
	
	mainWindow->Show(true);
 return true;
}


/*
 * Cleanup for VilavilelaApp
 */

int VilavilelaApp::OnExit()
{    
////@begin VilavilelaApp cleanup
	return wxApp::OnExit();
////@end VilavilelaApp cleanup
}

