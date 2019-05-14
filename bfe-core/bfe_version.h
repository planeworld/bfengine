////////////////////////////////////////////////////////////////////////////////
//
// This file is part of BFEngine, a 2D simulation engine.
// Copyright (C) 2019 Torsten Büschenfeld
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
/// \file       bfe_version.h
/// \brief      Version string using build time
///
/// \author     Torsten Büschenfeld (bfengine@bfeld.eu)
/// \date       2019-05-14
///
////////////////////////////////////////////////////////////////////////////////

#ifndef BFE_VERSION_H
#define BFE_VERSION_H

//--- Program header ---------------------------------------------------------//
#include "build_time_formatter.h"

//--- Standard header --------------------------------------------------------//
#include <string>


/// BFEngine namespace
namespace bfe
{

/// BFEngine version
constexpr int BFE_VERSION_MAJOR = 0;
constexpr int BFE_VERSION_MINOR = 8;
extern std::string BFE_VERSION_FULL;

} // namespace bfe
                    
#endif
