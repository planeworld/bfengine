FIND_PACKAGE(OpenGL REQUIRED)

IF (UNIX)
    FIND_PACKAGE(X11 REQUIRED)
    INCLUDE_DIRECTORIES (${X11_INCLUDE_DIR})
ENDIF()

SET(HDRS
    font_user.h
    widget.h
    widget_console.h
    widget_text.h
    win_frame_user.h
    window.h
)

SET(SRCS
    widget_console.cpp
    widget_text.cpp
    win_frame_user.cpp
    window.cpp
)

ADD_LIBRARY (bfe-gfx-wm SHARED ${SRCS} ${HDRS})

target_include_directories(
                    bfe-gfx-wm PRIVATE
                    ${OPENGL_INCLUDE_DIR}
                    ../../bfe-core/
                    ../../bfe-core/3rdparty/ConcurrentQueue/
                    ../../bfe-log/
                    ../../bfe-util/math/
                    ../core/
                    ../core/3rdparty/stb_truetype/
                    .
                    )

IF(WIN32)
    INSTALL (TARGETS bfe-gfx-wm
        RUNTIME DESTINATION lib)
ELSE()
    INSTALL (TARGETS bfe-gfx-wm
        LIBRARY DESTINATION lib)
ENDIF()

INSTALL (FILES ${HDRS} DESTINATION include)
