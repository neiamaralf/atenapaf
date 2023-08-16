/////////////////////////////////////////////////////////////////////////////
// Name:        balanco.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     16/08/2012 09:57:03
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

#include "balanco.h"

////@begin XPM images
////@end XPM images


/*
 * Balanco type definition
 */

IMPLEMENT_DYNAMIC_CLASS( Balanco, wxDialog )


/*
 * Balanco event table definition
 */

BEGIN_EVENT_TABLE( Balanco, wxDialog )

////@begin Balanco event table entries
////@end Balanco event table entries

END_EVENT_TABLE()


/*
 * Balanco constructors
 */

Balanco::Balanco()
{
    Init();
}

Balanco::Balanco( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * Balanco creator
 */

bool Balanco::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin Balanco creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end Balanco creation
    return true;
}


/*
 * Balanco destructor
 */

Balanco::~Balanco()
{
////@begin Balanco destruction
////@end Balanco destruction
}


/*
 * Member initialisation
 */

void Balanco::Init()
{
////@begin Balanco member initialisation
////@end Balanco member initialisation
}


/*
 * Control creation for Balanco
 */

void Balanco::CreateControls()
{    
////@begin Balanco content construction
    Balanco* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Data inicial"));
    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCalendarCtrl* itemCalendarCtrl5 = new wxCalendarCtrl( itemDialog1, ID_CALCTRL_BALANCO, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER );
    itemStaticBoxSizer4->Add(itemCalendarCtrl5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer6Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("Data final( se o balan")) + (wxChar) 0x00E7 + wxT("o for por data)")));
    wxStaticBoxSizer* itemStaticBoxSizer6 = new wxStaticBoxSizer(itemStaticBoxSizer6Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCalendarCtrl* itemCalendarCtrl7 = new wxCalendarCtrl( itemDialog1, ID_CALCTRL_BALANCOF, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER );
    itemStaticBoxSizer6->Add(itemCalendarCtrl7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxArrayString itemRadioBox8Strings;
    itemRadioBox8Strings.Add(_("&Mensal"));
    itemRadioBox8Strings.Add(_("&Anual"));
    itemRadioBox8Strings.Add(_("&Data"));
    wxRadioBox* itemRadioBox8 = new wxRadioBox( itemDialog1, ID_RB_BALANCO, wxGetTranslation(wxString(wxT("Tipo balan")) + (wxChar) 0x00E7 + wxT("o")), wxDefaultPosition, wxDefaultSize, itemRadioBox8Strings, 1, wxRA_SPECIFY_ROWS );
    itemRadioBox8->SetSelection(0);
    itemBoxSizer2->Add(itemRadioBox8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer9 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer9->AddButton(itemButton10);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer9->AddButton(itemButton11);

    itemStdDialogButtonSizer9->Realize();

////@end Balanco content construction
}


/*
 * Should we show tooltips?
 */

bool Balanco::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap Balanco::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin Balanco bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end Balanco bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon Balanco::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin Balanco icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end Balanco icon retrieval
}
