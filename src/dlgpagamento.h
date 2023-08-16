/////////////////////////////////////////////////////////////////////////////
// Name:        dlgpagamento.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     31/10/2012 10:37:24
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _DLGPAGAMENTO_H_
#define _DLGPAGAMENTO_H_


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
#define ID_DLGPAGAMENTO 10169
#define ID_PAGTO_TIPO 10050
#define ID_PAGTO_VAL 10170
#define SYMBOL_DLGPAGAMENTO_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxSTAY_ON_TOP|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_DLGPAGAMENTO_TITLE _("Pagamento")
#define SYMBOL_DLGPAGAMENTO_IDNAME ID_DLGPAGAMENTO
#define SYMBOL_DLGPAGAMENTO_SIZE wxSize(600, 300)
#define SYMBOL_DLGPAGAMENTO_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * dlgPagamento class declaration
 */

class dlgPagamento: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( dlgPagamento )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    dlgPagamento();
    dlgPagamento( wxWindow* parent, wxWindowID id = SYMBOL_DLGPAGAMENTO_IDNAME, const wxString& caption = SYMBOL_DLGPAGAMENTO_TITLE, const wxPoint& pos = SYMBOL_DLGPAGAMENTO_POSITION, const wxSize& size = SYMBOL_DLGPAGAMENTO_SIZE, long style = SYMBOL_DLGPAGAMENTO_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DLGPAGAMENTO_IDNAME, const wxString& caption = SYMBOL_DLGPAGAMENTO_TITLE, const wxPoint& pos = SYMBOL_DLGPAGAMENTO_POSITION, const wxSize& size = SYMBOL_DLGPAGAMENTO_SIZE, long style = SYMBOL_DLGPAGAMENTO_STYLE );

    /// Destructor
    ~dlgPagamento();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin dlgPagamento event handler declarations

////@end dlgPagamento event handler declarations

////@begin dlgPagamento member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end dlgPagamento member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin dlgPagamento member variables
////@end dlgPagamento member variables
};

#endif
    // _DLGPAGAMENTO_H_
