/////////////////////////////////////////////////////////////////////////////
// Name:        dlgprintbarcode.cpp
// Purpose:
// Author:
// Modified by:
// Created:     Tue 28 Aug 2012 20:07:00 BRT
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


#include "vilavilela.h"
#define FN_ETIQUETAS "etiquetas.ini"
////@begin XPM images
////@end XPM images


/*
 * dlgPrintBarCode type definition
 */

IMPLEMENT_DYNAMIC_CLASS ( dlgPrintBarCode, wxDialog )


/*
 * dlgPrintBarCode event table definition
 */

BEGIN_EVENT_TABLE ( dlgPrintBarCode, wxDialog )

	////@begin dlgPrintBarCode event table entries
    EVT_INIT_DIALOG( dlgPrintBarCode::OnInitDialog )
    EVT_IDLE( dlgPrintBarCode::OnIdle )

    EVT_CHOICE( ID_CB_CB_PRESET, dlgPrintBarCode::OnCbCbPresetSelected )

    EVT_BUTTON( ID_BT_CB_NPRESET, dlgPrintBarCode::OnBtCbNpresetClick )

    EVT_BUTTON( ID_BT_CB_DELPRESET, dlgPrintBarCode::OnBtCbDelpresetClick )

    EVT_BUTTON( wxID_CANCEL, dlgPrintBarCode::OnCancelClick )

    EVT_BUTTON( wxID_OK, dlgPrintBarCode::OnImprimeClick )

    EVT_BUTTON( wxID_APPLY, dlgPrintBarCode::OnSalvarClick )

	////@end dlgPrintBarCode event table entries

END_EVENT_TABLE()


/*
 * dlgPrintBarCode constructors
 */

dlgPrintBarCode::dlgPrintBarCode() {
	Init();
}

dlgPrintBarCode::dlgPrintBarCode ( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style ) {
	Init();
	Create ( parent, id, caption, pos, size, style );
}


/*
 * dlgPrintBarCode creator
 */

bool dlgPrintBarCode::Create ( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style ) {
////@begin dlgPrintBarCode creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end dlgPrintBarCode creation
	return true;
}


/*
 * dlgPrintBarCode destructor
 */

dlgPrintBarCode::~dlgPrintBarCode() {
////@begin dlgPrintBarCode destruction
////@end dlgPrintBarCode destruction
}


/*
 * Member initialisation
 */

void dlgPrintBarCode::Init() {
	lstetiquetainfo.etiquetapadrao=0;
////@begin dlgPrintBarCode member initialisation
////@end dlgPrintBarCode member initialisation
}


/*
 * Control creation for dlgPrintBarCode
 */

