/////////////////////////////////////////////////////////////////////////////
// Name:        inserirproduto.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     16/05/2012 14:31:03
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
#include "inserirproduto.h"
#ifndef WIN32
#include "kernel.h"
#else

#endif
VilaVilela* vilavielaframe;
////@begin XPM images
////@end XPM images


/*
 * Inserirproduto type definition
 */

IMPLEMENT_DYNAMIC_CLASS( Inserirproduto, wxDialog )


/*
 * Inserirproduto event table definition
 */

BEGIN_EVENT_TABLE( Inserirproduto, wxDialog )

////@begin Inserirproduto event table entries
    

    EVT_UPDATE_UI( ID_INSPROD_QUANT, Inserirproduto::OnInsprodQuantUpdate )

    EVT_BUTTON( wxID_APPLY, Inserirproduto::OnApplyClick )

////@end Inserirproduto event table entries
#ifndef WIN32
EVT_LIST_KEY_DOWN( ID_INSPROD_LIST, Inserirproduto::OnInsprodListKeyDown )
#endif
EVT_TIMER(1000,Inserirproduto::OnTimer)
END_EVENT_TABLE()


/*
 * Inserirproduto constructors
 */

Inserirproduto::Inserirproduto():baltimer(this,1000)
{
    Init();
				
}


	int  Inserirproduto::_ShowModal(){
			 wxListCtrl* lstprod= ( wxListCtrl* ) this->FindWindowById ( ID_INSPROD_LIST,this );
				lstprod->SetFocus();
				return ShowModal();
		}

Inserirproduto::Inserirproduto( wxWindow* parent, wxWindowID id, 
																																const wxString& caption, const wxPoint& pos,
																																const wxSize& size, long style ):baltimer(this,1000){
	Init();	
	Create(parent, id, caption, pos, size, style);
	wxListCtrl* lstprod=(wxListCtrl*)this->FindWindowById(ID_INSPROD_LIST,this); 
	add_lstctrl_column ( lstprod,___ ("Nome"),0,140);
	add_lstctrl_column ( lstprod,___ ("Descrição"),1,110);
	add_lstctrl_column ( lstprod,___ ("Unidade"),2,110);
	add_lstctrl_column ( lstprod,___ ( "Preço" ),3,60 );
	add_lstctrl_column ( lstprod,___ ( "Estoque" ),4,60 );
		wxListItem itemCol;
	Palavra query;
	sql_ResultSet  *res2;
	wxString tmpstr;
	LstCellInfo *lstcellinfo;
	double quantestoque;
	query="SELECT prod.idproduto,prod.nome,prod.descricao,unid.abrev,unid.idunidade,prod.val_unit_venda \
							FROM unidade AS unid,produtos AS prod \
							WHERE unid.idunidade=prod.idunidade \
							ORDER BY prod.nome";	
	if((res2=vilavielaframe->_execquerywithresult(query))!=0){			
		int i=0;
		while (vilavielaframe->_nextrow(res2)) {	
			insert_lstctrl_item (lstprod,vilavielaframe->_getstringSQL ( res2,2 ).c_str(),i,&lstcellinfo,vilavielaframe->_getint ( res2,1 ));
			set_lstctrl_column (lstprod,vilavielaframe->_getstringSQL ( res2,3 ).c_str(),1,i,lstcellinfo,-1);
			set_lstctrl_column (lstprod,vilavielaframe->_getstringSQL ( res2,4 ).c_str(),2,i,lstcellinfo,vilavielaframe->_getint ( res2,5 ));
			set_lstctrl_column (lstprod,vilavielaframe->_getstringSQL ( res2,6 ).c_str(),3,i,NULL,-1);   
			quantestoque=vilavielaframe->_retorna_estoque(vilavielaframe->_getint ( res2,1 ));
			lstprod->SetItemBackgroundColour ( i,quantestoque<=0?wxColour(255,0,0 ):wxColour(255,255,255) );			
			tmpstr.Printf ( _ ( "%.3f" ),quantestoque );
			set_lstctrl_column (lstprod,tmpstr.To8BitData().data(),4,i++,NULL,-1);	

		}
		lstprod->SetColumnWidth(0, 100 );
		lstprod->SetColumnWidth(1, 100 );
		lstprod->SetAutoLayout(true);			
		lstprod->Update();
		lstprod->Show();
		lstprod->GetParent()->Layout();		
		vilavielaframe->_deleteresult(&res2);
	}	
#ifndef WIN32
if((vilavielaframe->hCom = PortaConfig( PORTACOM5, 2400, &vilavielaframe->oldtermio )) <= 0 )vilavielaframe->hCom=0; 
#endif
}


