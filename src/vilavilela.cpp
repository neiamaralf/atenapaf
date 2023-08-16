/////////////////////////////////////////////////////////////////////////////
// Name:        vilavilela.cpp
// Purpose:
// Author:
// Modified by:
// Created:     08/05/2012 20:34:13
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#define ASSERT_PRINTER_MODEL() \
	if(MODELO_IMPRESSORA==Bematech_MP_20_FI_II||MODELO_IMPRESSORA==Bematech_MP_40_FI_II||MODELO_IMPRESSORA==Sweda_Matricial){\
	wxMessageBox(___("Função não suportada pelo modelo de ECF utilizado"));\
	return;\
	}

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
#include "relatorios.h"
#include "vilavilela.h"
#include "inserirproduto.h"
#include "adicionarproduto.h"

#include "selecioneintervalodecrz.h"
#include "selecioneintervalodedata.h"
#include "selec_cliente.h"
#include "movimentoporecf.h"
#include "impressora_fiscal.h"
#include "dlgpagamento.h"
#include "balanco.h"
#include "dbhost_adress.h"

#ifndef WIN32
#include "kernel.h"
#endif
#include "siteupdater.h"
#include "wx/filedlg.h"

HANDLE VilaVilela::hCom=0;

////@begin XPM images
////@end XPM images


/*
 * VilaVilela type definition
 */

IMPLEMENT_CLASS(VilaVilela, wxFrame)


/*
 * VilaVilela event table definition
 */
char FLAG_LEITURA[2][4]={"c","s"};
#define FLAG_LEITURA_C 0
#define FLAG_LEITURA_S 1
BEGIN_EVENT_TABLE(VilaVilela, wxFrame)
	EVT_MENU_RANGE(ID_FIRSTPOPUP,ID_FIRSTPOPUP+100, VilaVilela::OnPopUpSearch)
	EVT_TIMER(1012,VilaVilela::OnTimer)
	////@begin VilaVilela event table entries
    EVT_SIZE( VilaVilela::OnSize )
    EVT_KEY_DOWN( VilaVilela::OnKeyDown )

    EVT_MENU( ID_MENUI_CopiaSeg, VilaVilela::OnMENUICopiaSegClick )

    EVT_MENU( ID_MENUI_RESTAURABKUP, VilaVilela::OnMenuiRestaurabkupClick )

    EVT_MENU( ID_MENUITEMLOGINASADMIN, VilaVilela::OnMenuitemloginasadminClick )

    EVT_MENU( ID_MENU_UPDATESITE, VilaVilela::OnMenuUpdatesiteClick )

    EVT_MENU( ID_MNDBHOST, VilaVilela::OnMndbhostClick )

    EVT_MENU( ID_MENU_REdX, VilaVilela::OnMENUREdXClick )

    EVT_MENU( ID_MN_LMFC_ECF_IDATA, VilaVilela::OnMnLmfcEcfIdataClick )

    EVT_MENU( ID_MN_LMFC_ECF_ICRZ, VilaVilela::OnMnLmfcEcfIcrzClick )

    EVT_MENU( ID_MN_LMFC_ARQ_IDATA, VilaVilela::OnMnLmfcArqIdataClick )

    EVT_MENU( ID_MN_LMFC_ARQ_ICRZ, VilaVilela::OnMnLmfcArqIcrzClick )

    EVT_MENU( ID_MN_LMFC_COTEP1704_IDATA, VilaVilela::OnMnLmfcCotep1704IdataClick )

    EVT_MENU( ID_MN_LMFC_COTEP1704_ICRZ, VilaVilela::OnMnLmfcCotep1704IcrzClick )

    EVT_MENU( ID_MN_LMFS_ECF_IDATA, VilaVilela::OnMnLmfsEcfIdataClick )

    EVT_MENU( ID_MN_LMFS_ECF_ICRZ, VilaVilela::OnMnLmfsEcfIcrzClick )

    EVT_MENU( ID_MN_LMFS_ARQ_IDATA, VilaVilela::OnMnLmfsArqIdataClick )

    EVT_MENU( ID_MN_LMFS_ARQ_ICRZ, VilaVilela::OnMnLmfsArqIcrzClick )

    EVT_MENU( ID_MNESPELHOMFD_DATA, VilaVilela::OnMnespelhomfdDataClick )

    EVT_MENU( ID_MNESPELHOMFD_COO, VilaVilela::OnMnespelhomfdCooClick )

    EVT_MENU( ID_MNArqMFD_DATA, VilaVilela::OnMNArqMFDDATAClick )

    EVT_MENU( ID_MNArqMFD_COO, VilaVilela::OnMNArqMFDCOOClick )

    EVT_MENU( ID_MNTabProd, VilaVilela::OnMNTabProdClick )

    EVT_MENU( ID_MI_ESTOQUE_TOTAL, VilaVilela::OnMiEstoqueTotalClick )

    EVT_MENU( ID_MI_ESTOQUE_PARCIAL, VilaVilela::OnMiEstoqueParcialClick )

    EVT_MENU( ID_MM_MOVECF, VilaVilela::OnMmMovecfClick )

    EVT_MENU( ID_MENURECIBO, VilaVilela::OnMenureciboClick )

    EVT_MENU( ID_MENUITEM, VilaVilela::OnMenuitemClick )

    EVT_MENU( ID_MENUBALANCOM, VilaVilela::OnMenubalancomClick )

    EVT_MENU( ID_MENU_RedZ, VilaVilela::OnMENURedZClick )

    EVT_MENU( ID_MENU_RedXArq, VilaVilela::OnMENURedXArqClick )

    EVT_MENU( ID_MENUI_RegAliq, VilaVilela::OnMENUIRegAliqClick )

    EVT_MENU( ID_MN_CANCELAULTCUPOM, VilaVilela::OnMnCancelaultcupomClick )

    EVT_MENU( ID_MN_CANCELAITEMANT, VilaVilela::OnMnCancelaitemantClick )

    EVT_MENU( ID_MN_CANCELAITEM, VilaVilela::OnMnCancelaitemClick )

    EVT_MENU( ID_TOOLFIRSTREC, VilaVilela::OnToolfirstrecClick )

    EVT_MENU( ID_TOOLPREVREC, VilaVilela::OnToolprevrecClick )

    EVT_MENU( ID_TOOLNEXTREC, VilaVilela::OnToolnextrecClick )

    EVT_MENU( ID_TOOLLASTREC, VilaVilela::OnToollastrecClick )

    EVT_MENU( ID_TOOLInsert, VilaVilela::OnTOOLInsertClick )

    EVT_MENU( ID_TOOLEdit, VilaVilela::OnTOOLEditClick )

    EVT_MENU( ID_TOOLCancel, VilaVilela::OnTOOLCancelClick )

    EVT_MENU( ID_MN_DESC_PERCENT, VilaVilela::OnMnDescPercentClick )

    EVT_MENU( ID_MN_INS_PAGTO, VilaVilela::OnMnInsPagtoClick )

    EVT_MENU( ID_TOOLDelete, VilaVilela::OnTOOLDeleteClick )

    EVT_MENU( ID_MN_PESQPROD, VilaVilela::OnVendasBtinsprodClick )

    EVT_TEXT_ENTER( ID_SEARCHCTRL, VilaVilela::OnSearchctrlEnter )

    EVT_TOGGLEBUTTON( ID_TOOLFILTER, VilaVilela::OnToolfilterClick )

    EVT_MENU( ID_MN_PESQPROD, VilaVilela::OnMnPesqprodClick )

    EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, VilaVilela::OnNotebookPageChanged )
    EVT_NOTEBOOK_PAGE_CHANGING( ID_NOTEBOOK, VilaVilela::OnNotebookPageChanging )

    EVT_UPDATE_UI( ID_PGVENDAS, VilaVilela::OnPgvendasUpdate )

    EVT_LIST_DELETE_ITEM( ID_VENDAS_INSPROD_GRID, VilaVilela::OnVendasInsprodGridDeleteItem )
    EVT_LIST_DELETE_ALL_ITEMS( ID_VENDAS_INSPROD_GRID, VilaVilela::OnVendasInsprodGridDeleteAllItems )
    EVT_LIST_KEY_DOWN( ID_VENDAS_INSPROD_GRID, VilaVilela::OnVendasInsprodGridKeyDown )
    EVT_UPDATE_UI( ID_VENDAS_INSPROD_GRID, VilaVilela::OnVendasInsprodGridUpdate )

    EVT_TEXT( ID_VENDAS_DESCONTO, VilaVilela::OnVendasDescontoTextUpdated )

    EVT_UPDATE_UI( ID_VENDAS_TOTAL_GERAL, VilaVilela::OnVendasTotalGeralUpdate )

    EVT_UPDATE_UI( ID_VENDAS_TROCO, VilaVilela::OnVendasTrocoUpdate )

    EVT_LIST_ITEM_SELECTED( ID_VENDAS_GRID, VilaVilela::OnGridSelected )

    EVT_BUTTON( ID_COMPRAS_BT_INS_PROD, VilaVilela::OnComprasBtInsProdClick )

    EVT_LIST_DELETE_ITEM( ID_COMPRAS_PROD_GRID, VilaVilela::OnComprasProdGridDeleteItem )
    EVT_LIST_DELETE_ALL_ITEMS( ID_COMPRAS_PROD_GRID, VilaVilela::OnComprasProdGridDeleteAllItems )
    EVT_LIST_KEY_DOWN( ID_COMPRAS_PROD_GRID, VilaVilela::OnComprasProdGridKeyDown )
    EVT_UPDATE_UI( ID_COMPRAS_PROD_GRID, VilaVilela::OnComprasProdGridUpdate )

    EVT_LIST_ITEM_SELECTED( ID_COMPRAS_GRID, VilaVilela::OnGridSelected )

    EVT_LIST_ITEM_SELECTED( ID_UNIDADE_GRID, VilaVilela::OnGridSelected )

    EVT_BUTTON( ID_CLIENT_INS_FONE, VilaVilela::OnClientInsFoneClick )

    EVT_BUTTON( ID_CLIENT_DEL_FONE, VilaVilela::OnClientDelFoneClick )

    EVT_BUTTON( ID_CLIENT_DELALL_FONE, VilaVilela::OnClientDelallFoneClick )

    EVT_LIST_ITEM_SELECTED( ID_CLIENT_GRID, VilaVilela::OnGridSelected )

    EVT_BUTTON( ID_FORNEC_INS_FONE, VilaVilela::OnFornecInsFoneClick )

    EVT_BUTTON( ID_FORNEC_DEL_FONE, VilaVilela::OnFornecDelFoneClick )

    EVT_BUTTON( ID_FORNEC_DELALL_FONE, VilaVilela::OnFornecDelallFoneClick )

    EVT_LIST_ITEM_SELECTED( ID_FORNEC_GRID, VilaVilela::OnGridSelected )

    EVT_BUTTON( ID_BTPROD_IMG, VilaVilela::OnBtprodImgClick )

    EVT_BUTTON( ID_PROD_DELIMAGE, VilaVilela::OnProdDelimageClick )

    EVT_LIST_ITEM_SELECTED( ID_PROD_GRID, VilaVilela::OnGridSelected )

    EVT_LIST_ITEM_SELECTED( ID_FORMAPGTO_GRID, VilaVilela::OnGridSelected )

    EVT_LIST_ITEM_SELECTED( ID_CATEGORIA_GRID, VilaVilela::OnGridSelected )

    EVT_LIST_ITEM_SELECTED( ID_ALIQUOTAS_GRID, VilaVilela::OnGridSelected )

    EVT_UPDATE_UI( ID_STATUSBAR, VilaVilela::OnStatusbarUpdate )

	////@end VilaVilela event table entries

END_EVENT_TABLE()


/*
 * VilaVilela constructors
 */


char VilaVilela::main_tables[NUM_TABS][32]= {"fornecedores","cliente","unidade","formapagto","produtos","vendas","compras","fones_cliente","fones_fornec","produto_entrada","saida","categoria","aliquotas","vendapagtos"};
char VilaVilela::main_tablekeys[NUM_TABS][32]= {"idfornecedor","idcliente","idunidade","idformapagto","idproduto","idvenda","idcompra","idfones_cliente","idfones_fornec","idproduto_entrada","idsaida","idcategoria","idaliquota","idvendapagtos"};
char VilaVilela::main_tablesortfield[NUM_TABS][32]= {"nome","nome","descricao","descricao","nome","data","data","idfones_cliente","idfones_fornec","idproduto_entrada","idsaida","descricao","abrev","idvendapagtos"};

#define NUM_NOTEBOOK_TABS 9
int _pageIds[NUM_NOTEBOOK_TABS]={ID_PGVENDAS,ID_PGCOMPRAS,ID_PGUNIDADE,ID_PGCLIENTES,ID_PGFORNEC,ID_PGPRODUTOS,ID_PGFORMAPAGTO,ID_PGCATEGORIA,ID_PGALIQUOTAS};


using namespace RELATORIOS::assinatura;
using namespace RELATORIOS::atoCOTEP1704;
using namespace RELATORIOS::utils;
using namespace RELATORIOS::requisitoXXV;
using namespace RELATORIOS::requisitoXXII;
using namespace RELATORIOS::requisitoIX;
using namespace IMPRESSORA_FISCAL;

void VilaVilela::OnPopUpSearch(wxCommandEvent& event) {
	wxMenu* mn= (wxMenu*) event.GetEventObject();
	wxMenuItem *mnitem= mn->FindItem(event.GetId());
	if (!mnitem)
		return;
	FieldInfo *fi;
	menuitemdado *refdata= (menuitemdado*) mnitem->GetRefData();
	if (!refdata)
		return;
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL)
		seachfieldinfo[tb->indtablename]=*refdata;
	fi=refdata->searchfield;
	if (!fi)
		return;
	if (fi->field_type==__DB_FIELD_TYPE_DATE|| (refdata->fi&& (refdata->fi->field_type==__DB_FIELD_TYPE_DATE))) {
		(this->FindWindowById(ID_SEARCHDATE1,this))->Enable();
		(this->FindWindowById(ID_SEARCHDATE2,this))->Enable();
		(this->FindWindowById(ID_SEARCHCTRL,this))->Disable();
		(this->FindWindowById(ID_SEARCHDATE1,this))->SetFocus();
	}
	else	{
		(this->FindWindowById(ID_SEARCHDATE1,this))->Disable();
		(this->FindWindowById(ID_SEARCHDATE2,this))->Disable();
		(this->FindWindowById(ID_SEARCHCTRL,this))->Enable();
		(this->FindWindowById(ID_SEARCHCTRL,this))->SetFocus();
	}
}




VilaVilela::VilaVilela() : timer(this, 1012) {
	Init();
}


VilaVilela::VilaVilela(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style) : timer(this, 1012) {
	admin=false;
	vilavielaframe=this;
	db_mode=__DB_MODE_READ;
	setlocale(LC_CTYPE, "pt_BR.ISO-8859-1");
	ERR_load_crypto_strings();
	if (!wxDirExists(_("./_imagens"))) {
		wxMkdir(_("./_imagens"));
	}
	wxString tmpstr;
	g_printData =  new wxPrintData ;
	venda_total=0;
		conexao_de_seguranca=false;
	pode_cancelar_cupom=false;

	strcpy(db_host,"127.0.0.1");
	load_config(false);
	//wxMessageBox(_("stop"));
//restaura_arquivo_auxiliar("arquivo_auxiliare.txt");
	MODELO_IMPRESSORA=Bematech_MP_20_FI_II;//Bematech_MP_2000_TH_FI;//Bematech_MP_2100_TH_FI;
#ifdef DEVELOPING
	//char *bd;
	//int sz=descriptografa_arquivo ( "arquivo_auxiliare.txt",&bd );
	//FILE *dest=fopen ( "descriptold.txt","w+b" );
	//fwrite ( bd,1,sz,dest );
	//delete []bd;
	//fclose ( dest );
#endif
	_createtablesinfos();
	if (_open_db(&glb_stmt)) {
		_create_tables_and_db();
	}
	_update_db_cache();
	//verificaestadoimpressora();
	timer.Start(3000);
	gravalistaexecutaveis();
	Init();
	Create(parent, id, caption, pos, size, style);


	
	
	wxNotebook *ntbk=((wxNotebook*)wxWindow::FindWindowById(ID_NOTEBOOK,this));
	TableInfo *tb;
	for (tb=lsttableinfo.prm;tb;tb=tb->prx){
		_set_dbmode(tb->pageid,__DB_MODE_READ);
		if(tb->pageid!=-1){
		 tb->page=ntbk->GetPage(tb->pageindex);
			tb->label=ntbk->GetPageText(tb->pageindex);
			tb->bmp=ntbk->GetPageImage(tb->pageindex);
		}
	}
	wxListCtrl* lstprodcompra= (wxListCtrl*) this->FindWindowById(ID_COMPRAS_PROD_GRID,this);
	add_lstctrl_column(lstprodcompra,_("Nome"),0,140);
	add_lstctrl_column(lstprodcompra,___("Descrição"),1,110);
	add_lstctrl_column(lstprodcompra,_("Unidade"),2,90);
	add_lstctrl_column(lstprodcompra,_("Quant"),3,80);
	add_lstctrl_column(lstprodcompra,_("Val. unit. venda"),4,140);
	add_lstctrl_column(lstprodcompra,_("Val. unit. compra"),5,140);
	add_lstctrl_column(lstprodcompra,_("Subtotal"),6,100);
	lstprodcompra->Layout();
	lstprodcompra->Update();

	wxListCtrl* lstprodvenda= (wxListCtrl*) this->FindWindowById(ID_VENDAS_INSPROD_GRID,this);
	add_lstctrl_column(lstprodvenda,_("Item"),0,60);
	add_lstctrl_column(lstprodvenda,___("Código"),1,80);
	add_lstctrl_column(lstprodvenda,_("Nome"),2,140);
	add_lstctrl_column(lstprodvenda,___("Descrição"),3,110);
	add_lstctrl_column(lstprodvenda,_("Unidade"),4,90);
	add_lstctrl_column(lstprodvenda,_("Quant"),5,80);
	add_lstctrl_column(lstprodvenda,___("Val. unitário"),6,140);
	add_lstctrl_column(lstprodvenda,_("Subtotal"),7,100);

	wxListCtrl* lstpagtos=(wxListCtrl*)this->FindWindowById(ID_VENDAS_VALREC,this); 
	add_lstctrl_column ( lstpagtos,___ ("Tipo"),0,70);
	add_lstctrl_column ( lstpagtos,___ ("Valor"),1,70);
	_db_update(_get_pageid());

	_enable_disable_notebook_abas(false);
}

bool VilaVilela::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style) {
	wxIconBundle iconBundle(wxIcon(___("./icons/atenapaf_16x16-4.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_16x16-8.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_16x16-32.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_32x32-4.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_32x32-8.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_32x32-32.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_48x48-8.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_48x48-32.png"), wxBITMAP_TYPE_PNG));
	iconBundle.AddIcon(wxIcon(___("./icons/atenapaf_256x256-32.png"), wxBITMAP_TYPE_PNG));


////@begin VilaVilela creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    SetIcon(GetIconResource(wxT("images/atenapaf.png")));
    Centre();
////@end VilaVilela creation
	SetIcons(iconBundle);
	return true;
}


VilaVilela::~VilaVilela() {
#ifndef DEVELOPING
	if (impressoraligada)
		registro_R02_R03();
#endif
	delete g_printData;
	for (int i=0;i<4;i++)
		_delete_gl_res(i,false);
	_close_db(&glb_stmt);
}



void VilaVilela::show_config_dlg(int CONFIG_ITEM) {
	switch (CONFIG_ITEM) {
	case CONFIG_DBHOST: {
			dbhost_adress *dlg=new dbhost_adress(NULL);
			wxTextCtrl *ip1=(wxTextCtrl*)wxWindow::FindWindowById(ID_IPV4_1,(wxWindow*)dlg);
			ip1->SetValue(wxString::FromAscii(db_host));
			ip1->SetFocus();
			ip1->SetSelection(-1,-1);

			if (dlg->ShowModal()==wxID_OK) {
				sprintf(db_host,"%s",ip1->GetValue().ToAscii().data());
			}
			delete dlg;
		}
		break;
	}
}


void VilaVilela::load_config(bool update) {
	FILE *f=fopen(CONFIG_FNAME,"rb");
	if (f==NULL||update) {
		f=fopen(CONFIG_FNAME,"w+b");
		if (f!=NULL) {
			if (!update)
				show_config_dlg(CONFIG_DBHOST);
			fprintf(f,
			        "db_host\t%s\x0a",db_host);
			fclose(f);
		}
	}
	else {
		char tbuf[32];
		fscanf(f,"%s%s",tbuf,db_host);
		fclose(f);
	}
}

void VilaVilela::Init() { 
//_sign_file("test.xml", "privkeyv.pem", "cacert.pem","dirsicaf")	;
//conecta_receita();
	////@begin VilaVilela member initialisation
    vendassizerv = NULL;
    vendasprodsizer = NULL;
	////@end VilaVilela member initialisation

}

