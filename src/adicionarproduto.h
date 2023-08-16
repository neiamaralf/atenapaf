/////////////////////////////////////////////////////////////////////////////
// Name:        adicionarproduto.h
// Purpose:
// Author:
// Modified by:
// Created:     18/05/2012 13:53:25
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _ADICIONARPRODUTO_H_
#define _ADICIONARPRODUTO_H_


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
#define ID_ADICIONARPRODUTO 10136
#define ID_INSPROD_LIST 10163
#define ID_INSPROD_QUANT 10137
#define SYMBOL_ADICIONARPRODUTO_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxWANTS_CHARS|wxTAB_TRAVERSAL
#define SYMBOL_ADICIONARPRODUTO_TITLE _("Adicionar produto")
#define SYMBOL_ADICIONARPRODUTO_IDNAME ID_ADICIONARPRODUTO
#define SYMBOL_ADICIONARPRODUTO_SIZE wxSize(600, 450)
#define SYMBOL_ADICIONARPRODUTO_POSITION wxDefaultPosition
////@end control identifiers


/*!
* Adicionarproduto class declaration
*/

class Adicionarproduto: public wxDialog {
  DECLARE_DYNAMIC_CLASS ( Adicionarproduto )
  DECLARE_EVENT_TABLE()

 public:
  wxTimer baltimer;
		int _ShowModal(int idfocus);
  void OnTimer ( wxTimerEvent &event );
  /// Constructors
  Adicionarproduto();
  Adicionarproduto ( wxWindow* parent, wxWindowID id = SYMBOL_ADICIONARPRODUTO_IDNAME, const wxString& caption = SYMBOL_ADICIONARPRODUTO_TITLE, const wxPoint& pos = SYMBOL_ADICIONARPRODUTO_POSITION, const wxSize& size = SYMBOL_ADICIONARPRODUTO_SIZE, long style = SYMBOL_ADICIONARPRODUTO_STYLE );

  /// Creation
  bool Create ( wxWindow* parent, wxWindowID id = SYMBOL_ADICIONARPRODUTO_IDNAME, const wxString& caption = SYMBOL_ADICIONARPRODUTO_TITLE, const wxPoint& pos = SYMBOL_ADICIONARPRODUTO_POSITION, const wxSize& size = SYMBOL_ADICIONARPRODUTO_SIZE, long style = SYMBOL_ADICIONARPRODUTO_STYLE );

  /// Destructor
  ~Adicionarproduto();

  /// Initialises member variables
  void Init();

  /// Creates the controls and sizers
  void CreateControls();

  ////@begin Adicionarproduto event handler declarations

    /// wxEVT_COMMAND_LIST_KEY_DOWN event handler for ID_INSPROD_LIST
    void OnInsprodListKeyDown( wxListEvent& event );

    /// wxEVT_CHAR event handler for ID_INSPROD_LIST
    void OnChar( wxKeyEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_INSPROD_QUANT
    void OnInsprodQuantUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
    void OnApplyClick( wxCommandEvent& event );

  ////@end Adicionarproduto event handler declarations

  ////@begin Adicionarproduto member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
  ////@end Adicionarproduto member function declarations

  /// Should we show tooltips?
  static bool ShowToolTips();

  ////@begin Adicionarproduto member variables
  ////@end Adicionarproduto member variables
 };

#endif
// _ADICIONARPRODUTO_H_
