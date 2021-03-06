////////////////////////////////////////////////////////////////////////////////
//
// This file is part of BFEngine, a 2D simulation engine.
// Copyright (C) 2009-2019 Torsten Büschenfeld
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
/// \file       graphics.h
/// \brief      prototype of class "CGraphics"
///
/// \author     Torsten Büschenfeld (planeworld@bfeld.eu)
/// \date       2009-10-18
///
////////////////////////////////////////////////////////////////////////////////
#ifndef GRAPHICS_H
#define GRAPHICS_H

//--- Standard header --------------------------------------------------------//
#include <array>
#include <list>
#include <stack>

//--- Program header ---------------------------------------------------------//
#include "circular_buffer.h"
#include "log.h"
#include "math_constants.h"
#include "shader_program.h"
#include "shape_subtypes.h"
#include "render_mode.h"

//--- Misc header ------------------------------------------------------------//
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include "GL/glext.h"
#include <glm/mat4x4.hpp>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

using namespace Eigen;

/// BFEngine namespace
namespace bfe
{

/// Type definition for window handle to enable easy changes
typedef sf::Window WindowHandleType;

// Constants
constexpr std::uint16_t GRAPHICS_WIDTH_DEFAULT =  800u;     ///< Default x-resolution
constexpr std::uint16_t GRAPHICS_HEIGHT_DEFAULT = 600u;     ///< Default y-resolution

constexpr GLuint GRAPHICS_SIZE_OF_INDEX_BUFFER = 10000u;    ///< Size of VBOs/VAOs/IBOs to keep all data

constexpr double GRAPHICS_PX_PER_METER = 2.0;               ///< Default resolution, pixel per meter
constexpr double GRAPHICS_FOV_DEFAULT = 45.0;               ///< Default fov
constexpr double GRAPHICS_RIGHT_DEFAULT =
                    double(GRAPHICS_WIDTH_DEFAULT)*0.5
                          /GRAPHICS_PX_PER_METER;           ///< Default right plane
constexpr double GRAPHICS_LEFT_DEFAULT = 
                    -GRAPHICS_RIGHT_DEFAULT;                ///< Default left plane
constexpr double GRAPHICS_TOP_DEFAULT =
                    double(GRAPHICS_HEIGHT_DEFAULT)*0.5
                          /GRAPHICS_PX_PER_METER;           ///< Default top plane
constexpr double GRAPHICS_BOTTOM_DEFAULT =
                    -GRAPHICS_TOP_DEFAULT;                  ///< Default bottom plane
constexpr double GRAPHICS_NEAR_DEFAULT = 0.1;               ///< Default min depth
constexpr double GRAPHICS_FAR_DEFAULT = 1000.0;             ///< Default max depth

constexpr double GRAPHICS_DEPTH_DEFAULT = -15.0;            ///< Default drawing depth

constexpr double GRAPHICS_MAX_CACHE_SIZE = 1024;            ///< Maximum size of cache

const  double    GRAPHICS_CIRCLE_SEG_ANG = 1.0 / 360.0 * MATH_2PI; ///< Segment angle (increment) of circles
constexpr double GRAPHICS_CIRCLE_SEG_MAX = 200.0;           ///< Maximum segment size of circles
constexpr double GRAPHICS_CIRCLE_SEG_MIN = 3.0;             ///< Minimum segment size of circles
constexpr bool   GRAPHICS_CIRCLE_USE_CACHE = true;          ///< Flag for using sine/cosine cache

constexpr bool GRAPHICS_RENDER_BATCH_CALL_FORCED = true;    ///< Indicates a forced render batch call, ignoring stack
constexpr bool GRAPHICS_RENDER_BATCH_CALL_NORMAL = false;   ///< Indicates a normal render batch call


/// Type definition for RGB colours
typedef std::array<double, 3> ColorTypeRGB;
/// Type definition for RGBA colours
typedef std::array<double, 4> ColorTypeRGBA;

/// Type definition of a render modes, accessed by name
typedef std::unordered_map<std::string, CRenderMode*> RenderModesByNameType;

// Structure containing viewport information
struct ViewPort
{
    double leftplane = GRAPHICS_LEFT_DEFAULT;        ///< Left plane of viewport
    double rightplane = GRAPHICS_RIGHT_DEFAULT;      ///< Right plane of viewport
    double topplane = GRAPHICS_TOP_DEFAULT;          ///< Top plane of viewport
    double bottomplane = GRAPHICS_BOTTOM_DEFAULT;    ///< Bottom plane of viewport
    double nearplane = GRAPHICS_NEAR_DEFAULT;        ///< Near plane of viewport
    double farplane = GRAPHICS_FAR_DEFAULT;          ///< Far plane of viewport
};

////////////////////////////////////////////////////////////////////////////////
///
/// \brief graphics-wrapper
///
/// This class is responsible for all graphical stuff. That is:
/// initialization and providing methods for drawing lines. The class is built
/// on top of OpenGL and the SFML. The class is implemented as a meyers-singleton
/// to provide easy access to its methods for graphics abstraction classes like
/// IShape.
///
/// \todo Implement frustum culling
/// \todo Perhaps moving the camera towards z-axis is better than scaling, see
///         frustum culling.
///
////////////////////////////////////////////////////////////////////////////////
class CGraphics
{

