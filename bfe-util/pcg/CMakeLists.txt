INCLUDE_DIRECTORIES(.)

SET(HDRS
    namegenerator.h
)

SET(SRCS
    namegenerator.cpp
)

ADD_LIBRARY (bfe-util SHARED ${SRCS})

IF(WIN32)
    INSTALL (TARGETS bfe-util
        RUNTIME DESTINATION lib)
ELSE()
    INSTALL (TARGETS bfe-util
        LIBRARY DESTINATION lib)
ENDIF()

INSTALL (FILES ${HDRS} DESTINATION include)