/*
 * Inserirproduto creator
 */

bool Inserirproduto::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin Inserirproduto creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end Inserirproduto creation
    return true;
}


/*
 * Inserirproduto destructor
 */

Inserirproduto::~Inserirproduto()
{
	baltimer.Stop();
#ifndef WIN32
	PortaUnconfig( vilavielaframe->hCom, &vilavielaframe->oldtermio );
#endif
////@begin Inserirproduto destruction
////@end Inserirproduto destruction
}


/*
 * Member initialisation
 */

void Inserirproduto::Init()
{

////@begin Inserirproduto member initialisation
////@end Inserirproduto member initialisation
}


/*
 * Control creation for Inserirproduto
 */

void Inserirproduto::CreateControls()
{    
////@begin Inserirproduto content construction
    Inserirproduto* itemDialog1 = this;

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

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATICCOMPRA, wxGetTranslation(wxString(wxT("Valor unit")) + (wxChar) 0x00E1 + wxT("rio compra")), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText8, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl9 = new wxTextCtrl( itemDialog1, ID_INSPROD_VALCOMPRA, wxEmptyString, wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer5->Add(itemTextCtrl9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer10 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("&Inserir e fechar"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton11->SetDefault();
    itemStdDialogButtonSizer10->AddButton(itemButton11);

    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer10->AddButton(itemButton12);

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_APPLY, _("&Inserir"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer10->AddButton(itemButton13);

    itemStdDialogButtonSizer10->Realize();

    // Connect events and objects
    itemListCtrl4->Connect(ID_INSPROD_LIST, wxEVT_CHAR, wxKeyEventHandler(Inserirproduto::OnChar), NULL, this);
////@end Inserirproduto content construction
}


/*
 * Should we show tooltips?
 */

bool Inserirproduto::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap Inserirproduto::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin Inserirproduto bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end Inserirproduto bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon Inserirproduto::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin Inserirproduto icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end Inserirproduto icon retrieval
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
 */

void Inserirproduto::OnApplyClick( wxCommandEvent& event ){
	if(vilavielaframe->_insprod(this)){
		((wxTextCtrl*)this->FindWindowById(ID_INSPROD_QUANT,this))->Clear();
		((wxTextCtrl*)this->FindWindowById(ID_INSPROD_VALCOMPRA,this))->Clear();
		wxListCtrl* lstprod=(wxListCtrl*)this->FindWindowById(ID_INSPROD_LIST,this); 
		lstprod->SetFocus();
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY in Inserirproduto.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY in Inserirproduto. 
}


/*
 * wxEVT_UPDATE_UI event handler for ID_INSPROD_QUANT
 */


int sendpeso(){
 char buf[7];
 DCB dcb;	
 char szBuff[20];
	BOOL fSuccess;
 HANDLE h;
 	h = CreateFile( _("COM5"),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0, NULL );
  if (h == INVALID_HANDLE_VALUE) {h=0;return (0);}
		SecureZeroMemory(&dcb, sizeof(DCB));
		dcb.DCBlength = sizeof(DCB);
		fSuccess = GetCommState(h, &dcb);
		if (!fSuccess) return 0;
		dcb.BaudRate = CBR_2400;     //  baud rate
		dcb.ByteSize = 8;             //  data size, xmit and rcv
		dcb.Parity   = NOPARITY;      //  parity bit
		dcb.StopBits = ONESTOPBIT;    //  stop bit
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		fSuccess = SetCommState(h, &dcb);
		if (!fSuccess) return 0;
		fSuccess = GetCommState(h, &dcb);
		if (!fSuccess) return 0;
		COMMTIMEOUTS   CommTimeouts; 
		GetCommTimeouts (vilavielaframe->hCom, &CommTimeouts);
		CommTimeouts.ReadIntervalTimeout = 50; 
	CommTimeouts.ReadTotalTimeoutConstant = 50; 
	CommTimeouts.ReadTotalTimeoutMultiplier=10;
	CommTimeouts.WriteTotalTimeoutMultiplier=10;
	CommTimeouts.WriteTotalTimeoutConstant = 50; 
  
		if (!SetCommTimeouts (vilavielaframe->hCom, &CommTimeouts)) 
	{ 
        MessageBox (NULL, L"Could not create the read thread.(SetCommTimeouts Failed)" ,L"Error", MB_OK);
		return 0; 
	} 
  DWORD myBytesRead = 0;
  ReadFile(h, szBuff, 1, &myBytesRead, NULL);		
if(	szBuff[0] == 0x05) /* ENQ */
{
DWORD write=1; // Number of bytes to write to serial port
buf[0] = 0x02;
WriteFile(h,buf,write,&write,NULL);
write=20; 
memcpy((void*)szBuff,"00000000000000001234",20);
WriteFile(h,szBuff,write,&write,NULL);
buf[0] = 0x03;
write=1; 
WriteFile(h,buf,write,&write,NULL);
}
  

	


 CloseHandle(h);
 return 1;
}

int retpeso(char szBuff[20]){
	static char buf[7];
	#ifdef WIN32
	DCB dcb;	
	BOOL fSuccess;
 //sendpeso();return 0;
	if(!vilavielaframe->hCom|(vilavielaframe->hCom == INVALID_HANDLE_VALUE)){
		vilavielaframe->hCom = CreateFile( _(PORTACOM4),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0, NULL );
  if (vilavielaframe->hCom == INVALID_HANDLE_VALUE) {vilavielaframe->hCom=0;return (0);}
		SecureZeroMemory(&dcb, sizeof(DCB));
		dcb.DCBlength = sizeof(DCB);
		fSuccess = GetCommState(vilavielaframe->hCom, &dcb);
		if (!fSuccess) return 0;
		dcb.BaudRate = CBR_2400;     //  baud rate
		dcb.ByteSize = 8;             //  data size, xmit and rcv
		dcb.Parity   = NOPARITY;      //  parity bit
		dcb.StopBits = ONESTOPBIT;    //  stop bit
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		


		fSuccess = SetCommState(vilavielaframe->hCom, &dcb);
		if (!fSuccess) return 0;
		fSuccess = GetCommState(vilavielaframe->hCom, &dcb);
		if (!fSuccess) return 0;
		COMMTIMEOUTS   CommTimeouts; 
		GetCommTimeouts (vilavielaframe->hCom, &CommTimeouts);
		CommTimeouts.ReadIntervalTimeout = 50; 
	CommTimeouts.ReadTotalTimeoutConstant = 50; 
	CommTimeouts.ReadTotalTimeoutMultiplier=10;
	CommTimeouts.WriteTotalTimeoutMultiplier=10;
	CommTimeouts.WriteTotalTimeoutConstant = 50; 
  
		if (!SetCommTimeouts (vilavielaframe->hCom, &CommTimeouts)) 
	{ 
        MessageBox (NULL, L"Could not create the read thread.(SetCommTimeouts Failed)" ,L"Error", MB_OK);
		return 0; 
	} 
	}
	
	DWORD write=1; // Number of bytes to write to serial port
	buf[0] = 0x05; /* ENQ */
	BOOL ret=WriteFile(vilavielaframe->hCom,buf,write,&write,NULL);
	if(!ret)return 0;
	DWORD myBytesRead = 0;
	ReadFile(vilavielaframe->hCom, szBuff, 20, &myBytesRead, NULL);		
	if(myBytesRead==0)return 0;
#else
 if(!vilavielaframe->hCom)return 0;
 if(!enviaENQ( vilavielaframe->hCom ))return 0;   
 if(recebeBuffer( vilavielaframe->hCom, szBuff ) <= 0 )  return 0;
#endif
	return 1;
}

static wxString st_tmpstr=wxEmptyString;

void Inserirproduto::OnTimer(wxTimerEvent &event){
		wxListCtrl* lstprod=(wxListCtrl*)this->FindWindowById(ID_INSPROD_LIST,this);
	long item = -1;
	int peso;
	static int tinterv=0;
	if(tinterv==LIST_CTRL_FIND_SECONDS){
		tinterv=0;
	st_tmpstr=wxEmptyString;
	}
	tinterv++;
	item = lstprod->GetNextItem(item,	wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
	if ( item != -1 ){		
		wxString tmpstr;	
 	tmpstr=vilavielaframe->listctrl_get_colomn_text(lstprod,item,2);
		if(tmpstr==_("kg")||tmpstr==_("Kg")||tmpstr==_("KG")){			
			static char buf[20]= "",preco[8]="",total[20]="",*ptrbuf;		
			if(retpeso(buf)&&(*(ptrbuf=buf+1)!='I'&&*ptrbuf!='N'&&*ptrbuf!='S')){				
				ptrbuf[strlen(ptrbuf)-1]=0;			
				peso=atoi(ptrbuf);
				tmpstr.Printf(_("%.3f"),peso/1000.0);//=wxString::FromAscii(buf);
				((wxTextCtrl*)this->FindWindowById(ID_INSPROD_QUANT,this))->SetValue(tmpstr);
			}						
		}
	}
}

void Inserirproduto::OnInsprodQuantUpdate( wxUpdateUIEvent& event ){

////@begin wxEVT_UPDATE_UI event handler for ID_INSPROD_QUANT in Inserirproduto.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_UPDATE_UI event handler for ID_INSPROD_QUANT in Inserirproduto. 
}


/*
 * wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_INSPROD_LIST
 */

void Inserirproduto::OnInsprodListKeyDown( wxListEvent& event ){
	int ccode=event.GetKeyCode();
	static char buf[32];
	static int index=-1,pstx_etx=0;
	switch ( ccode ) {
#ifndef WIN32
	case WXK_CONTROL://possible STX ou ETX
		pstx_etx=1;
		break;
	case 66://more possible STX->B
		if ( pstx_etx==1 ) {
			index=0;
			pstx_etx=0;
			break;
		}		
#else
		case 2://STX->0x02		
			index=0;
			break;		
#endif
#ifndef WIN32
	case 67://more possible ETX->C
#else
 case 3://ETX->0x03
		pstx_etx=1;
#endif
		if ( pstx_etx==1&&index>0) { //ETX
			buf[index]=0;
			Palavra query;
			sql_ResultSet  *res;
			query="SELECT nome	FROM produtos WHERE barcode='";
			query.append(buf);query.append("'");			
			if ( (  res=vilavielaframe->_execquerywithresult ( query ) ) !=0 ) {
				if ( vilavielaframe->_nextrow ( res ) ) {
						wxListCtrl* lstprod= ( wxListCtrl* ) this->FindWindowById ( ID_INSPROD_LIST,this );	
					if(_lstctrl_find(lstprod,vilavielaframe->_getstring(res,1),1)){
						this->FindWindowById ( ID_INSPROD_QUANT,this )->SetFocus();						
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
		if ( index!=-1 ) {
			buf[index++]=ccode;
		} 
		else {
			wxListCtrl* lstprod= ( wxListCtrl* ) this->FindWindowById ( ID_INSPROD_LIST,this );
#ifdef WIN32
			st_tmpstr=st_tmpstr+wxString::FromAscii((char)ccode);
#else
			st_tmpstr.Append((wchar_t)ccode);	
#endif
			_lstctrl_find(lstprod,st_tmpstr,1);
		}
	}
////@begin wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_INSPROD_LIST in Inserirproduto.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_INSPROD_LIST in Inserirproduto. 
}


/*
 * wxEVT_CHAR event handler for ID_INSPROD_LIST
 */

void Inserirproduto::OnChar( wxKeyEvent& event )
{
#ifdef WIN32
	wxListEvent levt;
	levt.m_code=event.GetKeyCode();
	OnInsprodListKeyDown(levt);
#endif
////@begin wxEVT_CHAR event handler for ID_INSPROD_LIST in Inserirproduto.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_CHAR event handler for ID_INSPROD_LIST in Inserirproduto. 
}

