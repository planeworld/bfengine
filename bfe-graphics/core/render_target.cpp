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
/// \file       render_target.cpp
/// \brief      Implementation of class "CRenderTarget"
///
/// \author     Torsten Büschenfeld (planeworld@bfeld.eu)
/// \date       2016-04-22
///
////////////////////////////////////////////////////////////////////////////////

#include "render_target.h"

using namespace bfe;

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Destructor, deletes GL buffers
///
////////////////////////////////////////////////////////////////////////////////
CRenderTarget::~CRenderTarget()
{
    METHOD_ENTRY("CRenderTarget::~CRenderTarget")
    DTOR_CALL("CRenderTarget::~CRenderTarget")
    
    glDeleteFramebuffers(1, &m_unIDFBO);
    glDeleteTextures(1, &m_unIDTex);
}

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Initialise render target
///
/// \param _unResX Width  (resolution in pixels)
/// \param _unResY Height (resolution in pixels)
/// \param _unSub  Subsampling factor
///
/// \return Success?
///
////////////////////////////////////////////////////////////////////////////////
bool CRenderTarget::init(const std::uint16_t _unResX, const std::uint16_t _unResY,
                         const std::uint16_t _unSub)
{
    METHOD_ENTRY("CRenderTarget::init")

    // Delete FBO and texture if already existing (i.e. when init is called
    // multiple times which happens when the buffer is resized)
    glDeleteFramebuffers(1, &m_unIDFBO);
    glDeleteTextures(1, &m_unIDTex);
    
    // Frame buffer
    glGenFramebuffers(1, &m_unIDFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_unIDFBO);
    
    // Texture
    glGenTextures(1, &m_unIDTex);
    glBindTexture(GL_TEXTURE_2D, m_unIDTex);
    
    const int nNoOfMipMapLevels = std::floor(std::log2(std::max(_unResX,_unResY)))+1;
    DOM_VAR(DEBUG_MSG("Render Target", nNoOfMipMapLevels << " MipMapLevels created."))
    
    glTexStorage2D(GL_TEXTURE_2D, nNoOfMipMapLevels, GL_RGBA8, _unResX/_unSub, _unResY/_unSub);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _unResX/_unSub, _unResY/_unSub, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Configure frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_unIDTex, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    // Check for errors
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        ERROR_MSG("Render Target", "Failed to create frame buffer")
        return false;
    }
    
    // Unbind
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // Store size
    m_unResX = _unResX;
    m_unResY = _unResY;
    m_unSub  = _unSub;
    
    return true;
}
