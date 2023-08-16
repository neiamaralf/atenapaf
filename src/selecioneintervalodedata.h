/////////////////////////////////////////////////////////////////////////////
// Name:        selecioneintervalodedata.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     Wed 11 Jul 2012 11:18:19 BRT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _SELECIONEINTERVALODEDATA_H_
#define _SELECIONEINTERVALODEDATA_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/datectrl.h"
#include "wx/dateevt.h"
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
#define ID_SELECIONEINTERVALODEDATA 11114
#define ID_DLGSELDATA_DATAINI 11115
#define ID_DLGSELDATA_DATAFIM 11116
#define SYMBOL_SELECIONEINTERVALODEDATA_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_SELECIONEINTERVALODEDATA_TITLE _("Selecione Intervalo de Data")
#define SYMBOL_SELECIONEINTERVALODEDATA_IDNAME ID_SELECIONEINTERVALODEDATA
#define SYMBOL_SELECIONEINTERVALODEDATA_SIZE wxSize(400, 300)
#define SYMBOL_SELECIONEINTERVALODEDATA_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * SelecioneIntervalodeData class declaration
 */

class SelecioneIntervalodeData: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( SelecioneIntervalodeData )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SelecioneIntervalodeData();
    SelecioneIntervalodeData( wxWindow* parent, wxWindowID id = SYMBOL_SELECIONEINTERVALODEDATA_IDNAME, const wxString& caption = SYMBOL_SELECIONEINTERVALODEDATA_TITLE, const wxPoint& pos = SYMBOL_SELECIONEINTERVALODEDATA_POSITION, const wxSize& size = SYMBOL_SELECIONEINTERVALODEDATA_SIZE, long style = SYMBOL_SELECIONEINTERVALODEDATA_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SELECIONEINTERVALODEDATA_IDNAME, const wxString& caption = SYMBOL_SELECIONEINTERVALODEDATA_TITLE, const wxPoint& pos = SYMBOL_SELECIONEINTERVALODEDATA_POSITION, const wxSize& size = SYMBOL_SELECIONEINTERVALODEDATA_SIZE, long style = SYMBOL_SELECIONEINTERVALODEDATA_STYLE );

    /// Destructor
    ~SelecioneIntervalodeData();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin SelecioneIntervalodeData event handler declarations

////@end SelecioneIntervalodeData event handler declarations

////@begin SelecioneIntervalodeData member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SelecioneIntervalodeData member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SelecioneIntervalodeData member variables
////@end SelecioneIntervalodeData member variables
};

#endif
    // _SELECIONEINTERVALODEDATA_H_
