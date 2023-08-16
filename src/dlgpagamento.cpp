/////////////////////////////////////////////////////////////////////////////
// Name:        dlgpagamento.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     31/10/2012 10:37:24
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

#include "dlgpagamento.h"
#include "vilavilela.h"
////@begin XPM images
////@end XPM images


/*
 * dlgPagamento type definition
 */

IMPLEMENT_DYNAMIC_CLASS( dlgPagamento, wxDialog )


/*
 * dlgPagamento event table definition
 */

BEGIN_EVENT_TABLE( dlgPagamento, wxDialog )

////@begin dlgPagamento event table entries
////@end dlgPagamento event table entries

END_EVENT_TABLE()


/*
 * dlgPagamento constructors
 */

dlgPagamento::dlgPagamento()
{
	Init();
	
}

dlgPagamento::dlgPagamento( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
	Init();
	Create(parent, id, caption, pos, size, style);

	Palavra query;
	sql_ResultSet *res;
	query="SELECT idformapagto,descricao FROM formapagto";									
	if ((res=vilavielaframe->_execquerywithresult(query)) !=NULL) {
		wxChoice* cbx=(wxChoice*)this->FindWindowById(ID_PAGTO_TIPO,this); 
		wxString tmpstr;
		cbx->Clear();
		while (vilavielaframe->_nextrow(res)) {
			tmpstr=vilavielaframe->_getstring(res,2);
			cbx->Append(tmpstr, (wxClientData*)(new chcIdRef(vilavielaframe->_getint(res,1))));
		}
		vilavielaframe->_deleteresult(&res);
		cbx->SetSelection(0);
	}
}


/*
 * dlgPagamento creator
 */

bool dlgPagamento::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin dlgPagamento creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end dlgPagamento creation
    return true;
}


/*
 * dlgPagamento destructor
 */

dlgPagamento::~dlgPagamento()
{
////@begin dlgPagamento destruction
////@end dlgPagamento destruction
}


/*
 * Member initialisation
 */

void dlgPagamento::Init()
{
////@begin dlgPagamento member initialisation
////@end dlgPagamento member initialisation
}


/*
 * Control creation for dlgPagamento
 */

void dlgPagamento::CreateControls()
{    
////@begin dlgPagamento content construction
    dlgPagamento* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Tipo"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxArrayString itemChoice5Strings;
    wxChoice* itemChoice5 = new wxChoice( itemDialog1, ID_PAGTO_TIPO, wxDefaultPosition, wxDefaultSize, itemChoice5Strings, wxFULL_REPAINT_ON_RESIZE );
    itemChoice5->SetBackgroundColour(wxColour(255, 255, 255));
    itemFlexGridSizer3->Add(itemChoice5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 1);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Valor"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxTextCtrl* itemTextCtrl7 = new wxTextCtrl( itemDialog1, ID_PAGTO_VAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemTextCtrl7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer8 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_CANCEL, _("&Fechar"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton9);

    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_OK, _("&Confirmar"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton10->SetDefault();
    itemStdDialogButtonSizer8->AddButton(itemButton10);

    itemStdDialogButtonSizer8->Realize();

////@end dlgPagamento content construction
}


/*
 * Should we show tooltips?
 */

bool dlgPagamento::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap dlgPagamento::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin dlgPagamento bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end dlgPagamento bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon dlgPagamento::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin dlgPagamento icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end dlgPagamento icon retrieval
}



