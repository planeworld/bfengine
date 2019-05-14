SET(HDRS
    3rdparty/ConcurrentQueue/concurrentqueue.h
    bfe_version.h
    build_time_formatter.h
    circular_buffer.h
    circular_buffer.tpp
    conf_bfengine.h
    com_console.h
    com_interface.h
    com_interface.tpp
    com_interface_provider.h
    com_interface_user.h
    entity.h
    handle.h
    handle_manager.h
    handle_mixin.h
    input_manager.h
    serializable.h
    serialize_macros.h
    serializer.h
    serializer_basic.h
    spinlock.h
    thread_module.h
    timer.h
    uid.h
    uid_user.h
)

SET(SRCS
    bfe_version.cpp
    com_console.cpp
    com_interface.cpp
    handle.cpp
    handle_manager.cpp
    input_manager.cpp
    serializable.cpp
    spinlock.cpp
    thread_module.cpp
    timer.cpp
    uid.cpp
)

ADD_LIBRARY (bfe-core SHARED ${SRCS} ${HDRS})

target_include_directories(
                            bfe-core PRIVATE
                            ./3rdparty/ConcurrentQueue/
                            ../bfe-log/
                            ../bfe-util/
                            .
                          )

IF(WIN32)
    INSTALL (TARGETS bfe-core
        RUNTIME DESTINATION lib)
ELSE()
    INSTALL (TARGETS bfe-core
        LIBRARY DESTINATION lib)
ENDIF()

INSTALL (FILES ${HDRS} DESTINATION include)