void dlgPrintBarCode::CreateControls() {
////@begin dlgPrintBarCode content construction
    dlgPrintBarCode* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("Predefini")) + (wxChar) 0x00E7 + (wxChar) 0x00F5 + wxT("es")));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxArrayString itemChoice4Strings;
    wxChoice* itemChoice4 = new wxChoice( itemDialog1, ID_CB_CB_PRESET, wxDefaultPosition, wxSize(200, -1), itemChoice4Strings, 0 );
    itemStaticBoxSizer3->Add(itemChoice4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton5 = new wxBitmapButton( itemDialog1, ID_BT_CB_NPRESET, itemDialog1->GetBitmapResource(wxT("images/DataContainer_NewRecordHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    if (dlgPrintBarCode::ShowToolTips())
        itemBitmapButton5->SetToolTip(wxGetTranslation(wxString(wxT("Nova predefini")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")));
    itemStaticBoxSizer3->Add(itemBitmapButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton6 = new wxBitmapButton( itemDialog1, ID_BT_CB_DELPRESET, itemDialog1->GetBitmapResource(wxT("images/DeleteHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    if (dlgPrintBarCode::ShowToolTips())
        itemBitmapButton6->SetToolTip(wxGetTranslation(wxString(wxT("Excluir predefini")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o atual")));
    itemStaticBoxSizer3->Add(itemBitmapButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer8Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Tipo"));
    wxStaticBoxSizer* itemStaticBoxSizer8 = new wxStaticBoxSizer(itemStaticBoxSizer8Static, wxHORIZONTAL);
    itemBoxSizer7->Add(itemStaticBoxSizer8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice9Strings;
    itemChoice9Strings.Add(_("3 de 9"));
    itemChoice9Strings.Add(_("128 A"));
    itemChoice9Strings.Add(_("128 B"));
    itemChoice9Strings.Add(_("128 C"));
    itemChoice9Strings.Add(_("UPC A"));
    itemChoice9Strings.Add(_("EAN 13"));
    itemChoice9Strings.Add(_("EAN 8"));
    wxChoice* itemChoice9 = new wxChoice( itemDialog1, ID_CB_CB_TIPO, wxDefaultPosition, wxSize(200, -1), itemChoice9Strings, 0 );
    itemChoice9->SetStringSelection(_("UPC A"));
    itemStaticBoxSizer8->Add(itemChoice9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer10Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("No. de c")) + (wxChar) 0x00F3 + wxT("pias")));
    wxStaticBoxSizer* itemStaticBoxSizer10 = new wxStaticBoxSizer(itemStaticBoxSizer10Static, wxHORIZONTAL);
    itemBoxSizer7->Add(itemStaticBoxSizer10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl11 = new wxSpinCtrl( itemDialog1, ID_TXT_CB_NC, _T("1"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 0, 1000, 1 );
    itemStaticBoxSizer10->Add(itemSpinCtrl11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer12Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Altura texto"));
    wxStaticBoxSizer* itemStaticBoxSizer12 = new wxStaticBoxSizer(itemStaticBoxSizer12Static, wxHORIZONTAL);
    itemBoxSizer7->Add(itemStaticBoxSizer12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl13 = new wxTextCtrl( itemDialog1, ID_TXT_CB_AT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer12->Add(itemTextCtrl13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer14 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer2->Add(itemFlexGridSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer15Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Margem H"));
    wxStaticBoxSizer* itemStaticBoxSizer15 = new wxStaticBoxSizer(itemStaticBoxSizer15Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer15, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl16 = new wxTextCtrl( itemDialog1, ID_TXT_CB_MH, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer15->Add(itemTextCtrl16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText17 = new wxStaticText( itemDialog1, wxID_STATIC, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer15->Add(itemStaticText17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer18Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Margem V"));
    wxStaticBoxSizer* itemStaticBoxSizer18 = new wxStaticBoxSizer(itemStaticBoxSizer18Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer18, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl19 = new wxTextCtrl( itemDialog1, ID_TXT_CB_MV, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer18->Add(itemTextCtrl19, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( itemDialog1, wxID_STATIC, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer18->Add(itemStaticText20, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer21Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("Dist")) + (wxChar) 0x00E2 + wxT("ncia entre colunas")));
    wxStaticBoxSizer* itemStaticBoxSizer21 = new wxStaticBoxSizer(itemStaticBoxSizer21Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer21, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl22 = new wxTextCtrl( itemDialog1, ID_TXT_CB_DC, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer21->Add(itemTextCtrl22, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText23 = new wxStaticText( itemDialog1, wxID_STATIC, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer21->Add(itemStaticText23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer24Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("Dist")) + (wxChar) 0x00E2 + wxT("ncia entre linhas")));
    wxStaticBoxSizer* itemStaticBoxSizer24 = new wxStaticBoxSizer(itemStaticBoxSizer24Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer24, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl25 = new wxTextCtrl( itemDialog1, ID_TXT_CB_DL, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer24->Add(itemTextCtrl25, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText26 = new wxStaticText( itemDialog1, wxID_STATIC, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer24->Add(itemStaticText26, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer27Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("Largura C")) + (wxChar) 0x00F3 + wxT("digo de Barras")));
    wxStaticBoxSizer* itemStaticBoxSizer27 = new wxStaticBoxSizer(itemStaticBoxSizer27Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer27, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl28 = new wxTextCtrl( itemDialog1, ID_TXT_CB_LCB, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer27->Add(itemTextCtrl28, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText29 = new wxStaticText( itemDialog1, wxID_STATIC, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer27->Add(itemStaticText29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer30Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("Altura C")) + (wxChar) 0x00F3 + wxT("digo de Barras")));
    wxStaticBoxSizer* itemStaticBoxSizer30 = new wxStaticBoxSizer(itemStaticBoxSizer30Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer30, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl31 = new wxTextCtrl( itemDialog1, ID_TXT_CB_ACB, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer30->Add(itemTextCtrl31, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText32 = new wxStaticText( itemDialog1, wxID_STATIC, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer30->Add(itemStaticText32, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer33Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("N")) + (wxChar) 0x00FA + wxT("mero Etiquetas H")));
    wxStaticBoxSizer* itemStaticBoxSizer33 = new wxStaticBoxSizer(itemStaticBoxSizer33Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer33, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl34 = new wxTextCtrl( itemDialog1, ID_TXT_CB_NEH, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer33->Add(itemTextCtrl34, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer35Static = new wxStaticBox(itemDialog1, wxID_ANY, wxGetTranslation(wxString(wxT("N")) + (wxChar) 0x00FA + wxT("mero de Etiquetas V")));
    wxStaticBoxSizer* itemStaticBoxSizer35 = new wxStaticBoxSizer(itemStaticBoxSizer35Static, wxHORIZONTAL);
    itemFlexGridSizer14->Add(itemStaticBoxSizer35, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl36 = new wxTextCtrl( itemDialog1, ID_TXT_CB_NEV, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0 );
    itemStaticBoxSizer35->Add(itemTextCtrl36, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer37 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer37, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton38 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer37->AddButton(itemButton38);

    wxButton* itemButton39 = new wxButton( itemDialog1, wxID_OK, _("&Imprimir"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer37->AddButton(itemButton39);

    wxButton* itemButton40 = new wxButton( itemDialog1, wxID_APPLY, _("&Salvar"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton40->Enable(false);
    itemStdDialogButtonSizer37->AddButton(itemButton40);

    itemStdDialogButtonSizer37->Realize();

////@end dlgPrintBarCode content construction
}


/*
 * Should we show tooltips?
 */

bool dlgPrintBarCode::ShowToolTips() {
	return true;
}



/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
 */

void dlgPrintBarCode::OnSalvarClick ( wxCommandEvent& event ) {
	lstetiquetainfo.savetofile ( FN_ETIQUETAS );
	wxButton *bt= ( wxButton* ) this->FindWindowById ( wxID_APPLY,this );
	bt->Disable();
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY in dlgPrintBarCode.
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void dlgPrintBarCode::OnImprimeClick ( wxCommandEvent& event ) {
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in dlgPrintBarCode.
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void dlgPrintBarCode::OnCancelClick ( wxCommandEvent& event ) {
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in dlgPrintBarCode.
}



/*
 * wxEVT_IDLE event handler for ID_DLGPRINTBARCODE
 */

void dlgPrintBarCode::OnIdle ( wxIdleEvent& event ) {
	wxButton *bt= ( wxButton* ) this->FindWindowById ( wxID_APPLY,this );
	if ( bt ) {
			if ( changed() ) {
					updatelist();
					bt->Enable();
				}
		}
////@begin wxEVT_IDLE event handler for ID_DLGPRINTBARCODE in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_IDLE event handler for ID_DLGPRINTBARCODE in dlgPrintBarCode.
}


void LstEtiquetaInfo::loadfromfile ( const char *fname ) {
	limpa();
	etiquetapadrao=0;
	FILE *f=fopen ( fname,"rb" );
	char descricao[64];
	int CB_NC,CB_NEH,CB_NEV,CB_TIPO,padrao;
	double CB_AT,CB_MH,CB_MV,CB_DC,CB_DL,CB_LCB,CB_ACB;
	if ( f!=NULL ) {
			char c[2],*ptrc;
			int bytes;
			while (
			 fscanf ( f,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d\t%d\t%d\t%d\t",
			          &CB_LCB,&CB_ACB,&CB_AT,&CB_MH,&CB_MV,&CB_DC,&CB_DL,&CB_NC,&CB_NEH,&CB_NEV,&CB_TIPO,&padrao ) !=EOF ) {
					ptrc=descricao;

					while ( ( bytes = fread ( c, 1, 1, f ) ) != 0 ) {

							if ( *c!='\n' )
								* ( ptrc++ ) =*c;
							else
								break;
						}
					*ptrc=0;
					novo ( descricao,CB_LCB,CB_ACB,CB_AT,CB_MH,CB_MV,CB_DC,CB_DL,CB_NC,CB_NEH,CB_NEV,CB_TIPO,padrao );
					if ( padrao )
						etiquetapadrao=ult;
				}
			fclose ( f );
		} else {
			f=fopen ( fname,"w+b" );
			if ( f!=NULL ) {
					strcpy ( descricao,"80 por folha" );
					CB_AT=3;CB_LCB=40,CB_ACB=10;
					CB_MH=17.225,CB_MV=14.35,CB_DC=47.5,CB_DL=12.7,CB_NC=1,CB_NEH=4,CB_NEV=20,CB_TIPO=CODE_UPC_A,padrao=1;
					fprintf ( f,"%g\t%g\t%g\t%g\t%g\t%g\t%g\t%d\t%d\t%d\t%d\t%d\t%s\n",CB_LCB,CB_ACB,CB_AT,CB_MH,CB_MV,CB_DC,CB_DL,CB_NC,CB_NEH,CB_NEV,CB_TIPO,padrao,descricao );
					novo ( descricao,CB_LCB,CB_ACB,CB_AT,CB_MH,CB_MV,CB_DC,CB_DL,CB_NC,CB_NEH,CB_NEV,CB_TIPO,padrao );
					etiquetapadrao=ult;
					fclose ( f );
				}
		}

}

void LstEtiquetaInfo::savetofile ( const char *fname ) {
	EtiquetaInfo *et;
	FILE *f=fopen ( fname,"w+b" );
	if ( f!=NULL ) {
			for ( et=prm;et;et=et->prx ) {
					fprintf ( f,"%g\t%g\t%g\t%g\t%g\t%g\t%g\t%d\t%d\t%d\t%d\t%d\t%s\n",et->CB_LCB,et->CB_ACB,et->CB_AT,et->CB_MH,et->CB_MV,et->CB_DC,et->CB_DL,et->CB_NC,et->CB_NEH,
					          et->CB_NEV,et->CB_TIPO,etiquetapadrao==et?1:0,et->descricao );
				}
			fclose ( f );
		}
}

void dlgPrintBarCode::updatecontrols() {
	if ( !lstetiquetainfo.etiquetapadrao ) return;
	wxChoice *cb= ( wxChoice* ) this->FindWindowById ( ID_CB_CB_TIPO,this );
	cb->SetSelection ( lstetiquetainfo.etiquetapadrao->CB_TIPO );
	wxTextCtrl *txt;
	wxSpinCtrl *sp= ( wxSpinCtrl* ) this->FindWindowById ( ID_TXT_CB_NC,this );
	sp->SetValue ( lstetiquetainfo.etiquetapadrao->CB_NC  );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_LCB,this );
	txt->SetValue ( wxString::Format ( _ ( "%.3f" ),lstetiquetainfo.etiquetapadrao->CB_LCB ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_ACB,this );
	txt->SetValue ( wxString::Format ( _ ( "%.3f" ),lstetiquetainfo.etiquetapadrao->CB_ACB ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_AT,this );
	txt->SetValue ( wxString::Format ( _ ( "%.3f" ),lstetiquetainfo.etiquetapadrao->CB_AT ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_MH,this );
	txt->SetValue ( wxString::Format ( _ ( "%.3f" ),lstetiquetainfo.etiquetapadrao->CB_MH ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_MV,this );
	txt->SetValue ( wxString::Format ( _ ( "%.3f" ),lstetiquetainfo.etiquetapadrao->CB_MV ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_DC,this );
	txt->SetValue ( wxString::Format ( _ ( "%.3f" ),lstetiquetainfo.etiquetapadrao->CB_DC ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_DL,this );
	txt->SetValue ( wxString::Format ( _ ( "%.3f" ),lstetiquetainfo.etiquetapadrao->CB_DL ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_NEH,this );
	txt->SetValue ( wxString::Format ( _ ( "%d" ),lstetiquetainfo.etiquetapadrao->CB_NEH ) );
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_NEV,this );
	txt->SetValue ( wxString::Format ( _ ( "%d" ),lstetiquetainfo.etiquetapadrao->CB_NEV ) );
	wxButton *bt= ( wxButton* ) this->FindWindowById ( wxID_APPLY,this );
	bt->Disable();
}

EtiquetaInfo *LstEtiquetaInfo::etiquetapadrao=0;
bool dlgPrintBarCode::changed() {
	if ( !lstetiquetainfo.etiquetapadrao ) return false;
	wxChoice *cb= ( wxChoice* ) this->FindWindowById ( ID_CB_CB_TIPO,this );
	if ( cb->GetSelection () !=lstetiquetainfo.etiquetapadrao->CB_TIPO ) return true;
	wxTextCtrl *txt;
	long lval;
	double dbval;
	wxSpinCtrl *sp= ( wxSpinCtrl* ) this->FindWindowById ( ID_TXT_CB_NC,this );
	lval=sp->GetValue ();

	if ( ( int ) lval!=lstetiquetainfo.etiquetapadrao->CB_NC ) return true;
	
		txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_LCB,this );
	txt->GetValue().ToDouble ( &dbval );
	if ( dbval!=lstetiquetainfo.etiquetapadrao->CB_LCB ) return true;
	
		txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_ACB,this );
	txt->GetValue().ToDouble ( &dbval );
	if ( dbval!=lstetiquetainfo.etiquetapadrao->CB_ACB ) return true;
	
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_AT,this );
	txt->GetValue().ToDouble ( &dbval );
	if ( dbval!=lstetiquetainfo.etiquetapadrao->CB_AT ) return true;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_MH,this );
	txt->GetValue().ToDouble ( &dbval );
	if ( dbval!=lstetiquetainfo.etiquetapadrao->CB_MH ) return true;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_MV,this );
	txt->GetValue().ToDouble ( &dbval );
	if ( dbval!=lstetiquetainfo.etiquetapadrao->CB_MV ) return true;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_DC,this );
	txt->GetValue().ToDouble ( &dbval );
	if ( dbval!=lstetiquetainfo.etiquetapadrao->CB_DC ) return true;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_DL,this );
	txt->GetValue().ToDouble ( &dbval );
	if ( dbval!=lstetiquetainfo.etiquetapadrao->CB_DL ) return true;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_NEH,this );
	txt->GetValue().ToLong ( &lval );
	if ( ( int ) lval!=lstetiquetainfo.etiquetapadrao->CB_NEH ) return true;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_NEV,this );
	txt->GetValue().ToLong ( &lval );
	if ( ( int ) lval!=lstetiquetainfo.etiquetapadrao->CB_NEV ) return true;
	return false;
}

void dlgPrintBarCode::updatelist() {
	if ( !lstetiquetainfo.etiquetapadrao ) return ;
	wxChoice *cb= ( wxChoice* ) this->FindWindowById ( ID_CB_CB_TIPO,this );
	lstetiquetainfo.etiquetapadrao->CB_TIPO=cb->GetSelection ();
	wxTextCtrl *txt;
	long lval;
	double dbval;
		wxSpinCtrl *sp= ( wxSpinCtrl* ) this->FindWindowById ( ID_TXT_CB_NC,this );
	lval=sp->GetValue ();
	lstetiquetainfo.etiquetapadrao->CB_NC= ( int ) lval;
	
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_LCB,this );
	txt->GetValue().ToDouble ( &dbval );
	lstetiquetainfo.etiquetapadrao->CB_LCB=dbval;
	
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_ACB,this );
	txt->GetValue().ToDouble ( &dbval );
	lstetiquetainfo.etiquetapadrao->CB_ACB=dbval;
	
	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_AT,this );
	txt->GetValue().ToDouble ( &dbval );
	lstetiquetainfo.etiquetapadrao->CB_AT=dbval;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_MH,this );
	txt->GetValue().ToDouble ( &dbval );
	lstetiquetainfo.etiquetapadrao->CB_MH=dbval;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_MV,this );
	txt->GetValue().ToDouble ( &dbval );
	lstetiquetainfo.etiquetapadrao->CB_MV=dbval;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_DC,this );
	txt->GetValue().ToDouble ( &dbval );
	lstetiquetainfo.etiquetapadrao->CB_DC=dbval;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_DL,this );
	txt->GetValue().ToDouble ( &dbval );
	lstetiquetainfo.etiquetapadrao->CB_DL=dbval;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_NEH,this );
	txt->GetValue().ToLong ( &lval );
	lstetiquetainfo.etiquetapadrao->CB_NEH= ( int ) lval;

	txt= ( wxTextCtrl* ) this->FindWindowById ( ID_TXT_CB_NEV,this );
	txt->GetValue().ToLong ( &lval );
	lstetiquetainfo.etiquetapadrao->CB_NEV= ( int ) lval;
}


/*
 * wxEVT_INIT_DIALOG event handler for ID_DLGPRINTBARCODE
 */

void dlgPrintBarCode::OnInitDialog ( wxInitDialogEvent& event ) {
	lstetiquetainfo.loadfromfile ( FN_ETIQUETAS );
	wxChoice *cb= ( wxChoice* ) this->FindWindowById ( ID_CB_CB_PRESET,this );
	EtiquetaInfo *et;
	for ( et=lstetiquetainfo.prm;et;et=et->prx ) {
			if ( et->padrao )
				lstetiquetainfo.etiquetapadrao=et;
			cb->Append ( ___ ( et->descricao ) );
		}
	if ( lstetiquetainfo.etiquetapadrao ) {
			int index;
			index=cb->FindString ( ___ ( lstetiquetainfo.etiquetapadrao->descricao ) );
			if ( index>=0 ) {
					cb->SetSelection ( index );
					updatecontrols();
				}
		}
////@begin wxEVT_INIT_DIALOG event handler for ID_DLGPRINTBARCODE in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_INIT_DIALOG event handler for ID_DLGPRINTBARCODE in dlgPrintBarCode.
}




/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_NPRESET
 */

void dlgPrintBarCode::OnBtCbNpresetClick ( wxCommandEvent& event ) {
	char descricao[64];
	int CB_NC,CB_NEH,CB_NEV,CB_TIPO,padrao;
	double CB_MH,CB_MV,CB_DC,CB_DL,CB_LCB,CB_ACB,CB_AT;
	wxString wxdesc;
	wxTextEntryDialog dialog ( this,___ ( "Digite um nome:" ),___ ( "Inserir nova predefinição" ),_ ( "" ),wxOK|wxCANCEL );
	if ( dialog.ShowModal() == wxID_OK ) {
			strcpy ( descricao,dialog.GetValue().To8BitData().data() );
			CB_LCB=40,CB_ACB=10,CB_AT=3;
			CB_MH=17.225,CB_MV=14.35,CB_DC=47.5,CB_DL=12.7,CB_NC=1,CB_NEH=4,CB_NEV=20,CB_TIPO=CODE_UPC_A,padrao=1;
			lstetiquetainfo.novo ( descricao,CB_LCB,CB_ACB,CB_AT,CB_MH,CB_MV,CB_DC,CB_DL,CB_NC,CB_NEH,CB_NEV,CB_TIPO,padrao );
			lstetiquetainfo.etiquetapadrao=lstetiquetainfo.ult;

			if ( lstetiquetainfo.etiquetapadrao ) {
					int index;
					wxChoice *cb= ( wxChoice* ) this->FindWindowById ( ID_CB_CB_PRESET,this );
					cb->Append ( ___ ( lstetiquetainfo.etiquetapadrao->descricao ) );
					index=cb->FindString ( ___ ( lstetiquetainfo.etiquetapadrao->descricao ) );
					if ( index>=0 ) {
							cb->SetSelection ( index );
							updatecontrols();
							lstetiquetainfo.savetofile ( FN_ETIQUETAS );
						}
				}
		}

////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_NPRESET in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_NPRESET in dlgPrintBarCode.
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_DELPRESET
 */

void dlgPrintBarCode::OnBtCbDelpresetClick ( wxCommandEvent& event ) {
	if ( lstetiquetainfo.quant>1 ) {
			wxMessageDialog dialog ( NULL,___ ( "Tem certeza que deseja excluir a predefinição atual, \nisto não pode ser desfeito!!!" ),
			                         ___ ( "Confirmar exclusão" ),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION );
			if ( dialog.ShowModal() ==wxID_YES ) {
			lstetiquetainfo.apaga ( lstetiquetainfo.etiquetapadrao );
			lstetiquetainfo.etiquetapadrao=lstetiquetainfo.atual;
			wxChoice *cb= ( wxChoice* ) this->FindWindowById ( ID_CB_CB_PRESET,this );
			int GetSelection=cb->GetSelection();
			cb->Delete(GetSelection);
			if(GetSelection>0)
				cb->SetSelection(GetSelection-1);
			else
				cb->SetSelection(0);
				updatecontrols();
			lstetiquetainfo.savetofile ( FN_ETIQUETAS );
			}
		} else
		wxMessageBox ( _( "Ao menos uma predefinição deve existir" ) );

////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_DELPRESET in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_DELPRESET in dlgPrintBarCode.
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CB_CB_PRESET
 */

void dlgPrintBarCode::OnCbCbPresetSelected ( wxCommandEvent& event ) {
	wxChoice *cb= ( wxChoice* ) this->FindWindowById ( ID_CB_CB_PRESET,this );
	lstetiquetainfo.etiquetapadrao=lstetiquetainfo.find_by_descricao ( cb->GetString ( cb->GetSelection() ).To8BitData().data() );
	updatecontrols();
	lstetiquetainfo.savetofile ( FN_ETIQUETAS );
////@begin wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CB_CB_PRESET in dlgPrintBarCode.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CB_CB_PRESET in dlgPrintBarCode.
}


/*
 * Get bitmap resources
 */

wxBitmap dlgPrintBarCode::GetBitmapResource( const wxString& name )
{
	 wxUnusedVar(name);
    if (name == _T("images/DataContainer_NewRecordHS.png"))
    {
        wxBitmap bitmap(_T("images/DataContainer_NewRecordHS.png"), wxBITMAP_TYPE_PNG);
        return bitmap;
    }
    else if (name == _T("images/DeleteHS.png"))
    {
        wxBitmap bitmap(_T("images/DeleteHS.png"), wxBITMAP_TYPE_PNG);
        return bitmap;
    }
    return wxNullBitmap;
    // Bitmap retrieval
////@begin dlgPrintBarCode bitmap retrieval
    wxUnusedVar(name);
    if (name == _T("images/DataContainer_NewRecordHS.png"))
    {
        wxBitmap bitmap(_T("images/DataContainer_NewRecordHS.png"), wxBITMAP_TYPE_PNG);
        return bitmap;
    }
    else if (name == _T("images/DeleteHS.png"))
    {
        wxBitmap bitmap(_T("images/DeleteHS.png"), wxBITMAP_TYPE_PNG);
        return bitmap;
    }
    return wxNullBitmap;
////@end dlgPrintBarCode bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon dlgPrintBarCode::GetIconResource( const wxString& name )
{
	return wxNullIcon;
    // Icon retrieval
////@begin dlgPrintBarCode icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end dlgPrintBarCode icon retrieval
}