    public:
    
        /// Returns instance of meyers-singleton
        static CGraphics& getInstance()
        {
            static CGraphics Instance;
            return (Instance);
        };
        
        //
        //--- Methods for videomanagement ------------------------------------//
        //

        //--- Constant methods -----------------------------------------------//
        Vector2d        screen2World(const Vector2d&) const;
        Vector2d        screen2World(const double&, const double&) const;
        Vector2d        world2Screen(const Vector2d&) const;
        int             getDrawCalls() const {return m_nDrawCalls;}
        int             getLinesPerFrame() const {return m_nLines;}
        int             getPointsPerFrame() const {return m_nPoints;}
        int             getTrianglesPerFrame() const {return m_nTriangles;}
        int             getVerticesPerFrame() const {return m_nVerts;}
        double          getDynPelSize() const;
        double          getResMPX() const;
        double          getResMPY() const;
        double          getResPMX() const;
        double          getResPMY() const;
        unsigned short  getWidthScr() const;
        unsigned short  getHeightScr() const;
        Vector2i        getScreenRes() const;
        void setColor(const ColorTypeRGBA&);
        void setColor(const double&, const double&, const double&);
        void setColor(const double&, const double&, const double&, const double&);
        void setLineWidth(const double&) const;
        void setPointSize(const double&) const;
        
        WindowHandleType* getWindow() const;

        //--- Methods --------------------------------------------------------//
        void beginRenderBatch(CRenderMode* const, const bool = false);
        bool beginRenderBatch(const std::string&);
        void endRenderBatch(const bool = GRAPHICS_RENDER_BATCH_CALL_NORMAL);
        bool restartRenderBatch(const std::string&);
        void restartRenderBatch(CRenderMode* const);
        void registerRenderMode(const std::string& _strName, CRenderMode* const);
        
        bool init();
        void resizeViewport(unsigned short, unsigned short);
        bool resizeWindow(unsigned short, unsigned short);
        void setWidthScr(const unsigned short&);
        void setHeightScr(const unsigned short&);
        void setViewPort(const double&, const double&, const double&, const double&);
        void setupScreenSpace();
        void setupWorldSpace();
        void swapBuffers();
        
        void setWindow(WindowHandleType* const);

        void cacheSinCos(const int);
        //
        //--- Methods for camera movement ------------------------------------//
        //

        //--- Constant methods -----------------------------------------------//
        Vector2d    getCamPos() const;
        double      getCamAng() const;
        double      getCamZoom() const;
        
        const ViewPort&    getViewPort() const;
        
        //--- Methods --------------------------------------------------------//
        void applyCamMovement();
        void resetCam();
        void rotCamBy(const double&);
        void rotCamTo(const double&);
        void transCamBy(const Vector2d&);
        void transCamTo(const Vector2d&);
        void zoomCamBy(const double&);
        void zoomCamTo(const double&);

        //
        //--- Methods for drawing --------------------------------------------//
        //

        //--- Constant methods -----------------------------------------------//
        void drawArcDyn(const Vector2d&, const double&, const double&, const double&);
        void drawCircleDyn(const Vector2d&, const double&);
        void circle(const Vector2d&, const double&, const int = 12, const bool = false);
        void showVec(const Vector2d&, const Vector2d&);

        //--- Methods --------------------------------------------------------//
        void addVertex(const Vector2d&);
        void addVertex(const double&, const double&);
        void dot(const Vector2d&);
        void dots(bfe::CCircularBuffer<Vector2d>&, const Vector2d& _vecOffset = Vector2d(0.0,0.0));
        void filledCircle(const Vector2d&, const double&, const int = 12, const bool = false);
        void filledRect(const Vector2d&, const Vector2d&);
        void filledTriangle(const Vector2d&, const Vector2d&, const Vector2d&);
        void polygon(const VertexListType&, const PolygonType&, const Vector2d& _vecOffset = Vector2d(0.0,0.0));
        void rect(const Vector2d&, const Vector2d&);
        void setDepth(const double&);
        void texturedRect(const Vector2d&,
                          const Vector2d&,
                          const std::vector<GLfloat>* const);
        void texturedRect(const Vector2d&,
                          const Vector2d&,
                          const std::vector<GLfloat>* const,
                          const std::vector<GLfloat>* const);
        void beginLine(const PolygonType&);
        void endLine();
        
