/////////////////////////////////////////////////////////////////////////////
// Name:        dlgprintbarcode.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     Tue 28 Aug 2012 20:07:00 BRT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _DLGPRINTBARCODE_H_
#define _DLGPRINTBARCODE_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/spinctrl.h"
////@end includes


#include "wx/print.h"
#include "wx/printdlg.h"
/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DLGPRINTBARCODE 10094
#define ID_CB_CB_PRESET 10146
#define ID_BT_CB_NPRESET 10147
#define ID_BT_CB_DELPRESET 10148
#define ID_CB_CB_TIPO 11007
#define ID_TXT_CB_NC 10149
#define ID_TXT_CB_AT 10150
#define ID_TXT_CB_MH 10145
#define ID_TXT_CB_MV 11000
#define ID_TXT_CB_DC 11002
#define ID_TXT_CB_DL 11001
#define ID_TXT_CB_LCB 15001
#define ID_TXT_CB_ACB 15000
#define ID_TXT_CB_NEH 11006
#define ID_TXT_CB_NEV 11005
#define SYMBOL_DLGPRINTBARCODE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_DLGPRINTBARCODE_TITLE wxGetTranslation(wxString(wxT("Imprimir c")) + (wxChar) 0x00F3 + wxT("digo de barras"))
#define SYMBOL_DLGPRINTBARCODE_IDNAME ID_DLGPRINTBARCODE
#define SYMBOL_DLGPRINTBARCODE_SIZE wxSize(400, 300)
#define SYMBOL_DLGPRINTBARCODE_POSITION wxDefaultPosition
////@end control identifiers

#include "listas.h"




class EtiquetaInfo {
	public:
		EtiquetaInfo *ant,*prx;
		double CB_MH,CB_MV,CB_DC,CB_DL,CB_LCB,CB_ACB,CB_AT;
		int CB_NC,CB_NEH,CB_NEV,CB_TIPO,padrao;
		char descricao[64];
	};
	
	class LstEtiquetaInfo:public Lista<EtiquetaInfo> {
	public:
		static EtiquetaInfo *etiquetapadrao;
		void novo (const char *descricao,double CB_LCB,double CB_ACB,double CB_AT,double CB_MH,double CB_MV,double CB_DC,double CB_DL,
													int CB_NC,int CB_NEH,int CB_NEV,int CB_TIPO,int padrao=0) {
			novoptr();
			ult->CB_LCB=CB_LCB;
			ult->CB_ACB=CB_ACB;
			ult->CB_AT=CB_AT;
			ult->CB_MH=CB_MH;
			ult->CB_MV=CB_MV;
			ult->CB_DC=CB_DC;
			ult->CB_DL=CB_DL;
			ult->CB_NC=CB_NC;
		 ult->CB_NEH=CB_NEH;
			ult->CB_NEV=CB_NEV;
			ult->CB_TIPO=CB_TIPO;
			ult->padrao=padrao;
			strcpy(ult->descricao,descricao);
		}

		EtiquetaInfo* find_by_descricao ( const char *descricao ) {
			for ( EtiquetaInfo* tb=prm;tb;tb=tb->prx ) {
					if ( strcmp ( tb->descricao,descricao ) ==0 )
						return tb;
				}
			return  0;
		}
		
		void loadfromfile(const char *fname);
		void savetofile(const char *fname);
	};
	
	
	
/*!
 * dlgPrintBarCode class declaration
 */

class dlgPrintBarCode: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( dlgPrintBarCode )
    DECLARE_EVENT_TABLE()

public:
	LstEtiquetaInfo lstetiquetainfo;
	void updatecontrols();
	bool changed();
	void updatelist();
    /// Constructors
    dlgPrintBarCode();
    dlgPrintBarCode( wxWindow* parent, wxWindowID id = SYMBOL_DLGPRINTBARCODE_IDNAME, const wxString& caption = SYMBOL_DLGPRINTBARCODE_TITLE, const wxPoint& pos = SYMBOL_DLGPRINTBARCODE_POSITION, const wxSize& size = SYMBOL_DLGPRINTBARCODE_SIZE, long style = SYMBOL_DLGPRINTBARCODE_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DLGPRINTBARCODE_IDNAME, const wxString& caption = SYMBOL_DLGPRINTBARCODE_TITLE, const wxPoint& pos = SYMBOL_DLGPRINTBARCODE_POSITION, const wxSize& size = SYMBOL_DLGPRINTBARCODE_SIZE, long style = SYMBOL_DLGPRINTBARCODE_STYLE );

    /// Destructor
    ~dlgPrintBarCode();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin dlgPrintBarCode event handler declarations

    /// wxEVT_INIT_DIALOG event handler for ID_DLGPRINTBARCODE
    void OnInitDialog( wxInitDialogEvent& event );

    /// wxEVT_IDLE event handler for ID_DLGPRINTBARCODE
    void OnIdle( wxIdleEvent& event );

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CB_CB_PRESET
    void OnCbCbPresetSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_NPRESET
    void OnBtCbNpresetClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BT_CB_DELPRESET
    void OnBtCbDelpresetClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnImprimeClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
    void OnSalvarClick( wxCommandEvent& event );

////@end dlgPrintBarCode event handler declarations

////@begin dlgPrintBarCode member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end dlgPrintBarCode member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin dlgPrintBarCode member variables
////@end dlgPrintBarCode member variables
};


#define IMPRIME_CODIGO_PRODUTO 1
#define IMPRIME_PRODUTOS_KG 2
class _DbRow;
class _DbResult;
class PrintBarCode: public wxPrintout {
	public:
		int m_numpages;
		_DbResult *glbres;
		_DbRow *curgrav,*currprint;
		dlgPrintBarCode *bcopts;
		int tipoimpressao;
		wxPageSetupDialogData m_page_setup;
		bool performPageSetup(const bool showPageSetupDialog);
		/** the type of paper (letter, A4, etc...) */
		wxPaperSize m_paper_type;
		/** number of pages we want to print. here it's static, but in a real example you will often
		  * want to calculate dynamically once you know the size of the printable area from page setup
		  */
		int m_page_amount;

		/** margins, in millimeters */
		int m_margin_left, m_margin_right, m_margin_top, m_margin_bottom;
		/** will contain the dimensions of the coordinate system, once it's calculated.
      * in the printing callback, you can then draw from (0, 0) to (m_coord_system_width, m_coord_system_height),
      * which will be the area covering the paper minus the margins
      */
    int m_coord_system_width, m_coord_system_height;
				/** horizontal or vertical */
    int m_orient;
		bool preview;
		~PrintBarCode(){
			delete bcopts;
		}
		PrintBarCode ( const wxChar *title = _T ( "Impressao codigo de barras" ) ,int tipoimp=IMPRIME_CODIGO_PRODUTO);
		 wxPrintData getPrintData()
    {
        return m_page_setup.GetPrintData();
    }
    void OnBeginPrinting();
				void OnEndPrinting();
    void OnPreparePrinting();
		bool OnPrintPage ( int page );
		bool HasPage ( int page );
		bool OnBeginDocument ( int startPage, int endPage );
		void GetPageInfo ( int *minPage, int *maxPage, int *selPageFrom, int *selPageTo );
		void DrawPage ( wxDC *dc );
	};

#endif
    // _DLGPRINTBARCODE_H_
