/////////////////////////////////////////////////////////////////////////////
// Name:        vilavilela.h
// Purpose:
// Author:
// Modified by:
// Created:     08/05/2012 20:34:14
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _VILAVILELA_H_
#define _VILAVILELA_H_

#define DEVELOPING//comentar no produto final
//#define TESTANDO//comentar no produto final
//#define CPPCONN_LIB_BUILD
/*!
* Includes
*/

////@begin includes
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/datectrl.h"
#include "wx/dateevt.h"
#include "wx/tglbtn.h"
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/statusbr.h"
////@end includes

#include "wx/filedlg.h"

#include "wx/textfile.h"
#include "wx/stream.h"
#include "wx/mstream.h"
#include "wx/wfstream.h"
#include "wx/zipstrm.h"
#include "wx/txtstrm.h"
#include "wx/datstrm.h"
#include "wx/image.h"
#include "wx/timer.h"

#include "wx/protocol/ftp.h"

#include "dlgprintbarcode.h"

/*#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include<cppconn/prepared_statement.h>*/
#include "sqlite3.h"
#include "__string.h"
#include "bematech.h"
#include "libpq-fe.h"


/*!
* Forward declarations
*/

////@begin forward declarations
class wxBoxSizer;
////@end forward declarations

/*!
* Control identifiers
*/

////@begin control identifiers
#define ID_MAIN 10000
#define ID_MENUI_CopiaSeg 10038
#define ID_MENUI_RESTAURABKUP 10037
#define ID_MENUITEMLOGINASADMIN 10092
#define ID_MENU_UPDATESITE 10104
#define ID_MNDBHOST 10156
#define ID_MENU_REdX 10040
#define ID_MN_LMFC 10107
#define ID_MN_LMFC_ECF 10108
#define ID_MN_LMFC_ECF_IDATA 10111
#define ID_MN_LMFC_ECF_ICRZ 10110
#define ID_MN_LMFC_ARQ 10109
#define ID_MN_LMFC_ARQ_IDATA 10112
#define ID_MN_LMFC_ARQ_ICRZ 10113
#define ID_MN_LMFC_COTEP1704 10121
#define ID_MN_LMFC_COTEP1704_IDATA 10114
#define ID_MN_LMFC_COTEP1704_ICRZ 10115
#define ID_MN_LMFS 10122
#define ID_MN_LMFS_ECF 10116
#define ID_MN_LMFS_ECF_IDATA 10117
#define ID_MN_LMFS_ECF_ICRZ 10118
#define ID_MN_LMFS_ARQ 10119
#define ID_MN_LMFS_ARQ_IDATA 10120
#define ID_MN_LMFS_ARQ_ICRZ 10123
#define ID_MNESPELHOMFD 10124
#define ID_MNESPELHOMFD_DATA 10125
#define ID_MNESPELHOMFD_COO 10128
#define ID_MNArqMFD 10126
#define ID_MNArqMFD_DATA 10165
#define ID_MNArqMFD_COO 10166
#define ID_MNTabProd 10127
#define ID_MNEstoque 10129
#define ID_MI_ESTOQUE_TOTAL 10078
#define ID_MI_ESTOQUE_PARCIAL 10151
#define ID_MM_MOVECF 10130
#define ID_MENURECIBO 10077
#define ID_MENUITEM 10136
#define ID_MENUBALANCOM 10093
#define ID_MENU_RedZ 10042
#define ID_MENU_RedXArq 10041
#define ID_MENUI_RegAliq 10045
#define ID_MN_CANCELAULTCUPOM 10139
#define ID_MN_CANCELAITEMANT 10140
#define ID_MN_CANCELAITEM 10141
#define ID_TOOLFIRSTREC 10013
#define ID_TOOLPREVREC 10014
#define ID_TOOLNEXTREC 10016
#define ID_TOOLLASTREC 10017
#define ID_TOOLInsert 10015
#define ID_TOOLEdit 10019
#define ID_TOOLCancel 10068
#define ID_MN_DESC_PERCENT 10018
#define ID_MN_INS_PAGTO 10094
#define ID_TOOLDelete 10067
#define ID_MN_PESQPROD 10164
#define ID_TOOLBAR 10002
#define ID_SEARCHCTRL 10001
#define ID_SEARCHDATE1 10087
#define ID_SEARCHDATE2 10086
#define ID_TOOLFILTER 10074
#define ID_NOTEBOOK 10003
#define ID_PGVENDAS 10039
#define ID_STVENDAS_CLIENTE 10158
#define ID_VENDAS_CLIENTE 10035
#define ID_STVENDAS_FORMAPAGTO 10162
#define ID_VENDAS_FORMAPAGTO 10073
#define ID_STVENDAS_NO_NOTA 10159
#define ID_VENDAS_NO_NOTA 10057
#define ID_STVENDAS_DATA 10160
#define ID_VENDAS_DATA 10056
#define ID_PANEL_VENDAS1 10090
#define ID_VENDAS_INSPROD_GRID 10060
#define wxID_STATIC_TOTDESC 10171
#define ID_VENDAS_TOTAL 10050
#define wxID_STATIC_DESCPERC 10096
#define ID_CHK_PERCENTUAL 10131
#define wxID_STATIC_VALDESC 10059
#define ID_VENDAS_DESCONTO 10088
#define wxID_STATIC_VALREC 10065
#define ID_VENDAS_VALREC 10061
#define wxID_STATIC_TOTAL 10036
#define ID_VENDAS_TOTAL_GERAL 10095
#define wxID_STATIC_TROCO 10071
#define ID_VENDAS_TROCO 10063
#define ID_PANEL_VENDAS_OWNER 10091
#define ID_PANEL_VENDAS 10089
#define ID_VENDAS_GRID 10058
#define ID_PGCOMPRAS 10046
#define ID_COMPRAS_FORNEC 10049
#define ID_COMPRAS_DATA 10053
#define ID_COMPRAS_NO_NOTA 10047
#define ID_COMPRAS_BT_INS_PROD 10051
#define ID_COMPRAS_PROD_GRID 10048
#define ID_COMPRAS_TOTAL 10079
#define ID_COMPRAS_GRID 10054
#define ID_PGUNIDADE 10043
#define ID_UNIDADE_DESC 10072
#define ID_UNIDADE_ABREV 10069
#define ID_UNIDADE_GRID 10075
#define ID_PGCLIENTES 10006
#define ID_CLIENT_NOME 10021
#define ID_CLIENT_END 10022
#define ID_CLIENT_COMP 10023
#define ID_CLIENT_EMAIL 10024
#define ID_CLIENT_DATANASC 10025
#define ID_CLIENT_CPF 10026
#define wxID_STATIC_CLFONE 10028
#define ID_CLIENT_INS_FONE 10032
#define ID_CLIENT_DEL_FONE 10082
#define ID_CLIENT_DELALL_FONE 10083
#define ID_CBCLIENTFONES 10029
#define ID_CLIENT_GRID 10064
#define ID_PGFORNEC 10004
#define ID_FORNEC_NOME 10007
#define ID_FORNEC_END 10008
#define ID_FORNEC_COMP 10009
#define ID_FORNEC_EMAIL 10010
#define ID_FORNEC_CONTATO 10011
#define ID_FORNEC_CNPJ 10012
#define wxID_STATIC_FNFONE 10030
#define ID_FORNEC_INS_FONE 10031
#define ID_FORNEC_DEL_FONE 10081
#define ID_FORNEC_DELALL_FONE 10084
#define ID_CBFORNECFONES 10027
#define ID_FORNEC_GRID 10066
#define ID_PGPRODUTOS 10033
#define ID_PROD_NOME 10052
#define ID_PROD_DESC 10034
#define ID_PROD_VALUNIT 10020
#define ID_PROD_UNIT 10070
#define ID_PROD_CATEGORIA 10099
#define ID_PROD_BARCOD 10055
#define ID_PROD_ICMS 10085
#define ID_PROD_SUGESTAO 10105
#define ID_PROD_DESTAQUE 10106
#define ID_PROD_IMG 10098
#define ID_BTPROD_IMG 10097
#define ID_PROD_DELIMAGE 10102
#define ID_PROD_GRID 10062
#define ID_PGFORMAPAGTO 10044
#define ID_FORMAPGTO_DESC 10076
#define ID_FORMAPGTO_GRID 10080
#define ID_PGCATEGORIA 10100
#define ID_CATEGORIA_DESC 10101
#define ID_CATEGORIA_GRID 10103
#define ID_PGALIQUOTAS 10132
#define ID_ALIQUOTAS_DESC 10133
#define ID_ALIQUOTAS_ABREV 10134
#define ID_ALIQUOTAS_TIPO 10157
#define ID_ALIQUOTAS_GRID 10135
#define ID_STATUSBAR 10005
#define SYMBOL_VILAVILELA_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMAXIMIZE|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX|wxWANTS_CHARS
#define SYMBOL_VILAVILELA_TITLE _("AtenaPAF")
#define SYMBOL_VILAVILELA_IDNAME ID_MAIN
#define SYMBOL_VILAVILELA_SIZE wxSize(1000, 800)
#define SYMBOL_VILAVILELA_POSITION wxDefaultPosition
////@end control identifiers
#define ID_FIRSTPOPUP 20000
#ifndef WIN32
#define HANDLE int
#define DWORD int
#define fechabalanca(a,b) {PortaUnconfig(a,b);hCom=0;}
#define PORTACOM4 "/dev/ttyUSB0"
#define PORTACOM5 "/dev/ttyUSB1"
#include <termio.h>
#else
#define fechabalanca(a,b) {CloseHandle(a);hCom=0;}
#define termio int

