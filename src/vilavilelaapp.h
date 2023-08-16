/////////////////////////////////////////////////////////////////////////////
// Name:        vilavilelaapp.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     08/05/2012 09:52:28
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _VILAVILELAAPP_H_
#define _VILAVILELAAPP_H_
#define _WIN32_WINDOWS 0x0400

/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "vilavilela.h"
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
////@end control identifiers

/*!
 * VilavilelaApp class declaration
 */

class VilavilelaApp: public wxApp
{    
    DECLARE_CLASS( VilavilelaApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    VilavilelaApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin VilavilelaApp event handler declarations

////@end VilavilelaApp event handler declarations

////@begin VilavilelaApp member function declarations

////@end VilavilelaApp member function declarations

////@begin VilavilelaApp member variables
////@end VilavilelaApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(VilavilelaApp)
////@end declare app

#endif
    // _VILAVILELAAPP_H_
