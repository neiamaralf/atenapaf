/////////////////////////////////////////////////////////////////////////////
// Name:        balanco.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     16/08/2012 09:57:03
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _BALANCO_H_
#define _BALANCO_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/calctrl.h"
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
#define ID_BALANCO 10018
#define ID_CALCTRL_BALANCO 10142
#define ID_CALCTRL_BALANCOF 12000
#define ID_RB_BALANCO 10143
#define SYMBOL_BALANCO_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_BALANCO_TITLE wxGetTranslation(wxString(wxT("Balan")) + (wxChar) 0x00E7 + wxT("o"))
#define SYMBOL_BALANCO_IDNAME ID_BALANCO
#define SYMBOL_BALANCO_SIZE wxSize(400, 300)
#define SYMBOL_BALANCO_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * Balanco class declaration
 */

class Balanco: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( Balanco )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    Balanco();
    Balanco( wxWindow* parent, wxWindowID id = SYMBOL_BALANCO_IDNAME, const wxString& caption = SYMBOL_BALANCO_TITLE, const wxPoint& pos = SYMBOL_BALANCO_POSITION, const wxSize& size = SYMBOL_BALANCO_SIZE, long style = SYMBOL_BALANCO_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_BALANCO_IDNAME, const wxString& caption = SYMBOL_BALANCO_TITLE, const wxPoint& pos = SYMBOL_BALANCO_POSITION, const wxSize& size = SYMBOL_BALANCO_SIZE, long style = SYMBOL_BALANCO_STYLE );

    /// Destructor
    ~Balanco();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin Balanco event handler declarations

////@end Balanco event handler declarations

////@begin Balanco member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end Balanco member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin Balanco member variables
////@end Balanco member variables
};

#endif
    // _BALANCO_H_