        void resetBufferObjects();                      ///< Clear all VAOs, VBOs, IBOs...
        
    private:
        
        void restartRenderBatchInternal();
        
        //--- Variables [private] --------------------------------------------//
        WindowHandleType*   m_pWindow;                  ///< Pointer to main window
        
        ViewPort            m_ViewPort;                 ///< Viewport for graphics
        glm::mat4           m_matTransform;             ///< Final transformation matrix
        glm::mat4           m_matProjection;            ///< Projection matrix
        bool                m_bScreenSpace;             ///< Indicates if coordinates are screen space related
        
        std::uint32_t       m_uncI = 0u;                ///< Index counter
        GLuint              m_unIndex = 0u;             ///< Pointer to current index in buffer
        GLuint              m_unIndexMax = GRAPHICS_SIZE_OF_INDEX_BUFFER; ///< Maximum number of vertices;
        GLuint              m_unIndexVerts = 0u;        ///< Index of current vertex in buffer
        GLuint              m_unIndexCol = 0u;          ///< Index of current colour in buffer
        GLuint              m_unIndexUV0 = 0u;          ///< Index of current texture coordinates (texture 0) in buffer
        GLuint              m_unIndexUV1 = 0u;          ///< Index of current texture coordinates (texture 1) in buffer
        GLuint              m_unIndexLines = 0u;        ///< Index of current element in line index buffer
        GLuint              m_unIndexPoints = 0u;       ///< Index of current element in point index buffer
        GLuint              m_unIndexTriangles = 0u;    ///< Index of current element in triangle index buffer
        int                 m_nLineNrOfVerts = 0;       ///< Number of vertices for current line
        bool                m_bLineBatchCall = false;   ///< Indicates, that only a line segment of current batch is drawn
        bool                m_bLineBatchFirst = true;   ///< Indicates first call of a line segment of current batch
        std::array<double,7> m_aVertFirst;              ///< Stores vertex and colour of first element in Polygon for loop type

        GLuint              m_unIBOLines = 0u;          ///< Index buffer object for lines
        GLuint              m_unIBOPoints = 0u;         ///< Index buffer object for points
        GLuint              m_unIBOTriangles = 0u;      ///< Index buffer object for triangles
        GLuint              m_unVAO = 0u;               ///< Vertex array object
        GLuint              m_unVBO = 0u;               ///< Vertex buffer
        GLuint              m_unVBOColours = 0u;        ///< Colour buffer
        GLuint              m_unVBOUV0s = 0u;           ///< Texture coordinate buffer, texture 0
        GLuint              m_unVBOUV1s = 0u;           ///< Texture coordinate buffer, texture 1
        
        PolygonType         m_PolyType = PolygonType::LINE_STRIP; ///< Type of currently drawn polygon
               
        // Basic Debug information:
        int                 m_nDrawCalls;               ///< Basic draw call counter
        int                 m_nLines;                   ///< Number of lines per frame
        int                 m_nPoints;                  ///< Number of points per frame
        int                 m_nTriangles;               ///< Number of triangles per frame
        int                 m_nVerts;                   ///< Number of vertices per frame
        
        ColorTypeRGBA       m_aColour;                  ///< Currently set color
        
        std::vector<GLuint>   m_vecIndicesLines;        ///< Indices for single lines within buffers
        std::vector<GLuint>   m_vecIndicesPoints;       ///< Indices for points within buffers
        std::vector<GLuint>   m_vecIndicesTriangles;    ///< Indices for triangles within buffers
        
        std::vector<GLfloat>    m_vecColours;           ///< Temporary buffer for colours of vertices
        std::vector<GLfloat>    m_vecVertices;          ///< Temporary buffer for vertices
        std::vector<GLfloat>    m_vecUV0s;              ///< Temporary buffer for texture coordinates (texture 0)
        std::vector<GLfloat>    m_vecUV1s;              ///< Temporary buffer for texture coordinates (texture 1)
        
