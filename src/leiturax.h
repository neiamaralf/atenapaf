/////////////////////////////////////////////////////////////////////////////
// Name:        leiturax.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     23/05/2012 10:58:31
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _LEITURAX_H_
#define _LEITURAX_H_


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
#define ID_LEITURAX 10144
#define ID_TEXTLEITURAX 10173
#define SYMBOL_LEITURAX_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL
#define SYMBOL_LEITURAX_TITLE _("Leitura X")
#define SYMBOL_LEITURAX_IDNAME ID_LEITURAX
#define SYMBOL_LEITURAX_SIZE wxSize(400, 400)
#define SYMBOL_LEITURAX_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * LeituraX class declaration
 */

class LeituraX: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( LeituraX )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    LeituraX();
    LeituraX( wxWindow* parent, wxWindowID id = SYMBOL_LEITURAX_IDNAME, const wxString& caption = SYMBOL_LEITURAX_TITLE, const wxPoint& pos = SYMBOL_LEITURAX_POSITION, const wxSize& size = SYMBOL_LEITURAX_SIZE, long style = SYMBOL_LEITURAX_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_LEITURAX_IDNAME, const wxString& caption = SYMBOL_LEITURAX_TITLE, const wxPoint& pos = SYMBOL_LEITURAX_POSITION, const wxSize& size = SYMBOL_LEITURAX_SIZE, long style = SYMBOL_LEITURAX_STYLE );

    /// Destructor
    ~LeituraX();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin LeituraX event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

////@end LeituraX event handler declarations

////@begin LeituraX member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end LeituraX member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin LeituraX member variables
////@end LeituraX member variables
};

#endif
    // _LEITURAX_H_
