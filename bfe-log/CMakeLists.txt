SET(HDRS
    conf_log.h
    log.h
    log_common_types.h
    log_defines.h
    log_listener.h
)

SET(SRCS
    log.cpp
)

ADD_LIBRARY (bfe-log SHARED ${SRCS} ${HDRS})

target_include_directories(
                            bfe-log PRIVATE 
                            ../bfe-core/
                            . )

IF(WIN32)
    INSTALL (TARGETS bfe-log
        RUNTIME DESTINATION lib)
ELSE()
    INSTALL (TARGETS bfe-log
        LIBRARY DESTINATION lib)
ENDIF()

INSTALL (FILES ${HDRS} DESTINATION include)
