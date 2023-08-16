/////////////////////////////////////////////////////////////////////////////
// Name:        leiturax.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     23/05/2012 10:58:31
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

////@begin includes
////@end includes

#include "leiturax.h"

////@begin XPM images
////@end XPM images


/*
 * LeituraX type definition
 */

IMPLEMENT_DYNAMIC_CLASS( LeituraX, wxDialog )


/*
 * LeituraX event table definition
 */

BEGIN_EVENT_TABLE( LeituraX, wxDialog )

////@begin LeituraX event table entries
    EVT_BUTTON( wxID_OK, LeituraX::OnOkClick )

////@end LeituraX event table entries

END_EVENT_TABLE()


/*
 * LeituraX constructors
 */

LeituraX::LeituraX()
{
    Init();
}

LeituraX::LeituraX( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * LeituraX creator
 */

bool LeituraX::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin LeituraX creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end LeituraX creation
    return true;
}


/*
 * LeituraX destructor
 */

LeituraX::~LeituraX()
{
////@begin LeituraX destruction
////@end LeituraX destruction
}


/*
 * Member initialisation
 */

void LeituraX::Init()
{
////@begin LeituraX member initialisation
////@end LeituraX member initialisation
}


/*
 * Control creation for LeituraX
 */

void LeituraX::CreateControls()
{    
////@begin LeituraX content construction
    LeituraX* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxTextCtrl* itemTextCtrl3 = new wxTextCtrl( itemDialog1, ID_TEXTLEITURAX, wxEmptyString, wxDefaultPosition, wxSize(300, 500), wxTE_MULTILINE );
    itemBoxSizer2->Add(itemTextCtrl3, 1, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer4 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton5 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer4->AddButton(itemButton5);

    itemStdDialogButtonSizer4->Realize();

////@end LeituraX content construction
}


/*
 * Should we show tooltips?
 */

bool LeituraX::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap LeituraX::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin LeituraX bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end LeituraX bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon LeituraX::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin LeituraX icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end LeituraX icon retrieval
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void LeituraX::OnOkClick( wxCommandEvent& event )
{
	Destroy();
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in LeituraX.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in LeituraX. 
}

