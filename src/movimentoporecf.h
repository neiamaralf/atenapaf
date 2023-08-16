/////////////////////////////////////////////////////////////////////////////
// Name:        movimentoporecf.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     17/07/2012 17:48:09
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MOVIMENTOPORECF_H_
#define _MOVIMENTOPORECF_H_


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
#define ID_MOVIMENTOPORECF 11131
#define ID_CB_ECF 11132
#define ID_MOVECF_DI 11133
#define ID_MOVECF_DF 11134
#define SYMBOL_MOVIMENTOPORECF_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_MOVIMENTOPORECF_TITLE _("Movimento por ECF")
#define SYMBOL_MOVIMENTOPORECF_IDNAME ID_MOVIMENTOPORECF
#define SYMBOL_MOVIMENTOPORECF_SIZE wxSize(400, 300)
#define SYMBOL_MOVIMENTOPORECF_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * MovimentoporECF class declaration
 */

class MovimentoporECF: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( MovimentoporECF )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MovimentoporECF();
    MovimentoporECF( wxWindow* parent, wxWindowID id = SYMBOL_MOVIMENTOPORECF_IDNAME, const wxString& caption = SYMBOL_MOVIMENTOPORECF_TITLE, const wxPoint& pos = SYMBOL_MOVIMENTOPORECF_POSITION, const wxSize& size = SYMBOL_MOVIMENTOPORECF_SIZE, long style = SYMBOL_MOVIMENTOPORECF_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MOVIMENTOPORECF_IDNAME, const wxString& caption = SYMBOL_MOVIMENTOPORECF_TITLE, const wxPoint& pos = SYMBOL_MOVIMENTOPORECF_POSITION, const wxSize& size = SYMBOL_MOVIMENTOPORECF_SIZE, long style = SYMBOL_MOVIMENTOPORECF_STYLE );

    /// Destructor
    ~MovimentoporECF();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin MovimentoporECF event handler declarations

////@end MovimentoporECF event handler declarations

////@begin MovimentoporECF member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MovimentoporECF member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MovimentoporECF member variables
////@end MovimentoporECF member variables
};

#endif
    // _MOVIMENTOPORECF_H_
