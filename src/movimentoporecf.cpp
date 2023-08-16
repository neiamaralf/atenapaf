/////////////////////////////////////////////////////////////////////////////
// Name:        movimentoporecf.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     17/07/2012 17:48:09
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

#include "movimentoporecf.h"

////@begin XPM images
////@end XPM images

#include "vilavilela.h"
#include "relatorios.h"
#include "impressora_fiscal.h"


/*
 * MovimentoporECF type definition
 */

IMPLEMENT_DYNAMIC_CLASS( MovimentoporECF, wxDialog )


/*
 * MovimentoporECF event table definition
 */

BEGIN_EVENT_TABLE( MovimentoporECF, wxDialog )

////@begin MovimentoporECF event table entries
////@end MovimentoporECF event table entries

END_EVENT_TABLE()


/*
 * MovimentoporECF constructors
 */

MovimentoporECF::MovimentoporECF()
{
    Init();
}

MovimentoporECF::MovimentoporECF( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * MovimentoporECF creator
 */

bool MovimentoporECF::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MovimentoporECF creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end MovimentoporECF creation
				char noserieteste[21]="";
				IMPRESSORA_FISCAL::_NumSerieImpressora(noserieteste);
				char *bd;
				int sz=RELATORIOS::requisitoXXII::descriptografa_arquivo("arquivo_auxiliare.txt",&bd);	
				List_String lst;_String *str;
				RELATORIOS::requisitoXXII::atualiza_arquivo_auxiliar("ECFS",bd,sz,NULL,NULL,false,true,&lst);
				wxChoice* cb=(wxChoice*)this->FindWindowById(ID_CB_ECF,this);
				cb->Clear();
				for(str=lst.prm;str;str=str->prx)
					cb->Append(str->str);
				wxString strf;
				strf=wxString::FromAscii(noserieteste);
				cb->Select(cb->FindString(strf));
				delete []bd;
    return true;
}


/*
 * MovimentoporECF destructor
 */

MovimentoporECF::~MovimentoporECF()
{
////@begin MovimentoporECF destruction
////@end MovimentoporECF destruction
}


/*
 * Member initialisation
 */

void MovimentoporECF::Init()
{
////@begin MovimentoporECF member initialisation
////@end MovimentoporECF member initialisation
}


/*
 * Control creation for MovimentoporECF
 */

void MovimentoporECF::CreateControls()
{    
////@begin MovimentoporECF content construction
    MovimentoporECF* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("ECF"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxArrayString itemChoice4Strings;
    wxChoice* itemChoice4 = new wxChoice( itemDialog1, ID_CB_ECF, wxDefaultPosition, wxDefaultSize, itemChoice4Strings, 0 );
    itemBoxSizer2->Add(itemChoice4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxGridSizer* itemGridSizer5 = new wxGridSizer(0, 2, 0, 0);
    itemBoxSizer2->Add(itemGridSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Data inicial"), wxDefaultPosition, wxDefaultSize, 0 );
    itemGridSizer5->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("Data final"), wxDefaultPosition, wxDefaultSize, 0 );
    itemGridSizer5->Add(itemStaticText7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxDatePickerCtrl* itemDatePickerCtrl8 = new wxDatePickerCtrl( itemDialog1, ID_MOVECF_DI, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN|wxDP_DEFAULT );
    itemGridSizer5->Add(itemDatePickerCtrl8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxDatePickerCtrl* itemDatePickerCtrl9 = new wxDatePickerCtrl( itemDialog1, ID_MOVECF_DF, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN|wxDP_DEFAULT );
    itemGridSizer5->Add(itemDatePickerCtrl9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer10 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer10->AddButton(itemButton11);

    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer10->AddButton(itemButton12);

    itemStdDialogButtonSizer10->Realize();

////@end MovimentoporECF content construction
}


/*
 * Should we show tooltips?
 */

bool MovimentoporECF::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MovimentoporECF::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MovimentoporECF bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end MovimentoporECF bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MovimentoporECF::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MovimentoporECF icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end MovimentoporECF icon retrieval
}