#define termios DCB
#define PORTACOM4 "COM4"
#endif

/*!
* VilaVilela class declaration
*/
enum __DB_SERVER {__DB_SERVER_MYSQL,__DB_SERVER_SQLITE,__DB_SERVER_POSTGRESQL,__DB_SERVER_MSSQLSERVER};
enum __DB_MODE {__DB_MODE_READ,__DB_MODE_INSERT,__DB_MODE_EDIT,__DB_MODE_UPDATINGGRID};
enum __DB_UPD_MODE {__DB_UPD_MODE_FIRST,__DB_UPD_MODE_LAST};
enum __DB_FIELD_TYPES {__DB_FIELD_TYPE_INT,__DB_FIELD_TYPE_STR,__DB_FIELD_TYPE_DATE,__DB_FIELD_TYPE_FLOAT,__DB_FIELD_TYPE_IMAGE,
                       __DB_FIELD_TYPE_REFS,__DB_FIELD_TYPE_REFM,__DB_FIELD_TYPE_REFN,__DB_FIELD_TYPE_LIST,__DB_FIELD_TYPE_BARCODE,__DB_FIELD_TYPE_NONE
                      };
enum __DB_CTRLS_TYPES {__DB_CTRLS_TYPE_CHECK,__DB_CTRLS_TYPE_TXT,__DB_CTRLS_TYPE_CB,__DB_CTRLS_TYPE_GRID,
                       __DB_CTRLS_TYPE_DATE,__DB_CTRLS_TYPE_LIST,__DB_CTRLS_TYPE_BUTTON,__DB_CTRLS_TYPE_BUTTONIMG,__DB_CTRLS_TYPE_STATICIMG,__DB_CTRLS_TYPE_NONE
                      };
