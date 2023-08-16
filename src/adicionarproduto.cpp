/////////////////////////////////////////////////////////////////////////////
// Name:        adicionarproduto.cpp
// Purpose:
// Author:
// Modified by:
// Created:     18/05/2012 13:53:25
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
#include "wx/imaglist.h"
////@end includes
#include "vilavilela.h"
#include "adicionarproduto.h"
#ifndef WIN32
#include "kernel.h"
#endif
////@begin XPM images
////@end XPM images

#ifdef WIN32
#define INDEX_COLUMN 1
#else
#define INDEX_COLUMN 2
#endif
/*
 * Adicionarproduto type definition
 */

IMPLEMENT_DYNAMIC_CLASS(Adicionarproduto, wxDialog)


/*
 * Adicionarproduto event table definition
 */

BEGIN_EVENT_TABLE(Adicionarproduto, wxDialog)
	////@begin Adicionarproduto event table entries    

    EVT_UPDATE_UI( ID_INSPROD_QUANT, Adicionarproduto::OnInsprodQuantUpdate )

    EVT_BUTTON( wxID_APPLY, Adicionarproduto::OnApplyClick )

	////@end Adicionarproduto event table entries
#ifndef WIN32
	EVT_LIST_KEY_DOWN( ID_INSPROD_LIST, Adicionarproduto::OnInsprodListKeyDown )
#endif
	EVT_TIMER(1001,Adicionarproduto::OnTimer)
END_EVENT_TABLE()


/*
 * Adicionarproduto constructors
 */

Adicionarproduto::Adicionarproduto() :baltimer(this,1001) {
	Init();

}

void set_lstctrl_column(wxListCtrl* lstctrl,const char *text,int indcolumn,int id,LstCellInfo *lstcellinfo,int reffield) {
	static wxListItem itemCol;
	static wxString tmpstr;
	itemCol.Clear();
	tmpstr=wxString::FromUTF8(text);
	itemCol.SetText(tmpstr);
	itemCol.SetColumn(indcolumn);
	itemCol.SetId(id);
	lstctrl->SetItem(itemCol);
	if (lstcellinfo) {
		lstcellinfo->novo(indcolumn,reffield,tmpstr);
	}
}

void set_lstctrl_column(wxListCtrl* lstctrl,wxString &text,int indcolumn,int id,LstCellInfo *lstcellinfo,int reffield) {
	static wxListItem itemCol;
	itemCol.Clear();
	itemCol.SetText(text);
	itemCol.SetColumn(indcolumn);
	itemCol.SetId(id);
	lstctrl->SetItem(itemCol);
	if (lstcellinfo) {
		lstcellinfo->novo(indcolumn,reffield,text);
	}
}

void insert_lstctrl_item(wxListCtrl* lstctrl,const char *text,int id,LstCellInfo **lstcellinfo,int reffield) {
	static wxString tmpstr;
	tmpstr=wxString::FromUTF8(text);
	lstctrl->InsertItem(id,tmpstr);
	if (lstcellinfo) {
		*lstcellinfo=new LstCellInfo();
		lstctrl->SetItemData(id, (long) *lstcellinfo);
		if (*lstcellinfo!=NULL)
			(*lstcellinfo)->novo(0,reffield,tmpstr);
	}
}

void insert_lstctrl_item(wxListCtrl* lstctrl,wxString &text,int id,LstCellInfo **lstcellinfo,int reffield) {
	lstctrl->InsertItem(id,text);
	if (lstcellinfo) {
		*lstcellinfo=new LstCellInfo();
		lstctrl->SetItemData(id, (long) *lstcellinfo);
		if (*lstcellinfo!=NULL)
			(*lstcellinfo)->novo(0,reffield,text);
	}
}