        RenderModesByNameType   m_RenderModesByName;    ///< Map of render modes, accessed by name
        CRenderMode*            m_pRenderMode;          ///< Currently selected render mode
        RenderModeType          m_RenderModeType;       ///< Currently used render mode
        std::stack<CRenderMode*> m_RenderModeStack;     ///< Temporarily saves render batch information
        
        Vector3d            m_vecCamPos;                ///< camera position
        double              m_fCamAng;                  ///< camera angle
        double              m_fCamZoom;                 ///< camera zoom
        double              m_fDepth;                   ///< depth of lines in list
        double              m_fDepthMax;                ///< maximum depth of levels
        double              m_fDepthMin;                ///< minimum depth of levels

        int                 m_nVideoFlags;              ///< videoflags like fullscreen, resolution
        unsigned short      m_unWidthScr;               ///< Screen width
        unsigned short      m_unHeightScr;              ///< Screen height

        std::vector<double>     m_CosCache;             ///< Cache for cosine values
        std::vector<double>     m_SinCache;             ///< Cache of sine values
        
        //--- Constructor/destructor [private] -------------------------------//
        CGraphics();
        ~CGraphics();

        //--- Operators [private] --------------------------------------------//
        CGraphics& operator=(const CGraphics&); ///< empty private operator=

};

//--- Implementation is done here for inline optimisation --------------------//

////////////////////////////////////////////////////////////////////////////////
///
/// \brief Base class for graphics
///
/// This class is the base class for all classes using graphics. It just defines
/// a constructor that initializes the meyers-singleton for the graphics
/// instance.
/// 
////////////////////////////////////////////////////////////////////////////////
class CGraphicsBase
{
public:
        CGraphics& getGraphics() {return m_Graphics;}
    
    protected:
        //--- Protected constructor ------------------------------------------//
        CGraphicsBase():m_Graphics(CGraphics::getInstance())
        {
            CTOR_CALL("GraphicsBase");
        };

