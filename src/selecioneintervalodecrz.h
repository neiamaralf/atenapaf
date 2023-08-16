/////////////////////////////////////////////////////////////////////////////
// Name:        selecioneintervalodecrz.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     Wed 11 Jul 2012 11:23:10 BRT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _SELECIONEINTERVALODECRZ_H_
#define _SELECIONEINTERVALODECRZ_H_
 

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
#define ID_SELECIONEINTERVALODECRZ 11117
#define wxID_LABEL_CRZI 10167
#define wxID_LABEL_CRZF 10168
#define ID_DLGSELCRZ_INI 11118
#define ID_DLGSELCRZ_FIM 11119
#define SYMBOL_SELECIONEINTERVALODECRZ_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_SELECIONEINTERVALODECRZ_TITLE _("Selecione Intervalo de CRZ")
#define SYMBOL_SELECIONEINTERVALODECRZ_IDNAME ID_SELECIONEINTERVALODECRZ
#define SYMBOL_SELECIONEINTERVALODECRZ_SIZE wxSize(400, 300)
#define SYMBOL_SELECIONEINTERVALODECRZ_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * SelecioneIntervalodeCRZ class declaration
 */

class SelecioneIntervalodeCRZ: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( SelecioneIntervalodeCRZ )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SelecioneIntervalodeCRZ();
    SelecioneIntervalodeCRZ( wxWindow* parent, wxWindowID id = SYMBOL_SELECIONEINTERVALODECRZ_IDNAME, const wxString& caption = SYMBOL_SELECIONEINTERVALODECRZ_TITLE, const wxPoint& pos = SYMBOL_SELECIONEINTERVALODECRZ_POSITION, const wxSize& size = SYMBOL_SELECIONEINTERVALODECRZ_SIZE, long style = SYMBOL_SELECIONEINTERVALODECRZ_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SELECIONEINTERVALODECRZ_IDNAME, const wxString& caption = SYMBOL_SELECIONEINTERVALODECRZ_TITLE, const wxPoint& pos = SYMBOL_SELECIONEINTERVALODECRZ_POSITION, const wxSize& size = SYMBOL_SELECIONEINTERVALODECRZ_SIZE, long style = SYMBOL_SELECIONEINTERVALODECRZ_STYLE );

    /// Destructor
    ~SelecioneIntervalodeCRZ();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin SelecioneIntervalodeCRZ event handler declarations

////@end SelecioneIntervalodeCRZ event handler declarations

////@begin SelecioneIntervalodeCRZ member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SelecioneIntervalodeCRZ member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SelecioneIntervalodeCRZ member variables
////@end SelecioneIntervalodeCRZ member variables
};

#endif
    // _SELECIONEINTERVALODECRZ_H_