#define NUM_TABS 14

#define FIELD_FLAG_NOTNULL 1
#define FIELD_FLAG_DEFAULTZERO 2



class FieldInfo {
	public:
		FieldInfo *ant,*prx;
		int idctrl,reftable,reftable2,reffield;
		char fieldname[32],fieldnameref[32],search_menulabel[32];
		int flag,fieldindex;
		bool soadmin;
		__DB_FIELD_TYPES field_type;
		__DB_CTRLS_TYPES control_type;
	};

class menuitemdado:public wxObjectRefData {
	public:
		FieldInfo *fi,*searchfield;
		int searchtable;

		menuitemdado() :wxObjectRefData() {
			fi=NULL;
			searchtable=-1;
			searchfield=NULL;
		}
		menuitemdado ( int _searchtable,FieldInfo *_searchfield,FieldInfo *_fi ) :wxObjectRefData() {
			fi=_fi;
			searchtable=_searchtable;
			searchfield=_searchfield;
		}
		                                    
       menuitemdado(const menuitemdado& it):wxObjectRefData(){*this=it;}    
        menuitemdado& operator=(const menuitemdado& it){			
									fi=it.fi;
									searchfield=it.searchfield;
									searchtable=it.searchtable;				
									return *this;
								}
	};

class LstFieldInfo:public Lista<FieldInfo> {
	public:
		void novo ( int fieldindex,const char *search_menulabel,const char* fieldname,int idctrl,__DB_FIELD_TYPES field_type=__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPES control_type=__DB_CTRLS_TYPE_TXT,
		            int reftable=-1,int reffield=-1,const char *fieldnameref=0,int flag=0,int reftable2=-1,bool soadmin =false) {
			novoptr();
			ult->idctrl=idctrl;
			ult->field_type=field_type;
			ult->reftable=reftable;
			ult->reftable2=reftable2;
			ult->reffield=reffield;
			ult->fieldindex=fieldindex;
			ult->flag=flag;
			ult->soadmin=soadmin;
			if ( fieldnameref )
				strcpy ( ult->fieldnameref,fieldnameref );
			else
				*ult->fieldnameref=0;
			ult->control_type=control_type;
			strcpy ( ult->fieldname,fieldname );
			if ( search_menulabel )
				strcpy ( ult->search_menulabel,search_menulabel );
			else
				*ult->search_menulabel=0;
		}

		FieldInfo* find_by_name ( char *name ) {
			for ( FieldInfo* tb=prm;tb;tb=tb->prx ) {
					if ( strcmp ( tb->fieldname,name ) ==0 )
						return tb;
				}
			return  0;
		}
	};

class TableInfo {
	public:
		TableInfo *ant,*prx;
		int indtablename;
		int pageid;
		int idfirstctrl;
		LstFieldInfo fields;
		wxNotebookPage* page;
		int bmp;
		wxString label;
		int pageindex;
	};


class LstTableInfo:public Lista<TableInfo> {
	public:
		void novo ( int indtablename,int pageid,int idfirstctrl,int pageindex ) ;

		TableInfo* find_by_pageid ( int pageid ) {
			for ( TableInfo* tb=prm;tb;tb=tb->prx ) {
					if ( tb->pageid==pageid )
						return tb;
				}
			return  0;
		}

		TableInfo* find_by_tableid ( int tableid ) {
			for ( TableInfo* tb=prm;tb;tb=tb->prx ) {
					if ( tb->indtablename==tableid )
						return tb;
				}
			return  0;
		}
	};

class CellInfo {
	public:
		CellInfo *ant,*prx;
		int collumn;
		int reffield;
		wxString str;
	};


class LstCellInfo:public Lista<CellInfo> {
	public:
		LstCellInfo() {}
		LstCellInfo ( LstCellInfo* lstcinfo ) {
			CellInfo* cinfo;
			if ( lstcinfo ) {
					for ( cinfo=lstcinfo->prm;cinfo;cinfo=cinfo->prx )
						novo ( cinfo->collumn,cinfo->reffield,cinfo->str );
				}
		}
		void novo ( int collumn,int reffield,const wxString &str ) {
			novoptr();
			ult->collumn=collumn;
			ult->reffield=reffield;
			ult->str=str;
			ult->str.Replace ( _ ( "," ),_ ( "." ) );
		}

		CellInfo* find_by_collumn ( int collumn ) {
			for ( CellInfo* tb=prm;tb;tb=tb->prx ) {
					if ( tb->collumn==collumn )
						return tb;
				}
			return  0;
		}
	};

class MyPrintout: public wxPrintout {
	public:
		int firstheight ,itemscount;
		MyPrintout ( const wxChar *title = _T ( "Impressao" ) ) :wxPrintout ( title ) {}
		bool OnPrintPage ( int page );
		bool HasPage ( int page );
		bool OnBeginDocument ( int startPage, int endPage );
		void GetPageInfo ( int *minPage, int *maxPage, int *selPageFrom, int *selPageTo );
		void DrawPage ( wxDC *dc );
	};



#define BALANCO_ANUAL 0
#define BALANCO_MENSAL 1


class PrimaryKey {
	public:
		PrimaryKey *ant,*prx;
		int id;
	};

class ListPrimaryKey:public Lista<PrimaryKey> {
	public:
		void novo ( int id ) {
			novoptr();
			ult->id=id;
		}
	};