Adicionarproduto::Adicionarproduto(wxWindow* parent, wxWindowID id,
                                   const wxString& caption, const wxPoint& pos,
                                   const wxSize& size, long style) :baltimer(this,1001) {
	Init();
	Create(parent, id, caption, pos, size, style);
	wxListCtrl* lstprod= (wxListCtrl*) this->FindWindowById(ID_INSPROD_LIST,this);
	add_lstctrl_column(lstprod,___("Código"),0,90);
	add_lstctrl_column(lstprod,___("Nome"),1,140);
	add_lstctrl_column(lstprod,___("Descrição"),2,110);
	add_lstctrl_column(lstprod,___("Unidade"),3,80);
	add_lstctrl_column(lstprod,___("Preço"),4,60);
	add_lstctrl_column(lstprod,___("Estoque"),5,60);

	wxString tmpstr;
	
	LstCellInfo *lstcellinfo;
	double quantestoque;
	wxString str;//produto_entrada AS pe, AND pe.idproduto=prod.idproduto
	Palavra query;
	sql_ResultSet  *res;
	query="SELECT prod.idproduto,prod.barcode,prod.nome,prod.descricao,unid.abrev,unid.idunidade,prod.val_unit_venda \
							FROM unidade AS unid,produtos AS prod \
							WHERE unid.idunidade=prod.idunidade \
							ORDER BY prod.nome";
	if ((res=vilavielaframe->_execquerywithresult(query)) !=0) {
		int i=0;
		while (vilavielaframe->_nextrow(res)) {
			insert_lstctrl_item(lstprod,vilavielaframe->_getstringSQL(res,2).c_str(),i,&lstcellinfo,vilavielaframe->_getint(res,1));
			set_lstctrl_column(lstprod,vilavielaframe->_getstringSQL(res,3).c_str(),1,i,lstcellinfo,vilavielaframe->_getint(res,1));
			set_lstctrl_column(lstprod,vilavielaframe->_getstringSQL(res,4).c_str(),2,i,lstcellinfo,vilavielaframe->_getint(res,1));
			set_lstctrl_column(lstprod,vilavielaframe->_getstringSQL(res,5).c_str(),3,i,lstcellinfo,vilavielaframe->_getint(res,6));
			set_lstctrl_column(lstprod,vilavielaframe->_getstringSQL(res,7).c_str(),4,i,NULL,-1);
			quantestoque=vilavielaframe->_retorna_estoque(vilavielaframe->_getint(res,1));

			wxListCtrl* lstprodvenda= (wxListCtrl*) vilavielaframe->FindWindowById(ID_VENDAS_INSPROD_GRID,vilavielaframe);
			long item = -1;
			wxString ltext;
			for (;;) {
				item = lstprodvenda->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
				if (item == -1)
					break;
				ltext=get_lstctrl_column_text(lstprodvenda,item,1);				
				if (vilavielaframe->_getstring(res,2) == ltext) {
					quantestoque-=atof(get_lstctrl_column_text(lstprodvenda,item,5).ToAscii().data());				
				}
			}

			lstprod->SetItemBackgroundColour(i,quantestoque<=0?wxColour(255,0,0):wxColour(255,255,255));

			str.Printf(_("%.3f"),quantestoque);
			set_lstctrl_column(lstprod,str.To8BitData().data(),5,i++,NULL,-1);

		}
		lstprod->SetColumnWidth(0, 100);
		lstprod->SetColumnWidth(1, 100);
		lstprod->SetAutoLayout(true);
		lstprod->Update();
		lstprod->Show();
		lstprod->GetParent()->Layout();
		vilavielaframe->_deleteresult(&res);
	}
#ifndef WIN32
	vilavielaframe->hCom=0;
	if ((vilavielaframe->hCom = PortaConfig(PORTACOM5, 2400, &vilavielaframe->oldtermio)) <= 0)
		vilavielaframe->hCom=0;
#endif
}


/*
 * Adicionarproduto creator
 */

bool Adicionarproduto::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style) {
////@begin Adicionarproduto creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end Adicionarproduto creation
	wxListCtrl* lstprod= (wxListCtrl*) this->FindWindowById(ID_INSPROD_LIST,this);
//lstprod->Connect(ID_INSPROD_LIST, wxEVT_CHAR, wxKeyEventHandler(Adicionarproduto::onchar), NULL, this);
	return true;
}