        //--- Protected variables --------------------------------------------//
        CGraphics&  m_Graphics;                 ///< Instance of graphics class
};

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns horizontal resolution
///
/// \return Horizontal resolution in m/pel
///
///////////////////////////////////////////////////////////////////////////////
inline double CGraphics::getResMPX() const
{
    METHOD_ENTRY("CGraphics::getResMPX()");
    return ((m_ViewPort.rightplane-m_ViewPort.leftplane) /
            (m_fCamZoom * m_unWidthScr));
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns vertical resolution
///
/// \return Vertical resolution in m/pel
///
///////////////////////////////////////////////////////////////////////////////
inline double CGraphics::getResMPY() const
{
    METHOD_ENTRY("CGraphics::getResMPY()");
    return ((m_ViewPort.topplane-m_ViewPort.bottomplane) /
            (m_fCamZoom * m_unHeightScr));
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns horizontal resolution
///
/// \return Horizontal resolution in pel/m
///
///////////////////////////////////////////////////////////////////////////////
inline double CGraphics::getResPMX() const
{
    METHOD_ENTRY("CGraphics::getResPMX()");
    return ((m_fCamZoom * m_unWidthScr) / 
            (m_ViewPort.rightplane-m_ViewPort.leftplane));
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns vertical resolution
///
/// \return Vertical resolution in pel/m
///
///////////////////////////////////////////////////////////////////////////////
inline double CGraphics::getResPMY() const
{
    METHOD_ENTRY("CGraphics::getResPMY()");
    return ((m_fCamZoom * m_unHeightScr) / 
            (m_ViewPort.topplane-m_ViewPort.bottomplane));
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns the screen width
///
/// \return Screen width in pel
///
///////////////////////////////////////////////////////////////////////////////
inline unsigned short CGraphics::getWidthScr() const
{
    METHOD_ENTRY("CGraphics::getWidthScr()");
    return m_unWidthScr;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns the screen height
///
/// \return Screen HeightScr in pel
///
///////////////////////////////////////////////////////////////////////////////
inline unsigned short CGraphics::getHeightScr() const
{
    METHOD_ENTRY("CGraphics::getHeightScr()");
    return m_unHeightScr;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns the screen resolution
///
/// \return Screen resolution in pixel (width, height)
///
///////////////////////////////////////////////////////////////////////////////
inline Vector2i CGraphics::getScreenRes() const
{
    METHOD_ENTRY("CGraphics::getScreenRes");
    return Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Set RGBA colour
///
/// \param _RGBA Colour as RGBA values between 0.0 and 1.0
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setColor(const ColorTypeRGBA& _RGBA)
{
    METHOD_ENTRY("CGraphics::setColor")
    m_aColour = _RGBA;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Set RGB color
///
/// \param _fR Red value between 0.0 and 1.0
/// \param _fG Green value between 0.0 and 1.0
/// \param _fB Blue value between 0.0 and 1.0
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setColor(const double& _fR, const double& _fG,
                                const double& _fB)
{
    METHOD_ENTRY("CGraphics::setColor")
    m_aColour = {{_fR, _fG, _fB, 1.0}};
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Set RGB color with alpha value
///
/// \param _fR Red value between 0.0 and 1.0
/// \param _fG Green value between 0.0 and 1.0
/// \param _fB Blue value between 0.0 and 1.0
/// \param _fA Alpha value between 0.0 and 1.0
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setColor(const double& _fR, const double& _fG,
                                const double& _fB, const double& _fA)
{
    METHOD_ENTRY("CGraphics::setColor")
    m_aColour = {{_fR, _fG, _fB, _fA}};
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets width of lines
///
/// \param _fW Width of lines
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setLineWidth(const double& _fW) const
{
    METHOD_ENTRY("CGraphics::setLineWidth")
    glLineWidth(_fW);
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets the size of points
///
/// \param _fS Size of points
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setPointSize(const double& _fS) const
{
    METHOD_ENTRY("CGraphics::setPointSize")
    glPointSize(_fS);
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns the main window of initialisation
///
/// This method return a pointer to the main window that is created when 
/// initialising the graphics with. It is needed for external use of
/// event loop which is hooked to the main window.
///
/// \return Main window
///
///////////////////////////////////////////////////////////////////////////////
inline WindowHandleType* CGraphics::getWindow() const
{
    METHOD_ENTRY("CGraphics::getWindow")
    if (m_pWindow == nullptr)
    {
        ERROR_MSG("Graphics", "No window handle. Maybe graphics wasn't initialised before.")
    }
    return m_pWindow;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Registeres a render mode to call by name later using \ref beginRenderBatch
///
/// \param _strName Name of render mode to be registered
/// \param _pRenderMode Render mode to register
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::registerRenderMode(const std::string& _strName, CRenderMode* const _pRenderMode)
{
    METHOD_ENTRY("CGraphics::registerRenderMode")
    m_RenderModesByName.insert({_strName, _pRenderMode});
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Set the screen width
///
/// Actually, this method does not resize the screen, it just modifies the
/// variable. To resize the screen, it must be initialized again.
///
/// \param _unWidthScr Screen width in pel
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setWidthScr(const unsigned short& _unWidthScr)
{
    METHOD_ENTRY("CGraphics::setWidthScr");
    m_unWidthScr = _unWidthScr;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Set the screen height
///
/// Actually, this method does not resize the screen, it just modifies the
/// variable. To resize the screen, it must be initialized again.
///
/// \param _unHeightScr Screen height in pel
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setHeightScr(const unsigned short& _unHeightScr)
{
    METHOD_ENTRY("CGraphics::setHeightScr");
    m_unHeightScr = _unHeightScr;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Set the main window
///
/// \param _pWindow Main window
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setWindow(WindowHandleType* const _pWindow)
{
    METHOD_ENTRY("CGraphics::setWindow");
    m_pWindow = _pWindow;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns the camera angle
///
/// \return The camera angle
///
///////////////////////////////////////////////////////////////////////////////
inline Vector2d CGraphics::getCamPos() const
{
    METHOD_ENTRY("CGraphics::getCamPos()");
    return Vector2d(m_vecCamPos[0], m_vecCamPos[1]);
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns the camera angle
///
/// \return The camera angle
///
///////////////////////////////////////////////////////////////////////////////
inline double CGraphics::getCamAng() const
{
    METHOD_ENTRY("CGraphics::getCamAngle()");
    return m_fCamAng;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns the camera zoom
///
/// \return The camera zoom
///
///////////////////////////////////////////////////////////////////////////////
inline double CGraphics::getCamZoom() const
{
    METHOD_ENTRY("CGraphics::getCamZoom()");
    return m_fCamZoom;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Returns viewport information
///
/// \return Viewport information
///
///////////////////////////////////////////////////////////////////////////////
inline const ViewPort& CGraphics::getViewPort() const
{
    METHOD_ENTRY("CGraphics::getViewPort()");
    return m_ViewPort;
}

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets depth of primitiv that should be drawn
///
/// \param _fD Depth of primitiv
///
///////////////////////////////////////////////////////////////////////////////
inline void CGraphics::setDepth(const double& _fD)
{
    METHOD_ENTRY("CGraphics::setDepth")
    m_fDepth = _fD;
}

} // namespace bfe

#endif // GRAPHICS_H