class _DbCell {
	public:
		void *val;
		__DB_FIELD_TYPES type;

		_DbCell() {
			reset();
		}

		~_DbCell() {
			if ( val ) {
					free ( val );
					reset();
				}
		}

		void reset() {
			val=NULL;
			type=__DB_FIELD_TYPE_NONE;
		}

		bool Create ( __DB_FIELD_TYPES _type,void *_val ) {
			if(_val==NULL)return false;
			switch ( _type ) {
				case __DB_FIELD_TYPE_INT:
					val=malloc ( sizeof ( int ) );
					if ( val!=NULL ) * ( ( int* ) val ) =* ( ( int* ) _val );
					break;
				case __DB_FIELD_TYPE_DATE:
				case __DB_FIELD_TYPE_STR:
					val=malloc ( sizeof ( char ) * ( strlen ( ( char* ) _val ) +1 ) );
					if ( val!=NULL ) strcpy ( ( char* ) val, ( char* ) _val );
					break;
				case __DB_FIELD_TYPE_FLOAT:
					val=malloc ( sizeof ( float ) );
					if ( val!=NULL ) * ( ( float* ) val ) =* ( ( float* ) _val );
					break;
				}
			type=_type;
			return ( val!=NULL );
		}

		int getint() {
			int vint;
			if ( val==NULL ) return 0;
			switch ( type ) {
				case __DB_FIELD_TYPE_INT:
					vint=* ( ( int* ) val );
					break;
				case __DB_FIELD_TYPE_DATE:
				case __DB_FIELD_TYPE_STR:
					vint=atoi ( ( char* ) val );
					break;
				case __DB_FIELD_TYPE_FLOAT:
					vint= ( int ) ( * ( ( float* ) val ) );
					break;
				}
			return vint;
		}

		void getstr ( wxString *str ) {
			if ( val==NULL ) return;
			switch ( type ) {
				case __DB_FIELD_TYPE_INT:
					str->Printf ( _ ( "%d" ),* ( ( int* ) val ) );
					break;
				case __DB_FIELD_TYPE_DATE:
				case __DB_FIELD_TYPE_STR:
					*str=wxString::FromUTF8 ( ( ( char* ) val ) );
					break;
				case __DB_FIELD_TYPE_FLOAT:
					str->Printf ( _ ( "%.2f" ),* ( ( float* ) val ) );
					break;
				}
		}

		void getcstr ( char *str ) {
			if ( val==NULL ) return;
			switch ( type ) {
				case __DB_FIELD_TYPE_INT:
					sprintf ( str,"%d",* ( ( int* ) val ) );
					break;
				case __DB_FIELD_TYPE_DATE:
				case __DB_FIELD_TYPE_STR:
					strcpy ( str, ( char* ) val );
					break;
				case __DB_FIELD_TYPE_FLOAT:
					sprintf ( str,"%.2f",* ( ( float* ) val ) );
					break;
				}
		}
	};

class _DbRow {
	public:
		int ncols;
		_DbCell *cols,*lastcol;

		_DbRow() {
			reset();
		}

		~_DbRow() {
			if ( cols ) {
					delete []cols;
					reset();
				}
		}

		void reset() {
			lastcol=cols=NULL;
			ncols=0;
		}

		int getint ( int icol ) {
			icol--;
			if ( icol<0||icol>=ncols ) return 0;
			return cols[icol].getint();
		}

		wxString getstr ( int icol );
		char* getcstr ( int icol );
		bool init ( int _ncols ) {
			cols=new _DbCell[sizeof ( _DbCell ) *_ncols];
			lastcol=cols+_ncols-1;
			if ( cols!=NULL ) ncols=_ncols;
			else ncols=0;
			return ( cols!=NULL );
		}

	};

class _DbResult {
	public:
		int nrows;
		_DbRow *rows,*current,*lastrow;
		_DbResult() {
			reset();
		}

		~_DbResult() {
			if ( rows ) {
					delete []rows;
					reset();
				}
		}

		void reset() {
			lastrow=current=rows=NULL;
			nrows=0;
		}

		bool first() {
			current=rows;
			return ( current!=NULL );
		}

		bool last() {
			current=lastrow;
			return ( current!=NULL );
		}

		bool next() {
			if ( current==lastrow ) return false;
			current++;
			return ( current!=NULL );
		}

		bool prev() {
			if ( current==rows ) return false;
			current--;
			return ( current!=NULL );
		}

		bool init ( int _nrows,int _ncols ) {
			rows=new _DbRow[sizeof ( _DbRow ) *_nrows];
			if ( rows!=NULL ) {
					nrows=_nrows;
					_DbRow *ptr;
					lastrow=rows+nrows-1;
					for ( ptr=rows;;ptr++ ) {
							ptr->init ( _ncols );
							if ( ptr==lastrow ) break;
						}
				} else nrows=0;
			return ( rows!=NULL );
		}

	};


class chcIdRef:public wxClientData {
	public:
		int val;
		chcIdRef ( int _val ) {
			val=_val;
		}
	};
//#define VILAVIELAMYSQL
//#define VILAVIELASQLITE3
#define VILAVIELAPOSTGRESQL

