/////////////////////////////////////////////////////////////////////////////
// Name:        selecioneintervalodedata.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     Wed 11 Jul 2012 11:18:19 BRT
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

#include "selecioneintervalodedata.h"

////@begin XPM images
////@end XPM images


/*
 * SelecioneIntervalodeData type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SelecioneIntervalodeData, wxDialog )


/*
 * SelecioneIntervalodeData event table definition
 */

BEGIN_EVENT_TABLE( SelecioneIntervalodeData, wxDialog )

////@begin SelecioneIntervalodeData event table entries
////@end SelecioneIntervalodeData event table entries

END_EVENT_TABLE()


/*
 * SelecioneIntervalodeData constructors
 */

SelecioneIntervalodeData::SelecioneIntervalodeData()
{
    Init();
}

SelecioneIntervalodeData::SelecioneIntervalodeData( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * SelecioneIntervalodeData creator
 */

bool SelecioneIntervalodeData::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin SelecioneIntervalodeData creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end SelecioneIntervalodeData creation
    return true;
}


/*
 * SelecioneIntervalodeData destructor
 */

SelecioneIntervalodeData::~SelecioneIntervalodeData()
{
////@begin SelecioneIntervalodeData destruction
////@end SelecioneIntervalodeData destruction
}


/*
 * Member initialisation
 */

void SelecioneIntervalodeData::Init()
{
////@begin SelecioneIntervalodeData member initialisation
////@end SelecioneIntervalodeData member initialisation
}


/*
 * Control creation for SelecioneIntervalodeData
 */

void SelecioneIntervalodeData::CreateControls()
{    
////@begin SelecioneIntervalodeData content construction
    SelecioneIntervalodeData* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxGridSizer* itemGridSizer3 = new wxGridSizer(0, 2, 0, 0);
    itemBoxSizer2->Add(itemGridSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Data inicial"), wxDefaultPosition, wxDefaultSize, 0 );
    itemGridSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("Data final"), wxDefaultPosition, wxDefaultSize, 0 );
    itemGridSizer3->Add(itemStaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxDatePickerCtrl* itemDatePickerCtrl6 = new wxDatePickerCtrl( itemDialog1, ID_DLGSELDATA_DATAINI, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
    itemGridSizer3->Add(itemDatePickerCtrl6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxDatePickerCtrl* itemDatePickerCtrl7 = new wxDatePickerCtrl( itemDialog1, ID_DLGSELDATA_DATAFIM, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
    itemGridSizer3->Add(itemDatePickerCtrl7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer8 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton9);

    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton10);

    itemStdDialogButtonSizer8->Realize();

////@end SelecioneIntervalodeData content construction
}


/*
 * Should we show tooltips?
 */

bool SelecioneIntervalodeData::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SelecioneIntervalodeData::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin SelecioneIntervalodeData bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end SelecioneIntervalodeData bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SelecioneIntervalodeData::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin SelecioneIntervalodeData icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end SelecioneIntervalodeData icon retrieval
}