/*
 * Adicionarproduto destructor
 */

Adicionarproduto::~Adicionarproduto() {
	baltimer.Stop();
#ifndef WIN32
	PortaUnconfig(vilavielaframe->hCom, &vilavielaframe->oldtermio);
#endif
////@begin Adicionarproduto destruction
////@end Adicionarproduto destruction
}


/*
 * Member initialisation
 */

void Adicionarproduto::Init() {
////@begin Adicionarproduto member initialisation
////@end Adicionarproduto member initialisation
}


/*
 * Control creation for Adicionarproduto
 */


void Adicionarproduto::CreateControls() {
////@begin Adicionarproduto content construction
    Adicionarproduto* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Lista de Produtos"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 1, wxGROW|wxALL, 5);

    wxListCtrl* itemListCtrl4 = new wxListCtrl( itemDialog1, ID_INSPROD_LIST, wxDefaultPosition, wxSize(400, -1), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES );
    itemStaticBoxSizer3->Add(itemListCtrl4, 1, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer2->Add(itemFlexGridSizer5, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Quantidade"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl7 = new wxTextCtrl( itemDialog1, ID_INSPROD_QUANT, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer5->Add(itemTextCtrl7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer8 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_OK, _("&Inserir e fechar"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton9->SetDefault();
    itemStdDialogButtonSizer8->AddButton(itemButton9);

    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton10);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_APPLY, _("&Inserir"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton11);

    itemStdDialogButtonSizer8->Realize();

    // Connect events and objects
    itemListCtrl4->Connect(ID_INSPROD_LIST, wxEVT_CHAR, wxKeyEventHandler(Adicionarproduto::OnChar), NULL, this);
////@end Adicionarproduto content construction
}


bool Adicionarproduto::ShowToolTips() {
	return true;
}


void Adicionarproduto::OnApplyClick(wxCommandEvent& event) {
	if (vilavielaframe->_insprodvenda(this)) {
		((wxTextCtrl*) this->FindWindowById(ID_INSPROD_QUANT,this))->Clear();
		wxListCtrl* lstprod= (wxListCtrl*) this->FindWindowById(ID_INSPROD_LIST,this);
		lstprod->SetFocus();
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY in Adicionarproduto.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY in Adicionarproduto.
}
static wxString st_tmpstr=wxEmptyString;

void Adicionarproduto::OnTimer(wxTimerEvent &event) {
	wxListCtrl* lstprod= (wxListCtrl*) this->FindWindowById(ID_INSPROD_LIST,this);
	long item = -1;
	int peso;
	static int tinterv=0;
	if (tinterv==LIST_CTRL_FIND_SECONDS) {
		tinterv=0;
		st_tmpstr=wxEmptyString;
	}
	tinterv++;
	item = lstprod->GetNextItem(item,	wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
	if (item != -1) {
		wxString tmpstr;
		tmpstr=vilavielaframe->listctrl_get_colomn_text(lstprod,item,3);
		if (tmpstr==_("kg") ||tmpstr==_("Kg") ||tmpstr==_("KG")) {
			static char buf[20]= "",preco[8]="",total[20]="",*ptrbuf;//printf("ini bal\n");
			//int retpesovr=Bematech_FI_InfoBalanca(PORTACOM5,1,buf,preco,total);printf("retpesovr = %d\n",retpesovr);
			//retpesovr>0
			if (retpeso(buf) && (* (ptrbuf=buf+1) !='I'&&*ptrbuf!='N'&&*ptrbuf!='S')) {
				ptrbuf[strlen(ptrbuf)-1]=0;
				peso=atoi(ptrbuf);
				tmpstr.Printf(_("%.3f"),peso/1000.0);      //=wxString::FromAscii(buf);
				((wxTextCtrl*) this->FindWindowById(ID_INSPROD_QUANT,this))->SetValue(tmpstr);
			}
		}
	}
}

void Adicionarproduto::OnInsprodQuantUpdate(wxUpdateUIEvent& event) {

////@begin wxEVT_UPDATE_UI event handler for ID_INSPROD_QUANT in Adicionarproduto.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_INSPROD_QUANT in Adicionarproduto.
}

int  Adicionarproduto::_ShowModal(int idfocus) {
	wxWindow* lstprod=  this->FindWindowById(idfocus,this);
	lstprod->SetFocus();
	return ShowModal();
}

bool _lstctrl_find(wxListCtrl* lstctrl,const wxString &str ,int column) {
	if (str.empty())
		return false;
	long item = -1;
	wxString ltext,str_upper,line_upper;
	for (;;) {
		item = lstctrl->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
		if (item == -1)
			break;
		ltext=get_lstctrl_column_text(lstctrl,item,column-1);
		str_upper = str.Upper();
		line_upper = ltext.Upper();
		if (line_upper.find(str_upper) == 0) {
			lstctrl->SetItemState(item,wxLIST_STATE_SELECTED|wxLIST_STATE_FOCUSED,wxLIST_STATE_SELECTED|wxLIST_STATE_FOCUSED);
			lstctrl->EnsureVisible(item);
			lstctrl->Update();
			return true;
		}
	}
	return false;
}

void Adicionarproduto::OnInsprodListKeyDown(wxListEvent& event) {
	int ccode=event.GetKeyCode();
	static char buf[32];
	static int index=-1,pstx_etx=0;
	switch (ccode) {
	case WXK_CONTROL://possible STX ou ETX
		pstx_etx=1;
		break;
	case 66://more possible STX->B
		if (pstx_etx==1) {
			index=0;
			pstx_etx=0;
			break;
		}
	case 67://more possible ETX->C
		if (pstx_etx==1&&index>0) {   //ETX
			buf[index]=0;
			Palavra query;
			sql_ResultSet  *res;
			query="SELECT nome	FROM produtos WHERE barcode='";
			query.append(buf);
			query.append("'");
			if ((res=vilavielaframe->_execquerywithresult(query)) !=0) {
				if (vilavielaframe->_nextrow(res)) {
					wxListCtrl* lstprod= (wxListCtrl*) this->FindWindowById(ID_INSPROD_LIST,this);
					if (_lstctrl_find(lstprod,vilavielaframe->_getstring(res,1),2)) {
						this->FindWindowById(ID_INSPROD_QUANT,this)->SetFocus();
					}
				}
				vilavielaframe->_deleteresult(&res);
			}
			index=-1;
			pstx_etx=0;
			break;
		}

	default:
		pstx_etx=0;
		if (index!=-1) {
			buf[index++]=ccode;
		}
		else if(ccode<256){
			wxListCtrl* lstprod= (wxListCtrl*) this->FindWindowById(ID_INSPROD_LIST,this);
#ifdef WIN32
			st_tmpstr=st_tmpstr+wxString::FromAscii((char)ccode);
#else
			st_tmpstr.Append((wchar_t)ccode);			
#endif
			
			_lstctrl_find(lstprod,st_tmpstr,2);
		}
  else{

  }
	}
 event.Skip();

}


wxBitmap Adicionarproduto::GetBitmapResource(const wxString& name) {
// Bitmap retrieval
////@begin Adicionarproduto bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end Adicionarproduto bitmap retrieval
}


wxIcon Adicionarproduto::GetIconResource(const wxString& name) {
// Icon retrieval
////@begin Adicionarproduto icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end Adicionarproduto icon retrieval
}




/*
 * wxEVT_CHAR event handler for ID_INSPROD_LIST
 */

void Adicionarproduto::OnChar( wxKeyEvent& event )
{
#ifdef WIN32
	wxListEvent levt;
	levt.m_code=event.GetKeyCode();
	OnInsprodListKeyDown(levt);
#endif
////@begin wxEVT_CHAR event handler for ID_INSPROD_LIST in Adicionarproduto.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_CHAR event handler for ID_INSPROD_LIST in Adicionarproduto. 
}