#ifdef VILAVIELASQLITE3
#define DB_ENGINE ""
#define AUTO_INCREMENT ""
#define INT_PRIMARY_KEY_NOT_NULL "INTEGER PRIMARY KEY NOT NULL"
#define IF_NOT_EXISTS "IF NOT EXISTS"
#define DATETIME "DATETIME"
#define sql_ResultSetd sqlite3_stmt
#define _DBVARd sqlite3
#define sql_Connectiond void
#define sql_PreparedStatement sqlite3_stmt
#endif
#ifdef VILAVIELAMYSQL
#define DB_ENGINE "ENGINE = InnoDB"
#define INT_PRIMARY_KEY_NOT_NULL "INT PRIMARY KEY "
#define IF_NOT_EXISTS "IF NOT EXISTS"
#define AUTO_INCREMENT "AUTO_INCREMENT"
#define DATETIME "DATETIME"
#define sql_ResultSetd sql::ResultSet
#define _DBVARd sql::Statement
#define sql_Connectiond sql::Connection
#define sql_PreparedStatement sql::PreparedStatement
#endif
#ifdef VILAVIELAPOSTGRESQL
#define DB_ENGINE ""
#define INT_PRIMARY_KEY_NOT_NULL "SERIAL PRIMARY KEY "
#define IF_NOT_EXISTS ""
#define AUTO_INCREMENT ""
#define DATETIME "timestamp"
#define sql_ResultSetd PGresult
#define _DBVARd PGconn
#define sql_Connectiond void
#define sql_PreparedStatement char
#endif

class sql_ResultSet {
	public:
		sql_ResultSet() {
			i=j=0;
			res=NULL;
		}
		~sql_ResultSet() {
#ifdef VILAVIELASQLITE3
			sqlite3_finalize ( res );
#endif
#ifdef VILAVIELAMYSQL
			delete res;
#endif
#ifdef VILAVIELAPOSTGRESQL
			PQclear ( res );
#endif
		}
		sql_ResultSetd *res;
		int i,j;//necessario para o postgres
	};

class _DBVAR {
	public:
		_DBVAR() {
			db=NULL;
			con=NULL;
		}
		_DBVARd *db;
		sql_Connectiond *con;
	};
	
	class ECF_info{
	public:
	ECF_info(){
		*Numero_de_fabricacao=*MF_adicional=*Modelo_do_ECF=*Marca_ECF=*tipo_ECF=*versao_SB=*Numero_do_usuario=*CCF=*COO=*IAT=
		*dataUsuario=*dataSWBasico=*horaUsuario=*horaSWBasico=*NumeroCaixa=*CNI=*CNPJUSUARIO=*IEUSUARIO=
		*Nome_do_contribuinte=*Endereco=*NoSubstProp=*Versao_da_biblioteca=0;
	}
		char Numero_de_fabricacao[21],MF_adicional[21],Modelo_do_ECF[21],Marca_ECF[21],tipo_ECF[8],versao_SB[11],Numero_do_usuario[21],CCF[21],COO[21],IAT[6];
		char dataUsuario[21],dataSWBasico[21],horaUsuario[21],horaSWBasico[21],NumeroCaixa[5],CNI[7],CNPJUSUARIO[32],IEUSUARIO[32],
		Nome_do_contribuinte[512],Endereco[256],NoSubstProp[6],Versao_da_biblioteca[10];
	};

class VilaVilela: public wxFrame {
		DECLARE_CLASS ( VilaVilela )
		DECLARE_EVENT_TABLE()
	public:
		wxTimer timer;
		bool conexao_de_seguranca;
		char host[16];
		void verificaestadoimpressora();
		void OnTimer ( wxTimerEvent &event );
		int MODELO_IMPRESSORA;
		__DB_SERVER db_server;
		_DBVAR glb_stmt;
		bool pode_cancelar_cupom,dados_imp_fiscal_ok,impressorabloqueada,impressoraligada;
		static HANDLE hCom;
		termio oldtermio;
		wxString imgpath;
		bool admin;
		int IRetorno;
		wxPrintData *g_printData;
		__DB_MODE db_mode;
		menuitemdado seachfieldinfo[NUM_TABS];
		bool isfiltered[NUM_TABS];

		ListPrimaryKey listprimarykey[NUM_TABS];
  ECF_info ecf;
  char CNPJ_USER[15],IE_USER[15],IM_USER[15],NOME_USER[41];
		char data_abertura_dia[9],hora_abertura_dia[7];		
		char db_host[16];
		_DbResult  *glb_res[NUM_TABS];
		int db_table_id[NUM_TABS];
		static char main_tables[NUM_TABS][32];
		static char main_tablekeys[NUM_TABS][32];
		static char main_tablesortfield[NUM_TABS][32];
		wxToolBarToolBase *_tool[7];
		wxMenuItem *_mnitem[7];
		LstTableInfo lsttableinfo;
		double venda_total;
		void _imprimecodbarras(int tipo);
		bool MemoriaFiscalPorData ( char *buffname=0,int flag=0,bool MFD=false );
		bool MemoriaFiscalPorREDZ ( char *buffname=0,int flag=0,bool MFD=false );
		bool MemoriaFiscalPorDataSerial ( char *buffname=0,int flag=0,bool MFD=false );
		bool MemoriaFiscalPorREDZSerial ( char *buffname=0,int flag=0,bool MFD=false );
		wxString listctrl_get_colomn_text ( wxListCtrl* lst,long item,int column );
		void _enable_disable_notebook_abas(bool enable);
		void _EnableTool(int id,bool enable);
		void _RemoveTool(int id);
		void _AddTool(wxToolBarToolBase *tool,wxMenuItem *mnitem);
		void _loginasadmin();
		int __ini_recibo ( MyPrintout *prout,wxDC *dc,char *cgc );
		int __insere_venda ( MyPrintout *prout,wxDC *dc,char *codigo,char *nome,char *tipounid,char *quant,char *valunit,char *unidade );
		void __termina_recibo ( MyPrintout *prout,wxDC *dc,double valtotal,char *formapagto );
		void __printrecibo ( MyPrintout *prout,wxDC *dc );

