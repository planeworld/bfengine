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
/// \file       texture.cpp
/// \brief      Implementation of class "CTexture"
///
/// \author     Torsten Büschenfeld (planeworld@bfeld.eu)
/// \date       2017-06-05
///
////////////////////////////////////////////////////////////////////////////////

#include "texture.h"

//--- Standard header --------------------------------------------------------//
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace bfe;

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Deletes texture
///
////////////////////////////////////////////////////////////////////////////////
bool CTexture::destroy()
{
    METHOD_ENTRY("CTexture::destroy")
    glDeleteTextures(1, &m_unID);
    return true;
}

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Initialise texture
///
/// \param _unResX X resolution of the texture
/// \param _unResY Y resolution of the texture
///
/// \return Success?
///
////////////////////////////////////////////////////////////////////////////////
bool CTexture::init(const std::uint16_t _unResX, const std::uint16_t _unResY,
                    const unsigned char* const _puchData)
{
    METHOD_ENTRY("CTexture::init")
    
    // Delete texture if already existing (i.e. when init is called
    // multiple times)
    glDeleteTextures(1, &m_unID);
    
    // Texture
    glGenTextures(1, &m_unID);
    glBindTexture(GL_TEXTURE_2D, m_unID);
    
    const int nNoOfMipMapLevels = std::floor(std::log2(std::max(_unResX,_unResY)))+1;
    DOM_VAR(DEBUG_MSG("Texture", nNoOfMipMapLevels << " MipMapLevels created."))
    
    glTexStorage2D(GL_TEXTURE_2D, nNoOfMipMapLevels, GL_RGBA8, _unResX, _unResY);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _unResX, _unResY, GL_RGB, GL_UNSIGNED_BYTE, _puchData);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Load texture from file
///
/// \param _strName Name of texture file to load
///
/// \return Success?
///
////////////////////////////////////////////////////////////////////////////////
bool CTexture::load(const std::string& _strName)
{
    METHOD_ENTRY("CTexture::load")
    
    int nWidth, nHeight, nNrChannels;
    unsigned char* puchData = stbi_load(_strName.c_str(), &nWidth, &nHeight, &nNrChannels, 0);
    
    if (puchData != nullptr)
    {
        this->init(nWidth, nHeight, puchData);
        stbi_image_free(puchData);
        DOM_FIO(INFO_MSG("Texture", "Successfully loaded texture " << _strName))
        
        return true;
    }
    else
    {
        DOM_FIO(WARNING_MSG("Texture", "Couldn't load texture " << _strName))
        return false;
    }
}
