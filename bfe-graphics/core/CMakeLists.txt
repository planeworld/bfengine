FIND_PACKAGE(OpenGL REQUIRED)

IF (UNIX)
    FIND_PACKAGE(X11 REQUIRED)
    INCLUDE_DIRECTORIES (${X11_INCLUDE_DIR})
ENDIF()

SET(HDRS
    3rdparty/stb_truetype/stb_rect_pack.h
    3rdparty/stb_truetype/stb_truetype.h
    font_manager.h
    graphics.h
    render_mode.h
    render_target.h
    shader.h
    shader_program.h
    shape_subtypes.h
    text.h
    texture.h
)

SET(SRCS
    font_manager.cpp
    graphics.cpp
    render_mode.cpp
    render_target.cpp
    shader.cpp
    shader_program.cpp
    text.cpp
    texture.cpp
)

ADD_LIBRARY (bfe-gfx-core SHARED ${SRCS} ${HDRS})

target_include_directories(
                    bfe-gfx-core PRIVATE
                    ${OPENGL_INCLUDE_DIR}
                    ./3rdparty/stb_truetype/
                    ../../bfe-core/
                    ../../bfe-log/
                    ../../bfe-util/math/
                    .
                    )

IF(WIN32)
    INSTALL (TARGETS bfe-gfx-core
        RUNTIME DESTINATION lib)
ELSE()
    INSTALL (TARGETS bfe-gfx-core
        LIBRARY DESTINATION lib)
ENDIF()

INSTALL (FILES ${HDRS} DESTINATION include)