  void show_config_dlg(int CONFIG_ITEM);
		bool Analisa_iRetorno ( int IRetorno );
		bool _create_tables(_DBVAR *dbvar);
		void _ini_default_table_values();
		void _clearcontrols ( int pageid,int insert_ref_s=false,bool cleargrid=false );
		void _createsearchpopupmenu ( wxMenu *menu );
		void _createtablesinfos();
		void _db_update ( int pageid,bool selectgridrow=true,bool atualizagrid=true );
		bool _db_walk_around ( bool next,bool updatedb=true );
		void _delete_row ( int pageid );
		void _deleteresult ( sql_ResultSet  **res );
		void _edit_values ( int pageid );
		bool  _verificaconexao(_DBVAR *dbvar);
		int _execquery ( _DBVAR *dbvar, const char *query,bool showerrmsg=true );
		sql_ResultSet  *_execquerywithresult ( _DBVAR *dbvar, const char *query );

		int _execquery ( _DBVAR *dbvar, Palavra &queryfields,bool showerrmsg=true );
		sql_ResultSet  *_execquerywithresult ( _DBVAR *dbvar, Palavra &query );

		int _execquery ( const char *queryfields,bool showerrmsg=true );
		sql_ResultSet  *_execquerywithresult ( const char *query );

		int _execquery ( Palavra &queryfields,bool showerrmsg=true );
		sql_ResultSet  *_execquerywithresult ( Palavra &query );
		void _atualiza_bkupdb();
		void load_config(bool update);
		void _grid_update ( wxListCtrl* grid,long item );
		bool _insert_values ( int pageid );
		void _update_db_cache();
		bool _open_db(_DBVAR *dbvar,bool setflag=true);
		bool _open_secdb(_DBVAR *dbvar,bool showmsg=true,bool setflag=true);
		double _retorna_estoque(int idproduto);
		bool _open_db (const char *_dbname, _DBVAR *dbvar,const char *host,const char *user,const char *password,const char *sqlitedbname );
		bool _prepareStatement ( _DBVAR *db,sql_PreparedStatement **prepstm,const char *prepchar );
		bool prep_stmt_setString ( sql_PreparedStatement	*prep_stmt,int index, const Palavra &val );
		bool prep_stmt_setInt ( sql_PreparedStatement	*prep_stmt,int index,  int val );
		bool prep_stmt_setDouble ( sql_PreparedStatement	*prep_stmt,int index,  float val );
		bool prep_stmt_execute ( sql_PreparedStatement	*prep_stmt );
		void _delete_prep_stmt ( sql_PreparedStatement	**prep_stmt );
		bool _create_tables_and_db();
		bool _nextrow ( sql_ResultSet  *res );
		bool _prevrow ( sql_ResultSet  *res );
		bool _firstrow ( sql_ResultSet  *res );
		bool _lastrow ( sql_ResultSet  *res );
  bool _cancelaitem(wxListCtrl* lstprod,LstCellInfo *lstcellinfo,long itemindex);
		int _getint ( sql_ResultSet  *res,int column );
		int _getint ( sql_ResultSet  *res,const char *columnname );
		wxString _getstring ( sql_ResultSet  *res,int column );
		wxString _getstring ( sql_ResultSet  *res,const char *columnname );
		Palavra _getstringSQL ( sql_ResultSet  *res,int column );
		Palavra _getstringSQL ( sql_ResultSet  *res,const char *columnname );
		__DB_FIELD_TYPES _getColumnType ( sql_ResultSet  *res,int iCol );
		int _getColumnCount ( sql_ResultSet  *res );
		int _rowsCount ( sql_ResultSet  *res );
		void _close_db ( _DBVAR *statmt );
		double _getdouble ( sql_ResultSet  *res,int column );
		double _getdouble ( sql_ResultSet  *res,const char *columnname );
		void _selectfirsttxtctrl ( int pageid );
		void _set_dbmode ( int pageid,__DB_MODE new_mode );
		void _setreadonly_ctrls_of_page ( int pageid,bool enable=true );
		void _delete_gl_res ( int index,bool realoc=true );
		void _fetch_and_update_gl_res ( int i,__DB_UPD_MODE mode,int curgrav=-1,const wxString &filter=wxEmptyString,const wxString &filter2=wxEmptyString );
		int _get_pageid();
		void _restaura_do_bkup ( wxString &dir,wxString &filename );
		void _filter_database ( const wxString &filter,const wxString &filter2=wxEmptyString );
		void _showdlg_insprod();
		void _showdlg_insprodvenda(const wxString &barcode=wxEmptyString);
		void _show_hide_auxcontrols ( int pageid,bool show=true,bool resettotal=true );
		bool _insprod ( wxWindow *dlg );
		bool imprimeitemvenda(LstCellInfo *lstcinfo);
		bool _insprodvenda ( wxWindow *dlg );
		void OnPopUpSearch ( wxCommandEvent& event );
		/// Constructors
		VilaVilela();
		VilaVilela ( wxWindow* parent, wxWindowID id = SYMBOL_VILAVILELA_IDNAME, const wxString& caption = SYMBOL_VILAVILELA_TITLE, const wxPoint& pos = SYMBOL_VILAVILELA_POSITION, const wxSize& size = SYMBOL_VILAVILELA_SIZE, long style = SYMBOL_VILAVILELA_STYLE );

