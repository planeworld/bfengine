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
/// \file       bfe_version.cpp
/// \brief      Helper file to use compile time in version string
///
/// \author     Torsten Büschenfeld (bfengine@bfeld.eu)
/// \date       2019-05-14
///
////////////////////////////////////////////////////////////////////////////////

#include "bfe_version.h"

/// BFEngine namespace
namespace bfe
{

/// BFEngine version
std::string BFE_VERSION_FULL =  std::to_string(BFE_VERSION_MAJOR)+"."+
                                std::to_string(BFE_VERSION_MINOR)+"-"+
                                BUILD_YEAR_CH0+
                                BUILD_YEAR_CH1+
                                BUILD_YEAR_CH2+
                                BUILD_YEAR_CH3+
                                BUILD_MONTH_CH0+
                                BUILD_MONTH_CH1+
                                BUILD_DAY_CH0+
                                BUILD_DAY_CH1+"."+
                                BUILD_HOUR_CH0+
                                BUILD_HOUR_CH1+
                                BUILD_MIN_CH0+
                                BUILD_MIN_CH1+
                                BUILD_SEC_CH0+
                                BUILD_SEC_CH1;

} // namespace bfe
