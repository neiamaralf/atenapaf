/////////////////////////////////////////////////////////////////////////////
// Name:        inserirproduto.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     16/05/2012 14:31:03
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _INSERIRPRODUTO_H_
#define _INSERIRPRODUTO_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/listctrl.h"
////@end includes
#include "wx/timer.h"
/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_INSERIRPRODUTO 10161
#define ID_INSPROD_LIST 10163
#define ID_INSPROD_QUANT 10137
#define wxID_STATICCOMPRA 11120
#define ID_INSPROD_VALCOMPRA 10152
#define SYMBOL_INSERIRPRODUTO_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_INSERIRPRODUTO_TITLE _("Inserir produto")
#define SYMBOL_INSERIRPRODUTO_IDNAME ID_INSERIRPRODUTO
#define SYMBOL_INSERIRPRODUTO_SIZE wxSize(500, 450)
#define SYMBOL_INSERIRPRODUTO_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * Inserirproduto class declaration
 */

class Inserirproduto: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( Inserirproduto )
    DECLARE_EVENT_TABLE()

public:
		wxTimer baltimer;
	void OnTimer(wxTimerEvent &event);
    /// Constructors
		int _ShowModal();
    Inserirproduto();
    Inserirproduto( wxWindow* parent, wxWindowID id = SYMBOL_INSERIRPRODUTO_IDNAME, const wxString& caption = SYMBOL_INSERIRPRODUTO_TITLE, const wxPoint& pos = SYMBOL_INSERIRPRODUTO_POSITION, const wxSize& size = SYMBOL_INSERIRPRODUTO_SIZE, long style = SYMBOL_INSERIRPRODUTO_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_INSERIRPRODUTO_IDNAME, const wxString& caption = SYMBOL_INSERIRPRODUTO_TITLE, const wxPoint& pos = SYMBOL_INSERIRPRODUTO_POSITION, const wxSize& size = SYMBOL_INSERIRPRODUTO_SIZE, long style = SYMBOL_INSERIRPRODUTO_STYLE );

    /// Destructor
    ~Inserirproduto();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin Inserirproduto event handler declarations

    /// wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_INSPROD_LIST
    void OnInsprodListKeyDown( wxListEvent& event );

    /// wxEVT_CHAR event handler for ID_INSPROD_LIST
    void OnChar( wxKeyEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_INSPROD_QUANT
    void OnInsprodQuantUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
    void OnApplyClick( wxCommandEvent& event );

////@end Inserirproduto event handler declarations

////@begin Inserirproduto member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end Inserirproduto member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin Inserirproduto member variables
////@end Inserirproduto member variables
};

#endif
    // _INSERIRPRODUTO_H_
