/////////////////////////////////////////////////////////////////////////////
// Name:        selecioneintervalodecrz.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     Wed 11 Jul 2012 11:23:10 BRT
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

#include "selecioneintervalodecrz.h"

////@begin XPM images
////@end XPM images


/*
 * SelecioneIntervalodeCRZ type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SelecioneIntervalodeCRZ, wxDialog )


/*
 * SelecioneIntervalodeCRZ event table definition
 */

BEGIN_EVENT_TABLE( SelecioneIntervalodeCRZ, wxDialog )

////@begin SelecioneIntervalodeCRZ event table entries
////@end SelecioneIntervalodeCRZ event table entries

END_EVENT_TABLE()


/*
 * SelecioneIntervalodeCRZ constructors
 */

SelecioneIntervalodeCRZ::SelecioneIntervalodeCRZ()
{
    Init();
}

SelecioneIntervalodeCRZ::SelecioneIntervalodeCRZ( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * SelecioneIntervalodeCRZ creator
 */

bool SelecioneIntervalodeCRZ::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin SelecioneIntervalodeCRZ creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end SelecioneIntervalodeCRZ creation
    return true;
}


/*
 * SelecioneIntervalodeCRZ destructor
 */

SelecioneIntervalodeCRZ::~SelecioneIntervalodeCRZ()
{
////@begin SelecioneIntervalodeCRZ destruction
////@end SelecioneIntervalodeCRZ destruction
}


/*
 * Member initialisation
 */

void SelecioneIntervalodeCRZ::Init()
{
////@begin SelecioneIntervalodeCRZ member initialisation
////@end SelecioneIntervalodeCRZ member initialisation
}


/*
 * Control creation for SelecioneIntervalodeCRZ
 */

void SelecioneIntervalodeCRZ::CreateControls()
{    
////@begin SelecioneIntervalodeCRZ content construction
    SelecioneIntervalodeCRZ* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxGridSizer* itemGridSizer3 = new wxGridSizer(0, 2, 0, 0);
    itemBoxSizer2->Add(itemGridSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_LABEL_CRZI, _("CRZ inicial"), wxDefaultPosition, wxDefaultSize, 0 );
    itemGridSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_LABEL_CRZF, _("CRZ final"), wxDefaultPosition, wxDefaultSize, 0 );
    itemGridSizer3->Add(itemStaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl6 = new wxTextCtrl( itemDialog1, ID_DLGSELCRZ_INI, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemTextCtrl6->SetMaxLength(4);
    itemGridSizer3->Add(itemTextCtrl6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl7 = new wxTextCtrl( itemDialog1, ID_DLGSELCRZ_FIM, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemTextCtrl7->SetMaxLength(4);
    itemGridSizer3->Add(itemTextCtrl7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer8 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton9);

    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton10);

    itemStdDialogButtonSizer8->Realize();

////@end SelecioneIntervalodeCRZ content construction
}


/*
 * Should we show tooltips?
 */

bool SelecioneIntervalodeCRZ::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SelecioneIntervalodeCRZ::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin SelecioneIntervalodeCRZ bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end SelecioneIntervalodeCRZ bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SelecioneIntervalodeCRZ::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin SelecioneIntervalodeCRZ icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end SelecioneIntervalodeCRZ icon retrieval
}