void VilaVilela::CreateControls() {
////@begin VilaVilela content construction
    VilaVilela* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* itemMenu3 = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_MENUI_CopiaSeg, wxGetTranslation(wxString(wxT("C")) + (wxChar) 0x00F3 + wxT("pia de seguran") + (wxChar) 0x00E7 + wxT("a...\tCtrl+S")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/backup.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu3->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_MENUI_RESTAURABKUP, _("Restaurar do backup...\tCtrl+K"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/restore.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu3->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_MENUITEMLOGINASADMIN, _("Login como administrador...\tCtrl+L"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/Login.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu3->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_MENU_UPDATESITE, _("Update site\tCtrl+U"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/update.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu3->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_MNDBHOST, _("IP servidor...\tCtrl+I"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/ipserver.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu3->Append(menuItem);
    }
    menuBar->Append(itemMenu3, _("Ferramentas"));
    wxMenu* itemMenu9 = new wxMenu;
    itemMenu9->Append(ID_MENU_REdX, _("LX\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
    wxMenu* itemMenu11 = new wxMenu;
    wxMenu* itemMenu12 = new wxMenu;
    itemMenu12->Append(ID_MN_LMFC_ECF_IDATA, _("Por Intervalo de Data"), wxEmptyString, wxITEM_NORMAL);
    itemMenu12->Append(ID_MN_LMFC_ECF_ICRZ, _("Por intervalo de CRZ"), wxEmptyString, wxITEM_NORMAL);
    itemMenu11->Append(ID_MN_LMFC_ECF, wxGetTranslation(wxString(wxT("Impress")) + (wxChar) 0x00E3 + wxT("o")), itemMenu12);
    wxMenu* itemMenu15 = new wxMenu;
    itemMenu15->Append(ID_MN_LMFC_ARQ_IDATA, _("Por Intervalo de Data"), wxEmptyString, wxITEM_NORMAL);
    itemMenu15->Append(ID_MN_LMFC_ARQ_ICRZ, _("Por intervalo de CRZ"), wxEmptyString, wxITEM_NORMAL);
    itemMenu11->Append(ID_MN_LMFC_ARQ, _("Espelho"), itemMenu15);
    wxMenu* itemMenu18 = new wxMenu;
    itemMenu18->Append(ID_MN_LMFC_COTEP1704_IDATA, _("Por Intervalo de Data"), wxEmptyString, wxITEM_NORMAL);
    itemMenu18->Append(ID_MN_LMFC_COTEP1704_ICRZ, _("Por intervalo de CRZ"), wxEmptyString, wxITEM_NORMAL);
    itemMenu11->Append(ID_MN_LMFC_COTEP1704, _("Formato COTEPE/ICMS 17/04"), itemMenu18);
    itemMenu9->Append(ID_MN_LMFC, _("LMFC"), itemMenu11);
    wxMenu* itemMenu21 = new wxMenu;
    wxMenu* itemMenu22 = new wxMenu;
    itemMenu22->Append(ID_MN_LMFS_ECF_IDATA, _("Por Intervalo de Data"), wxEmptyString, wxITEM_NORMAL);
    itemMenu22->Append(ID_MN_LMFS_ECF_ICRZ, _("Por intervalo de CRZ"), wxEmptyString, wxITEM_NORMAL);
    itemMenu21->Append(ID_MN_LMFS_ECF, _("ECF"), itemMenu22);
    wxMenu* itemMenu25 = new wxMenu;
    itemMenu25->Append(ID_MN_LMFS_ARQ_IDATA, _("Por Intervalo de Data"), wxEmptyString, wxITEM_NORMAL);
    itemMenu25->Append(ID_MN_LMFS_ARQ_ICRZ, _("Por intervalo de CRZ"), wxEmptyString, wxITEM_NORMAL);
    itemMenu21->Append(ID_MN_LMFS_ARQ, _("Espelho"), itemMenu25);
    itemMenu9->Append(ID_MN_LMFS, _("LMFS"), itemMenu21);
    wxMenu* itemMenu28 = new wxMenu;
    itemMenu28->Append(ID_MNESPELHOMFD_DATA, _("Data"), wxEmptyString, wxITEM_NORMAL);
    itemMenu28->Append(ID_MNESPELHOMFD_COO, _("COO"), wxEmptyString, wxITEM_NORMAL);
    itemMenu9->Append(ID_MNESPELHOMFD, _("Espelho MFD"), itemMenu28);
    wxMenu* itemMenu31 = new wxMenu;
    itemMenu31->Append(ID_MNArqMFD_DATA, _("Data"), wxEmptyString, wxITEM_NORMAL);
    itemMenu31->Append(ID_MNArqMFD_COO, _("COO"), wxEmptyString, wxITEM_NORMAL);
    itemMenu9->Append(ID_MNArqMFD, _("Arq. MFD"), itemMenu31);
    itemMenu9->Append(ID_MNTabProd, _("Tab. Prod."), wxEmptyString, wxITEM_NORMAL);
    wxMenu* itemMenu35 = new wxMenu;
    itemMenu35->Append(ID_MI_ESTOQUE_TOTAL, _("ESTOQUE TOTAL"), wxEmptyString, wxITEM_NORMAL);
    itemMenu35->Append(ID_MI_ESTOQUE_PARCIAL, _("ESTOQUE PARCIAL"), wxEmptyString, wxITEM_NORMAL);
    itemMenu9->Append(ID_MNEstoque, _("Estoque"), itemMenu35);
    itemMenu9->Append(ID_MM_MOVECF, _("Movimento  por  ECF"), wxEmptyString, wxITEM_NORMAL);
    menuBar->Append(itemMenu9, _("MENU FISCAL"));
    wxMenu* itemMenu39 = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu39, ID_MENURECIBO, wxGetTranslation(wxString(wxT("C")) + (wxChar) 0x00F3 + wxT("digo de barras...\tCtrl+R")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/barcode.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu39->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu39, ID_MENUITEM, wxGetTranslation(wxString(wxT("C")) + (wxChar) 0x00F3 + wxT("digo de barras kg...\tCtrl+K")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/printd.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu39->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu39, ID_MENUBALANCOM, wxGetTranslation(wxString(wxT("Balan")) + (wxChar) 0x00E7 + wxT("o...\tCtrl+M")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/balance.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu39->Append(menuItem);
    }
    menuBar->Append(itemMenu39, wxGetTranslation(wxString(wxT("Impress")) + (wxChar) 0x00E3 + wxT("o")));
    wxMenu* itemMenu43 = new wxMenu;
    itemMenu43->Append(ID_MENU_RedZ, wxGetTranslation(wxString(wxT("Redu")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o Z\tCtrl+Z")), wxEmptyString, wxITEM_NORMAL);
    itemMenu43->Append(ID_MENU_RedXArq, _("Leitura X em arquivo\tCtrl+Shift+X"), wxEmptyString, wxITEM_NORMAL);
    itemMenu43->Append(ID_MENUI_RegAliq, wxGetTranslation(wxString(wxT("Registrar al")) + (wxChar) 0x00ED + wxT("quota ICMS\tCtrl+Shift+Z")), wxEmptyString, wxITEM_NORMAL);
    itemMenu43->Append(ID_MN_CANCELAULTCUPOM, wxGetTranslation(wxString(wxT("Cancelar ")) + (wxChar) 0x00FA + wxT("ltimo cupom")), wxEmptyString, wxITEM_NORMAL);
    itemMenu43->Append(ID_MN_CANCELAITEMANT, _("Cancela item anterior\tCtrl+Alt+A"), wxEmptyString, wxITEM_NORMAL);
    itemMenu43->Append(ID_MN_CANCELAITEM, _("Cancela item...\tCtrl+Alt+I"), wxEmptyString, wxITEM_NORMAL);
    menuBar->Append(itemMenu43, wxGetTranslation(wxString(wxT("Opera")) + (wxChar) 0x00E7 + (wxChar) 0x00F5 + wxT("es fiscais")));
    wxMenu* itemMenu50 = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLFIRSTREC, wxGetTranslation(wxString(wxT("primeira grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o\tCtrl+Shift+Left")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MoveFirstHS.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLPREVREC, wxGetTranslation(wxString(wxT("grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o anterior\tCtrl+Left")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MovePreviousHS.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLNEXTREC, wxGetTranslation(wxString(wxT("pr")) + (wxChar) 0x00F3 + wxT("xima grava") + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o\tCtrl+Right")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MoveNextHS.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLLASTREC, wxGetTranslation(wxString() + (wxChar) 0x00FA + wxT("ltima grava") + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o\tCtrl+Shift+Right")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MoveLastHS.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLInsert, _("Inserir\tF1"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_NewRecordHS.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLEdit, _("Editar\tCtrl+E"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/005_Task_16x16_72.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLCancel, _("Cancelar\tF3"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/cancel.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    itemMenu50->Enable(ID_TOOLCancel, false);
    itemMenu50->Append(ID_MN_DESC_PERCENT, _("Desconto percentual\tF4"), wxEmptyString, wxITEM_NORMAL);
    itemMenu50->Append(ID_MN_INS_PAGTO, _("Inserir pagto\tF5"), wxEmptyString, wxITEM_NORMAL);
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_TOOLDelete, wxGetTranslation(wxString(wxT("Excluir grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o\tCtrl+DEL")), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/DeleteHS.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(itemMenu50, ID_MN_PESQPROD, _("Produtos\tF2"), wxEmptyString, wxITEM_NORMAL);
        wxBitmap bitmap(itemFrame1->GetBitmapResource(wxT("images/products.png")));
        menuItem->SetBitmap(bitmap);
        itemMenu50->Append(menuItem);
    }
    menuBar->Append(itemMenu50, wxGetTranslation(wxString(wxT("Grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")));
    itemFrame1->SetMenuBar(menuBar);

    wxToolBar* itemToolBar62 = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL|wxTB_TEXT, ID_TOOLBAR );
    itemToolBar62->SetToolBitmapSize(wxSize(16, 16));
    wxTextCtrl* itemTextCtrl63 = new wxTextCtrl( itemToolBar62, ID_SEARCHCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
    if (VilaVilela::ShowToolTips())
        itemTextCtrl63->SetToolTip(_("digite um texto para procurar"));
    itemToolBar62->AddControl(itemTextCtrl63);
    wxDatePickerCtrl* itemDatePickerCtrl64 = new wxDatePickerCtrl( itemToolBar62, ID_SEARCHDATE1, wxDateTime(), wxDefaultPosition, wxSize(130, -1), wxDP_DROPDOWN|wxDP_DEFAULT );
    if (VilaVilela::ShowToolTips())
        itemDatePickerCtrl64->SetToolTip(_("data inicial"));
    itemToolBar62->AddControl(itemDatePickerCtrl64);
    wxDatePickerCtrl* itemDatePickerCtrl65 = new wxDatePickerCtrl( itemToolBar62, ID_SEARCHDATE2, wxDateTime(), wxDefaultPosition, wxSize(130, -1), wxDP_DROPDOWN|wxDP_DEFAULT|wxDP_ALLOWNONE );
    if (VilaVilela::ShowToolTips())
        itemDatePickerCtrl65->SetToolTip(_("data final"));
    itemToolBar62->AddControl(itemDatePickerCtrl65);
    wxToggleButton* itemToggleButton66 = new wxToggleButton( itemToolBar62, ID_TOOLFILTER, _("Filtro"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemToggleButton66->SetValue(false);
    if (VilaVilela::ShowToolTips())
        itemToggleButton66->SetToolTip(_("filtra tabela"));
    itemToolBar62->AddControl(itemToggleButton66);
    itemToolBar62->AddSeparator();
    wxBitmap itemtool68Bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_NewRecordHS.png")));
    wxBitmap itemtool68BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLInsert, _("Inserir[F1]"), itemtool68Bitmap, itemtool68BitmapDisabled, wxITEM_NORMAL, _("Inserir[F1]"), wxGetTranslation(wxString(wxT("Insere nova grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")));
    wxBitmap itemtool69Bitmap(itemFrame1->GetBitmapResource(wxT("images/products.png")));
    wxBitmap itemtool69BitmapDisabled;
    itemToolBar62->AddTool(ID_MN_PESQPROD, _("Produtos[F2]"), itemtool69Bitmap, itemtool69BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    wxBitmap itemtool70Bitmap(itemFrame1->GetBitmapResource(wxT("images/cancel.png")));
    wxBitmap itemtool70BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLCancel, _("Cancelar[F3]"), itemtool70Bitmap, itemtool70BitmapDisabled, wxITEM_NORMAL, _("Cancelar[F3]"), wxEmptyString);
    itemToolBar62->EnableTool(ID_TOOLCancel, false);
    wxBitmap itemtool71Bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MoveFirstHS.png")));
    wxBitmap itemtool71BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLFIRSTREC, wxEmptyString, itemtool71Bitmap, itemtool71BitmapDisabled, wxITEM_NORMAL, wxGetTranslation(wxString(wxT("primeira grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o[ctrl + shift + <-]")), wxGetTranslation(wxString(wxT("Vai para a primeira grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")));
    wxBitmap itemtool72Bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MovePreviousHS.png")));
    wxBitmap itemtool72BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLPREVREC, wxEmptyString, itemtool72Bitmap, itemtool72BitmapDisabled, wxITEM_NORMAL, wxGetTranslation(wxString(wxT("grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o anterior[ctrl + <-]")), wxEmptyString);
    wxBitmap itemtool73Bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MoveNextHS.png")));
    wxBitmap itemtool73BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLNEXTREC, wxEmptyString, itemtool73Bitmap, itemtool73BitmapDisabled, wxITEM_NORMAL, wxGetTranslation(wxString(wxT("pr")) + (wxChar) 0x00F3 + wxT("xima grava") + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o[ctrl + ->]")), wxEmptyString);
    wxBitmap itemtool74Bitmap(itemFrame1->GetBitmapResource(wxT("images/DataContainer_MoveLastHS.png")));
    wxBitmap itemtool74BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLLASTREC, wxEmptyString, itemtool74Bitmap, itemtool74BitmapDisabled, wxITEM_NORMAL, wxGetTranslation(wxString() + (wxChar) 0x00FA + wxT("ltimas grava") + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o[ctrl + shift + ->]")), wxGetTranslation(wxString(wxT("Vai para a ")) + (wxChar) 0x00FA + wxT("ltima grava") + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")));
    wxBitmap itemtool75Bitmap(itemFrame1->GetBitmapResource(wxT("images/005_Task_16x16_72.png")));
    wxBitmap itemtool75BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLEdit, wxEmptyString, itemtool75Bitmap, itemtool75BitmapDisabled, wxITEM_NORMAL, _("Editar[Ctrl+E]"), wxEmptyString);
    wxBitmap itemtool76Bitmap(itemFrame1->GetBitmapResource(wxT("images/DeleteHS.png")));
    wxBitmap itemtool76BitmapDisabled;
    itemToolBar62->AddTool(ID_TOOLDelete, wxEmptyString, itemtool76Bitmap, itemtool76BitmapDisabled, wxITEM_NORMAL, wxGetTranslation(wxString(wxT("Excluir grava")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o[Ctrl+DEL]")), wxEmptyString);
    itemToolBar62->Realize();
    itemFrame1->SetToolBar(itemToolBar62);

    wxBoxSizer* itemBoxSizer77 = new wxBoxSizer(wxVERTICAL);
    itemFrame1->SetSizer(itemBoxSizer77);

    wxNotebook* itemNotebook78 = new wxNotebook( itemFrame1, ID_NOTEBOOK, wxDefaultPosition, wxSize(850, 600), wxBK_DEFAULT|wxFULL_REPAINT_ON_RESIZE );
    wxImageList* itemNotebook78ImageList = new wxImageList(32, 32, true, 9);
    {
        wxIcon itemNotebook78Icon0(itemFrame1->GetIconResource(wxT("images/icon-pagamento.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon0);
        wxIcon itemNotebook78Icon1(itemFrame1->GetIconResource(wxT("images/cesta.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon1);
        wxIcon itemNotebook78Icon2(itemFrame1->GetIconResource(wxT("images/unidade.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon2);
        wxIcon itemNotebook78Icon3(itemFrame1->GetIconResource(wxT("images/users-3.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon3);
        wxIcon itemNotebook78Icon4(itemFrame1->GetIconResource(wxT("images/icon_fornecedor.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon4);
        wxIcon itemNotebook78Icon5(itemFrame1->GetIconResource(wxT("images/unnamed.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon5);
        wxIcon itemNotebook78Icon6(itemFrame1->GetIconResource(wxT("images/formaspagamento.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon6);
        wxIcon itemNotebook78Icon7(itemFrame1->GetIconResource(wxT("images/category.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon7);
        wxIcon itemNotebook78Icon8(itemFrame1->GetIconResource(wxT("images/Percent-icon.png")));
        itemNotebook78ImageList->Add(itemNotebook78Icon8);
    }
    itemNotebook78->AssignImageList(itemNotebook78ImageList);
    itemNotebook78->SetBackgroundColour(wxColour(218, 218, 218));

    wxScrolledWindow* itemScrolledWindow79 = new wxScrolledWindow( itemNotebook78, ID_PGVENDAS, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxFULL_REPAINT_ON_RESIZE|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow79->SetScrollbars(1, 1, 0, 0);
    vendassizerv = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow79->SetSizer(vendassizerv);

    wxFlexGridSizer* itemFlexGridSizer81 = new wxFlexGridSizer(0, 4, 0, 0);
    vendassizerv->Add(itemFlexGridSizer81, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText82 = new wxStaticText( itemScrolledWindow79, ID_STVENDAS_CLIENTE, _("Cliente"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer81->Add(itemStaticText82, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl83 = new wxTextCtrl( itemScrolledWindow79, ID_VENDAS_CLIENTE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemFlexGridSizer81->Add(itemTextCtrl83, 1, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxALL, 5);

    wxStaticText* itemStaticText84 = new wxStaticText( itemScrolledWindow79, ID_STVENDAS_FORMAPAGTO, _("Forma pagto"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer81->Add(itemStaticText84, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice85Strings;
    wxChoice* itemChoice85 = new wxChoice( itemScrolledWindow79, ID_VENDAS_FORMAPAGTO, wxDefaultPosition, wxSize(150, -1), itemChoice85Strings, 0 );
    itemFlexGridSizer81->Add(itemChoice85, 1, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxALL, 5);

    wxStaticText* itemStaticText86 = new wxStaticText( itemScrolledWindow79, ID_STVENDAS_NO_NOTA, wxGetTranslation(wxString(wxT("N")) + (wxChar) 0x00FA + wxT("mero nota/cupom")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer81->Add(itemStaticText86, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl87 = new wxTextCtrl( itemScrolledWindow79, ID_VENDAS_NO_NOTA, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer81->Add(itemTextCtrl87, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText88 = new wxStaticText( itemScrolledWindow79, ID_STVENDAS_DATA, _("Data"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer81->Add(itemStaticText88, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxDatePickerCtrl* itemDatePickerCtrl89 = new wxDatePickerCtrl( itemScrolledWindow79, ID_VENDAS_DATA, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN|wxDP_DEFAULT );
    itemFlexGridSizer81->Add(itemDatePickerCtrl89, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxPanel* itemPanel90 = new wxPanel( itemScrolledWindow79, ID_PANEL_VENDAS1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
    vendassizerv->Add(itemPanel90, 2, wxGROW|wxALL, 5);
    wxStaticBox* itemStaticBoxSizer91Static = new wxStaticBox(itemPanel90, wxID_ANY, _("Lista de Produtos nesta Venda"));
    wxStaticBoxSizer* itemStaticBoxSizer91 = new wxStaticBoxSizer(itemStaticBoxSizer91Static, wxHORIZONTAL);
    itemPanel90->SetSizer(itemStaticBoxSizer91);

    vendasprodsizer = new wxBoxSizer(wxVERTICAL);
    itemStaticBoxSizer91->Add(vendasprodsizer, 2, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer93 = new wxBoxSizer(wxHORIZONTAL);
    vendasprodsizer->Add(itemBoxSizer93, 2, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl94 = new wxListCtrl( itemPanel90, ID_VENDAS_INSPROD_GRID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_EDIT_LABELS|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER|wxFULL_REPAINT_ON_RESIZE );
    itemListCtrl94->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Tahoma")));
    itemBoxSizer93->Add(itemListCtrl94, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer95 = new wxBoxSizer(wxHORIZONTAL);
    vendasprodsizer->Add(itemBoxSizer95, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);
    wxBoxSizer* itemBoxSizer96 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer95->Add(itemBoxSizer96, 0, wxALIGN_TOP|wxALL, 5);
    wxStaticText* itemStaticText97 = new wxStaticText( itemPanel90, wxID_STATIC_TOTDESC, _("Total sem desconto"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_THEME );
    itemBoxSizer96->Add(itemStaticText97, 0, wxGROW|wxALL, 0);

    wxTextCtrl* itemTextCtrl98 = new wxTextCtrl( itemPanel90, ID_VENDAS_TOTAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxFULL_REPAINT_ON_RESIZE );
    itemTextCtrl98->SetBackgroundColour(wxColour(255, 255, 255));
    itemTextCtrl98->Enable(false);
    itemBoxSizer96->Add(itemTextCtrl98, 0, wxGROW|wxALL, 1);

    wxBoxSizer* itemBoxSizer99 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer95->Add(itemBoxSizer99, 0, wxALIGN_TOP|wxALL, 5);
    wxStaticText* itemStaticText100 = new wxStaticText( itemPanel90, wxID_STATIC_DESCPERC, _("Desconto Percentual[F4]"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_THEME );
    itemBoxSizer99->Add(itemStaticText100, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxCheckBox* itemCheckBox101 = new wxCheckBox( itemPanel90, ID_CHK_PERCENTUAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemCheckBox101->SetValue(true);
    itemBoxSizer99->Add(itemCheckBox101, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer102 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer95->Add(itemBoxSizer102, 0, wxALIGN_TOP|wxALL, 5);
    wxStaticText* itemStaticText103 = new wxStaticText( itemPanel90, wxID_STATIC_VALDESC, _("Valor Desconto"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_THEME );
    itemBoxSizer102->Add(itemStaticText103, 1, wxGROW|wxALL, 0);

    wxTextCtrl* itemTextCtrl104 = new wxTextCtrl( itemPanel90, ID_VENDAS_DESCONTO, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE );
    itemTextCtrl104->SetBackgroundColour(wxColour(255, 255, 255));
    itemBoxSizer102->Add(itemTextCtrl104, 0, wxGROW|wxALL, 1);

    wxBoxSizer* itemBoxSizer105 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer95->Add(itemBoxSizer105, 0, wxALIGN_TOP|wxALL, 5);
    wxStaticText* itemStaticText106 = new wxStaticText( itemPanel90, wxID_STATIC_VALREC, _("Pagamentos[F5=insere novo]"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_THEME );
    itemBoxSizer105->Add(itemStaticText106, 0, wxGROW|wxALL, 0);

    wxListCtrl* itemListCtrl107 = new wxListCtrl( itemPanel90, ID_VENDAS_VALREC, wxDefaultPosition, wxSize(150, 80), wxLC_REPORT|wxLC_NO_HEADER|wxLC_HRULES|wxLC_VRULES|wxFULL_REPAINT_ON_RESIZE );
    itemListCtrl107->SetBackgroundColour(wxColour(255, 255, 255));
    itemBoxSizer105->Add(itemListCtrl107, 0, wxGROW|wxALL, 1);

    wxBoxSizer* itemBoxSizer108 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer95->Add(itemBoxSizer108, 0, wxALIGN_TOP|wxALL, 5);
    wxStaticText* itemStaticText109 = new wxStaticText( itemPanel90, wxID_STATIC_TOTAL, _("Total"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_THEME );
    itemBoxSizer108->Add(itemStaticText109, 0, wxGROW|wxALL, 0);

    wxTextCtrl* itemTextCtrl110 = new wxTextCtrl( itemPanel90, ID_VENDAS_TOTAL_GERAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxFULL_REPAINT_ON_RESIZE );
    itemTextCtrl110->SetBackgroundColour(wxColour(255, 255, 255));
    itemTextCtrl110->Enable(false);
    itemBoxSizer108->Add(itemTextCtrl110, 0, wxGROW|wxALL, 1);

    wxBoxSizer* itemBoxSizer111 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer95->Add(itemBoxSizer111, 0, wxALIGN_TOP|wxALL, 5);
    wxStaticText* itemStaticText112 = new wxStaticText( itemPanel90, wxID_STATIC_TROCO, _("Troco"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_THEME );
    itemBoxSizer111->Add(itemStaticText112, 0, wxGROW|wxALL, 0);

    wxTextCtrl* itemTextCtrl113 = new wxTextCtrl( itemPanel90, ID_VENDAS_TROCO, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxFULL_REPAINT_ON_RESIZE );
    itemTextCtrl113->SetBackgroundColour(wxColour(255, 255, 255));
    itemTextCtrl113->Enable(false);
    itemBoxSizer111->Add(itemTextCtrl113, 0, wxGROW|wxALL, 1);

    wxPanel* itemPanel114 = new wxPanel( itemScrolledWindow79, ID_PANEL_VENDAS_OWNER, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
    vendassizerv->Add(itemPanel114, 1, wxGROW|wxALL, 5);
    wxStaticBox* itemStaticBoxSizer115Static = new wxStaticBox(itemPanel114, ID_PANEL_VENDAS, _("Vendas"));
    wxStaticBoxSizer* itemStaticBoxSizer115 = new wxStaticBoxSizer(itemStaticBoxSizer115Static, wxVERTICAL);
    itemStaticBoxSizer115Static->Show(false);
    itemPanel114->SetSizer(itemStaticBoxSizer115);

    wxListCtrl* itemListCtrl116 = new wxListCtrl( itemPanel114, ID_VENDAS_GRID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemListCtrl116->Show(false);
    itemStaticBoxSizer115->Add(itemListCtrl116, 1, wxGROW|wxALL, 5);

    itemScrolledWindow79->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow79, _("Vendas"), false, 0);

    wxScrolledWindow* itemScrolledWindow117 = new wxScrolledWindow( itemNotebook78, ID_PGCOMPRAS, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow117->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer118 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow117->SetSizer(itemBoxSizer118);

    wxFlexGridSizer* itemFlexGridSizer119 = new wxFlexGridSizer(0, 4, 0, 0);
    itemBoxSizer118->Add(itemFlexGridSizer119, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText120 = new wxStaticText( itemScrolledWindow117, wxID_STATIC, _("Fornecedor"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer119->Add(itemStaticText120, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer121 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer119->Add(itemBoxSizer121, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxArrayString itemChoice122Strings;
    wxChoice* itemChoice122 = new wxChoice( itemScrolledWindow117, ID_COMPRAS_FORNEC, wxDefaultPosition, wxDefaultSize, itemChoice122Strings, 0 );
    itemBoxSizer121->Add(itemChoice122, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText123 = new wxStaticText( itemScrolledWindow117, wxID_STATIC, _("Data"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer119->Add(itemStaticText123, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxDatePickerCtrl* itemDatePickerCtrl124 = new wxDatePickerCtrl( itemScrolledWindow117, ID_COMPRAS_DATA, wxDateTime(), wxDefaultPosition, wxSize(150, -1), wxDP_DROPDOWN|wxDP_DEFAULT );
    itemFlexGridSizer119->Add(itemDatePickerCtrl124, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText125 = new wxStaticText( itemScrolledWindow117, wxID_STATIC, wxGetTranslation(wxString(wxT("N")) + (wxChar) 0x00FA + wxT("mero nota")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer119->Add(itemStaticText125, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl126 = new wxTextCtrl( itemScrolledWindow117, ID_COMPRAS_NO_NOTA, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer119->Add(itemTextCtrl126, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer127Static = new wxStaticBox(itemScrolledWindow117, wxID_ANY, _("Lista de Produtos nesta Compra"));
    wxStaticBoxSizer* itemStaticBoxSizer127 = new wxStaticBoxSizer(itemStaticBoxSizer127Static, wxHORIZONTAL);
    itemBoxSizer118->Add(itemStaticBoxSizer127, 1, wxGROW|wxALL, 5);
    wxBitmapButton* itemBitmapButton128 = new wxBitmapButton( itemScrolledWindow117, ID_COMPRAS_BT_INS_PROD, itemFrame1->GetBitmapResource(wxT("images/RecordHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton128->SetToolTip(_("Adicionar produto"));
    itemStaticBoxSizer127->Add(itemBitmapButton128, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxListCtrl* itemListCtrl129 = new wxListCtrl( itemScrolledWindow117, ID_COMPRAS_PROD_GRID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_HRULES|wxLC_VRULES|wxFULL_REPAINT_ON_RESIZE );
    itemListCtrl129->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Tahoma")));
    itemStaticBoxSizer127->Add(itemListCtrl129, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer130 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer118->Add(itemBoxSizer130, 0, wxALIGN_RIGHT|wxALL, 0);
    wxStaticText* itemStaticText131 = new wxStaticText( itemScrolledWindow117, wxID_STATIC, _("Total"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer130->Add(itemStaticText131, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxTextCtrl* itemTextCtrl132 = new wxTextCtrl( itemScrolledWindow117, ID_COMPRAS_TOTAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemTextCtrl132->SetBackgroundColour(wxColour(255, 255, 255));
    itemTextCtrl132->Enable(false);
    itemBoxSizer130->Add(itemTextCtrl132, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1);

    wxStaticBox* itemStaticBoxSizer133Static = new wxStaticBox(itemScrolledWindow117, wxID_ANY, _("Compras"));
    wxStaticBoxSizer* itemStaticBoxSizer133 = new wxStaticBoxSizer(itemStaticBoxSizer133Static, wxHORIZONTAL);
    itemBoxSizer118->Add(itemStaticBoxSizer133, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl134 = new wxListCtrl( itemScrolledWindow117, ID_COMPRAS_GRID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemStaticBoxSizer133->Add(itemListCtrl134, 1, wxGROW|wxALL, 5);

    itemScrolledWindow117->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow117, _("Compras"), false, 1);

    wxScrolledWindow* itemScrolledWindow135 = new wxScrolledWindow( itemNotebook78, ID_PGUNIDADE, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow135->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer136 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow135->SetSizer(itemBoxSizer136);

    wxFlexGridSizer* itemFlexGridSizer137 = new wxFlexGridSizer(0, 4, 0, 0);
    itemBoxSizer136->Add(itemFlexGridSizer137, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText138 = new wxStaticText( itemScrolledWindow135, wxID_STATIC, wxGetTranslation(wxString(wxT("Descri")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer137->Add(itemStaticText138, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl139 = new wxTextCtrl( itemScrolledWindow135, ID_UNIDADE_DESC, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer137->Add(itemTextCtrl139, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText140 = new wxStaticText( itemScrolledWindow135, wxID_STATIC, _("Abreviatura"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer137->Add(itemStaticText140, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl141 = new wxTextCtrl( itemScrolledWindow135, ID_UNIDADE_ABREV, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer137->Add(itemTextCtrl141, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer142Static = new wxStaticBox(itemScrolledWindow135, wxID_ANY, _("Lista de unidades"));
    wxStaticBoxSizer* itemStaticBoxSizer142 = new wxStaticBoxSizer(itemStaticBoxSizer142Static, wxHORIZONTAL);
    itemBoxSizer136->Add(itemStaticBoxSizer142, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl143 = new wxListCtrl( itemScrolledWindow135, ID_UNIDADE_GRID, wxDefaultPosition, wxSize(600, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemStaticBoxSizer142->Add(itemListCtrl143, 1, wxGROW|wxALL, 5);

    itemScrolledWindow135->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow135, _("Unidades"), false, 2);

    wxScrolledWindow* itemScrolledWindow144 = new wxScrolledWindow( itemNotebook78, ID_PGCLIENTES, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow144->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer145 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow144->SetSizer(itemBoxSizer145);

    wxFlexGridSizer* itemFlexGridSizer146 = new wxFlexGridSizer(0, 4, 0, 0);
    itemBoxSizer145->Add(itemFlexGridSizer146, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText147 = new wxStaticText( itemScrolledWindow144, wxID_STATIC, _("Nome"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer146->Add(itemStaticText147, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl148 = new wxTextCtrl( itemScrolledWindow144, ID_CLIENT_NOME, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer146->Add(itemTextCtrl148, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText149 = new wxStaticText( itemScrolledWindow144, wxID_STATIC, wxGetTranslation(wxString(wxT("Endre")) + (wxChar) 0x00E7 + wxT("o")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer146->Add(itemStaticText149, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl150 = new wxTextCtrl( itemScrolledWindow144, ID_CLIENT_END, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer146->Add(itemTextCtrl150, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText151 = new wxStaticText( itemScrolledWindow144, wxID_STATIC, _("Complemento"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer146->Add(itemStaticText151, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl152 = new wxTextCtrl( itemScrolledWindow144, ID_CLIENT_COMP, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer146->Add(itemTextCtrl152, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText153 = new wxStaticText( itemScrolledWindow144, wxID_STATIC, _("Email"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer146->Add(itemStaticText153, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl154 = new wxTextCtrl( itemScrolledWindow144, ID_CLIENT_EMAIL, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer146->Add(itemTextCtrl154, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText155 = new wxStaticText( itemScrolledWindow144, wxID_STATIC, _("Data nascimento"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer146->Add(itemStaticText155, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxDatePickerCtrl* itemDatePickerCtrl156 = new wxDatePickerCtrl( itemScrolledWindow144, ID_CLIENT_DATANASC, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN|wxDP_DEFAULT );
    itemFlexGridSizer146->Add(itemDatePickerCtrl156, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText157 = new wxStaticText( itemScrolledWindow144, wxID_STATIC, _("C.P.F."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer146->Add(itemStaticText157, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl158 = new wxTextCtrl( itemScrolledWindow144, ID_CLIENT_CPF, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0 );
    itemFlexGridSizer146->Add(itemTextCtrl158, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText159 = new wxStaticText( itemScrolledWindow144, wxID_STATIC_CLFONE, _("Fones"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer146->Add(itemStaticText159, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer160 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer146->Add(itemBoxSizer160, 0, wxALIGN_LEFT|wxGROW|wxALL, 5);
    wxBitmapButton* itemBitmapButton161 = new wxBitmapButton( itemScrolledWindow144, ID_CLIENT_INS_FONE, itemFrame1->GetBitmapResource(wxT("images/RecordHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxFULL_REPAINT_ON_RESIZE );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton161->SetToolTip(_("Inserir fone"));
    itemBoxSizer160->Add(itemBitmapButton161, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton162 = new wxBitmapButton( itemScrolledWindow144, ID_CLIENT_DEL_FONE, itemFrame1->GetBitmapResource(wxT("images/telephone-delete-icon.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxFULL_REPAINT_ON_RESIZE );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton162->SetToolTip(_("Apagar fone"));
    itemBoxSizer160->Add(itemBitmapButton162, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton163 = new wxBitmapButton( itemScrolledWindow144, ID_CLIENT_DELALL_FONE, itemFrame1->GetBitmapResource(wxT("images/DeleteHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxFULL_REPAINT_ON_RESIZE );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton163->SetToolTip(_("Apagar todos os telefones"));
    itemBoxSizer160->Add(itemBitmapButton163, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice164Strings;
    wxChoice* itemChoice164 = new wxChoice( itemScrolledWindow144, ID_CBCLIENTFONES, wxDefaultPosition, wxSize(150, -1), itemChoice164Strings, 0 );
    itemBoxSizer160->Add(itemChoice164, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer165Static = new wxStaticBox(itemScrolledWindow144, wxID_ANY, _("Lista de clientes"));
    wxStaticBoxSizer* itemStaticBoxSizer165 = new wxStaticBoxSizer(itemStaticBoxSizer165Static, wxHORIZONTAL);
    itemBoxSizer145->Add(itemStaticBoxSizer165, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl166 = new wxListCtrl( itemScrolledWindow144, ID_CLIENT_GRID, wxDefaultPosition, wxSize(600, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES );
    itemStaticBoxSizer165->Add(itemListCtrl166, 1, wxGROW|wxALL, 5);

    itemScrolledWindow144->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow144, _("Clientes"), false, 3);

    wxScrolledWindow* itemScrolledWindow167 = new wxScrolledWindow( itemNotebook78, ID_PGFORNEC, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow167->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer168 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow167->SetSizer(itemBoxSizer168);

    wxFlexGridSizer* itemFlexGridSizer169 = new wxFlexGridSizer(0, 4, 0, 0);
    itemBoxSizer168->Add(itemFlexGridSizer169, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText170 = new wxStaticText( itemScrolledWindow167, wxID_STATIC, _("Nome"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer169->Add(itemStaticText170, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl171 = new wxTextCtrl( itemScrolledWindow167, ID_FORNEC_NOME, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer169->Add(itemTextCtrl171, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText172 = new wxStaticText( itemScrolledWindow167, wxID_STATIC, wxGetTranslation(wxString(wxT("Endre")) + (wxChar) 0x00E7 + wxT("o")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer169->Add(itemStaticText172, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl173 = new wxTextCtrl( itemScrolledWindow167, ID_FORNEC_END, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer169->Add(itemTextCtrl173, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText174 = new wxStaticText( itemScrolledWindow167, wxID_STATIC, _("Complemento"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer169->Add(itemStaticText174, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl175 = new wxTextCtrl( itemScrolledWindow167, ID_FORNEC_COMP, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer169->Add(itemTextCtrl175, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText176 = new wxStaticText( itemScrolledWindow167, wxID_STATIC, _("Email"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer169->Add(itemStaticText176, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl177 = new wxTextCtrl( itemScrolledWindow167, ID_FORNEC_EMAIL, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer169->Add(itemTextCtrl177, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText178 = new wxStaticText( itemScrolledWindow167, wxID_STATIC, _("Contato"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer169->Add(itemStaticText178, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl179 = new wxTextCtrl( itemScrolledWindow167, ID_FORNEC_CONTATO, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer169->Add(itemTextCtrl179, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText180 = new wxStaticText( itemScrolledWindow167, wxID_STATIC, _("C.N.P.J."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer169->Add(itemStaticText180, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl181 = new wxTextCtrl( itemScrolledWindow167, ID_FORNEC_CNPJ, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0 );
    itemFlexGridSizer169->Add(itemTextCtrl181, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText182 = new wxStaticText( itemScrolledWindow167, wxID_STATIC_FNFONE, _("Fones"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer169->Add(itemStaticText182, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer183 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer169->Add(itemBoxSizer183, 0, wxALIGN_LEFT|wxGROW|wxALL, 5);
    wxBitmapButton* itemBitmapButton184 = new wxBitmapButton( itemScrolledWindow167, ID_FORNEC_INS_FONE, itemFrame1->GetBitmapResource(wxT("images/RecordHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxFULL_REPAINT_ON_RESIZE );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton184->SetToolTip(_("Inserir fone"));
    itemBoxSizer183->Add(itemBitmapButton184, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton185 = new wxBitmapButton( itemScrolledWindow167, ID_FORNEC_DEL_FONE, itemFrame1->GetBitmapResource(wxT("images/telephone-delete-icon.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxFULL_REPAINT_ON_RESIZE );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton185->SetToolTip(_("Apagar fone"));
    itemBoxSizer183->Add(itemBitmapButton185, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton186 = new wxBitmapButton( itemScrolledWindow167, ID_FORNEC_DELALL_FONE, itemFrame1->GetBitmapResource(wxT("images/DeleteHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxFULL_REPAINT_ON_RESIZE );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton186->SetToolTip(_("Apagar todos os telefones"));
    itemBoxSizer183->Add(itemBitmapButton186, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice187Strings;
    wxChoice* itemChoice187 = new wxChoice( itemScrolledWindow167, ID_CBFORNECFONES, wxDefaultPosition, wxSize(150, -1), itemChoice187Strings, 0 );
    itemBoxSizer183->Add(itemChoice187, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer188Static = new wxStaticBox(itemScrolledWindow167, wxID_ANY, _("Lista de fornecedores"));
    wxStaticBoxSizer* itemStaticBoxSizer188 = new wxStaticBoxSizer(itemStaticBoxSizer188Static, wxHORIZONTAL);
    itemBoxSizer168->Add(itemStaticBoxSizer188, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl189 = new wxListCtrl( itemScrolledWindow167, ID_FORNEC_GRID, wxDefaultPosition, wxSize(600, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemStaticBoxSizer188->Add(itemListCtrl189, 1, wxGROW|wxALL, 5);

    itemScrolledWindow167->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow167, _("Fornecedores"), false, 4);

    wxScrolledWindow* itemScrolledWindow190 = new wxScrolledWindow( itemNotebook78, ID_PGPRODUTOS, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow190->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer191 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow190->SetSizer(itemBoxSizer191);

    wxFlexGridSizer* itemFlexGridSizer192 = new wxFlexGridSizer(0, 4, 0, 0);
    itemBoxSizer191->Add(itemFlexGridSizer192, 1, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText193 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, _("Nome"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText193, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl194 = new wxTextCtrl( itemScrolledWindow190, ID_PROD_NOME, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE );
    itemFlexGridSizer192->Add(itemTextCtrl194, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText195 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, wxGetTranslation(wxString(wxT("Descri")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText195, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl196 = new wxTextCtrl( itemScrolledWindow190, ID_PROD_DESC, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer192->Add(itemTextCtrl196, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText197 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, wxGetTranslation(wxString(wxT("Valor unit")) + (wxChar) 0x00E1 + wxT("rio")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText197, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl198 = new wxTextCtrl( itemScrolledWindow190, ID_PROD_VALUNIT, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer192->Add(itemTextCtrl198, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText199 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, _("Unidade"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText199, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice200Strings;
    wxChoice* itemChoice200 = new wxChoice( itemScrolledWindow190, ID_PROD_UNIT, wxDefaultPosition, wxSize(100, -1), itemChoice200Strings, 0 );
    itemFlexGridSizer192->Add(itemChoice200, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText201 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, _("Categoria"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText201, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice202Strings;
    wxChoice* itemChoice202 = new wxChoice( itemScrolledWindow190, ID_PROD_CATEGORIA, wxDefaultPosition, wxSize(150, -1), itemChoice202Strings, 0 );
    itemFlexGridSizer192->Add(itemChoice202, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText203 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, wxGetTranslation(wxString(wxT("C")) + (wxChar) 0x00F3 + wxT("digo")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText203, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl204 = new wxTextCtrl( itemScrolledWindow190, ID_PROD_BARCOD, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer192->Add(itemTextCtrl204, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText205 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, _("ICMS"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText205, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer206 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer192->Add(itemBoxSizer206, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 0);
    wxArrayString itemChoice207Strings;
    wxChoice* itemChoice207 = new wxChoice( itemScrolledWindow190, ID_PROD_ICMS, wxDefaultPosition, wxSize(150, -1), itemChoice207Strings, 0 );
    itemBoxSizer206->Add(itemChoice207, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox208 = new wxCheckBox( itemScrolledWindow190, ID_PROD_SUGESTAO, wxGetTranslation(wxString(wxT("Sugest")) + (wxChar) 0x00E3 + wxT("o")), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemCheckBox208->SetValue(false);
    itemFlexGridSizer192->Add(itemCheckBox208, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox209 = new wxCheckBox( itemScrolledWindow190, ID_PROD_DESTAQUE, _("Destaque"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemCheckBox209->SetValue(false);
    itemFlexGridSizer192->Add(itemCheckBox209, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText210 = new wxStaticText( itemScrolledWindow190, wxID_STATIC, _("Foto"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer192->Add(itemStaticText210, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer211 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer192->Add(itemBoxSizer211, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 0);
    wxStaticBitmap* itemStaticBitmap212 = new wxStaticBitmap( itemScrolledWindow190, ID_PROD_IMG, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer211->Add(itemStaticBitmap212, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton213 = new wxButton( itemScrolledWindow190, ID_BTPROD_IMG, _("Procurar..."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer211->Add(itemButton213, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton214 = new wxBitmapButton( itemScrolledWindow190, ID_PROD_DELIMAGE, itemFrame1->GetBitmapResource(wxT("images/DeleteHS.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxFULL_REPAINT_ON_RESIZE );
    if (VilaVilela::ShowToolTips())
        itemBitmapButton214->SetToolTip(_("Excluir foto"));
    itemBoxSizer211->Add(itemBitmapButton214, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer215Static = new wxStaticBox(itemScrolledWindow190, wxID_ANY, _("Lista de Produtos"));
    wxStaticBoxSizer* itemStaticBoxSizer215 = new wxStaticBoxSizer(itemStaticBoxSizer215Static, wxHORIZONTAL);
    itemBoxSizer191->Add(itemStaticBoxSizer215, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl216 = new wxListCtrl( itemScrolledWindow190, ID_PROD_GRID, wxDefaultPosition, wxSize(600, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemStaticBoxSizer215->Add(itemListCtrl216, 1, wxGROW|wxALL, 5);

    itemScrolledWindow190->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow190, _("Produtos"), false, 5);

    wxScrolledWindow* itemScrolledWindow217 = new wxScrolledWindow( itemNotebook78, ID_PGFORMAPAGTO, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow217->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer218 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow217->SetSizer(itemBoxSizer218);

    wxFlexGridSizer* itemFlexGridSizer219 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer218->Add(itemFlexGridSizer219, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText220 = new wxStaticText( itemScrolledWindow217, wxID_STATIC, wxGetTranslation(wxString(wxT("Descri")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer219->Add(itemStaticText220, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl221 = new wxTextCtrl( itemScrolledWindow217, ID_FORMAPGTO_DESC, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer219->Add(itemTextCtrl221, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer222Static = new wxStaticBox(itemScrolledWindow217, wxID_ANY, _("Lista formas de pagamento"));
    wxStaticBoxSizer* itemStaticBoxSizer222 = new wxStaticBoxSizer(itemStaticBoxSizer222Static, wxHORIZONTAL);
    itemBoxSizer218->Add(itemStaticBoxSizer222, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl223 = new wxListCtrl( itemScrolledWindow217, ID_FORMAPGTO_GRID, wxDefaultPosition, wxSize(600, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemStaticBoxSizer222->Add(itemListCtrl223, 1, wxGROW|wxALL, 5);

    itemScrolledWindow217->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow217, _("Formas pgto."), false, 6);

    wxScrolledWindow* itemScrolledWindow224 = new wxScrolledWindow( itemNotebook78, ID_PGCATEGORIA, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow224->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer225 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow224->SetSizer(itemBoxSizer225);

    wxFlexGridSizer* itemFlexGridSizer226 = new wxFlexGridSizer(0, 4, 0, 0);
    itemBoxSizer225->Add(itemFlexGridSizer226, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText227 = new wxStaticText( itemScrolledWindow224, wxID_STATIC, wxGetTranslation(wxString(wxT("Descri")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer226->Add(itemStaticText227, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl228 = new wxTextCtrl( itemScrolledWindow224, ID_CATEGORIA_DESC, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer226->Add(itemTextCtrl228, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer229Static = new wxStaticBox(itemScrolledWindow224, wxID_ANY, _("Lista de categorias"));
    wxStaticBoxSizer* itemStaticBoxSizer229 = new wxStaticBoxSizer(itemStaticBoxSizer229Static, wxHORIZONTAL);
    itemBoxSizer225->Add(itemStaticBoxSizer229, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl230 = new wxListCtrl( itemScrolledWindow224, ID_CATEGORIA_GRID, wxDefaultPosition, wxSize(600, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemStaticBoxSizer229->Add(itemListCtrl230, 1, wxGROW|wxALL, 5);

    itemScrolledWindow224->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow224, _("Categorias"), false, 7);

    wxScrolledWindow* itemScrolledWindow231 = new wxScrolledWindow( itemNotebook78, ID_PGALIQUOTAS, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL );
    itemScrolledWindow231->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer232 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow231->SetSizer(itemBoxSizer232);

    wxFlexGridSizer* itemFlexGridSizer233 = new wxFlexGridSizer(0, 6, 0, 0);
    itemBoxSizer232->Add(itemFlexGridSizer233, 0, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText234 = new wxStaticText( itemScrolledWindow231, wxID_STATIC, wxGetTranslation(wxString(wxT("Descri")) + (wxChar) 0x00E7 + (wxChar) 0x00E3 + wxT("o")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer233->Add(itemStaticText234, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl235 = new wxTextCtrl( itemScrolledWindow231, ID_ALIQUOTAS_DESC, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer233->Add(itemTextCtrl235, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText236 = new wxStaticText( itemScrolledWindow231, wxID_STATIC, _("Abreviatura"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer233->Add(itemStaticText236, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl237 = new wxTextCtrl( itemScrolledWindow231, ID_ALIQUOTAS_ABREV, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_CAPITALIZE );
    itemFlexGridSizer233->Add(itemTextCtrl237, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText238 = new wxStaticText( itemScrolledWindow231, wxID_STATIC, _("ISS"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer233->Add(itemStaticText238, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox239 = new wxCheckBox( itemScrolledWindow231, ID_ALIQUOTAS_TIPO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox239->SetValue(false);
    itemFlexGridSizer233->Add(itemCheckBox239, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer240Static = new wxStaticBox(itemScrolledWindow231, wxID_ANY, wxGetTranslation(wxString(wxT("Lista de al")) + (wxChar) 0x00ED + wxT("quotas")));
    wxStaticBoxSizer* itemStaticBoxSizer240 = new wxStaticBoxSizer(itemStaticBoxSizer240Static, wxHORIZONTAL);
    itemBoxSizer232->Add(itemStaticBoxSizer240, 1, wxGROW|wxALL, 5);
    wxListCtrl* itemListCtrl241 = new wxListCtrl( itemScrolledWindow231, ID_ALIQUOTAS_GRID, wxDefaultPosition, wxSize(600, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxSUNKEN_BORDER );
    itemStaticBoxSizer240->Add(itemListCtrl241, 1, wxGROW|wxALL, 5);

    itemScrolledWindow231->SetMinSize(wxDefaultSize);
    itemNotebook78->AddPage(itemScrolledWindow231, wxGetTranslation(wxString(wxT("Al")) + (wxChar) 0x00ED + wxT("quotas")), false, 8);

    itemBoxSizer77->Add(itemNotebook78, 1, wxGROW|wxALL, 5);

    wxStatusBar* itemStatusBar242 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar242->SetFieldsCount(3);
    itemFrame1->SetStatusBar(itemStatusBar242);

    // Connect events and objects
    itemToolBar62->Connect(ID_TOOLBAR, wxEVT_RIGHT_DOWN, wxMouseEventHandler(VilaVilela::OnRightDown), NULL, this);
    itemToolBar62->Connect(ID_TOOLBAR, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl63->Connect(ID_SEARCHCTRL, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemDatePickerCtrl64->Connect(ID_SEARCHDATE1, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemDatePickerCtrl65->Connect(ID_SEARCHDATE2, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemToggleButton66->Connect(ID_TOOLFILTER, wxEVT_RIGHT_DOWN, wxMouseEventHandler(VilaVilela::OnRightDown), NULL, this);
    itemNotebook78->Connect(ID_NOTEBOOK, wxEVT_RIGHT_DOWN, wxMouseEventHandler(VilaVilela::OnRightDown), NULL, this);
    itemNotebook78->Connect(ID_NOTEBOOK, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemScrolledWindow79->Connect(ID_PGVENDAS, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl83->Connect(ID_VENDAS_CLIENTE, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemChoice85->Connect(ID_VENDAS_FORMAPAGTO, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl87->Connect(ID_VENDAS_NO_NOTA, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemDatePickerCtrl89->Connect(ID_VENDAS_DATA, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl94->Connect(ID_VENDAS_INSPROD_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl98->Connect(ID_VENDAS_TOTAL, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl104->Connect(ID_VENDAS_DESCONTO, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl107->Connect(ID_VENDAS_VALREC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl110->Connect(ID_VENDAS_TOTAL_GERAL, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl113->Connect(ID_VENDAS_TROCO, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl116->Connect(ID_VENDAS_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemChoice122->Connect(ID_COMPRAS_FORNEC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemDatePickerCtrl124->Connect(ID_COMPRAS_DATA, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl126->Connect(ID_COMPRAS_NO_NOTA, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemBitmapButton128->Connect(ID_COMPRAS_BT_INS_PROD, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl129->Connect(ID_COMPRAS_PROD_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl134->Connect(ID_COMPRAS_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl139->Connect(ID_UNIDADE_DESC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl141->Connect(ID_UNIDADE_ABREV, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl143->Connect(ID_UNIDADE_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl148->Connect(ID_CLIENT_NOME, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl150->Connect(ID_CLIENT_END, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl152->Connect(ID_CLIENT_COMP, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl154->Connect(ID_CLIENT_EMAIL, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemDatePickerCtrl156->Connect(ID_CLIENT_DATANASC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl158->Connect(ID_CLIENT_CPF, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemChoice164->Connect(ID_CBCLIENTFONES, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl166->Connect(ID_CLIENT_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemScrolledWindow167->Connect(ID_PGFORNEC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl171->Connect(ID_FORNEC_NOME, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl173->Connect(ID_FORNEC_END, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl175->Connect(ID_FORNEC_COMP, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl177->Connect(ID_FORNEC_EMAIL, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl179->Connect(ID_FORNEC_CONTATO, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl181->Connect(ID_FORNEC_CNPJ, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemChoice187->Connect(ID_CBFORNECFONES, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl189->Connect(ID_FORNEC_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemScrolledWindow190->Connect(ID_PGPRODUTOS, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl194->Connect(ID_PROD_NOME, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl196->Connect(ID_PROD_DESC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl198->Connect(ID_PROD_VALUNIT, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemChoice200->Connect(ID_PROD_UNIT, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemChoice202->Connect(ID_PROD_CATEGORIA, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl204->Connect(ID_PROD_BARCOD, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemChoice207->Connect(ID_PROD_ICMS, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl216->Connect(ID_PROD_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemScrolledWindow217->Connect(ID_PGFORMAPAGTO, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl221->Connect(ID_FORMAPGTO_DESC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl223->Connect(ID_FORMAPGTO_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemScrolledWindow224->Connect(ID_PGCATEGORIA, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl228->Connect(ID_CATEGORIA_DESC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl230->Connect(ID_CATEGORIA_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl235->Connect(ID_ALIQUOTAS_DESC, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemTextCtrl237->Connect(ID_ALIQUOTAS_ABREV, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
    itemListCtrl241->Connect(ID_ALIQUOTAS_GRID, wxEVT_KEY_DOWN, wxKeyEventHandler(VilaVilela::OnKeyDown), NULL, this);
////@end VilaVilela content construction

				wxToolBar *toolbar=GetToolBar();
				wxMenuBar *mnbar=GetMenuBar();
				wxMenu *menu=mnbar->GetMenu(4);
				_tool[0]=toolbar->FindById(ID_TOOLFIRSTREC);
				_mnitem[0]=menu->FindItem(ID_TOOLFIRSTREC);
				_tool[1]=toolbar->FindById(ID_TOOLPREVREC);
				_mnitem[1]=menu->FindItem(ID_TOOLPREVREC);
				_tool[2]=toolbar->FindById(ID_TOOLNEXTREC);
				_mnitem[2]=menu->FindItem(ID_TOOLNEXTREC);
				_tool[3]=toolbar->FindById(ID_TOOLLASTREC);
				_mnitem[3]=menu->FindItem(ID_TOOLLASTREC);
				_tool[4]=toolbar->FindById(ID_TOOLEdit);
				_mnitem[4]=menu->FindItem(ID_TOOLEdit);
				_tool[5]=toolbar->FindById(ID_TOOLDelete);
				_mnitem[5]=menu->FindItem(ID_TOOLDelete);
				_tool[6]=toolbar->FindById(ID_MN_PESQPROD);
				_mnitem[6]=menu->FindItem(ID_MN_PESQPROD);
				
			
}


/*
 * wxEVT_SIZE event handler for ID_MAIN
 */

void VilaVilela::OnSize(wxSizeEvent& event) {

////@begin wxEVT_SIZE event handler for ID_MAIN in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_SIZE event handler for ID_MAIN in VilaVilela.
}


void VilaVilela::OnMenuiRestaurabkupClick(wxCommandEvent& event) {
	wxString caption = ___("Escolha um arquivo de backup");
	wxString wildcard =___("vla backupp (*.vla)|*.vla");
	wxString defaultDir = _("./bkups/");
	wxString defaultFilename = wxEmptyString;
	wxFileDialog dialog(this, caption, defaultDir, defaultFilename,	wildcard, wxFD_OPEN);
	dialog.Centre();
	if (dialog.ShowModal() == wxID_OK) {
		wxString fn=dialog.GetPath(),dr=dialog.GetDirectory();
		_restaura_do_bkup(dr,fn);
		for (int i=0;i<NUM_NOTEBOOK_TABS;i++) {
			TableInfo *tb=lsttableinfo.find_by_pageid(_pageIds[i]);
			if (tb)
				_fetch_and_update_gl_res(tb->indtablename,__DB_UPD_MODE_FIRST);
			_db_update(_pageIds[i],false);
		}
	}
	event;
}

void VilaVilela::OnMENUICopiaSegClick(wxCommandEvent& event) {
	event;
	Palavra query,tbquery;
	sql_ResultSet *res;
	char dir[256];
	getcwd(dir,256);
	if (!wxDirExists(_("./bkups"))) {
		wxMkdir(_("./bkups"));
	}
	wxString str,filename,zipfname;
	wxString wdir,tmpstr;
	wxUint8 data;
	wxDateTime datetime=wxDateTime::Now();
	filename=_("backup");
	filename.Append(datetime.Format());
	filename.Append(_(".vla"));
	filename.Replace(_("/"),_("-"));
	filename.Replace(_(" "),_("_"));
	filename.Replace(_(":"),_("-"));
	wdir=wxString::FromAscii(dir);
	wdir.Replace(_("\\"),_("/"));
	wdir.Append(_("/bkups/"));
	zipfname=wdir;
	zipfname.Append(filename);
	wxFFileOutputStream out(zipfname);
	wxZipOutputStream zip(out);
	wxDataOutputStream txt(zip);

#ifdef VILAVIELASQLITE3
	int rc;
	sqlite3 *pFile;
	sqlite3_backup *pBackup;
	query.append(wdir.ToAscii());
	query.append("bkup.db");
	rc = sqlite3_open(query.c_str(), &pFile);
	if (rc==SQLITE_OK) {
		pBackup = sqlite3_backup_init(pFile, "main", glb_stmt.db, "main");
		if (pBackup) {
			do {
				rc = sqlite3_backup_step(pBackup, 5);   // xProgress(sqlite3_backup_remaining(pBackup),sqlite3_backup_pagecount(pBackup));
				if (rc==SQLITE_OK || rc==SQLITE_BUSY || rc==SQLITE_LOCKED) {
					sqlite3_sleep(250);
				}
			}
			while (rc==SQLITE_OK || rc==SQLITE_BUSY || rc==SQLITE_LOCKED);
			(void) sqlite3_backup_finish(pBackup);
		}
		rc = sqlite3_errcode(pFile);
	}
	sqlite3_close(pFile);
	zip.PutNextEntry(_("bkup.db"));
	filename=wxString::FromAscii(query.c_str());
	wxFFileInputStream in(filename);
	wxDataInputStream file(in);
	if (file.IsOk()) {
		do {
			file >> data; // access data
			txt << data;
		}
		while (file.IsOk());
	}
	remove(filename.ToAscii());
#else
#ifdef VILAVIELAPOSTGRESQL
	tbquery="SELECT relname FROM pg_stat_user_tables WHERE schemaname='public'";
#endif
#ifdef VILAVIELAMYSQL
	tbquery="SHOW TABLES";
#endif
	Palavra tablename;
	if ((res=_execquerywithresult(tbquery)) !=NULL&&_nextrow(res)) {
		do {
			tablename=_getstringSQL(res,1);
#ifdef VILAVIELAMYSQL
			query="SELECT * INTO OUTFILE ";
			query.append("'");
			query.append(wdir.ToAscii());
			query.append(tablename);
			query.append(".dat'");
			//query.append(" FIELDS TERMINATED BY '|' OPTIONALLY ENCLOSED BY '\\'' LINES STARTING BY '_' TERMINATED BY '\\n'");
			query.append(" FROM ");
			query.append(tablename);
#endif
#ifdef VILAVIELAPOSTGRESQL
			query="COPY ";
			query.append(tablename);
			query.append(" TO '");
			query.append(wdir.ToAscii());
			query.append(tablename);
			query.append(".dat'");
#endif
			_execquery(query);
			str=_("");
			tmpstr=wxString::FromAscii(tablename.c_str());
			str.Append(tmpstr);
			str.Append(_(".dat"));
			zip.PutNextEntry(str);
			tmpstr=wxString::FromAscii(tablename.c_str());
			filename=wdir;
			filename.Append(tmpstr);
			filename.Append(_(".dat"));
			wxFFileInputStream in(filename);
			wxDataInputStream file(in);
			if (file.IsOk())
				do {
					file>>data; // access data
					txt<<data;
				}
				while (file.IsOk());

		}
		while (_nextrow(res));

		if (_firstrow(res)) {
			do {
				tablename=_getstringSQL(res,1);
				filename=wdir;
				tmpstr=wxString::FromAscii(tablename.c_str());
				filename.Append(tmpstr);
				filename.Append(_(".dat"));
				remove(filename.ToAscii());
			}
			while (_nextrow(res));
		}

		_deleteresult(&res);
	}

#endif
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOL
 */

void VilaVilela::OnToolfirstrecClick(wxCommandEvent& event) {
	if (db_mode!=__DB_MODE_READ)
		return;
	int pageid=_get_pageid();
	TableInfo *tb=lsttableinfo.find_by_pageid(pageid);
	if (tb) {
		_fetch_and_update_gl_res(tb->indtablename,__DB_UPD_MODE_FIRST);
		_db_update(pageid);
		_EnableTool(ID_TOOLFIRSTREC,false);
		_EnableTool(ID_TOOLPREVREC,false);
		_EnableTool(ID_TOOLLASTREC,true);
		_EnableTool(ID_TOOLNEXTREC,true);
	}
}


/*
 * Should we show tooltips?
 */

bool VilaVilela::ShowToolTips() {
	return true;
}




void VilaVilela::OnTOOLInsertClick(wxCommandEvent& event) {
 verificaestadoimpressora();
	if (!_verificaconexao(&glb_stmt))
		return ;
	wxToolBar* tb=this->GetToolBar();
	int pageid=_get_pageid();
	bool cancelado=false;
	if (db_mode==__DB_MODE_READ) {
		if (pageid==ID_PGVENDAS) {
#ifndef  IGNORETESTEIMPRESSORA
			TESTA_IMPRESSORA_VALIDA();
#endif
			if(admin){
				wxMessageBox(_("Administrador, para inserir nova venda, execute o logout do modo administrador(Ctrl+L)."));
				return; 
			}
			selec_cliente *dlg=new selec_cliente(this);
			char _cpf[20]="",_nome[30]="",_end[80]="";
			wxChoice* cb;
			if (dlg->ShowModal() ==wxID_OK) {
				cb= (wxChoice*) dlg->FindWindowById(ID_CBSELCLIENTE, (wxWindow*) dlg);
				if (cb->GetSelection() >=0) {
					int idcliente= ((chcIdRef*) cb->GetClientObject(cb->GetSelection()))->val;
					sql_ResultSet *res;
					Palavra query;
					query="SELECT cpf,nome,endr FROM cliente WHERE idcliente=";
					char tmpstr[16];
					sprintf(tmpstr,"%d",idcliente);
					query.append(tmpstr);
					res=_execquerywithresult(query);
					if (res!=NULL&&_nextrow(res)) {
						wxChoice* cbx= (wxChoice*) this->FindWindowById(ID_CBSELCLIENTE,this);
						wxString cpf=_getstring(res,1),nome=_getstring(res,2),end=_getstring(res,3);
						strcpy(_cpf,cpf.ToAscii());
						strcpy(_nome,nome.ToAscii());
						strcpy(_end,end.ToAscii());
						_cpf[19]=0;
						_nome[29]=0;
						_end[79]=0;
						wxTextCtrl* edx= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_CLIENTE,this);
						edx->SetValue(nome);
						edx->SetClientObject((wxClientData*)(new chcIdRef(idcliente)));
						_deleteresult(&res);
					}
				}
			}
			if (_abre_cupom(_cpf,_nome,_end)!=1)
				return;



		}
		_set_dbmode(pageid,__DB_MODE_INSERT);
		wxBitmap savebmp(this->GetBitmapResource(_("images/savechanges.png")));
		tb->SetToolNormalBitmap(ID_TOOLInsert,savebmp);
		_EnableTool(ID_TOOLCancel,true);
		_EnableTool(ID_TOOLEdit,false);
		_EnableTool(ID_TOOLDelete,false);
		_EnableTool(ID_TOOLFIRSTREC,false);
		_EnableTool(ID_TOOLLASTREC,false);
		_EnableTool(ID_TOOLNEXTREC,false);
		_EnableTool(ID_TOOLPREVREC,false);
		_EnableTool(ID_MN_PESQPROD,true);
		tb->SetToolShortHelp(ID_TOOLInsert,_("Salvar[F1]"));
	//	tb->SetTool(ID_TOOLInsert,_("Salvar[F1]"));
		_clearcontrols(pageid,true);
		_selectfirsttxtctrl(pageid);
		_show_hide_auxcontrols(pageid);
		if (pageid==ID_PGVENDAS) {
			wxChoice	*cb= (wxChoice*) this->FindWindowById(ID_VENDAS_FORMAPAGTO,this);
			int index=cb->FindString(_("Dinheiro"));
			if (index>=0)
				cb->SetSelection(index);
			wxTextCtrl* edx= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_NO_NOTA,this);
			char ncupom[7]="0";
			Palavra query,tmpsqlstr;
	  sql_ResultSet *res2;
			query="SELECT max(idvenda) FROM vendas";
			if ((res2=_execquerywithresult(query)) !=NULL&&_nextrow(res2)) {				
				tmpsqlstr=_getstringSQL(res2,1);
				strcpy(ncupom,tmpsqlstr.c_str());			
				_deleteresult(&res2);
			}
			_NumeroCupom(ncupom);
			edx->SetValue(wxString::FromAscii(ncupom));
		}
		else
			if (pageid==ID_PGPRODUTOS) {
				wxChoice	*cb= (wxChoice*) this->FindWindowById(ID_PROD_ICMS,this);
				int index=cb->FindString(_("Isentos ICMS tipo I"));
				if (index>=0)
					cb->SetSelection(index);
			}
	}
	else
		if (db_mode==__DB_MODE_INSERT) {
			if (pageid==ID_PGVENDAS) {
#ifndef  IGNORETESTEIMPRESSORA
				TESTA_IMPRESSORA_VALIDA();
#endif
				char cFormaPgto[16],cValorAcresDesc[16],cValorPago[16];
				bool desconto_percentual;
			
				wxListCtrl *lstvalpago= (wxListCtrl *) this->FindWindowById(ID_VENDAS_VALREC,this);
				wxTextCtrl *eddesconto= (wxTextCtrl *) this->FindWindowById(ID_VENDAS_DESCONTO,this),
				                                    *edsubtotal= (wxTextCtrl *) this->FindWindowById(ID_VENDAS_TOTAL,this);
				wxCheckBox *chkdescperc= (wxCheckBox *) this->FindWindowById(ID_CHK_PERCENTUAL,this);
				wxChoice *cbformapgto= (wxChoice *) this->FindWindowById(ID_VENDAS_FORMAPAGTO,this);
				float fsubtotal=venda_total,fdesc=atof(eddesconto->GetValue().ToAscii()),ftotal,fvalrec=0;
				long item=-1;
				wxString tmstr;
				for (;;) {
					item = lstvalpago->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
					if (item == -1)
						break;
					tmstr=get_lstctrl_column_text(lstvalpago,item,1);
					fvalrec+=atof(tmstr.ToAscii());					
				}
				

				desconto_percentual=chkdescperc->GetValue();
				strcpy(cFormaPgto,cbformapgto->GetString(cbformapgto->GetSelection()).ToAscii());
				strcpy(cValorAcresDesc,eddesconto->GetValue().ToAscii());
				removechar(cValorAcresDesc,'.');
				removechar(cValorAcresDesc,',');			
				if (desconto_percentual)
					ftotal=fsubtotal-fdesc*0.01*fsubtotal;
				else
					ftotal=fsubtotal-fdesc;
				if (fvalrec<(ftotal-0.01)) {
					wxMessageBox(___("o valor recebido não pode ser menor que o total!!\nAdicione novo pagamento."));
					return;
				}
				sprintf(cValorPago,"%.2f",fvalrec);
				removechar(cValorPago,'.');
				removechar(cValorPago,',');
				printf("cValorPago=%s\n",cValorPago);
		
				wxTextCtrl* ed= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_CLIENTE,this);
				chcIdRef* cd= (chcIdRef*) ed->GetClientObject();
				wxChoice* cb= (wxChoice*) this->FindWindowById(ID_VENDAS_FORMAPAGTO,this);
				char _cpf[20]="",_nome[30]="",_end[80]="",Meio_de_pagamento[20]="";
				strcpy(Meio_de_pagamento,cb->GetString(cb->GetSelection()).ToAscii());
				if (cd) {
					int idcliente=cd->val;
					sql_ResultSet *res;
					Palavra query;
					query="SELECT cpf,nome,endr FROM cliente WHERE idcliente=";
					char tmpstr[16];
					sprintf(tmpstr,"%d",idcliente);
					query.append(tmpstr);
					res=_execquerywithresult(query);
					if (res!=NULL&&_nextrow(res)) {
						wxString cpf=_getstring(res,1),nome=_getstring(res,2),end=_getstring(res,3);
						strcpy(_cpf,cpf.ToAscii());
						strcpy(_nome,nome.ToAscii());
						strcpy(_end,end.ToAscii());
						_cpf[19]=0;
						_nome[29]=0;
						_end[79]=0;
						_deleteresult(&res);
					}
				}
				if (fsubtotal>0.0) {
					int retimp;
					retimp=_FechaCupom(cFormaPgto,desconto_percentual,cValorAcresDesc,cValorPago);
					if (retimp!=1) {
						_cancela_cupom(Meio_de_pagamento,_cpf,_nome,_end);
						cancelado=true;
					}
					if (!cancelado)
						registro_R04(Meio_de_pagamento,_nome,_cpf,false);
     _RelatorioGerencial("18/03/2015 14:53:18   GNF:000001      COO:000011\n");
    
     _FechaRelatorioGerencial();
				}
				else {
					_cancela_cupom(Meio_de_pagamento,_cpf,_nome,_end);
					cancelado=true;

				}
			}
			if (_insert_values(pageid)||cancelado) {
				//if(!cancelado&&(pageid==ID_PGVENDAS)){

					_set_dbmode(pageid,__DB_MODE_READ);
					wxBitmap savebmp(this->GetBitmapResource(_("images/DataContainer_NewRecordHS.png")));
					tb->SetToolNormalBitmap(ID_TOOLInsert,savebmp);
					_EnableTool(ID_TOOLCancel,false);
					_EnableTool(ID_TOOLEdit,true);
					_EnableTool(ID_TOOLDelete,true);
					_EnableTool(ID_TOOLFIRSTREC,true);
					_EnableTool(ID_TOOLLASTREC,true);
					_EnableTool(ID_TOOLNEXTREC,true);
					_EnableTool(ID_TOOLPREVREC,true);
					_EnableTool(ID_MN_PESQPROD,false);
					tb->SetToolShortHelp(ID_TOOLInsert,_("Inserir[F1]"));
					_show_hide_auxcontrols(pageid,false,false);
			//	}
			}
		}


}


void VilaVilela::OnTOOLEditClick(wxCommandEvent& event) {
	wxToolBar* tb=this->GetToolBar();
	int pageid=_get_pageid();
#ifndef TESTANDO
	if (pageid==ID_PGVENDAS) {
		wxMessageBox(___("Não é possível editar uma venda já realizada!"));
		return;
	}
#endif
	if (db_mode==__DB_MODE_READ) {
		_set_dbmode(pageid,__DB_MODE_EDIT);
		wxBitmap savebmp(this->GetBitmapResource(_("images/savechanges.png")));
		tb->SetToolNormalBitmap(ID_TOOLEdit,savebmp);
		_EnableTool(ID_TOOLCancel,true);
		_EnableTool(ID_TOOLInsert,false);
		_EnableTool(ID_TOOLDelete,false);
		_EnableTool(ID_TOOLFIRSTREC,false);
		_EnableTool(ID_TOOLLASTREC,false);
		_EnableTool(ID_TOOLNEXTREC,false);
		_EnableTool(ID_TOOLPREVREC,false);
		tb->SetToolShortHelp(ID_TOOLEdit,_("Salvar(Alt+Insert)"));
		_selectfirsttxtctrl(pageid);
	}
	else
		if (db_mode==__DB_MODE_EDIT) {
			_set_dbmode(pageid,__DB_MODE_READ);
			wxBitmap savebmp(this->GetBitmapResource(_("images/005_Task_16x16_72.png")));
			tb->SetToolNormalBitmap(ID_TOOLEdit,savebmp);
			_EnableTool(ID_TOOLCancel,false);
			_EnableTool(ID_TOOLInsert,true);
			_EnableTool(ID_TOOLDelete,true);
			_EnableTool(ID_TOOLFIRSTREC,true);
			_EnableTool(ID_TOOLLASTREC,true);
			_EnableTool(ID_TOOLNEXTREC,true);
			_EnableTool(ID_TOOLPREVREC,true);
			tb->SetToolShortHelp(ID_TOOLEdit,_("Editar(Alt+Insert)"));
			_edit_values(pageid);
		}
}


void VilaVilela::OnTOOLDeleteClick(wxCommandEvent& event) {
	if (db_mode!=__DB_MODE_READ)
		return;
	int pageid=_get_pageid();
#ifndef TESTANDO
	if (pageid==ID_PGVENDAS) {
		wxMessageBox(___("Não é permitido excluir uma venda efetuada,\nse quiser cancelar o último cupom e excluir a \núltima venda clique no menu 'Cancelar último cupom'!"));
		return;
	}
#endif
	if (db_mode==__DB_MODE_READ) {
		wxMessageDialog dialog(this,___("Tem certeza que deseja excluir a gravação atual, \nisto não pode ser desfeito!!!"),
		                       ___("Confirmar exclusão"),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION);
		dialog.Centre();
		if (dialog.ShowModal() ==wxID_YES) {
			_delete_row(pageid);
		}
	}
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLCancel
 */

void VilaVilela::OnTOOLCancelClick(wxCommandEvent& event) {
	if (db_mode==__DB_MODE_READ)
		return;
	wxToolBar* tb=this->GetToolBar();
	int pageid=_get_pageid();
	if (pageid==ID_PGVENDAS) {
#ifndef  IGNORETESTEIMPRESSORA
		TESTA_IMPRESSORA_VALIDA();
#endif
		wxTextCtrl* ed= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_CLIENTE,this);
		chcIdRef* cd= (chcIdRef*) ed->GetClientObject();
		wxChoice* cb= (wxChoice*) this->FindWindowById(ID_VENDAS_FORMAPAGTO,this);
		char _cpf[20]="",_nome[30]="",_end[80]="",Meio_de_pagamento[20]="";
		strcpy(Meio_de_pagamento,cb->GetString(cb->GetSelection()).ToAscii());
		if (cd) {
			int idcliente=cd->val;
			sql_ResultSet *res;
			Palavra query;
			query="SELECT cpf,nome,endr FROM cliente WHERE idcliente=";
			char tmpstr[16];
			sprintf(tmpstr,"%d",idcliente);
			query.append(tmpstr);
			res=_execquerywithresult(query);
			if (res!=NULL&&_nextrow(res)) {
				wxChoice* cbx= (wxChoice*) this->FindWindowById(ID_CBSELCLIENTE,this);
				wxString cpf=_getstring(res,1),nome=_getstring(res,2),end=_getstring(res,3);
				strcpy(_cpf,cpf.ToAscii());
				strcpy(_nome,nome.ToAscii());
				strcpy(_end,end.ToAscii());
				_cpf[19]=0;
				_nome[29]=0;
				_end[79]=0;
				_deleteresult(&res);
			}
		}
		_cancela_cupom(Meio_de_pagamento,_cpf,_nome,_end,true);
		
			wxWindow::FindWindowById(ID_PANEL_VENDAS1,this)->Layout();
			wxWindow::FindWindowById(ID_PGVENDAS,this)->Layout();
	}
	if (db_mode==__DB_MODE_INSERT) {
		wxBitmap savebmp(this->GetBitmapResource(_("images/DataContainer_NewRecordHS.png")));
		tb->SetToolNormalBitmap(ID_TOOLInsert,savebmp);
		tb->SetToolShortHelp(ID_TOOLInsert,_("Inserir(Ctrl+Insert)"));

		_show_hide_auxcontrols(pageid,false);
	}
	else
		if (db_mode==__DB_MODE_EDIT) {
			wxBitmap savebmp(this->GetBitmapResource(_("images/005_Task_16x16_72.png")));
			tb->SetToolNormalBitmap(ID_TOOLEdit,savebmp);
			tb->SetToolShortHelp(ID_TOOLEdit,_("Editar(Ctrl+Shift+Insert)"));
		}

	_set_dbmode(pageid,__DB_MODE_READ);
	_db_update(pageid);
	_EnableTool(ID_TOOLCancel,false);
	_EnableTool(ID_MN_PESQPROD,false);
}

void VilaVilela::_EnableTool(int id,bool enable){
	wxToolBar* tb=this->GetToolBar();
	wxMenuBar *mnbar=this->GetMenuBar();
	if(tb->FindById(id))
	 tb->EnableTool(id,enable);
	if(mnbar->FindItem(id))
 	mnbar->Enable(id,enable);
}

/*
 * wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
 */



void VilaVilela::OnNotebookPageChanged(wxNotebookEvent& event) {
	int pageid=_get_pageid();


	TableInfo *tb=lsttableinfo.find_by_pageid(pageid);
	if (tb) {
		wxToolBar* tolb=this->GetToolBar();
		//wxToolBarToolBase *tbi= tolb->FindById(ID_TOOLFILTER);
		wxToggleButton* tgb=(wxToggleButton*)wxWindow::FindWindowById(ID_TOOLFILTER,this);
		//tbi->Toggle(isfiltered[tb->indtablename]);
		/*if(isfiltered[tb->indtablename])
			tgb->SetLabel(_("Limpar Filtro"));
		else
			tgb->SetLabel(_("Filtrar"));*/
		tgb->SetValue(isfiltered[tb->indtablename]);
		//	tolb->Refresh();
		//tbi->SetToggle(isfiltered[tb->indtablename]);
		_show_hide_auxcontrols(pageid,false);
		_db_update(pageid);
		FieldInfo* fi;
		fi=seachfieldinfo[tb->indtablename].fi?seachfieldinfo[tb->indtablename].fi:seachfieldinfo[tb->indtablename].searchfield;
		if (fi) {
			if (fi->field_type==__DB_FIELD_TYPE_DATE) {
				(this->FindWindowById(ID_SEARCHDATE1,this))->Enable();
				(this->FindWindowById(ID_SEARCHDATE2,this))->Enable();
				(this->FindWindowById(ID_SEARCHCTRL,this))->Disable();
			}
			else {
				(this->FindWindowById(ID_SEARCHDATE1,this))->Disable();
				(this->FindWindowById(ID_SEARCHDATE2,this))->Disable();
				(this->FindWindowById(ID_SEARCHCTRL,this))->Enable();
			}
		}
	}
////@begin wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK in VilaVilela.
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLNEXTREC
 */


void VilaVilela::OnToolnextrecClick(wxCommandEvent& event) {
	if (db_mode!=__DB_MODE_READ)
		return;
	_db_walk_around(true);
////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLNEXTREC in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLNEXTREC in VilaVilela.
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOL1
 */

void VilaVilela::OnToolprevrecClick(wxCommandEvent& event) {
	if (db_mode!=__DB_MODE_READ)
		return;
	_db_walk_around(false);
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLLASTREC
 */

void VilaVilela::OnToollastrecClick(wxCommandEvent& event) {
	if (db_mode!=__DB_MODE_READ)
		return;
	int pageid=_get_pageid();
	TableInfo *tb=lsttableinfo.find_by_pageid(pageid);
	if (tb) {
		_fetch_and_update_gl_res(tb->indtablename,__DB_UPD_MODE_LAST);
		_db_update(pageid);
		_EnableTool(ID_TOOLLASTREC,false);
		_EnableTool(ID_TOOLNEXTREC,false);
		_EnableTool(ID_TOOLFIRSTREC,true);
		_EnableTool(ID_TOOLPREVREC,true);
	}
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_INS_FONE
 */

void VilaVilela::OnClientInsFoneClick(wxCommandEvent& event) {
	Palavra query;
	wxString tmpstr;
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			wxTextEntryDialog dialog(this,___("Digite o número do novo fone:"),___("Inserir novo fone"),_(""),wxOK|wxCANCEL);
			dialog.Centre();
			if (dialog.ShowModal() == wxID_OK) {
				query="INSERT INTO fones_cliente(idcliente,numero) VALUES(";
				tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
				query.append(tmpstr.ToAscii());
				query.append(",");
				query.append("'");
				query.append(dialog.GetValue().ToAscii());
				query.append("'");
				query.append(")");
				_execquery(query);
				_db_update(_get_pageid());
			}
		}
	}

////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_INS_FONE in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_INS_FONE in VilaVilela.
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_INS_FONE
 */

void VilaVilela::OnFornecInsFoneClick(wxCommandEvent& event) {
	Palavra query;
	wxString tmpstr;
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			wxTextEntryDialog dialog(this,___("Digite o número do novo fone:"),_("Inserir novo fone"),_(""),wxOK|wxCANCEL);
			dialog.Centre();
			if (dialog.ShowModal() == wxID_OK) {
				query="INSERT INTO fones_fornec(idfornecedor,numero) VALUES(";
				tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
				query.append(tmpstr.ToAscii());
				query.append(",");
				query.append("'");
				query.append(dialog.GetValue().ToAscii());
				query.append("'");
				query.append(")");
				_execquery(query);
				_db_update(_get_pageid());
			}
		}
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_INS_FONE in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_INS_FONE in VilaVilela.
}




void VilaVilela::_grid_update(wxListCtrl* grid,long item) {
	int pageid=_get_pageid();
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			long key;
			wxString str=listctrl_get_colomn_text(grid,item,0);
			str.ToLong(&key);
			db_table_id[tb->indtablename]=key;
			_DbResult *glbres=glb_res[tb->indtablename];
			if (glbres->first()) {
				do {
					if (glbres->current->getint(1) ==key)
						break;
				}
				while (glbres->next());
			}
			_db_update(pageid,false,false);
		}
	}
}


/*
 * wxEVT_KEY_DOWN event handler for ID_CLIENT_GRID
 */

void VilaVilela::OnKeyDown(wxKeyEvent& event) { 
	int pageid=_get_pageid();
	if(pageid!=ID_PGVENDAS){event.Skip();return;}
	int ccode=event.GetKeyCode();
	static char buf[64];
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
			double preco;
			buf[index]=0;
_tentedenovo:
			bool itempesado=false;
			if (strlen(buf)==13&&*buf=='2') {//codigo com item pesado
				itempesado=true;
				char *ptrc=buf+7,tmpcstr[14];
				strcpy(tmpcstr,ptrc);
				tmpcstr[5]=0;
				preco=atoi(tmpcstr)/100.0;
				ptrc=buf+1;
				strcpy(tmpcstr,ptrc);
				tmpcstr[6]=0;
				strcpy(buf,tmpcstr);
			}
			Palavra query;
			wxString strquant;
			sql_ResultSet  *res;
			query="SELECT prod.idproduto,prod.barcode,prod.nome,prod.descricao,unid.abrev,unid.idunidade,prod.val_unit_venda	FROM unidade AS unid,produtos AS prod \
			WHERE  unid.idunidade=prod.idunidade AND prod.barcode='";
			query.append(buf);
			query.append("'");
			if ((res=_execquerywithresult(query)) !=0&&_nextrow(res)) {
				wxString strtmp;
				double quant=1;
				double subtotal;
				strtmp=_getstring(res,7);
				strtmp.ToDouble(&subtotal);
				strtmp=_getstring(res,5);
				strtmp.LowerCase();
				if (strtmp==_("kg")) {
					if (itempesado) {
						quant=preco/subtotal;
					}
					else {//mostra dialogo pesagem
						_showdlg_insprodvenda(_getstring(res,2));
						return;
					}
				}

				wxListCtrl* lstprodvenda= (wxListCtrl*) this->FindWindowById(ID_VENDAS_INSPROD_GRID,this);
				LstCellInfo *lstcellinfo;
				lstcellinfo=new LstCellInfo();
				
				int index=lstprodvenda->GetItemCount();
				strtmp.Printf(_("%03d"),index+1);
				lstcellinfo->novo(0,_getint(res,1),strtmp);
				lstcellinfo->novo(1,_getint(res,1),_getstring(res,2));
				lstcellinfo->novo(2,_getint(res,1),_getstring(res,3));
				lstcellinfo->novo(3,_getint(res,1),_getstring(res,4));
				lstcellinfo->novo(4,_getint(res,6),_getstring(res,5));

				
				strquant.Printf(_("%.3f"),quant);
				lstcellinfo->novo(5,-1,strquant);
				lstcellinfo->novo(6,-1,_getstring(res,7));

				subtotal*=quant;
				strtmp.Printf(_("%.2f"),subtotal);
				lstcellinfo->novo(7,-1,strtmp);

				if (imprimeitemvenda(lstcellinfo)) {
					insert_lstctrl_item(lstprodvenda,lstcellinfo->prm->str,index,NULL,-1);
					int cindex;
					CellInfo* ci;
					for (ci=lstcellinfo->prm->prx,cindex=1;ci;ci=ci->prx,cindex++)
						set_lstctrl_column(lstprodvenda,ci->str,cindex,index,NULL,-1);
					lstprodvenda->SetItemData(index, (long)lstcellinfo);
					venda_total+=subtotal;
					wxTextCtrl* stvaltot= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_TOTAL,this);
					strtmp.Printf(_("%.2f"),venda_total);
					stvaltot->SetValue(strtmp);

					if (lstprodvenda->GetItemCount()>0) {
						lstprodvenda->EnsureVisible(lstprodvenda->GetItemCount()-1);
						lstprodvenda->SetItemState(lstprodvenda->GetItemCount()-1,wxLIST_STATE_SELECTED|wxLIST_STATE_FOCUSED,wxLIST_STATE_SELECTED|wxLIST_STATE_FOCUSED);
					}
				}
				else
					delete lstcellinfo;
				_deleteresult(&res);
			}
			else {
				wxTextEntryDialog dialog(this,___("Digite o código do produto"),___("Produto não cadastrado"),_(""),wxOK | wxCANCEL);
				dialog.Centre(wxBOTH);
				while (dialog.ShowModal() == wxID_OK) {
					
					strcpy(buf,dialog.GetValue().ToAscii());
					if(*buf)
					 goto _tentedenovo;
					//wxMessageBox(dialog.GetValue(), ___("código"));
				}
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
		else event.Skip();
	}
	//
}

/*
 * wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING event handler for ID_NOTEBOOK
 */

void VilaVilela::OnNotebookPageChanging(wxNotebookEvent& event) {
	int sel=_get_pageid();
	if (!admin&&sel==ID_PGVENDAS) {
		event.Veto();
		return;
	}
	if (db_mode!=__DB_MODE_READ) {
		wxMessageDialog dialog(this,
		                       ___("Você está editando ou inserindo uma nova gravação!\n\
Se quiser cancelar a edição ou inserção clique em Sim.\n\
Caso contrário clique em não pra retornar à edição/inserção."),
		                       ___("Confirme transição de abas"),	wxNO_DEFAULT|wxYES_NO);
		wxCommandEvent eventcancel;
		dialog.Centre();
		switch (dialog.ShowModal()) {
		case wxID_YES:
			OnTOOLCancelClick(eventcancel);
			break;
		case wxID_NO:
			event.Veto();
			return;
		}
	}
////@begin wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING event handler for ID_NOTEBOOK in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING event handler for ID_NOTEBOOK in VilaVilela.
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_COMPRAS_INS_PROD
 */


bool assertvalueisfloat(wxTextCtrl* edbox,const char* msg) {
	bool retval=true;
	if (edbox->GetValue().IsEmpty()) {
		retval=false;
		wxString tmpstr;
		tmpstr=___(msg);
		wxMessageBox(tmpstr);
		edbox->SetFocus();
	}
	return retval;
}



bool VilaVilela::_insprod(wxWindow *dlg) {
	wxListCtrl* lstprod= (wxListCtrl*) dlg->FindWindowById(ID_INSPROD_LIST,dlg);
	wxListCtrl* lstprodcompra= (wxListCtrl*) this->FindWindowById(ID_COMPRAS_PROD_GRID,this);

	wxString tmpstr;
	long item = -1,i;
	item = lstprod->GetNextItem(item,	wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
	if (item == -1) {
		tmpstr=wxString::FromAscii("por favor selecione um produto");
		wxMessageBox(tmpstr);
		lstprod->SetFocus();
		return false;
	}
	LstCellInfo *lstcellinfo= (LstCellInfo*) lstprod->GetItemData(item);
	wxString buf[6];
	double dbval;
	double intval;
	buf[0]=listctrl_get_colomn_text(lstprod,item,1);
	buf[1]=listctrl_get_colomn_text(lstprod,item,2);

	wxTextCtrl* edbox= (wxTextCtrl*) dlg->FindWindowById(ID_INSPROD_QUANT,dlg);
	if (!assertvalueisfloat(edbox,"por favor preencha a quantidade\nex: 4"))
		return false;
	edbox->GetValue().ToDouble(&intval);
	buf[2].Printf(_("%f"),intval);

	int numloop=7;

	edbox= (wxTextCtrl*) dlg->FindWindowById(ID_INSPROD_VALCOMPRA,dlg);
	if (!assertvalueisfloat(edbox,"por favor preencha o valor unitário da compra\nex: 3.90"))
		return false;
	edbox->GetValue().ToDouble(&dbval);
	buf[4].Printf(_("%.2f"),dbval);
	lstcellinfo->novo(3,-1,buf[2]);

	Palavra query;
	sql_ResultSet  *res2;
	CellInfo *cellinfo=lstcellinfo->find_by_collumn(0);
	query="SELECT val_unit_venda FROM produtos  WHERE idproduto=";
	tmpstr.Printf(_("%d"),cellinfo->reffield);
	query.append(tmpstr.ToAscii());
	if ((res2=vilavielaframe->_execquerywithresult(query)) !=NULL) {
		if (_firstrow(res2)) {
			buf[3].Printf(_("%.2f"),_getdouble(res2,1));
			_deleteresult(&res2);
		}
	}
	lstcellinfo->novo(4,-1,buf[3]);

	lstcellinfo->novo(5,-1,buf[4]);

	double subtotal;
	buf[4].ToDouble(&subtotal);
	subtotal*=intval;
	venda_total+=subtotal;
	buf[5].Printf(_("%.2f"),subtotal);

	i=lstprodcompra->GetItemCount();
	lstprodcompra->InsertItem(i,lstprod->GetItemText(item));
	LstCellInfo* lstcinfo=new LstCellInfo(lstcellinfo);
	lstprodcompra->SetItemPtrData(i, (wxUIntPtr) lstcinfo);
	for (int j=1;j<numloop;j++)
		lstprodcompra->SetItem(i, j, buf[j-1]);

	wxTextCtrl* stvaltot= (wxTextCtrl*) this->FindWindowById(ID_COMPRAS_TOTAL,this);
	tmpstr.Printf(_("%.2f"),venda_total);
	stvaltot->SetValue(tmpstr);
	return true;
}



void VilaVilela::_showdlg_insprod() {
	Inserirproduto *dlg=new Inserirproduto(this);
	dlg->baltimer.Start(1000);
	while (dlg->_ShowModal() == wxID_OK) {
		if (_insprod(dlg)) {
			break;
		}
	}
	dlg->baltimer.Stop();
	fechabalanca(hCom,&oldtermio);
	dlg->Destroy();
}

void VilaVilela::OnComprasBtInsProdClick(wxCommandEvent& event) {
	_showdlg_insprod();

}


/*
 * wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_COMPRAS_PROD_GRID
 */

void VilaVilela::OnComprasProdGridKeyDown(wxListEvent& event) {
	long item;
	wxListCtrl* lstprodcompra= (wxListCtrl*) this->FindWindowById(ID_COMPRAS_PROD_GRID,this);
	switch (event.GetKeyCode())	{
	case WXK_DELETE:
		if (db_mode==__DB_MODE_READ)
			break;
		item = lstprodcompra->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		while (item != -1) {
			lstprodcompra->DeleteItem(item);
			// -1 because the indices were shifted by DeleteItem()
			item = lstprodcompra->GetNextItem(item - 1,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		}
		break;
	}
////@begin wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
}


/*
 * wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_VENDAS_INSPROD_GRID
 */

void VilaVilela::OnVendasInsprodGridKeyDown(wxListEvent& event) {
	wxListCtrl* lstprodvenda= (wxListCtrl*) this->FindWindowById(ID_VENDAS_INSPROD_GRID,this);
	switch (event.GetKeyCode())	{
	case WXK_DELETE:
		if (db_mode==__DB_MODE_READ)
			break;
		wxListCtrl* lstprod=(wxListCtrl*) event.GetEventObject();
		LstCellInfo* lstcellinfo=(LstCellInfo*) event.m_item.m_data;
		if (lstcellinfo->find_by_collumn(5)->str==_("0"))
			break;
		if (_cancelaitem(lstprod,lstcellinfo,event.m_item.GetId())) {
			
			wxFont font=event.m_item.GetFont();
#ifndef WIN32
			font.SetStrikethrough(true);
#endif
			lstprod->SetItemFont(event.m_itemIndex,font);
			lstprod->SetItemBackgroundColour(event.m_itemIndex,wxColour(255,0,0));printf("ok1\n");
			set_lstctrl_column(lstprod,"0",5,event.m_itemIndex,NULL,-1);printf("ok2\n");
			set_lstctrl_column(lstprod,"0",7,event.m_itemIndex,NULL,-1);printf("ok3\n");
			lstcellinfo->find_by_collumn(5)->str=_("0");printf("ok4\n"); 
			//lstcellinfo->find_by_collumn(7)->str=_("0");printf("ok5\n");
			printf("event.m_itemIndex=%ld,event.m_item=%ld\n",event.m_itemIndex,event.m_item.GetId());
			//event.Veto();return;
		}
		/*item = lstprodvenda->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		while (item != -1) {
			lstprodvenda->DeleteItem(item);
			// -1 because the indices were shifted by DeleteItem()
			item = lstprodvenda->GetNextItem(item - 1,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		}*/
		break;
	}
	wxKeyEvent keyevt;
	keyevt.m_keyCode=event.GetKeyCode();
	OnKeyDown(keyevt);
////@begin wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
}

wxString get_lstctrl_column_text(wxListCtrl* lstctrl,long item,int indcolumn) {
	wxListItem info;
	info.m_itemId=item;
	info.m_col = indcolumn;
	info.m_mask = wxLIST_MASK_TEXT;
	lstctrl->GetItem(info);
	return info.m_text;
}
wxString convertUTF8ToLatin1(const wxString& szValue) {
	wxCSConv ISOConv(wxFONTENCODING_ISO8859_1);
	return (wxString(szValue.wc_str(wxConvUTF8), ISOConv));
}
bool VilaVilela::imprimeitemvenda(LstCellInfo *lstcinfo) {
 #ifndef  IGNORETESTEIMPRESSORA
	TESTA_IMPRESSORA_VALIDABOOL();
#endif
	CellInfo *cellinfo=lstcinfo->find_by_collumn(2);
	if (cellinfo) {
  char cCodigo[32], cDescricao[256], cAliquota[32]={0}, cTipoQtde[32], cValor[32], cQtde[32], cUnidade[32];
		Palavra query;
		sql_ResultSet  *res;
		wxString tmpstr;
		query="SELECT p.barcode,a.abrev,u.tipo FROM produtos AS p,unidade AS u,aliquotas AS a WHERE a.idaliquota=p.idaliquota AND u.idunidade=p.idunidade AND p.idproduto=";
		tmpstr.Printf(_("%d"),cellinfo->reffield);
		query.append(tmpstr.ToAscii());
		if ((res=_execquerywithresult(query)) !=NULL&&_nextrow(res)) {
			strcpy(cCodigo,_getstring(res,1).ToAscii());
			strcpy(cAliquota,_getstring(res,2).ToAscii()); 
			strcpy(cTipoQtde,_getstring(res,3).ToAscii());
			_deleteresult(&res);
		}
		//wxString str=convertUTF8ToLatin1(cellinfo->str);
		strcpy(cDescricao,cellinfo->str.ToUTF8());   //descricao
		cellinfo=lstcinfo->find_by_collumn(4);
		strcpy(cUnidade,cellinfo->str.ToAscii());   //unidade
		cellinfo=lstcinfo->find_by_collumn(5);
		strcpy(cQtde,cellinfo->str.ToAscii());   //quantidade
		cellinfo=lstcinfo->find_by_collumn(6);
		strcpy(cValor,cellinfo->str.ToAscii());   //val unit
		//printf("cCodigo=%s,cDescricao=%s,cAliquota=%s,cTipoQtde =%s,cValor =%s,cQtde =%s,cUnidade=%s\n",cCodigo,cDescricao ,cAliquota,cTipoQtde ,cValor ,cQtde ,cUnidade);

		return (_VendeItem(cCodigo,cDescricao ,cAliquota,cTipoQtde ,cValor ,cQtde ,cUnidade)==1);
	}
	return false;
}

bool VilaVilela::_insprodvenda(wxWindow *dlg) {
	wxListCtrl* lstprod= (wxListCtrl*) dlg->FindWindowById(ID_INSPROD_LIST,dlg);
	wxListCtrl* lstprodvenda= (wxListCtrl*) this->FindWindowById(ID_VENDAS_INSPROD_GRID,this);
	wxListItem lstitem;
	wxString tmpstr;
	long item = -1,i;
	item = lstprod->GetNextItem(item,	wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
	if (item == -1) {
		tmpstr=___("por favor selecione um produto!");
		wxMessageBox(tmpstr);
		lstprod->SetFocus();
		return false;
	}
	LstCellInfo *lstcellinfo= (LstCellInfo*) lstprod->GetItemData(item);

	wxString buf[8];
	double intval;

	buf[0].Printf(_("%03d"),lstprodvenda->GetItemCount()+1);
	buf[1]=get_lstctrl_column_text(lstprod,item,0);
	buf[2]=get_lstctrl_column_text(lstprod,item,1);
	buf[3]=get_lstctrl_column_text(lstprod,item,2);
	buf[4]=get_lstctrl_column_text(lstprod,item,3);

	wxTextCtrl* edbox= (wxTextCtrl*) dlg->FindWindowById(ID_INSPROD_QUANT,dlg);
	if (!assertvalueisfloat(edbox,"por favor preencha a quantidade\nex: 3.2"))
		return false;
	edbox->GetValue().ToDouble(&intval);
	buf[5].Printf(_("%.3f"),intval);

	buf[6]=get_lstctrl_column_text(lstprod,item,4);

	double subtotal;
	buf[6].ToDouble(&subtotal);
	subtotal*=intval;
	venda_total+=subtotal;
	buf[7].Printf(_("%.2f"),subtotal);

	int numloop=8;


	i=lstprodvenda->GetItemCount();


	LstCellInfo* lstcinfo=new LstCellInfo();
	lstcinfo->novo(0,lstcellinfo->find_by_collumn(0)->reffield,buf[0]);
	lstcinfo->novo(1,lstcellinfo->find_by_collumn(0)->reffield,buf[1]);
	lstcinfo->novo(2,lstcellinfo->find_by_collumn(0)->reffield,buf[2]);
	lstcinfo->novo(3,lstcellinfo->find_by_collumn(0)->reffield,buf[3]);
	lstcinfo->novo(4,lstcellinfo->find_by_collumn(3)->reffield,buf[4]);
	lstcinfo->novo(5,-1,buf[5]);
	lstcinfo->novo(6,-1,buf[6]);
	if (imprimeitemvenda(lstcinfo)) {
		lstprodvenda->InsertItem(i,buf[0]);
		lstprodvenda->SetItemPtrData(i, (wxUIntPtr) lstcinfo);
		for (int j=1;j<numloop;j++)
			lstprodvenda->SetItem(i, j, buf[j]);
		wxTextCtrl* stvaltot= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_TOTAL,this);
		buf[4].Printf(_("%.2f"),venda_total);
		stvaltot->SetValue(buf[4]);

		if (lstprodvenda->GetItemCount()>0) {
			lstprodvenda->EnsureVisible(lstprodvenda->GetItemCount()-1);
			lstprodvenda->SetItemState(lstprodvenda->GetItemCount()-1,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
		}
	}
	else {
		delete lstcinfo;
		return false;
	}
	return true;
}

void VilaVilela::_showdlg_insprodvenda(const wxString &barcode) {
	Adicionarproduto *dlg=new Adicionarproduto(this);
	dlg->baltimer.Start(1000);
	int idfocus=ID_INSPROD_LIST;
	if(!barcode.IsEmpty()){
		wxListCtrl* lstprod= (wxListCtrl*) wxWindow::FindWindowById(ID_INSPROD_LIST,dlg);
		if(_lstctrl_find(lstprod,barcode,1))
			idfocus=ID_INSPROD_QUANT;
	}
	while (dlg->_ShowModal(idfocus) == wxID_OK) {
		if (_insprodvenda(dlg)) {
			break;
		}
	}
	delete dlg;
	fechabalanca(hCom,&oldtermio);

}

void VilaVilela::OnVendasBtinsprodClick(wxCommandEvent& event) {
	if(_get_pageid()==ID_PGVENDAS)
	 _showdlg_insprodvenda();

}


bool VilaVilela::_cancelaitem(wxListCtrl* lstprod,LstCellInfo *lstcellinfo,long itemindex) {
	char buf[8];
	long item;
	wxString stritem=lstprod->GetItemText(itemindex);
	stritem.ToLong(&item);
	sprintf(buf,"%03ld",item);
	printf("item=%s\n",buf);
	if (_CancelaItem(buf)==1) {
		if (lstcellinfo) {
			CellInfo *cell=lstcellinfo->find_by_collumn(5),*cell1=lstcellinfo->find_by_collumn(6);
			double val,val2;
			wxString strtot;
			cell->str.ToDouble(&val);
			cell1->str.ToDouble(&val2);
			venda_total-= (val*val2);
			wxTextCtrl* stvaltot= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_TOTAL,this);
			strtot.Printf(_("%.2f"),venda_total);
			stvaltot->SetValue(strtot);
			//	delete lstcellinfo;
			//	lstprod->SetItemPtrData(itemindex,0);
			return true;
		}
	}
	return false;
}

void VilaVilela::OnVendasInsprodGridDeleteItem(wxListEvent& event) {

////@begin wxEVT_COMMAND_LIST_DELETE_ITEM event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_DELETE_ITEM event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
}


/*
 * wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_VENDAS_INSPROD_GRID
 */

void VilaVilela::OnVendasInsprodGridDeleteAllItems(wxListEvent& event) {
	wxListCtrl* lstprod= (wxListCtrl*) event.GetEventObject();
	if (lstprod->GetItemCount() >0) {
		LstCellInfo *lstcellinfo;
		long item = -1;
		for (;;) {
			item = lstprod->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
			if (item == -1)
				break;
			lstcellinfo= (LstCellInfo*) lstprod->GetItemData(item);
			if (lstcellinfo) {

				delete lstcellinfo;
				lstprod->SetItemPtrData(item,0);
			}
		}
	}
////@begin wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
}


/*
 * wxEVT_COMMAND_LIST_DELETE_ITEM event handler for ID_COMPRAS_PROD_GRID
 */

void VilaVilela::OnComprasProdGridDeleteItem(wxListEvent& event) {
	wxListCtrl* lstprod= (wxListCtrl*) event.GetEventObject();
	LstCellInfo *lstcellinfo= (LstCellInfo*) lstprod->GetItemData(event.m_item.GetId());
	if (lstcellinfo) {
		CellInfo *cell=lstcellinfo->find_by_collumn(3),*cell1=lstcellinfo->find_by_collumn(5);
		double val,val2;
		wxString strtot;
		wxString strquant=get_lstctrl_column_text(lstprod,event.m_item.GetId(),3),strval=get_lstctrl_column_text(lstprod,event.m_item.GetId(),5);
		strquant.ToDouble(&val);
		strval.ToDouble(&val2);
		venda_total-= (val*val2);
		wxTextCtrl* stvaltot= (wxTextCtrl*) this->FindWindowById(ID_COMPRAS_TOTAL,this);
		strtot.Printf(_("%.2f"),venda_total);
		stvaltot->SetValue(strtot);
		delete lstcellinfo;
		lstprod->SetItemPtrData(event.m_itemIndex,0);
	}
////@begin wxEVT_COMMAND_LIST_DELETE_ITEM event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_DELETE_ITEM event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
}


/*
 * wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_COMPRAS_PROD_GRID
 */

void VilaVilela::OnComprasProdGridDeleteAllItems(wxListEvent& event) {
	wxListCtrl* lstprod= (wxListCtrl*) event.GetEventObject();
	if (lstprod->GetItemCount() >0) {
		LstCellInfo *lstcellinfo;
		long item = -1;
		for (;;) {
			item = lstprod->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
			if (item == -1)
				break;
			lstcellinfo= (LstCellInfo*) lstprod->GetItemData(item);
			if (lstcellinfo) {
				delete lstcellinfo;
				lstprod->SetItemPtrData(item,0);
			}
		}
	}

////@begin wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLPRINT
 */


int VilaVilela::__ini_recibo(MyPrintout *prout,wxDC *dc,char *cgc) {
	{
		int w, h,margemH,margemV=50,hl;
		double fat=1.5;
		wxFont fontb(20, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD, false,_("Arial"), wxFONTENCODING_ISO8859_1),
		fontl(10, wxFONTFAMILY_SWISS, wxNORMAL, wxLIGHT, false,_("Arial"), wxFONTENCODING_ISO8859_1);
		dc->GetSize(&w, &h);
		margemH=w/32;
		dc->SetBackground(*wxWHITE_BRUSH);
		dc->Clear();
		dc->SetBackgroundMode(wxTRANSPARENT);
		dc->SetBrush(*wxCYAN_BRUSH);
		dc->SetDeviceOrigin((long) 0, (long) 0);
		wxCoord width, height;
		wxString text;
		text=_("RECIBO");
		dc->SetFont(fontb);

		dc->GetTextExtent(text, &width, &height);
		hl=w/3/width;
		fontb.SetPointSize(20*hl);
		fontl.SetPointSize(10*hl);
		dc->SetFont(fontl);
		text=___("Vila Viela produtos orgânicos");
		dc->GetTextExtent(text, &width, &height);
		prout->firstheight=height+margemV;
		dc->DrawText(text, (w-width) /2, margemV);
		text=___("Rua Visconde de Nácar, 800-CENTRO");
		dc->GetTextExtent(text, &width, &height);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawText(text, (w-width) /2, prout->firstheight);
		text=_("CURITIBA-PR");
		dc->GetTextExtent(text, &width, &height);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawText(text, (w-width) /2, prout->firstheight);
		text=_("CNPJ: 80.054.013/0003-91");
		dc->GetTextExtent(text, &width, &height);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawText(text, (w-width) /2, prout->firstheight);

		text=_("IE: 80432545-40");
		dc->GetTextExtent(text, &width, &height);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawText(text, (w-width) /2, prout->firstheight);

		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawLine(margemH,prout->firstheight,w-margemH,prout->firstheight);

		wxDateTime dt=wxDateTime::Now();
		text=dt.Format();
		dc->GetTextExtent(text, &width, &height);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawText(text, (w-width) /2, prout->firstheight);

		text=_("RECIBO");
		dc->SetFont(fontb);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->GetTextExtent(text, &width, &height);

		dc->DrawText(text, (w-width) /2, prout->firstheight);

		text=___("não é documento fiscal");
		dc->SetFont(fontl);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->GetTextExtent(text, &width, &height);

		dc->DrawText(text, (w-width) /2, prout->firstheight);

		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawLine(margemH,prout->firstheight,w-margemH,prout->firstheight);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		prout->itemscount=0;
	}
	return 1;
}

int VilaVilela::__insere_venda(MyPrintout *prout,wxDC *dc,char *codigo,char *nome,char *tipounid,char *quant,char *valunit,char *unidade) {
	{
		int w, h,margemH;
		double fat=1.5;
		dc->GetSize(&w, &h);
		margemH=w/32;
		wxCoord width, height;
		prout->itemscount++;
		wxString text,str,str1,str2;

		str=___(codigo);
		str1=wxString::FromUTF8(nome);
		text.Printf(_("%d "),prout->itemscount);
		text.Append(str);
		text.Append(_(" "));
		text.Append(str1);
		dc->GetTextExtent(text, &width, &height);
		dc->DrawText(text, margemH, prout->firstheight);

		text=___(quant);
		str1=___(unidade);
		text.Append(str1);
		text.Append(_(" X "));
		str2=___(valunit);
		text.Append(str2);
		str.Printf(_("   %.2f"),atof(quant) *atof(valunit));
		text.Append(str);
		dc->GetTextExtent(text, &width, &height);
		dc->DrawText(text, w-margemH-width, prout->firstheight);


		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);

	}
	return 1;
}


void VilaVilela::__termina_recibo(MyPrintout *prout,wxDC *dc,double valtotal,char *formapagto) {
	wxString strtotal;
	char buf[8];
	bool temtroco=false;
	double troco=0;
	wxTextCtrl *lstvalpago= (wxTextCtrl *) this->FindWindowById(ID_VENDAS_VALREC,this);
	strtotal.Printf(_("%.2f"),valtotal);
	if (lstvalpago->IsShown()) {
		strcpy(buf,lstvalpago->GetValue().ToAscii());
		temtroco=true;
		lstvalpago->GetValue().ToDouble(&troco);
		troco-=valtotal;
	}
	else
		strcpy(buf,strtotal.ToAscii());
	{
		int w, h,margemH;
		double fat=1.5;
		dc->GetSize(&w, &h);
		margemH=w/32;
		wxCoord width, height;
		wxString text;
		dc->DrawLine(2*w/3,prout->firstheight,w-margemH,prout->firstheight);

		wxFont fontb((int)(dc->GetFont().GetPointSize() *1.5), wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD, false,_("Arial"), wxFONTENCODING_ISO8859_1),oldfont;
		oldfont=dc->GetFont();
		dc->SetFont(fontb);

		text=_("TOTAL R$");
		dc->GetTextExtent(text, &width, &height);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		dc->DrawText(text, margemH, prout->firstheight);

		dc->SetFont(oldfont);
		dc->GetTextExtent(strtotal, &width, &height);
		dc->DrawText(strtotal,w-width- margemH, prout->firstheight);

		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);

		text=___(formapagto);
		dc->GetTextExtent(text, &width, &height);
		dc->DrawText(text, margemH, prout->firstheight);

		text=___(buf);
		dc->GetTextExtent(text, &width, &height);
		dc->DrawText(text,w-width- margemH, prout->firstheight);

		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);

		if (temtroco) {
			text=_("TROCO");
			dc->GetTextExtent(text, &width, &height);
			dc->DrawText(text, margemH, prout->firstheight);

			text.Printf(_("%.2f"),	troco);
			dc->GetTextExtent(text, &width, &height);
			dc->DrawText(text, w-margemH-width, prout->firstheight);

			prout->firstheight=prout->firstheight+ (int) ceil(fat*height);

		}

		dc->DrawLine(margemH,prout->firstheight,w-margemH,prout->firstheight);
		prout->firstheight=prout->firstheight+ (int) ceil(fat*height);
		text=_("Obrigado, volte sempre!");
		dc->GetTextExtent(text, &width, &height);
		dc->DrawText(text, (w-width) /2, prout->firstheight);
	}
}

void VilaVilela::__printrecibo(MyPrintout *prout,wxDC *dc) {
	Palavra query;
	sql_ResultSet  *res,*res2,*res3;
	TableInfo *tb;
	double valtotal=0;
	char fieldrefid[32],unidade[16],codigo[16],nome[45],tipounid[4],valunit[16],quant[8],formapagto[16];
	int pageid=_get_pageid();
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			query="SELECT idcliente,fp.descricao FROM vendas AS v,formapagto AS fp WHERE v.idvenda=";
			sprintf(fieldrefid,"%d",db_table_id[tb->indtablename]);
			query.append(fieldrefid);
			query.append(" AND v.idformapagto=fp.idformapagto");
			if ((res=_execquerywithresult(query)) !=NULL) {
				if (_firstrow(res)) {
					query="SELECT cpf FROM cliente WHERE idcliente=";
					sprintf(fieldrefid,"%d",_getint(res,1));
					query.append(fieldrefid);
					if ((res2=_execquerywithresult(query)) !=NULL) {
						if (_firstrow(res2)) {
							strcpy(fieldrefid,_getstring(res2,1).ToAscii());
							IRetorno = __ini_recibo(prout,dc,fieldrefid);
							if (Analisa_iRetorno(IRetorno)) {
								query="SELECT u.abrev,u.tipo,p.nome,p.barcode,p.descricao,s.quant,p.val_unit_venda FROM produtos AS p,unidade AS u,saida AS s WHERE s.idvenda=";
								sprintf(fieldrefid,"%d",db_table_id[tb->indtablename]);
								query.append(fieldrefid);
								query.append(" AND p.idunidade=u.idunidade  AND s.idproduto=p.idproduto");
								if ((res3=_execquerywithresult(query)) !=NULL) {
									while (_nextrow(res3)) {
										strcpy(unidade,_getstring(res3,1).ToAscii());
										strcpy(codigo,_getstring(res3,4).ToAscii());
										strcpy(nome,_getstring(res3,3).ToAscii());
										strcpy(tipounid,_getstring(res3,2).ToAscii());
										sprintf(quant,"%.3f",_getdouble(res3,6));
										valtotal+= (_getdouble(res3,6) *_getdouble(res3,7));
										sprintf(valunit,"%.2f",_getdouble(res3,7));
										IRetorno = __insere_venda(prout,dc,codigo,nome,tipounid,quant,valunit,unidade);
										if (!Analisa_iRetorno(IRetorno)) {
											_deleteresult(&res);
											_deleteresult(&res2);
											_deleteresult(&res3);
											return;
										}
									}
									_deleteresult(&res3);
								}
							}
							strcpy(formapagto,_getstring(res,2).ToAscii());
							__termina_recibo(prout,dc,valtotal,formapagto);
						}
						_deleteresult(&res2);
					}
				}
				_deleteresult(&res);
			}
		}
	}
}


void VilaVilela::OnMENUREdXClick(wxCommandEvent& event) {
	TESTA_IMPRESSORA_VALIDA();
	int IRetorno = _LeituraX();
	Analisa_iRetorno(IRetorno);
	event;
}


#include "leiturax.h"

void VilaVilela::OnMENURedXArqClick(wxCommandEvent& event) {
	TESTA_IMPRESSORA_VALIDA();
	int IRetorno = _LeituraXSerial();
	Analisa_iRetorno(IRetorno);
	wxTextFile file;
	LeituraX *dlg=new LeituraX(this);
	wxTextCtrl *lx= (wxTextCtrl*) dlg->FindWindowById(ID_TEXTLEITURAX,dlg);
	if (file.Open(_("retorno.txt"),wxConvISO8859_1)) {
		wxString str;
		for (str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()) {
			str.Append(_("\n"));
			lx->AppendText(str);
		}
	}

	dlg->ShowModal();
}

void VilaVilela::OnMENURedZClick(wxCommandEvent& event) {

	event;
	if (admin==false) {
		wxMessageBox(___("Você precisa ser o administrador para executar esee comando, \npor favor execute o login!"));
		return;
	}
	wxMessageDialog dialog(this,___("Deseja emitir uma leitura Z?, \nA impressora ficará bloqueada até o fim do dia!"),
	                       ___("Confirmar emissão"),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION);
	dialog.Centre();
	if (dialog.ShowModal() !=wxID_YES)
		return;

	TESTA_IMPRESSORA_VALIDA();
	char data[38]="",hora[38]="";
	int Retorno=1;
	registro_R02_R03();
	Retorno= _ReducaoZ(data,hora);
	Analisa_iRetorno(Retorno);
	registro_R02_R03();
}

void VilaVilela::OnMENUIRegAliqClick(wxCommandEvent& event) {
	TESTA_IMPRESSORA_VALIDA();
	char buf[5]="1200";
	int IRetorno = _ProgramaAliquota(buf, 0);
	Analisa_iRetorno(IRetorno);
	event;
}

void VilaVilela::_filter_database(const wxString &filter,const wxString &filter2) {
	Palavra query;
	int pageid=_get_pageid();
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		_fetch_and_update_gl_res(tb->indtablename,__DB_UPD_MODE_FIRST,-1,filter,filter2);
		_db_update(pageid,true);
	}
}

void VilaVilela::OnSearchctrlEnter(wxCommandEvent& event) {
	OnToolfilterClick(event);
	TableInfo *tab;
	int pageid=_get_pageid();
	if ((tab=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		wxToggleButton* tgb=(wxToggleButton*)wxWindow::FindWindowById(ID_TOOLFILTER,this);
		tgb->SetValue(isfiltered[tab->indtablename]);

	}
////@begin wxEVT_COMMAND_TEXT_ENTER event handler for ID_SEARCHCTRL in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_TEXT_ENTER event handler for ID_SEARCHCTRL in VilaVilela.
}


void VilaVilela::OnToolfilterClick(wxCommandEvent& event) {
	wxString filter=wxEmptyString,filter2=wxEmptyString;
	TableInfo *tab;
	int pageid=_get_pageid();
	if ((tab=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		isfiltered[tab->indtablename]=!isfiltered[tab->indtablename];
		if (isfiltered[tab->indtablename]) {
			if (seachfieldinfo[tab->indtablename].searchfield) {
				if (seachfieldinfo[tab->indtablename].fi) {
					if (seachfieldinfo[tab->indtablename].fi->field_type==__DB_FIELD_TYPE_DATE) {
						wxDatePickerCtrl *dt1=	(wxDatePickerCtrl *) this->FindWindowById(ID_SEARCHDATE1,this),*dt2=	(wxDatePickerCtrl *) this->FindWindowById(ID_SEARCHDATE2,this);
						filter=dt1->GetValue().FormatISODate();
						filter2=dt2->GetValue().FormatISODate();
					}
					else {
						wxTextCtrl *sc=	(wxTextCtrl *) this->FindWindowById(ID_SEARCHCTRL,this);
						filter=sc->GetValue();
					}
				}
				else {
					if (seachfieldinfo[tab->indtablename].searchfield->field_type==__DB_FIELD_TYPE_DATE) {
						wxDatePickerCtrl *dt1=	(wxDatePickerCtrl *) this->FindWindowById(ID_SEARCHDATE1,this),*dt2=	(wxDatePickerCtrl *) this->FindWindowById(ID_SEARCHDATE2,this);
						wxDateTime dt;
						dt=dt1->GetValue();
						if (dt.IsValid())
							filter=dt.FormatISODate();
						dt=dt2->GetValue();
						if (dt.IsValid())
							filter2=dt.FormatISODate();
					}
					else {
						wxTextCtrl *sc=	(wxTextCtrl *) this->FindWindowById(ID_SEARCHCTRL,this);
						filter=sc->GetValue();
					}
				}
			}
		}
	}
	_filter_database(filter,filter2);
////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLFILTER in VilaVilela.
	// Before editing this code, remove the block markers.
	event.Skip();
////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLFILTER in VilaVilela.
}



void MyPrintout::DrawPage(wxDC *dc) {
	vilavielaframe->__printrecibo(this,dc);
	dc->SetPen(wxPen(*wxBLACK,0,wxDOT_DASH));
	dc->SetPen(*wxRED_PEN);
}


bool MyPrintout::OnBeginDocument(int startPage, int endPage) {
	if (!wxPrintout::OnBeginDocument(startPage, endPage))
		return false;
	return true;
}

void MyPrintout::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo) {
	*minPage = 1;
	*maxPage = 1;
	*selPageFrom = 1;
	*selPageTo = 1;
}

bool MyPrintout::HasPage(int pageNum) {
	return (pageNum == 1);
}

bool MyPrintout::OnPrintPage(int page) {
	wxDC *dc = GetDC();
	if (dc)	{
		DrawPage(dc);
		return true;
	}
	else
		return false;
}

//#define SETBARCODEPRODUTOS
void VilaVilela::_imprimecodbarras(int tipo){
	PrintBarCode printout(___("Impressão código barra"),tipo);
	if (!printout.performPageSetup(true)) {
		wxMessageBox(___("Impressão cancelada"), ___("Impressão"), wxOK);
		return;
	}

	if (printout.bcopts->ShowModal() ==wxID_OK) {
		wxPrintData pdata=printout.getPrintData();
		EtiquetaInfo *ei=printout.bcopts->lstetiquetainfo.etiquetapadrao;
		pdata.SetNoCopies(ei->CB_NC);
		wxPrintDialogData printDialogData(pdata);
		wxPrinter printer(& printDialogData);
		if (!printer.Print(this, &printout,true)) {
			if (wxPrinter::GetLastError() == wxPRINTER_ERROR)
				wxMessageBox(___("Houve um problema na impressão.\nVerifique a configuração da impressora."), ___("Impressão"), wxOK);
			else
				wxMessageBox(___("Impressão cancelada"), ___("Impressão"), wxOK);
		}
		else {
			(*g_printData) = printer.GetPrintDialogData().GetPrintData();
		}
	}

}
//#define SETBARCODEPRODUTOS
void VilaVilela::OnMenureciboClick(wxCommandEvent& event) {
#ifdef SETBARCODEPRODUTOS
	Palavra query;
	sql_ResultSet  *res;
	query="SELECT idproduto	FROM produtos";
	if ((res=_execquerywithresult(query)) !=0) {
		int i=0;
		while (_nextrow(res)) {		
	  query="UPDATE produtos SET barcode='";
			query.append(_getstringSQL(res,1));
			query.append("' WHERE idproduto=");
			query.append(_getstringSQL(res,1));
			_execquery(query);
		}		
		_deleteresult(&res);
	}
#endif
_imprimecodbarras(IMPRIME_CODIGO_PRODUTO);
	
}



void OnMenuprevreciboClick(wxCommandEvent& event) {
	//wxPrintPreview *preview = new wxPrintPreview(	new MyPrintout, new MyPrintout, g_printData);
	PrintBarCode *printout= new PrintBarCode(___("Impressão codigo barra")),
	*printoutprint= new PrintBarCode(___("Impressão codigo barra"));
	if (!printout->performPageSetup(true)) {
		return;
	}
	wxPrintDialogData printDialogData(printout->getPrintData());
	if (printout->bcopts->ShowModal() ==wxID_OK) {
		wxPrintPreview *preview = new wxPrintPreview(printout	, printoutprint, &printDialogData);
		if (!preview->Ok()) {
			delete preview;
			wxMessageBox(___("Houve um problema na visualização.\nVerifique a configuração da impressora?"),
			             ___("Visualizar impressão"), wxOK);
			return;
		}
		wxSize size(600,800);
		wxPreviewFrame *frame = new wxPreviewFrame(preview, vilavielaframe,___("Visualizar impressão recibo"),wxDefaultPosition,size);
		frame->Centre(wxBOTH);

		frame->Initialize();
		frame->Show(true);
	}
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_DEL_FONE
 */

void VilaVilela::OnClientDelFoneClick(wxCommandEvent& event) {
	Palavra query;
	wxString tmpstr;
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			wxMessageDialog dialog(this,___("Tem certeza que deseja excluir o número atual? \nIsto não poderá ser desfeito, a não ser que você tenha realizado uma cópia de segurança!!!"),
			                       ___("Confirmar exclusão"),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION);
			dialog.Centre();
			if (dialog.ShowModal() ==wxID_YES) {
				query="DELETE FROM fones_cliente WHERE idcliente=";
				tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
				query.append(tmpstr.ToAscii());
				wxChoice *cb= (wxChoice*) this->FindWindowById(ID_CBCLIENTFONES,this);
				query.append(" AND numero='");
				query.append(cb->GetString(cb->GetSelection()).ToAscii());
				query.append("'");
				_execquery(query);
				_db_update(_get_pageid());
			}
		}
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_DEL_FONE in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_DEL_FONE in VilaVilela.
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DEL_FONE
 */

void VilaVilela::OnFornecDelFoneClick(wxCommandEvent& event) {
	Palavra query;
	wxString tmpstr;
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			wxMessageDialog dialog(this,___("Tem certeza que deseja excluir o número atual? \nIsto não poderá ser desfeito, a não ser que você tenha realizado uma cópia de segurança!!!"),
			                       ___("Confirmar exclusão"),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION);
			dialog.Centre();
			if (dialog.ShowModal() ==wxID_YES) {
				query="DELETE FROM fones_fornec WHERE idfornecedor=";
				tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
				query.append(tmpstr.ToAscii());
				wxChoice *cb= (wxChoice*) this->FindWindowById(ID_CBFORNECFONES,this);
				query.append(" AND numero='");
				query.append(cb->GetString(cb->GetSelection()).ToAscii());
				query.append("'");
				_execquery(query);
				_db_update(_get_pageid());
			}
		}
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DEL_FONE in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DEL_FONE in VilaVilela.
}




/*
 * wxEVT_UPDATE_UI event handler for ID_COMPRAS_PROD_GRID
 */

void VilaVilela::OnComprasProdGridUpdate(wxUpdateUIEvent& event) {

////@begin wxEVT_UPDATE_UI event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_COMPRAS_PROD_GRID in VilaVilela.
}


/*
 * wxEVT_UPDATE_UI event handler for ID_VENDAS_INSPROD_GRID
 */

void VilaVilela::OnVendasInsprodGridUpdate(wxUpdateUIEvent& event) {


////@begin wxEVT_UPDATE_UI event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_VENDAS_INSPROD_GRID in VilaVilela.
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON2
 */

void VilaVilela::OnClientDelallFoneClick(wxCommandEvent& event) {
	Palavra query;
	wxString tmpstr;
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			wxMessageDialog dialog(this,___("Tem certeza que deseja excluir todos os telefones deste cliente? \nIsto não pode ser desfeito, a não ser que você tenha realizado uma cópia de segurança!!!"),
			                       ___("Confirmar exclusão"),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION);
			dialog.Centre();
			if (dialog.ShowModal() ==wxID_YES) {
				query="DELETE FROM fones_cliente WHERE idcliente=";
				tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
				query.append(tmpstr.ToAscii());
				_execquery(query);
				_db_update(_get_pageid());
			}
		}
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON2 in VilaVilela.
	// Before editing this code, remove the block markers.
	event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON2 in VilaVilela.
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DELALL_FONE
 */

void VilaVilela::OnFornecDelallFoneClick(wxCommandEvent& event) {
	Palavra query;
	wxString tmpstr;
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			wxMessageDialog dialog(this,___("Tem certeza que deseja excluir todos os telefones deste fornecedor? \nIsto não poderá ser desfeito, a não ser que você tenha realizado uma cópia de segurança!!!"),
			                       ___("Confirmar exclusão"),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION);
			dialog.Centre();
			if (dialog.ShowModal() ==wxID_YES) {
				query="DELETE FROM fones_fornec WHERE idfornecedor=";
				tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
				query.append(tmpstr.ToAscii());
				_execquery(query);
				_db_update(_get_pageid());
			}
		}
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DELALL_FONE in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DELALL_FONE in VilaVilela.
}




/*
 * wxEVT_RIGHT_DOWN event handler for ID_TOOLBAR
 */

void VilaVilela::OnRightDown(wxMouseEvent& event) {
	wxMenu *popmenu=new wxMenu();
	_createsearchpopupmenu(popmenu);
	wxToolBar* tl= (wxToolBar*) event.GetEventObject();
	tl->PopupMenu(popmenu);

////@begin wxEVT_RIGHT_DOWN event handler for ID_TOOLBAR in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_RIGHT_DOWN event handler for ID_TOOLBAR in VilaVilela.
}




/*
 * wxEVT_UPDATE_UI event handler for ID_STATUSBAR
 */

void VilaVilela::OnStatusbarUpdate(wxUpdateUIEvent& event) {
	wxStatusBar *stbar=this->GetStatusBar();
	if (admin) {

		wxString		tmpstr=_("filtrado por "),str2;
		TableInfo *tb;
		int rowcount=0;
		if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
			if (seachfieldinfo[tb->indtablename].searchfield) {
				if (seachfieldinfo[tb->indtablename].fi)
					str2=___(main_tables[
					          seachfieldinfo[tb->indtablename].searchfield->field_type==__DB_FIELD_TYPE_REFN?seachfieldinfo[tb->indtablename].searchfield->reftable2:seachfieldinfo[tb->indtablename].searchfield->reftable])+_("->")+___(seachfieldinfo[tb->indtablename].fi->search_menulabel);
				else
					str2=___(main_tables[tb->indtablename])+_("->")+___(seachfieldinfo[tb->indtablename].searchfield->search_menulabel);
				tmpstr.Append(str2);
			}
			wxToggleButton* tgb=(wxToggleButton*)wxWindow::FindWindowById(ID_TOOLFILTER,this);
			if (tgb->GetValue()) {
				tmpstr.Append(_(":ligado"));
			}
			else
				tmpstr.Append(_(":desligado"));
			stbar->SetStatusText(tmpstr,2);

			if (glb_res[tb->indtablename])
				rowcount=glb_res[tb->indtablename]->nrows;
			wxString fstr;
			if (rowcount>1) {
				if (tgb->GetValue())
					fstr=_("%d linhas nesta pesquisa");
				else
					fstr= _("%d linhas nesta tablela");
			}
			else {
				if (tgb->GetValue())
					fstr=_("%d linhas nesta pesquisa");
				else
					fstr= _("%d linhas nesta tablela");
			}
			tmpstr.Printf(fstr,rowcount);
			stbar->SetStatusText(tmpstr,1);
		}
	}
	else {
		if (impressorabloqueada)
			stbar->SetStatusText(_("Impressora fiscal bloqueada."),0);
		else
			if (impressoraligada)
				stbar->SetStatusText(_("Impressora fiscal conectada."),0);
			else
				stbar->SetStatusText(_("Impressora fiscal desconectada."),0);
		stbar->SetStatusText(wxEmptyString,1);
		stbar->SetStatusText(wxEmptyString,2);
	}
////@begin wxEVT_UPDATE_UI event handler for ID_STATUSBAR in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_STATUSBAR in VilaVilela.
}



/*
 * wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_VENDAS_GRID
 */

void VilaVilela::OnGridSelected(wxListEvent& event) {
	if (db_mode==__DB_MODE_INSERT||db_mode==__DB_MODE_EDIT||db_mode==__DB_MODE_UPDATINGGRID)
		return;
	long item = -1;
	item = ((wxListCtrl*) event.GetEventObject())->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
	_grid_update((wxListCtrl*) event.GetEventObject(),item);
////@begin wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_VENDAS_GRID in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_VENDAS_GRID in VilaVilela.
}

void VilaVilela::_loginasadmin() {
	wxPasswordEntryDialog *dialog=new wxPasswordEntryDialog(this,___("Digite sua senha"),___("Digite sua senha"),___(""),wxOK);
	admin=false;
	dialog->Centre();
	if (dialog->ShowModal() == wxID_OK) {
		if (dialog->GetValue() ==_("vvladmin")) {
			wxMessageBox(_("Bem vindo administrador."), ___("Administrador"));
			admin=true;
			wxMenuBarBase *mbar=GetMenuBar();
			if (mbar) {
				wxMenuItem *item = mbar->FindItem(ID_MENUITEMLOGINASADMIN);
				if (item) {
					item->SetText(_("Logout\tCtrl+L"));
					wxBitmap bitmap(this->GetBitmapResource(wxT("images/logout.png")));
		  	item->SetBitmap(bitmap);
					mbar->Refresh();
				}
			}
		}
	}
	dialog->Destroy();
}


void VilaVilela::_enable_disable_notebook_abas(bool enable) {
	for (TableInfo* tb=lsttableinfo.prm;tb;tb=tb->prx){
		if (tb->pageid!=-1){
			wxNotebook *nbk=(wxNotebook*)wxWindow::FindWindowById(ID_NOTEBOOK,this);
			if(tb->pageid!=ID_PGVENDAS){
				if(enable)
					nbk->AddPage(tb->page,tb->label,false,tb->bmp);
				else
					nbk->RemovePage(nbk->GetPageCount()-1);
			}
			
		//	wxWindow::FindWindowById(tb->pageid,this)->Update(enable);
		//	wxWindow::FindWindowById(ID_NOTEBOOK,this)->Layout();
		//	wxWindow::FindWindowById(ID_NOTEBOOK,this)->Update();
		}
		
	}
	wxWindow::FindWindowById(ID_PANEL_VENDAS_OWNER,this)->Show(enable);
	wxWindow::FindWindowById(ID_SEARCHCTRL,this)->Show(enable);
	wxWindow::FindWindowById(ID_SEARCHDATE1,this)->Show(enable);
	wxWindow::FindWindowById(ID_SEARCHDATE2,this)->Show(enable);
	wxWindow::FindWindowById(ID_TOOLFILTER,this)->Show(enable);
	wxWindow::FindWindowById(ID_VENDAS_VALREC,this)->Show(enable);
	wxWindow::FindWindowById(wxID_STATIC_VALREC,this)->Show(enable);

	this->FindWindowById(wxID_STATIC_TOTDESC,this)->Show(enable);
	this->FindWindowById(ID_VENDAS_TOTAL,this)->Show(enable);
	this->FindWindowById(wxID_STATIC_DESCPERC,this)->Show(enable);
	this->FindWindowById(ID_CHK_PERCENTUAL,this)->Show(enable);
	this->FindWindowById(wxID_STATIC_VALDESC,this)->Show(enable);
	this->FindWindowById(ID_VENDAS_DESCONTO,this)->Show(enable);
	this->FindWindowById(wxID_STATIC_TOTAL,this)->Show(enable);
	this->FindWindowById(ID_VENDAS_TOTAL_GERAL,this)->Show(enable);

	wxWindow::FindWindowById(ID_STVENDAS_CLIENTE,this)->Show(enable);
	wxWindow::FindWindowById(ID_VENDAS_CLIENTE,this)->Show(enable);
	wxWindow::FindWindowById(ID_STVENDAS_FORMAPAGTO,this)->Show(enable);
	wxWindow::FindWindowById(ID_VENDAS_FORMAPAGTO,this)->Show(enable);
	wxWindow::FindWindowById(ID_STVENDAS_NO_NOTA,this)->Show(enable);
	wxWindow::FindWindowById(ID_VENDAS_NO_NOTA,this)->Show(enable);
	wxWindow::FindWindowById(ID_STVENDAS_DATA,this)->Show(enable);
	wxWindow::FindWindowById(ID_VENDAS_DATA,this)->Show(enable);
	wxToolBar *toolbar=GetToolBar();

	if (enable) {
		_AddTool(_tool[0],_mnitem[0]);
		_AddTool(_tool[1],_mnitem[1]);
		_AddTool(_tool[2],_mnitem[2]);
		_AddTool(_tool[3],_mnitem[3]);
		_AddTool(_tool[4],_mnitem[4]);
		_AddTool(_tool[5],_mnitem[5]);
		_RemoveTool(ID_MN_PESQPROD);	
	}
	else {
		_RemoveTool(ID_TOOLFIRSTREC);
		_RemoveTool(ID_TOOLPREVREC);
		_RemoveTool(ID_TOOLNEXTREC);
		_RemoveTool(ID_TOOLLASTREC);
		_RemoveTool(ID_TOOLEdit);
		_RemoveTool(ID_TOOLDelete);
		_RemoveTool(ID_MN_PESQPROD);
		_AddTool(_tool[6],_mnitem[6]);
		if (db_mode==__DB_MODE_READ)
			_EnableTool(ID_MN_PESQPROD,false); 
	}
	toolbar->Realize();
	wxWindow::FindWindowById(ID_PGVENDAS,this)->Layout();
	if(_get_pageid()==ID_PGVENDAS)
	 _db_update(ID_PGVENDAS);
}

void VilaVilela::_RemoveTool(int id){
	wxToolBar *toolbar=GetToolBar();
	wxMenuBar *mnbar=GetMenuBar();
	wxMenu *menu=mnbar->GetMenu(4);
	if(menu->FindChildItem(id)){
 	menu->Remove(id);
	}
	if(toolbar->FindById(id)){
	 toolbar->RemoveTool(id);
	}
}

void VilaVilela::_AddTool(wxToolBarToolBase *tool,wxMenuItem *mnitem){
	wxToolBar *toolbar=GetToolBar();
	wxMenuBar *mnbar=GetMenuBar();
	wxMenu *menu=mnbar->GetMenu(4);
	wxMenuItem* menuItem =mnitem;// new wxMenuItem(menu,mnitem->GetId(), mnitem->GetText(), mnitem->GetHelp(), wxITEM_NORMAL);
	wxBitmap bitmap(mnitem->GetBitmap());
	menuItem->SetBitmap(bitmap);
 mnitem=menu->Append(menuItem);
	
	mnbar->Refresh();
	toolbar->AddTool(tool);
}


void VilaVilela::OnMenuitemloginasadminClick(wxCommandEvent& event) {
	int id = event.GetId();
	wxMenuItem *item = GetMenuBar()->FindItem(id);
	bool oldadmin=admin;
	if (db_mode==__DB_MODE_READ){
		if (!admin) {
			_loginasadmin();
		}
		else {
			((wxNotebook*) this->FindWindowById(ID_NOTEBOOK,this))->SetSelection(0);
			item->SetText(_("Login como administrador...\tCtrl+L"));
			wxBitmap bitmap(this->GetBitmapResource(wxT("images/Login.png")));
			item->SetBitmap(bitmap);
			admin=false;
		}
		if(oldadmin!=admin)
			_enable_disable_notebook_abas(admin);
	}
	else
		wxMessageBox(___("Não é permitido fazer login ou logout no modo edição ou inserção,\n favor terminar ou cancelar a operação atual."));
}


void VilaVilela::OnBtprodImgClick(wxCommandEvent& event) {
	wxString wildcard =	_("arquivo de imagem") +wxImage::GetImageExtWildcard();
	wxString defaultDir = _("./");
	wxString defaultFilename = wxEmptyString;
	wxFileDialog dialog(this, _("seleciona uma imagem"), defaultDir, defaultFilename,wildcard, wxFD_OPEN);
	dialog.Centre();
	if (dialog.ShowModal() == wxID_OK) {
		wxString path = dialog.GetPath();
		wxImage image(dialog.GetPath());
		int height= (int)(DEFAULT_IMG_SIZE*image.GetHeight() / (double) image.GetWidth());
		image.Rescale(DEFAULT_IMG_SIZE,height,wxIMAGE_QUALITY_HIGH);
		wxBitmap _bitmap(image);
		wxStaticBitmap* stbmp= (wxStaticBitmap*) this->FindWindowById(ID_PROD_IMG,this);
		stbmp->SetBitmap(_bitmap);
		stbmp->Show();
		stbmp->SetSize(DEFAULT_IMG_SIZE,DEFAULT_IMG_SIZE);
		imgpath=dialog.GetPath();
		stbmp->GetParent()->Layout();
		stbmp->Refresh();
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BTPROD_IMG in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BTPROD_IMG in VilaVilela.
}


void VilaVilela::OnProdDelimageClick(wxCommandEvent& event) {
	wxStaticBitmap* stbmp= (wxStaticBitmap*) this->FindWindowById(ID_PROD_IMG,this);
	stbmp->SetBitmap(wxNullBitmap);
	stbmp->Hide();
	imgpath=wxEmptyString;
	stbmp->GetParent()->Layout();
	stbmp->Refresh();

////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_PROD_DELIMAGE in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_PROD_DELIMAGE in VilaVilela.
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENU_UPDATESITE
 */
//#define FTP_END "ftp.athena3d.com.br"
//#define FTP_USER "athen394"
//#define FTP_PASWD "ldae08"
#define FTP_END "ftp.vilaviela.com.br"
#define FTP_USER "vilaviela"
#define FTP_PASWD "gato888"
void VilaVilela::OnMenuUpdatesiteClick(wxCommandEvent& event) {
	sql_ResultSet  *res;
	Palavra query,tmpq;
	wxFTP ftp;
	ftp.SetUser(wxString::FromAscii(FTP_USER));
	ftp.SetPassword(wxString::FromAscii(FTP_PASWD));
	if (!ftp.Connect(_(FTP_END))) {
		wxMessageBox(___("imagem não enviada, cheque a conexão com a internet"));
		return ;
	}
	if (ftp.ChDir(_("/vilaviela/Web/vilaviela"))) {
		printf("changing dir\n");
		if (!ftp.ChDir(_(_IMAGE_DIR))) {
			printf("creating dir\n");
			ftp.MkDir(_(_IMAGE_DIR));
			if (ftp.ChDir(_(_IMAGE_DIR))) {
				printf("changing to created dir\n");
				wxArrayString files;
				if (ftp.GetFilesList(files,_("*.*"))) {
					printf("list ok-%d files\n",files.GetCount());
					for (unsigned int i=0;i<files.GetCount();i++)
						ftp.RmFile(files.Item(i));
				}
			}
		}
		//TableInfo *tb;

		//if((tb=lsttableinfo.find_by_pageid(_get_pageid()))!=NULL)
		{
			//	if(db_table_id[tb->indtablename])
			{
				//char fieldrefid[16];
				query="SELECT image FROM produtos";/*  WHERE idproduto=";
				sprintf(fieldrefid,"%d",db_table_id[tb->indtablename]);
				query.append(fieldrefid);						*/
				if ((res=_execquerywithresult(query)) !=NULL) {
					while (_nextrow(res)) {
						//char *arq;
						int size;
						query=_IMAGE_DIR;
						tmpq=_getstringSQL(res,"image");
						printf("file %s\n",tmpq.c_str());
						if (tmpq.length() >0) {
							query.append(tmpq);

							char arq[1024];
							FILE *f = fopen(query.c_str(), "rb");
							wxString fn=wxString::FromAscii(_getstringSQL(res,"image").c_str());
							wxOutputStream *out = ftp.GetOutputStream(fn);
							if (out)
								while ((size = fread(arq, 1, 1024, f)) != 0)

									//size=_load_file_to_buf(query.c_str(),&arq,false);printf("loading %s tam=%d\n",query.c_str(),size);
								{
									out->Write(arq,size);
									printf("writed %d bytes\n",out->LastWrite());
								}

							delete out;
							fclose(f);
						}
					}
					_deleteresult(&res);
				}
			}

		}
	}

//#define conn_params "www.athena3d.com.br:3306", "athen394", "ldae08",""
#define conn_params "dbmy0060.whservidor.com", "vilaviela", "gato888","vilaviela"
	void *conn;
	if ((conn=su_opendb(conn_params)) !=NULL) {
		wxString	tmpstr;
		char errstr[256];
		if (!su_query(conn,"USE vilaviela"))
			printf("%s\n",errstr);
		su_query(conn,"CREATE TABLE  IF NOT EXISTS categoria (idcategoria "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,descricao VARCHAR(45) NULL )  CHARACTER SET utf8 COLLATE utf8_general_ci ");
		if ((res=_execquerywithresult("SELECT * FROM categoria")) !=NULL) {
			Palavra queryprefix="INSERT INTO categoria VALUES (",query;
			su_query(conn,"DELETE FROM categoria");
			while (_nextrow(res)) {
				query=queryprefix;
				query.append(_getint(res,"idcategoria"));
				query.append(",'");
				query.append(_getstringSQL(res,"descricao"));
				query.append("')");
				su_query(conn,query.c_str());
			}
			_deleteresult(&res);
		}
		su_query(conn,"CREATE  TABLE IF NOT EXISTS produtos(\
																									idproduto "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,\
																									nome VARCHAR(45) NULL ,\
																									descricao VARCHAR(45) NULL ,\
																									barcode VARCHAR(45) NULL ,\
																									idunidade INT NULL ,\
																									val_unit_venda FLOAT NULL ,\
																									icms VARCHAR(6) NULL DEFAULT 0 ,\
																									image VARCHAR(45) NULL ,\
																									idcategoria INT NULL ,\
																									sugestao INT NULL DEFAULT 0,\
																									destaque INT NULL DEFAULT 0\
																									) CHARACTER SET utf8 COLLATE utf8_general_ci ");
		su_query(conn,"CREATE  TABLE IF NOT EXISTS unidade (\
																									idunidade "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,\
																									descricao VARCHAR(45) NULL ,\
																									abrev VARCHAR(16) NULL ,\
																									tipo VARCHAR(4) NULL DEFAULT 'I'\
																									)");
		if ((res=_execquerywithresult("SELECT * FROM produtos")) !=NULL) {
			Palavra queryprefix="INSERT INTO produtos VALUES (",query;
			su_query(conn,"DELETE FROM produtos");
			while (_nextrow(res)) {
				query=queryprefix;
				query.append(_getint(res,"idproduto"));
				query.append(",'");
				query.append(_getstringSQL(res,"nome"));
				query.append("','");
				query.append(_getstringSQL(res,"descricao"));
				query.append("','");
				query.append(_getstringSQL(res,"barcode"));
				query.append("',");
				query.append(_getint(res,"idunidade"));
				query.append(",");
				query.append(_getdouble(res,"val_unit_venda"));
				query.append(",'");
				query.append(_getstringSQL(res,"icms"));
				query.append("','");
				query.append(_getstringSQL(res,"image"));
				query.append("',");
				query.append(_getint(res,"idcategoria"));
				query.append(",");
				query.append(_getint(res,"sugestao"));
				query.append(",");
				query.append(_getint(res,"destaque"));
				query.append(")");
				su_query(conn,query.c_str());
			}
			_deleteresult(&res);
		}
		if ((res=_execquerywithresult("SELECT * FROM unidade")) !=NULL) {
			Palavra queryprefix="INSERT INTO unidade VALUES (",query;
			su_query(conn,"DELETE FROM unidade");
			while (_nextrow(res)) {
				query=queryprefix;
				query.append(_getint(res,"idunidade"));
				query.append(",'");
				query.append(_getstringSQL(res,"descricao"));
				query.append("','");
				query.append(_getstringSQL(res,"abrev"));
				query.append("','");
				query.append(_getstringSQL(res,"tipo"));
				query.append("')");
				su_query(conn,query.c_str());
			}
			_deleteresult(&res);
		}
		su_closedb(conn);
		wxMessageBox(___("atualização concluída com sucesso!"));
	}

}

bool VilaVilela::MemoriaFiscalPorData(char *buffname,int flag,bool MFD) {
	SelecioneIntervalodeData* dlgdata=new SelecioneIntervalodeData(this);
	bool retbool=false;
	if (dlgdata->ShowModal() ==wxID_OK) {
		char dataini[16],datafim[16];
		wxDatePickerCtrl *dtpi= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAINI,dlgdata),
		                        *dtpf= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAFIM,dlgdata);
		wxDateTime dti=dtpi->GetValue(),dtf=dtpf->GetValue();
		sprintf(dataini,"%02d/%02d/%04d\0", (int) dti.GetDay(), (int) dti.GetMonth() +1,dti.GetYear());
		sprintf(datafim,"%02d/%02d/%04d\0", (int) dtf.GetDay(), (int) dtf.GetMonth() +1,dtf.GetYear());
		printf("%s\n",dataini);
		printf("%s\n",datafim);
		_LeituraMemoriaFiscalData(dataini,datafim,flag);
		retbool=true;
	}
	delete dlgdata;
	return retbool;
}

bool VilaVilela::MemoriaFiscalPorREDZ(char *buffname,int flag,bool MFD) {
	SelecioneIntervalodeCRZ* dlgCRZ=new SelecioneIntervalodeCRZ(this);
	bool retbool=false;
	if (dlgCRZ->ShowModal() ==wxID_OK) {
		char redi[16],redf[16];
		wxTextCtrl *dtpi= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_INI,dlgCRZ),
		                  *dtpf= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_FIM,dlgCRZ);
		long dti,dtf;
		dtpi->GetValue().ToLong(&dti);
		dtpf->GetValue().ToLong(&dtf);
		sprintf(redi,"%04d\0", (int) dti);
		sprintf(redf,"%04d\0", (int) dtf);
		printf("%s\n",redi);
		printf("%s\n",redf);
		_LeituraMemoriaFiscalReducao(redi,redf,flag);
		retbool=true;
	}
	delete dlgCRZ;
	return retbool;
}


void VilaVilela::OnMnLmfcEcfIdataClick(wxCommandEvent& event) {
	MemoriaFiscalPorData(0,FLAG_LEITURA_C);
}


void VilaVilela::OnMnLmfcEcfIcrzClick(wxCommandEvent& event) {
	MemoriaFiscalPorREDZ(0,FLAG_LEITURA_C);
}


bool VilaVilela::MemoriaFiscalPorDataSerial(char *buffname,int flag,bool MFD) {
	SelecioneIntervalodeData* dlgdata=new SelecioneIntervalodeData(this);
	bool retbool=false;

	if (dlgdata->ShowModal() ==wxID_OK) {
		char dataini[16],datafim[16];
		wxDatePickerCtrl *dtpi= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAINI,dlgdata),
		                        *dtpf= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAFIM,dlgdata);
		wxDateTime dti=dtpi->GetValue(),dtf=dtpf->GetValue();
		sprintf(dataini,"%02d/%02d/%04d\0", (int) dti.GetDay(), (int) dti.GetMonth() +1,dti.GetYear());
		sprintf(datafim,"%02d/%02d/%04d\0", (int) dtf.GetDay(), (int) dtf.GetMonth() +1,dtf.GetYear());
		int ret;
		ret=_LeituraMemoriaFiscalSerialData(dataini,datafim,flag);
		if (ret==1) {
			saveretornoimpressora("LMFC",buffname);
		}
		else {
			wxMessageBox(_("Erro ao salvar arquivo, verifique a impressora!"));
			goto _return;
		}
		retbool=true;
	}
_return:
	delete dlgdata;
	return retbool;
}

bool VilaVilela::MemoriaFiscalPorREDZSerial(char *buffname,int flag,bool MFD) {
	SelecioneIntervalodeCRZ* dlgCRZ=new SelecioneIntervalodeCRZ(this);
	bool retbool=false;
	if (dlgCRZ->ShowModal() ==wxID_OK) {
		char redi[16],redf[16];
		wxTextCtrl *dtpi= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_INI,dlgCRZ),
		                  *dtpf= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_FIM,dlgCRZ);
		long dti,dtf;
		dtpi->GetValue().ToLong(&dti);
		dtpf->GetValue().ToLong(&dtf);
		sprintf(redi,"%04d\0", (int) dti);
		sprintf(redf,"%04d\0", (int) dtf);
		int ret;
		ret=_LeituraMemoriaFiscalSerialReducao(redi,redf,flag);
		if (ret==1) {
			saveretornoimpressora("LMFC",buffname);
		}
		else {
			wxMessageBox(_("Erro ao salvar arquivo, verifique a impressora!"));
			goto _return;
		}
		retbool=true;
	}
_return:
	delete dlgCRZ;
	return retbool;
}

void VilaVilela::OnMnLmfcArqIdataClick(wxCommandEvent& event) {
	MemoriaFiscalPorDataSerial(0,FLAG_LEITURA_C);
}

void VilaVilela::OnMnLmfcArqIcrzClick(wxCommandEvent& event) {
	MemoriaFiscalPorREDZSerial(0,FLAG_LEITURA_C);
}

void VilaVilela::OnMnLmfcCotep1704IdataClick(wxCommandEvent& event) {
	if(MODELO_IMPRESSORA==Sweda_Matricial){
	 wxMessageBox(___("Função não suportada pelo modelo de ECF utilizado"));
		return;
	}
	else if (MODELO_IMPRESSORA==Bematech_MP_20_FI_II||MODELO_IMPRESSORA==Bematech_MP_40_FI_II) {
		char fname[64];
		if (MemoriaFiscalPorDataSerial(fname)) {
			cria_relatorio_atoCOTEP1704(fname);
			remove(fname);
		}
	}
	else{
		bool sucesso=false;
		char fnameCotep1704[64];
		mountcotepefname("MF",fnameCotep1704);
		SelecioneIntervalodeData* dlgdata=new SelecioneIntervalodeData(this);
		bool retbool=false;
		if (dlgdata->ShowModal() ==wxID_OK) {
			char dataini[16],datafim[16];
			wxDatePickerCtrl *dtpi= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAINI,dlgdata),
				*dtpf= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAFIM,dlgdata);
			wxDateTime dti=dtpi->GetValue(),dtf=dtpf->GetValue();
			sprintf(dataini,"%02d/%02d/%04d\0", (int) dti.GetDay(), (int) dti.GetMonth() +1,dti.GetYear());
			sprintf(datafim,"%02d/%02d/%04d\0", (int) dtf.GetDay(), (int) dtf.GetMonth() +1,dtf.GetYear());
			sucesso=(_geracotepe1704_DATA(fnameCotep1704,dataini,datafim,COTEPE1704_MF)==1);
			
		}
		delete dlgdata;
		if(sucesso){
			sign_file(fnameCotep1704);
			mostralocalgravacaoarquivos(fnameCotep1704);
		}
	}
}



void VilaVilela::OnMnLmfcCotep1704IcrzClick(wxCommandEvent& event) {	
	if(MODELO_IMPRESSORA==Sweda_Matricial){
	 wxMessageBox(___("Função não suportada pelo modelo de ECF utilizado"));
		return;
	}
	else if (MODELO_IMPRESSORA==Bematech_MP_20_FI_II||MODELO_IMPRESSORA==Bematech_MP_40_FI_II) {
		char fname[64];
		if (MemoriaFiscalPorREDZSerial(fname)) {
			cria_relatorio_atoCOTEP1704(fname);
			remove(fname);
		}
	}
	else{
		bool sucesso=false;
		char fnameCotep1704[64];
		mountcotepefname("MF",fnameCotep1704);
		SelecioneIntervalodeCRZ* dlgCRZ=new SelecioneIntervalodeCRZ(this);
		if (dlgCRZ->ShowModal() ==wxID_OK) {
			char redi[16],redf[16];
			wxTextCtrl *dtpi= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_INI,dlgCRZ),*dtpf= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_FIM,dlgCRZ);
			long dti,dtf;
			dtpi->GetValue().ToLong(&dti);
			dtpf->GetValue().ToLong(&dtf);
			sprintf(redi,"%04d\0", (int) dti);
			sprintf(redf,"%04d\0", (int) dtf);
			sucesso=_geracotepe1704_COO(fnameCotep1704,redi,redf,COTEPE1704_MF)==1;
		}
		delete dlgCRZ;
		if(sucesso){
			sign_file(fnameCotep1704);
			mostralocalgravacaoarquivos(fnameCotep1704);
		}
	}
}

void VilaVilela::OnMnLmfsEcfIdataClick(wxCommandEvent& event) {
	ASSERT_PRINTER_MODEL();
	MemoriaFiscalPorData(0,FLAG_LEITURA_S,true);
}


void VilaVilela::OnMnLmfsEcfIcrzClick(wxCommandEvent& event) {
	ASSERT_PRINTER_MODEL();
	MemoriaFiscalPorREDZ(0,FLAG_LEITURA_S,true);
}


void VilaVilela::OnMnLmfsArqIdataClick(wxCommandEvent& event) {
	ASSERT_PRINTER_MODEL();
	MemoriaFiscalPorDataSerial(0,FLAG_LEITURA_S,true);
}


void VilaVilela::OnMnLmfsArqIcrzClick(wxCommandEvent& event) {
	ASSERT_PRINTER_MODEL();
	MemoriaFiscalPorREDZSerial(0,FLAG_LEITURA_S,true);
}


void VilaVilela::OnMnespelhomfdDataClick(wxCommandEvent& event) {
	if (MODELO_IMPRESSORA==Bematech_MP_20_FI_II||MODELO_IMPRESSORA==Bematech_MP_40_FI_II||MODELO_IMPRESSORA==Bematech_MP_25_FI||MODELO_IMPRESSORA==Bematech_MP_50_FI) {
		wxMessageBox(___("Função não suportada pelo modelo de ECF utilizado"));
		return;
	}
	bool sucesso=false;
	char fname[128];
	mountcotepefname("ESPELHOMFDDATA",fname);
	SelecioneIntervalodeData* dlgdata=new SelecioneIntervalodeData(this);
	bool retbool=false;
	if (dlgdata->ShowModal() ==wxID_OK) {
		char dataini[16],datafim[16];
		wxDatePickerCtrl *dtpi= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAINI,dlgdata),
			*dtpf= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAFIM,dlgdata);
		wxDateTime dti=dtpi->GetValue(),dtf=dtpf->GetValue();
		sprintf(dataini,"%02d%02d%04d", (int) dti.GetDay(), (int) dti.GetMonth() +1,dti.GetYear());
		sprintf(datafim,"%02d%02d%04d", (int) dtf.GetDay(), (int) dtf.GetMonth() +1,dtf.GetYear());
		_DownloadMFD_DATA(dataini,datafim);
		sucesso=(_FormatoDadosMFD_DATA(fname,dataini,datafim)==1);
	}
	delete dlgdata;
	if(sucesso){
		sign_file(fname);
		mostralocalgravacaoarquivos(fname);
	}	
}

void VilaVilela::OnMnespelhomfdCooClick(wxCommandEvent& event) {
	if (MODELO_IMPRESSORA==Bematech_MP_20_FI_II||MODELO_IMPRESSORA==Bematech_MP_40_FI_II||MODELO_IMPRESSORA==Bematech_MP_25_FI||MODELO_IMPRESSORA==Bematech_MP_50_FI) {
		wxMessageBox(___("Função não suportada pelo modelo de ECF utilizado"));
		return;
	}
	bool sucesso=false;
	char fnameCotep1704[128];
	mountcotepefname("ESPELHOMFDCOO",fnameCotep1704);
	SelecioneIntervalodeCRZ* dlgCRZ=new SelecioneIntervalodeCRZ(this);
	dlgCRZ->SetTitle(_("Selecione intervalo de COO"));
	wxWindow::FindWindowById(wxID_LABEL_CRZI,dlgCRZ)->SetLabel(_("COO inicial"));
	wxWindow::FindWindowById(wxID_LABEL_CRZF,dlgCRZ)->SetLabel(_("COO final"));
	if (dlgCRZ->ShowModal() ==wxID_OK) {
		char redi[16],redf[16];
		wxTextCtrl *dtpi= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_INI,dlgCRZ),*dtpf= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_FIM,dlgCRZ);
		long dti,dtf;
		dtpi->GetValue().ToLong(&dti);
		dtpf->GetValue().ToLong(&dtf);
		sprintf(redi,"%04d\0", (int) dti);
		sprintf(redf,"%04d\0", (int) dtf);
		_DownloadMFD_COO(redi,redf);
		sucesso=(_FormatoDadosMFD_COO(fnameCotep1704,redi,redf)==1);
	}
	delete dlgCRZ;
	if(sucesso){
		sign_file(fnameCotep1704);
		mostralocalgravacaoarquivos(fnameCotep1704);
	}
}


void VilaVilela::OnMNTabProdClick(wxCommandEvent& event) {
	RELATORIOS::requisitoXX::gravarequisitoXX();
}


void VilaVilela::OnMmMovecfClick(wxCommandEvent& event) {
	MovimentoporECF *dlg=new MovimentoporECF(this);
	if (dlg->ShowModal() ==wxID_OK) {
		wxChoice *ecf= (wxChoice*) dlg->FindWindowById(ID_CB_ECF, (wxWindow*) dlg);
		wxDatePickerCtrl *di= (wxDatePickerCtrl*) dlg->FindWindowById(ID_MOVECF_DI, (wxWindow*) dlg),
		                      *df= (wxDatePickerCtrl*) dlg->FindWindowById(ID_MOVECF_DF, (wxWindow*) dlg);
		wxDateTime datei=di->GetValue(),datef=df->GetValue();
		long  datai,dataf;
		datai=datei.GetYear() *10000+ ((int) datei.GetMonth() +1) *100+datei.GetDay();
		dataf=datef.GetYear() *10000+ ((int) datef.GetMonth() +1) *100+datef.GetDay();
		char  cdatai[9],cdataf[9];
		sprintf(cdatai,"%8ld",datai);
		sprintf(cdataf,"%8ld",dataf);

		int sel=ecf->GetSelection();
		wxString tstr=ecf->GetString(sel);
		gravarequisitoXXV(cdatai,cdataf,true,tstr.ToAscii());
	}
	delete dlg;
}



void VilaVilela::OnMnCancelaultcupomClick(wxCommandEvent& event) {
	sql_ResultSet *res,*res2;
	Palavra query;
	TESTA_IMPRESSORA_VALIDA();
	if (_cancela_cupom() ==1&&pode_cancelar_cupom) {
		pode_cancelar_cupom=false;
		query="SELECT MAX(idR04) FROM r04";
		if ((res=_execquerywithresult(query)) !=NULL&&_nextrow(res)) {
			query="UPDATE r04 SET Ind_de_Cancelamento='S' WHERE idR04=";
			query.append(_getstring(res,1).ToAscii());
			_execquery(query);
			query="SELECT Meio_de_pagamento,Valor_Total_Liquido FROM r04 WHERE idR04=";
			query.append(_getstring(res,1).ToAscii());
			if ((res2=_execquerywithresult(query)) !=NULL&&_nextrow(res2)) {
				char Meio_de_pagamento[20]="",Valor_pago[20];
				strcpy(Meio_de_pagamento,_getstring(res2,1).ToAscii());
				strcpy(Valor_pago,_getstring(res2,2).ToAscii());
				registro_R06(Valor_pago,Meio_de_pagamento,"NC",true,Valor_pago);
				_deleteresult(&res2);
			}
			_deleteresult(&res);
		}
	}
}



void VilaVilela::OnMnCancelaitemantClick(wxCommandEvent& event) {

}



void VilaVilela::OnMnCancelaitemClick(wxCommandEvent& event) {

}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_VENDAS_DESCONTO
 */

void VilaVilela::OnVendasDescontoTextUpdated(wxCommandEvent& event) {
////@begin wxEVT_COMMAND_TEXT_UPDATED event handler for ID_VENDAS_DESCONTO in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_TEXT_UPDATED event handler for ID_VENDAS_DESCONTO in VilaVilela.
}

void VilaVilela::verificaestadoimpressora() {
	bool oldb=impressoraligada;
	impressoraligada=testa_impressora();
 
 NENHUMRELATORIO2() ;
	char *bd;
	int sz=descriptografa_arquivo("arquivo_auxiliare.txt",&bd);
	bool changed=false;
	wxString str;
	long vlong;
	atualiza_arquivo_auxiliar("NOME_USER",bd,sz,NULL,NOME_USER,false,true);
	if (strcmp(NOME_USER,"                                        ")==0) {
		wxTextEntryDialog dialog(this,___("Digite o nome do estabelecimento \n(máximo 40 caracteres)"),___("Nome do estabelecimento"),_(""),wxOK|wxCANCEL);
		dialog.Centre();
		dialog.Refresh();
		if (dialog.ShowModal() == wxID_OK) {
			sprintf(NOME_USER,"%-40s",dialog.GetValue().ToUTF8().data());
			atualiza_arquivo_auxiliar("NOME_USER",bd,sz,NOME_USER,NULL,true,false);
			changed=true;
		}
	}
	atualiza_arquivo_auxiliar("CNPJ_USER",bd,sz,NULL,CNPJ_USER,false,true);
	if (strcmp(CNPJ_USER,"00000000000000")==0) {
		wxTextEntryDialog dialog(this,___("Digite o CNPJ do estabelecimento (somente os números)"),___("CNPJ do estabelecimento"),_(""),wxOK|wxCANCEL);
		dialog.Centre();
		dialog.Refresh();
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToLong(&vlong);
			sprintf(CNPJ_USER,"%014ld",vlong);
			atualiza_arquivo_auxiliar("CNPJ_USER",bd,sz,CNPJ_USER,NULL,true,false);
			changed=true;
		}
	}
	atualiza_arquivo_auxiliar("IE_USER",bd,sz,NULL,IE_USER,false,true);
	if (strcmp(IE_USER,"00000000000000")==0) {
		wxTextEntryDialog dialog(this,___("Digite a I.E. do estabelecimento (somente os números)"),___("I.E. do estabelecimento"),_(""),wxOK|wxCANCEL);
		dialog.Centre();
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToLong(&vlong);
			sprintf(IE_USER,"%-14s",dialog.GetValue().ToUTF8().data());
			atualiza_arquivo_auxiliar("IE_USER",bd,sz,IE_USER,NULL,true,false);
			changed=true;
		}
	}
	atualiza_arquivo_auxiliar("IM_USER",bd,sz,NULL,IM_USER,false,true);
	if (strcmp(IM_USER,"00000000000000")==0) {
		wxTextEntryDialog dialog(this,___("Digite a I.M. do estabelecimento (somente os números)"),___("I.M. do estabelecimento"),_(""),wxOK|wxCANCEL);
		dialog.Centre();
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToLong(&vlong);
			sprintf(IM_USER,"%-14s",dialog.GetValue().ToUTF8().data());
			atualiza_arquivo_auxiliar("IM_USER",bd,sz,IM_USER,NULL,true,false);
			changed=true;
		}
	}
	if (oldb!=impressoraligada&&impressoraligada) {

		impressorabloqueada=!ECF_autorizada(bd,sz,ecf.CNI);
		if (!impressorabloqueada) {
			char ab_dia[16],fc_dia;
			atualiza_arquivo_auxiliar("ABERTURA_DIA",bd,sz,NULL,ab_dia,false,true);
			strncpy(data_abertura_dia,ab_dia,8);data_abertura_dia[8]=0;
			strncpy(hora_abertura_dia,ab_dia+9,6);
			
			char dataatual[9],horaatual[7];
			wxDateTime dt=wxDateTime::Now();
			getdateandhourcotepe(dt,dataatual,horaatual);
			
			if (strcmp(data_abertura_dia,dataatual)!=0) {
				if (strcmp(ab_dia,"AAAAMMDD HHMMSS")!=0) {
					atualiza_arquivo_auxiliar("FECHAMENTO_DIA",bd,sz,NULL,&fc_dia,false,true);
					if (fc_dia=='1') {
						wxMessageDialog dialog(this,___("Deseja executar o fechamento do dia anterior e emitir uma leitura Z?, \nSe a leitura Z foi emitida automaticamente hoje, clique em não,\ncaso contrário a impressora ficará bloqueada até o fim do dia!"),
						                       ___("Confirmar fechamento"),wxNO_DEFAULT|wxYES_NO|wxICON_QUESTION);
						dialog.Centre();
						if (dialog.ShowModal() ==wxID_YES)
							if (_FechamentoDoDia()==1) {
								atualiza_arquivo_auxiliar("FECHAMENTO_DIA",bd,sz,"0",NULL,true,false);
								changed=true;
							}
					}
				}
				char val[]="50,00",moeda[]="Dinheiro";
				_AberturaDoDia(val,moeda);
				sprintf(ab_dia,"%8s %6s",dataatual,horaatual);
				atualiza_arquivo_auxiliar("ABERTURA_DIA",bd,sz,ab_dia,NULL,true,false);
				atualiza_arquivo_auxiliar("FECHAMENTO_DIA",bd,sz,"1",NULL,true,false);

				_atualiza_bkupdb();
				strcpy(data_abertura_dia,dataatual);
				strcpy(hora_abertura_dia,horaatual);
				changed=true;
			}
		}
		if (changed)
			criptografa_buf("arquivo_auxiliare.txt",bd);

		if (!impressorabloqueada) {
			_atualiza_dados_impressora();
			registro_R02_R03();
		}
	}
	delete []bd;
}



void VilaVilela::OnTimer(wxTimerEvent &event) {
	MODOTESTE();

	return;
	verificaestadoimpressora();

}

void VilaVilela::OnPgvendasUpdate(wxUpdateUIEvent& event) {

////@begin wxEVT_UPDATE_UI event handler for ID_PGVENDAS in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_PGVENDAS in VilaVilela.
}



void VilaVilela::OnMenubalancomClick(wxCommandEvent& event) {
	Balanco *dlgbal=new Balanco(this);
	if (dlgbal->ShowModal() ==wxID_OK) {
		wxCalendarCtrl *cal= (wxCalendarCtrl*) dlgbal->FindWindowById(ID_CALCTRL_BALANCO,dlgbal);
		wxCalendarCtrl *calf= (wxCalendarCtrl*) dlgbal->FindWindowById(ID_CALCTRL_BALANCOF,dlgbal);
		wxRadioBox *rdbox= (wxRadioBox*) dlgbal->FindWindowById(ID_RB_BALANCO,dlgbal);
		wxDateTime dt,dtf;
		dt=cal->GetDate();
		dtf=calf->GetDate();
		wxString fname,filter1,filter2;
		char titulo[64];
		if (rdbox->GetSelection() ==0) {  //mensal
			fname.Printf(_("BAL-%s-%d.html"),dt.GetMonthName(dt.GetMonth()).ToAscii(),dt.GetYear());
			sprintf(titulo,"Balanco mensal -%s %d",dt.GetMonthName(dt.GetMonth()).ToAscii().data(),dt.GetYear());
			filter1.Printf(_("%d-%02d-01"),dt.GetYear(),dt.GetMonth() +1);
			filter2.Printf(_("%d-%02d-%02d 23:59:00"),dt.GetYear(),dt.GetMonth() +1,dt.GetNumberOfDays(dt.GetMonth()));
		}
		else
			if (rdbox->GetSelection() ==1) {  //anual
				fname.Printf(_("BAL-%d.html"),dt.GetYear());
				sprintf(titulo,"Balanco anual - %d",dt.GetYear());
				filter1.Printf(_("%d-01-01"),dt.GetYear());
				filter2.Printf(_("%d-12-31 23:59:00"),dt.GetYear());
			}
			else {//data
				fname.Printf(_("BAL-%02d_%02d_%02d-%02d_%02d_%02d.html"),dt.GetDay(),dt.GetMonth() +1,dt.GetYear(),dtf.GetDay(),dtf.GetMonth() +1,dtf.GetYear());
				sprintf(titulo,"Balanco %02d_%02d_%02d a %02d_%02d_%02d",dt.GetDay(),dt.GetMonth() +1,dt.GetYear(),dtf.GetDay(),dtf.GetMonth() +1,dtf.GetYear());
				filter1.Printf(_("%d-%02d-%02d"),dt.GetYear(),dt.GetMonth() +1,dt.GetDay());
				filter2.Printf(_("%d-%02d-%02d 23:59:00"),dtf.GetYear(),dtf.GetMonth() +1,dtf.GetDay());
			}
		FILE *fbal=fopen(fname.ToAscii(),"w+b");
		fprintf(fbal,
		        "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/> \
<html xmlns=\"http://www.w3.org/1999/xhtml\" >\n\
<head>\n\
    <title>%s</title>\n\
				<style type=\"text/css\">\n\
     .style1\n\
     {\n\
      width: 100%%;\n\
     }\n\
    </style>\n\
</head>\n\
<body>\n\
\
<table  border=\"0\" class=\"style1\" align=\"left\" cellpadding=\"0\" cellspacing=\"0\">\n\
  <tr >\n\
   <td >\n\
<table  border=\"1\"  align=\"center\" cellpadding=\"0\" cellspacing=\"0\">\n\
  <tr style=\"font-weight: bold\" align=\"center\" bgcolor=\"#E0E0E0\">\n\
   <td >\n\
    Id Venda</td>\n\
   <td>\n\
    Nota</td>\n\
   <td>\n\
    Data e hora</td>\n\
   <td>\n\
    Bruto recebido</td>\n\
   <td>\n\
    Imposto</td>\n\
   <td>\n\
    Desconto</td>\n\
   <td>\n\
    Lucro Liquido</td>\n\
  </tr>\n\
",titulo);

		Palavra query;
		query="Select v.idvenda,v.no_nota,v.data,v.desconto,v.desconto_percentual FROM vendas AS v  WHERE v.data>='";
		query.append(filter1.ToAscii());
		query.append("' AND v.data<='");
		query.append(filter2.ToAscii());
		query.append("' ORDER BY v.data");
		sql_ResultSet *res,*res2;
		Palavra idvenda,aliquota;
		double totalbruto=0,totalimposto=0,totaldesconto=0,totallucro=0;
		if ((res=_execquerywithresult(query)) !=NULL&&_nextrow(res)) {
			do {
				idvenda=_getstringSQL(res,1);
				query="Select a.abrev ,s.quant,p.val_unit_venda FROM saida AS s,aliquotas AS a, produtos AS p WHERE s.idvenda=";
				query.append(idvenda);
				query.append(" AND a.idaliquota=p.idaliquota AND p.idproduto=s.idproduto");
				double imposto=0.0,desconto=0.0,brutorec=0.0,percimp,subt,lucroliq;
				if ((res2=_execquerywithresult(query)) !=NULL&&_nextrow(res2)) {
					do {
						aliquota=_getstringSQL(res2,1);
						if (aliquota=="II"||aliquota=="NN"||aliquota=="FF")
							percimp=0.0;
						else
							percimp=atoi(aliquota.c_str()) /10000.0;
						subt=_getdouble(res2,3) *_getdouble(res2,2);
						imposto+=subt*percimp;
						brutorec+=subt;
					}
					while (_nextrow(res2));
					_deleteresult(&res2);
				}
				if (_getint(res,5))
					desconto=brutorec*_getdouble(res,4) /100.0;
				else
					desconto=_getdouble(res,4) /100.0;
				lucroliq=brutorec-imposto-desconto;
				totalbruto+=brutorec;
				totalimposto+=imposto;
				totaldesconto+=desconto;
				totallucro+=lucroliq;
				fprintf(fbal,"\
<tr>\n\
<td>\n\
%s</td>\n\
<td>\n\
%s</td>\n\
<td>\n\
%s</td>\n\
<td align=\"right\" width=\"150\">\n\
%.2f</td>\n\
<td align=\"right\" width=\"150\">\n\
%.2f</td>\n\
<td align=\"right\" width=\"150\">\n\
%.2f</td>\n\
<td align=\"right\" width=\"150\">\n\
%.2f</td>\n\
</tr>\n",idvenda.c_str(),_getstringSQL(res,2).c_str(),_getstringSQL(res,3).c_str(),brutorec,imposto,desconto,lucroliq);
			}
			while (_nextrow(res));
			_deleteresult(&res);
		}
		fprintf(fbal,"</table>\n\
															</td >\n\
   </tr >\n\
			<tr >\n\
   <td >&nbsp;</td >\n\
   </tr >\n\
															<tr >\n\
   <td >\n\
			<table align=\"center\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\">\n\
  <tr style=\"font-weight: bold\" align=\"center\" bgcolor=\"#E0E0E0\">\n\
   <td class=\"style2\">\n\
    Total Bruto recebido</td>\n\
   <td class=\"style2\">\n\
    Total Imposto</td>\n\
   <td class=\"style2\">\n\
    Total Desconto</td>\n\
   <td class=\"style2\">\n\
    Total Lucro Liquido</td>\n\
  </tr>\n\
  <tr>\n\
   <td  align=\"right\" width=\"150\">\n\
    %.2f</td>\n\
   <td  align=\"right\" width=\"150\">\n\
    %.2f</td>\n\
   <td  align=\"right\" width=\"150\">\n\
    %.2f</td>\n\
   <td  align=\"right\" width=\"150\">\n\
    %.2f</td>\n\
  </tr>\n\
 </table>	</td >	</tr > \n",totalbruto,totalimposto,totaldesconto,totallucro);
		query="Select p.idproduto,p.nome FROM produtos AS p";
		if ((res=_execquerywithresult(query)) !=NULL&&_nextrow(res)) {
			fprintf(fbal,"<tr >\n\
   <td >&nbsp;</td >\n\
   </tr >\n<tr ><td ><table class=\"style2\" align=\"center\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\">\n\
  <tr style=\"font-weight: bold\" align=\"center\" bgcolor=\"#E0E0E0\">\n\
   <td class=\"style2\">\n\
    </td>\n\
   <td class=\"style2\">\n\
    Dom</td>\n\
   <td class=\"style2\">\n\
    Seg</td>\n\
   <td class=\"style2\">\n\
    Ter</td>\n\
   <td class=\"style2\">\n\
    Qua</td>\n\
   <td class=\"style2\">\n\
    Qui</td>\n\
   <td class=\"style2\">\n\
    Sex</td>\n\
   <td>\n\
    Sab</td>\n\
  </tr>\n");
			wxDateTime dtw;
			do {
				query="Select v.data,s.quant FROM vendas AS v,saida AS s, produtos AS p  WHERE v.idvenda=s.idvenda AND s.idproduto=";
				query.append(_getstringSQL(res,1));
				query.append(" AND v.data>='");
				query.append(filter1.ToAscii());
				query.append("' AND v.data<='");
				query.append(filter2.ToAscii());
				query.append("'");
				double dom=0,seg=0,ter=0,qua=0,qui=0,sex=0,sab=0;
				if ((res2=_execquerywithresult(query)) !=NULL&&_nextrow(res2)) {
					do {
						dtw.ParseDate(_getstring(res2,1).data());
						if (dtw.IsValid()) {
							switch (dtw.GetWeekDay()) {
							case wxDateTime::Sun:
								dom+=_getdouble(res2,2);
								break;
							case wxDateTime::Mon:
								seg+=_getdouble(res2,2);
								break;
							case wxDateTime::Tue:
								ter+=_getdouble(res2,2);
								break;
							case wxDateTime::Wed:
								qua+=_getdouble(res2,2);
								break;
							case wxDateTime::Thu:
								qui+=_getdouble(res2,2);
								break;
							case wxDateTime::Fri:
								sex+=_getdouble(res2,2);
								break;
							case wxDateTime::Sat:
								sab+=_getdouble(res2,2);
								break;
							}
						}
					}
					while (_nextrow(res2));
					_deleteresult(&res2);
				}
				fprintf(fbal,"<tr>\n\
   <td align=\"right\" width=\"100\">\n\
    %s</td>\n\
   <td align=\"right\" width=\"100\">\n\
    %.3f</td>\n\
   <td align=\"right\" width=\"100\">\n\
    %.3f</td>\n\
   <td align=\"right\" width=\"100\">\n\
    %.3f</td>\n\
   <td align=\"right\" width=\"100\">\n\
    %.3f</td>\n\
   <td align=\"right\" width=\"100\">\n\
    %.3f</td>\n\
   <td align=\"right\" width=\"100\">\n\
    %.3f</td>\n\
   <td align=\"right\" width=\"100\">\n\
			%.3f</td></tr>",_getstringSQL(res,2).c_str(),dom,seg,ter,qua,qui,sex,sab);

			}
			while (_nextrow(res));
			_deleteresult(&res);
			fprintf(fbal,
			        "</table></td >	</tr > \n");
		}
		fprintf(fbal,
		        "</table></body>\n\
			</html>\n");
		fclose(fbal);
		mostralocalgravacaoarquivos(fname.ToAscii());
	}
	delete dlgbal;
}



/*
 * Get bitmap resources
 */

wxBitmap VilaVilela::GetBitmapResource(const wxString& name) {
	wxBitmap bitmap(name, wxBITMAP_TYPE_PNG);
	return bitmap;
}

/*
 * Get icon resources
 */

wxIcon VilaVilela::GetIconResource(const wxString& name) {
	wxIcon icon(name, wxBITMAP_TYPE_PNG);
	return icon;
}



/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_TOTAL
 */

void VilaVilela::OnMiEstoqueTotalClick(wxCommandEvent& event) {
	RELATORIOS::requisitoVII_8::estoquetotal();
////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_TOTAL in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_TOTAL in VilaVilela.
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_PARCIAL
 */

void VilaVilela::OnMiEstoqueParcialClick(wxCommandEvent& event) {
////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_PARCIAL in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_PARCIAL in VilaVilela.
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNDBHOST
 */

void VilaVilela::OnMndbhostClick(wxCommandEvent& event) {
	char olddbhost[16];
	strcpy(olddbhost,db_host);
	show_config_dlg(CONFIG_DBHOST);
	load_config(true);

	if (_open_db(&glb_stmt,false)) {
		_update_db_cache();
		if (db_mode==__DB_MODE_READ)
			_db_update(_get_pageid());
	}
	_verificaconexao(&glb_stmt);

////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNDBHOST in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNDBHOST in VilaVilela.
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNArqMFD_DATA
 */

void VilaVilela::OnMNArqMFDDATAClick( wxCommandEvent& event )
{
	ASSERT_PRINTER_MODEL();	
	bool sucesso=false;
	char fnameCotep1704[64];
	mountcotepefname("MF",fnameCotep1704);
	SelecioneIntervalodeData* dlgdata=new SelecioneIntervalodeData(this);
	bool retbool=false;
	if (dlgdata->ShowModal() ==wxID_OK) {
		char dataini[16],datafim[16];
		wxDatePickerCtrl *dtpi= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAINI,dlgdata),
			*dtpf= (wxDatePickerCtrl *) dlgdata->FindWindowById(ID_DLGSELDATA_DATAFIM,dlgdata);
		wxDateTime dti=dtpi->GetValue(),dtf=dtpf->GetValue();
		sprintf(dataini,"%02d/%02d/%04d\0", (int) dti.GetDay(), (int) dti.GetMonth() +1,dti.GetYear());
		sprintf(datafim,"%02d/%02d/%04d\0", (int) dtf.GetDay(), (int) dtf.GetMonth() +1,dtf.GetYear());
		sucesso=(_geracotepe1704_DATA(fnameCotep1704,dataini,datafim,COTEPE1704_MFD)==1);
	}
	delete dlgdata;
	if(sucesso){
		sign_file(fnameCotep1704);
		mostralocalgravacaoarquivos(fnameCotep1704);
	}
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNArqMFD_COO
 */

void VilaVilela::OnMNArqMFDCOOClick( wxCommandEvent& event )
{
	ASSERT_PRINTER_MODEL();
	bool sucesso=false;
	char fnameCotep1704[64];
	mountcotepefname("MF",fnameCotep1704);
	SelecioneIntervalodeCRZ* dlgCRZ=new SelecioneIntervalodeCRZ(this);
	dlgCRZ->SetTitle(_("Selecione intervalo de COO"));
	wxWindow::FindWindowById(wxID_LABEL_CRZI,dlgCRZ)->SetLabel(_("COO inicial"));
	wxWindow::FindWindowById(wxID_LABEL_CRZF,dlgCRZ)->SetLabel(_("COO final"));
	if (dlgCRZ->ShowModal() ==wxID_OK) {
		char redi[16],redf[16];
		wxTextCtrl *dtpi= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_INI,dlgCRZ),*dtpf= (wxTextCtrl *) dlgCRZ->FindWindowById(ID_DLGSELCRZ_FIM,dlgCRZ);
		long dti,dtf;
		dtpi->GetValue().ToLong(&dti);
		dtpf->GetValue().ToLong(&dtf);
		sprintf(redi,"%04d\0", (int) dti);
		sprintf(redf,"%04d\0", (int) dtf);
		sucesso=_geracotepe1704_COO(fnameCotep1704,redi,redf,COTEPE1704_MFD)==1;
	}
	delete dlgCRZ;
	if(sucesso){
		sign_file(fnameCotep1704);
		mostralocalgravacaoarquivos(fnameCotep1704);
	}
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_PESQPROD
 */

void VilaVilela::OnMnPesqprodClick( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_PESQPROD in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_PESQPROD in VilaVilela. 
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM
 */

void VilaVilela::OnMnDescPercentClick( wxCommandEvent& event ){
	if (db_mode==__DB_MODE_INSERT&&_get_pageid()==ID_PGVENDAS){
		wxCheckBox* chk=(wxCheckBox*)this->FindWindowById(ID_CHK_PERCENTUAL,this); 
		bool oldval=chk->GetValue();
		chk->SetValue(!oldval);
	}
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM1
 */

void VilaVilela::OnMnInsPagtoClick( wxCommandEvent& event ){
	if (db_mode==__DB_MODE_INSERT&&_get_pageid()==ID_PGVENDAS) {
		bool ok=false;
		dlgPagamento dlg(this);
		double valpago;
		wxChoice* cbx=(wxChoice*)this->FindWindowById(ID_PAGTO_TIPO,(wxWindow*)&dlg); 
		wxTextCtrl* edval=(wxTextCtrl*)this->FindWindowById(ID_PAGTO_VAL,(wxWindow*)&dlg); 	
		while (dlg.ShowModal() == wxID_OK) {	
			edval->GetValue().ToDouble(&valpago);
			if(valpago>0.0){
				ok=true;
				break;
			}
			else{
				wxMessageBox(_("Por favor, o valor do pagamento tem que ser maior que zero!"));
				edval->SetFocus();
			}
		}
		if(ok){
			wxListCtrl *lstvalpago= (wxListCtrl *) this->FindWindowById(ID_VENDAS_VALREC,this);
			chcIdRef* clientdata=(chcIdRef*)cbx->GetClientObject(cbx->GetSelection());	
			long item=lstvalpago->GetItemCount();
			lstvalpago->InsertItem(item,cbx->GetString(cbx->GetSelection()));
			lstvalpago->SetItemData(item, (long) (wxClientData*)(new chcIdRef(clientdata->val)));
			set_lstctrl_column(lstvalpago,wxString::Format(_("%.2f"),valpago),1,item,0,0);
		}
	}
}


/*
 * wxEVT_UPDATE_UI event handler for ID_VENDAS_TROCO
 */

void VilaVilela::OnVendasTrocoUpdate( wxUpdateUIEvent& event ){
	wxListCtrl *lstvalpago= (wxListCtrl *) this->FindWindowById(ID_VENDAS_VALREC,this);
	wxTextCtrl *eddesconto= (wxTextCtrl *) this->FindWindowById(ID_VENDAS_DESCONTO,this),
		*edsubtotal= (wxTextCtrl *) this->FindWindowById(ID_VENDAS_TOTAL,this),
		*edtotalgeral= (wxTextCtrl *) this->FindWindowById(ID_VENDAS_TOTAL_GERAL,this),*edtroco=(wxTextCtrl *) this->FindWindowById(ID_VENDAS_TROCO,this);
	wxCheckBox *chkdescperc= (wxCheckBox *) this->FindWindowById(ID_CHK_PERCENTUAL,this);
	wxChoice *cbformapgto= (wxChoice *) this->FindWindowById(ID_VENDAS_FORMAPAGTO,this);
	float fsubtotal=atof(edsubtotal->GetValue().ToAscii()),fdesc=atof(eddesconto->GetValue().ToAscii()),ftotal,fvalrec=0;
	long item=-1;
	wxString tmstr;
	for (;;) {
		item = lstvalpago->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
		if (item == -1)
			break;
		tmstr=get_lstctrl_column_text(lstvalpago,item,1);
		fvalrec+=atof(tmstr.ToAscii());					
	}
		bool desconto_percentual=chkdescperc->GetValue();
		if (desconto_percentual)
			ftotal=fsubtotal-fdesc*0.01*fsubtotal;
		else
			ftotal=fsubtotal-fdesc;
		if (fvalrec<ftotal) {
		////	edtroco->SetValue(_("0.00"));
		//	return;
		}
		tmstr.Printf(_("%.2f"),ftotal);
		edtotalgeral->SetValue(tmstr);
		tmstr.Printf(_("%.2f"),fvalrec-ftotal);
		edtroco->SetValue(tmstr);
////@begin wxEVT_UPDATE_UI event handler for ID_VENDAS_TROCO in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_VENDAS_TROCO in VilaVilela. 
}


/*
 * wxEVT_UPDATE_UI event handler for ID_TEXTCTRL
 */

void VilaVilela::OnVendasTotalGeralUpdate( wxUpdateUIEvent& event ){
	OnVendasTrocoUpdate(event);
////@begin wxEVT_UPDATE_UI event handler for ID_TEXTCTRL in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_TEXTCTRL in VilaVilela. 
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM
 */

void VilaVilela::OnMenuitemClick( wxCommandEvent& event )
{
	_imprimecodbarras(IMPRIME_PRODUTOS_KG);
////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM in VilaVilela.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM in VilaVilela. 
}

