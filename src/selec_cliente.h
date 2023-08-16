/////////////////////////////////////////////////////////////////////////////
// Name:        selec_cliente.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     23/07/2012 14:47:24
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _SELEC_CLIENTE_H_
#define _SELEC_CLIENTE_H_


/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_SELEC_CLIENTE 11135
#define ID_CBSELCLIENTE 10138
#define SYMBOL_SELEC_CLIENTE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_SELEC_CLIENTE_TITLE _("Selecione um cliente")
#define SYMBOL_SELEC_CLIENTE_IDNAME ID_SELEC_CLIENTE
#define SYMBOL_SELEC_CLIENTE_SIZE wxSize(300, 300)
#define SYMBOL_SELEC_CLIENTE_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * selec_cliente class declaration
 */

class selec_cliente: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( selec_cliente )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    selec_cliente();
    selec_cliente( wxWindow* parent, wxWindowID id = SYMBOL_SELEC_CLIENTE_IDNAME, const wxString& caption = SYMBOL_SELEC_CLIENTE_TITLE, const wxPoint& pos = SYMBOL_SELEC_CLIENTE_POSITION, const wxSize& size = SYMBOL_SELEC_CLIENTE_SIZE, long style = SYMBOL_SELEC_CLIENTE_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SELEC_CLIENTE_IDNAME, const wxString& caption = SYMBOL_SELEC_CLIENTE_TITLE, const wxPoint& pos = SYMBOL_SELEC_CLIENTE_POSITION, const wxSize& size = SYMBOL_SELEC_CLIENTE_SIZE, long style = SYMBOL_SELEC_CLIENTE_STYLE );

    /// Destructor
    ~selec_cliente();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin selec_cliente event handler declarations

    /// wxEVT_INIT_DIALOG event handler for ID_SELEC_CLIENTE
    void OnInitDialog( wxInitDialogEvent& event );

////@end selec_cliente event handler declarations

////@begin selec_cliente member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end selec_cliente member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin selec_cliente member variables
////@end selec_cliente member variables
};

#endif
    // _SELEC_CLIENTE_H_
