////////////////////////////////////////////////////////////////////////////////
//
// This file is part of BFEngine, a 2D simulation engine.
// Copyright (C) 2017-2019 Torsten Büschenfeld
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///
/// \file       widget_console.h
/// \brief      Prototype of "CWidgetConsole"
///
/// \author     Torsten Büschenfeld (planeworld@bfeld.eu)
/// \date       2017-04-09
///
////////////////////////////////////////////////////////////////////////////////
#ifndef WIDGET_CONSOLE_H
#define WIDGET_CONSOLE_H

//--- Standard header --------------------------------------------------------//

//--- Program header ---------------------------------------------------------//
#include "com_console.h"
#include "text.h"
#include "widget.h"

/// BFEngine namespace
namespace bfe
{

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Defines a command console widget
///
////////////////////////////////////////////////////////////////////////////////
class CWidgetConsole : public IWidget
{

    public:
    
        //--- Constructor/Destructor------------------------------------------//
        CWidgetConsole() = delete;
        CWidgetConsole(CFontManager* const);
        ~CWidgetConsole() override {}
        
        //--- Constant methods -----------------------------------------------//
        
        //--- Methods --------------------------------------------------------//
        void draw() override;
        void setComConsole(CComConsole* const);
        
        //--- Variables ------------------------------------------------------//
        CText           ConsoleText;            ///< Text output in com console
        
    private:
        
        //--- Methods [private] ----------------------------------------------//
        
        //--- Variables [private] --------------------------------------------//
        CComConsole*    m_pComConsole;          ///< Command console used in this widget
        int             m_nComHistoryVisible;   ///< Visible part of command history
};

//--- Implementation is done here for inline optimisation --------------------//

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets the command console used in this widget
///
/// \param _pComConsole Command console to be set
///
////////////////////////////////////////////////////////////////////////////////
inline void CWidgetConsole::setComConsole(CComConsole* const _pComConsole)
{
    METHOD_ENTRY("CWidgetConsole::setComConsole")
    m_pComConsole = _pComConsole;
}

} // namespace bfe

#endif // WIDGET_CONSOLE_H