		bool Create ( wxWindow* parent, wxWindowID id = SYMBOL_VILAVILELA_IDNAME, const wxString& caption = SYMBOL_VILAVILELA_TITLE, const wxPoint& pos = SYMBOL_VILAVILELA_POSITION, const wxSize& size = SYMBOL_VILAVILELA_SIZE, long style = SYMBOL_VILAVILELA_STYLE );

		/// Destructor
		~VilaVilela();

		/// Initialises member variables
		void Init();

		/// Creates the controls and sizers
		void CreateControls();

		////@begin VilaVilela event handler declarations

    /// wxEVT_SIZE event handler for ID_MAIN
    void OnSize( wxSizeEvent& event );

    /// wxEVT_KEY_DOWN event handler for ID_MAIN
    void OnKeyDown( wxKeyEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUI_CopiaSeg
    void OnMENUICopiaSegClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUI_RESTAURABKUP
    void OnMenuiRestaurabkupClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEMLOGINASADMIN
    void OnMenuitemloginasadminClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENU_UPDATESITE
    void OnMenuUpdatesiteClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNDBHOST
    void OnMndbhostClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENU_REdX
    void OnMENUREdXClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFC_ECF_IDATA
    void OnMnLmfcEcfIdataClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFC_ECF_ICRZ
    void OnMnLmfcEcfIcrzClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFC_ARQ_IDATA
    void OnMnLmfcArqIdataClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFC_ARQ_ICRZ
    void OnMnLmfcArqIcrzClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFC_COTEP1704_IDATA
    void OnMnLmfcCotep1704IdataClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFC_COTEP1704_ICRZ
    void OnMnLmfcCotep1704IcrzClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFS_ECF_IDATA
    void OnMnLmfsEcfIdataClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFS_ECF_ICRZ
    void OnMnLmfsEcfIcrzClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFS_ARQ_IDATA
    void OnMnLmfsArqIdataClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_LMFS_ARQ_ICRZ
    void OnMnLmfsArqIcrzClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNESPELHOMFD_DATA
    void OnMnespelhomfdDataClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNESPELHOMFD_COO
    void OnMnespelhomfdCooClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNArqMFD_DATA
    void OnMNArqMFDDATAClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNArqMFD_COO
    void OnMNArqMFDCOOClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MNTabProd
    void OnMNTabProdClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_TOTAL
    void OnMiEstoqueTotalClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MI_ESTOQUE_PARCIAL
    void OnMiEstoqueParcialClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MM_MOVECF
    void OnMmMovecfClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENURECIBO
    void OnMenureciboClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM
    void OnMenuitemClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUBALANCOM
    void OnMenubalancomClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENU_RedZ
    void OnMENURedZClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENU_RedXArq
    void OnMENURedXArqClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUI_RegAliq
    void OnMENUIRegAliqClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_CANCELAULTCUPOM
    void OnMnCancelaultcupomClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_CANCELAITEMANT
    void OnMnCancelaitemantClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_CANCELAITEM
    void OnMnCancelaitemClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLFIRSTREC
    void OnToolfirstrecClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLPREVREC
    void OnToolprevrecClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLNEXTREC
    void OnToolnextrecClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLLASTREC
    void OnToollastrecClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLInsert
    void OnTOOLInsertClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLEdit
    void OnTOOLEditClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLCancel
    void OnTOOLCancelClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_DESC_PERCENT
    void OnMnDescPercentClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_INS_PAGTO
    void OnMnInsPagtoClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOLDelete
    void OnTOOLDeleteClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_PESQPROD
    void OnVendasBtinsprodClick( wxCommandEvent& event );

    /// wxEVT_RIGHT_DOWN event handler for ID_TOOLBAR
    void OnRightDown( wxMouseEvent& event );

    /// wxEVT_COMMAND_TEXT_ENTER event handler for ID_SEARCHCTRL
    void OnSearchctrlEnter( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_TOOLFILTER
    void OnToolfilterClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MN_PESQPROD
    void OnMnPesqprodClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
    void OnNotebookPageChanged( wxNotebookEvent& event );

    /// wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING event handler for ID_NOTEBOOK
    void OnNotebookPageChanging( wxNotebookEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_PGVENDAS
    void OnPgvendasUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_LIST_DELETE_ITEM event handler for ID_VENDAS_INSPROD_GRID
    void OnVendasInsprodGridDeleteItem( wxListEvent& event );

    /// wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_VENDAS_INSPROD_GRID
    void OnVendasInsprodGridDeleteAllItems( wxListEvent& event );

    /// wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_VENDAS_INSPROD_GRID
    void OnVendasInsprodGridKeyDown( wxListEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_VENDAS_INSPROD_GRID
    void OnVendasInsprodGridUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_VENDAS_DESCONTO
    void OnVendasDescontoTextUpdated( wxCommandEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_VENDAS_TOTAL_GERAL
    void OnVendasTotalGeralUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_VENDAS_TROCO
    void OnVendasTrocoUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_VENDAS_GRID
    void OnGridSelected( wxListEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_COMPRAS_BT_INS_PROD
    void OnComprasBtInsProdClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_LIST_DELETE_ITEM event handler for ID_COMPRAS_PROD_GRID
    void OnComprasProdGridDeleteItem( wxListEvent& event );

    /// wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS event handler for ID_COMPRAS_PROD_GRID
    void OnComprasProdGridDeleteAllItems( wxListEvent& event );

    /// wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_COMPRAS_PROD_GRID
    void OnComprasProdGridKeyDown( wxListEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_COMPRAS_PROD_GRID
    void OnComprasProdGridUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_INS_FONE
    void OnClientInsFoneClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_DEL_FONE
    void OnClientDelFoneClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CLIENT_DELALL_FONE
    void OnClientDelallFoneClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_INS_FONE
    void OnFornecInsFoneClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DEL_FONE
    void OnFornecDelFoneClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FORNEC_DELALL_FONE
    void OnFornecDelallFoneClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BTPROD_IMG
    void OnBtprodImgClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_PROD_DELIMAGE
    void OnProdDelimageClick( wxCommandEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_STATUSBAR
    void OnStatusbarUpdate( wxUpdateUIEvent& event );

		////@end VilaVilela event handler declarations

		////@begin VilaVilela member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
		////@end VilaVilela member function declarations

		/// Should we show tooltips?
		static bool ShowToolTips();

		////@begin VilaVilela member variables
    wxBoxSizer* vendassizerv;
    wxBoxSizer* vendasprodsizer;
		////@end VilaVilela member variables
	};

class Fiscal_Printer {
	public:
		static char ST1_ERRORS[][48];
		static char ST2_ERRORS[][48];
		static bool parse_printer_bytes ( char _ACK,char _ST1,char _ST2 );
		static int montacmd ( char **buf,char *cmd );
		static HANDLE _AbrePorta ( const char* devName,  termios* pnewTermio,  termios* pOldTermio );
		static int _WriteBytes ( HANDLE porta,char *bytes,DWORD lenght );
		static int _ReadBytes ( HANDLE porta,char *bytes,DWORD lenght );
		static void _FechaPorta ( HANDLE porta, termios* pOldTermio );
		static bool _sendcmdtoprinter ( char *cmdbuf,char *bufread,DWORD lenghtread,DWORD *BytesRead );
		static int reducao_X();
		static int abre_cupom_fiscal();
		static int cancela_cupom_fiscal();
	};
struct stCNI_ECF {
		char CNI[7],MARCA[16],MODELO[20],VERSAOSB[16];
	};
#define NUM_MODELOS_ECFS 194
extern VilaVilela* vilavielaframe;
extern int   retpeso ( char szBuff[20] ) ;
extern char FLAG_LEITURA[2][4];
extern stCNI_ECF CNI_ECF[NUM_MODELOS_ECFS];
extern void add_lstctrl_column ( wxListCtrl* lstctrl,const wxString &label,int indcolumn,int width );
extern void set_lstctrl_column ( wxListCtrl* lstctrl,const char *text,int indcolumn,int id,LstCellInfo *lstcellinfo,int reffield);
extern void insert_lstctrl_item ( wxListCtrl* lstctrl,const char *text,int id,LstCellInfo **lstcellinfo,int reffield);
extern void set_lstctrl_column ( wxListCtrl* lstctrl,wxString &text,int indcolumn,int id,LstCellInfo *lstcellinfo,int reffield);
extern void insert_lstctrl_item ( wxListCtrl* lstctrl,wxString &text,int id,LstCellInfo **lstcellinfo,int reffield);
extern wxString get_lstctrl_column_text ( wxListCtrl* lstctrl,long item,int indcolumn);
extern bool _lstctrl_find ( wxListCtrl* lstctrl,const wxString &str,int column );
#ifdef WIN32
#include "iso8859str.str"
#else
#include "utf8str.str"
#endif

#define IGNORETESTEIMPRESSORA
#define NENHUMRELATORIO() return
#define NENHUMRELATORIO2() impressorabloqueada=false;return;
#ifndef TESTANDO
#define MODOTESTE()
#define TESTA_IMPRESSORA_VALIDA() verificaestadoimpressora();\
if(!impressoraligada){wxMessageBox(_("Conecte ou ligue a impressora fiscal e tente novamente!"));return;}\
else if(impressorabloqueada){wxMessageBox(_("Impressora bloqueada!"));return;}

#define TESTA_IMPRESSORA_VALIDABOOL() verificaestadoimpressora();\
if(!impressoraligada){wxMessageBox(_("Conecte ou ligue a impressora fiscal e tente novamente!"));return false;}\
else if(impressorabloqueada){wxMessageBox(_("Impressora bloqueada!"));return false;}
#else
#define MODOTESTE() return
#define TESTA_IMPRESSORA_VALIDA()
#define TESTA_IMPRESSORA_VALIDABOOL()
#endif

#define ___(a) wxString::From8BitData((a))

#define CODE_3_9 0
#define CODE_128_A 1
#define CODE_128_B 2
#define CODE_128_C 3
#define CODE_UPC_A 4
#define CODE_EAN_13 5
#define CODE_EAN_8 6

#define CONFIG_FNAME "config.conf" 
#define CONFIG_DBHOST 1

#define DEFAULT_IMG_SIZE 146
#define TABLE_fornecedores 0
#define TABLE_cliente 1
#define TABLE_produtos 4
#define TABLE_unidade 2
#define TABLE_vendas 5
#define TABLE_compras 6
#define TABLE_fones_cliente 7
#define TABLE_fones_fornec 8
#define TABLE_produto_entrada 9
#define TABLE_saida 10
#define TABLE_formapagto 3
#define TABLE_categoria 11
#define TABLE_aliquotas 12
#define TABLE_vendapagtos 13
#define _IMAGE_DIR "./_imagens/"
#define USANDO_EMULADOR
extern int _sign_file(const char* xml_file, const char* key_file, const char* cert_file,const char *pass) ;
extern int conecta_receita();
#define LIST_CTRL_FIND_SECONDS 4
#endif
// _VILAVILELA_H_
