////////////////////////////////////////////////////////////////////////////////
//
// This file is part of BFEngine, a 2D simulation engine.
// Copyright (C) 2016-2019 Torsten Büschenfeld
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
/// \file       shader_program.cpp
/// \brief      Implementation of class "CShaderProgram"
///
/// \author     Torsten Büschenfeld (planeworld@bfeld.eu)
/// \date       2016-04-10
///
////////////////////////////////////////////////////////////////////////////////

#include "shader_program.h"

using namespace bfe;

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Creates GL shader program consisting of vertex and fragment shader
///
/// \param _VertexShader Vertex shader of this program
/// \param _FragmentShader Fragment shader of this program
///
////////////////////////////////////////////////////////////////////////////////
void CShaderProgram::create(const CShader& _VertexShader,
                            const CShader& _FragmentShader)
{
    METHOD_ENTRY("CShaderProgram::create")
    m_unID = glCreateProgram();
    
    this->addShader(_VertexShader);
    this->addShader(_FragmentShader);
    this->link();
}

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Link GL shader program
///
////////////////////////////////////////////////////////////////////////////////
bool CShaderProgram::link()
{
    METHOD_ENTRY("CShaderProgram::link")
    
    glLinkProgram(m_unID);

    //--- Check for errors ---//
    GLint nIsLinked = 0;
    glGetProgramiv(m_unID, GL_LINK_STATUS, (int *)&nIsLinked);
    if (nIsLinked == GL_FALSE)
    {
        ERROR_MSG("Shader Program", "Failed to link shader program")
        
        GLint nLengthMax = 0;
        glGetProgramiv(m_unID, GL_INFO_LOG_LENGTH, &nLengthMax);

        std::vector<GLchar> ErrorLog(nLengthMax);
        glGetProgramInfoLog(m_unID, nLengthMax, &nLengthMax, &ErrorLog[0]);

        ERROR_BLK(
        for (auto ci : ErrorLog)
        {
            std::cerr << ci;
        }
        std::cerr << std::endl;
        )
        glDeleteProgram(m_unID);
        
        return false;
    }
    else
    {
        INFO_MSG("Shader Program", "Successfully linked shader program")
        
        // Detach shaders if succesfully linked
        for (auto it : Shaders)
        {
            glDetachShader(m_unID, it);
        }
        Shaders.clear();
    }
    return true;
}
