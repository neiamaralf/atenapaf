/////////////////////////////////////////////////////////////////////////////
// Name:        selec_cliente.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     23/07/2012 14:47:24
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

#include "selec_cliente.h"
#include "vilavilela.h"

////@begin XPM images
////@end XPM images


/*
 * selec_cliente type definition
 */

IMPLEMENT_DYNAMIC_CLASS( selec_cliente, wxDialog )


/*
 * selec_cliente event table definition
 */

BEGIN_EVENT_TABLE( selec_cliente, wxDialog )

////@begin selec_cliente event table entries
    EVT_INIT_DIALOG( selec_cliente::OnInitDialog )

////@end selec_cliente event table entries

END_EVENT_TABLE()


/*
 * selec_cliente constructors
 */

selec_cliente::selec_cliente()
{
    Init();
}

selec_cliente::selec_cliente( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * selec_cliente creator
 */

bool selec_cliente::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin selec_cliente creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end selec_cliente creation
				sql_ResultSet *res;
				Palavra query;
				query="SELECT idcliente,nome FROM cliente ORDER BY nome";
				res=vilavielaframe->_execquerywithresult(query);
				if(res!=NULL&&vilavielaframe->_nextrow(res)){
					wxChoice* cbx=(wxChoice*)this->FindWindowById(ID_CBSELCLIENTE,this);
					wxString tmpstr;
					do{
						tmpstr=vilavielaframe->_getstring(res,2);
						cbx->Append(tmpstr,(wxClientData*)(new chcIdRef(vilavielaframe->_getint(res,1))));
					}while(vilavielaframe->_nextrow(res));
					vilavielaframe->_deleteresult(&res);
					if(cbx->GetCount()>0)cbx->SetSelection(0);
				}
    return true;
}


/*
 * selec_cliente destructor
 */

selec_cliente::~selec_cliente()
{
////@begin selec_cliente destruction
////@end selec_cliente destruction
}


/*
 * Member initialisation
 */

void selec_cliente::Init()
{
	
////@begin selec_cliente member initialisation
////@end selec_cliente member initialisation
}


/*
 * Control creation for selec_cliente
 */

void selec_cliente::CreateControls()
{    
////@begin selec_cliente content construction
    selec_cliente* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxArrayString itemChoice3Strings;
    wxChoice* itemChoice3 = new wxChoice( itemDialog1, ID_CBSELCLIENTE, wxDefaultPosition, wxSize(200, -1), itemChoice3Strings, 0 );
    itemBoxSizer2->Add(itemChoice3, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer4 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton5 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton5->SetDefault();
    itemStdDialogButtonSizer4->AddButton(itemButton5);

    itemStdDialogButtonSizer4->Realize();

////@end selec_cliente content construction
}


/*
 * Should we show tooltips?
 */

bool selec_cliente::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap selec_cliente::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin selec_cliente bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end selec_cliente bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon selec_cliente::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin selec_cliente icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end selec_cliente icon retrieval
}


/*
 * wxEVT_INIT_DIALOG event handler for ID_SELEC_CLIENTE
 */

void selec_cliente::OnInitDialog( wxInitDialogEvent& event )
{
	FindWindowById(wxID_OK,this)->SetFocus();
////@begin wxEVT_INIT_DIALOG event handler for ID_SELEC_CLIENTE in selec_cliente.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_INIT_DIALOG event handler for ID_SELEC_CLIENTE in selec_cliente. 
}

