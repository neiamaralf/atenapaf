/////////////////////////////////////////////////////////////////////////////
// Name:        dbhost_adress.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     Wed 26 Sep 2012 10:29:57 BRT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _DBHOST_ADRESS_H_
#define _DBHOST_ADRESS_H_


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
#define ID_DBHOST_ADRESS 10153
#define ID_IPV4_1 10154
#define ID_PANEL1 10155
#define SYMBOL_DBHOST_ADRESS_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_DBHOST_ADRESS_TITLE wxGetTranslation(wxString(wxT("Endere")) + (wxChar) 0x00E7 + wxT("o do servidor de banco de dados"))
#define SYMBOL_DBHOST_ADRESS_IDNAME ID_DBHOST_ADRESS
#define SYMBOL_DBHOST_ADRESS_SIZE wxSize(200, 140)
#define SYMBOL_DBHOST_ADRESS_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * dbhost_adress class declaration
 */

class dbhost_adress: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( dbhost_adress )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    dbhost_adress();
    dbhost_adress( wxWindow* parent, wxWindowID id = SYMBOL_DBHOST_ADRESS_IDNAME, const wxString& caption = SYMBOL_DBHOST_ADRESS_TITLE, const wxPoint& pos = SYMBOL_DBHOST_ADRESS_POSITION, const wxSize& size = SYMBOL_DBHOST_ADRESS_SIZE, long style = SYMBOL_DBHOST_ADRESS_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DBHOST_ADRESS_IDNAME, const wxString& caption = SYMBOL_DBHOST_ADRESS_TITLE, const wxPoint& pos = SYMBOL_DBHOST_ADRESS_POSITION, const wxSize& size = SYMBOL_DBHOST_ADRESS_SIZE, long style = SYMBOL_DBHOST_ADRESS_STYLE );

    /// Destructor
    ~dbhost_adress();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin dbhost_adress event handler declarations

////@end dbhost_adress event handler declarations

////@begin dbhost_adress member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end dbhost_adress member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin dbhost_adress member variables
////@end dbhost_adress member variables
};

#endif
    // _DBHOST_ADRESS_H_
