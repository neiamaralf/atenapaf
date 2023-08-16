/////////////////////////////////////////////////////////////////////////////
// Name:        dbhost_adress.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     Wed 26 Sep 2012 10:29:57 BRT
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

#include "dbhost_adress.h"

////@begin XPM images
////@end XPM images


/*
 * dbhost_adress type definition
 */

IMPLEMENT_DYNAMIC_CLASS( dbhost_adress, wxDialog )


/*
 * dbhost_adress event table definition
 */

BEGIN_EVENT_TABLE( dbhost_adress, wxDialog )

////@begin dbhost_adress event table entries
////@end dbhost_adress event table entries

END_EVENT_TABLE()


/*
 * dbhost_adress constructors
 */

dbhost_adress::dbhost_adress()
{
    Init();
}

dbhost_adress::dbhost_adress( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * dbhost_adress creator
 */

bool dbhost_adress::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin dbhost_adress creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end dbhost_adress creation
    return true;
}


/*
 * dbhost_adress destructor
 */

dbhost_adress::~dbhost_adress()
{
////@begin dbhost_adress destruction
////@end dbhost_adress destruction
}


/*
 * Member initialisation
 */

void dbhost_adress::Init()
{
////@begin dbhost_adress member initialisation
////@end dbhost_adress member initialisation
}


/*
 * Control creation for dbhost_adress
 */

void dbhost_adress::CreateControls()
{    
////@begin dbhost_adress content construction
    dbhost_adress* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("Endere")) + (wxChar) 0x00E7 + wxT("o IPv4 (ex.:192.168.0.1)")));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl4 = new wxTextCtrl( itemDialog1, ID_IPV4_1, wxEmptyString, wxDefaultPosition, wxSize(itemDialog1->ConvertDialogToPixels(wxSize(150, -1)).x, -1), 0 );
    itemStaticBoxSizer3->Add(itemTextCtrl4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxPanel* itemPanel5 = new wxPanel( itemDialog1, ID_PANEL1, wxDefaultPosition, wxSize(-1, itemDialog1->ConvertDialogToPixels(wxSize(-1, 23)).y), wxTAB_TRAVERSAL );
    itemBoxSizer2->Add(itemPanel5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer6 = new wxStdDialogButtonSizer;

    itemPanel5->SetSizer(itemStdDialogButtonSizer6);

    wxButton* itemButton7 = new wxButton( itemPanel5, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer6->AddButton(itemButton7);

    wxButton* itemButton8 = new wxButton( itemPanel5, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxSize(-1, itemPanel5->ConvertDialogToPixels(wxSize(-1, 15)).y), 0 );
    itemStdDialogButtonSizer6->AddButton(itemButton8);

    itemStdDialogButtonSizer6->Realize();

////@end dbhost_adress content construction
}


/*
 * Should we show tooltips?
 */

bool dbhost_adress::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap dbhost_adress::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin dbhost_adress bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end dbhost_adress bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon dbhost_adress::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin dbhost_adress icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end dbhost_adress icon retrieval
}
