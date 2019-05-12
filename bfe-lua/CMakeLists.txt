FIND_PACKAGE(Lua REQUIRED)

SET(HDRS
    ./3rdparty/sol2/sol.hpp
    lua_manager.h
)

SET(SRCS
    lua_manager.cpp
)

ADD_LIBRARY (bfe-lua SHARED ${SRCS} ${HDRS})

target_include_directories(
                            bfe-lua PRIVATE 
                            ${LUA_INCLUDE_DIR}
                            ./3rdparty/sol2/
                            ../bfe-core/
                            ../bfe-core/3rdparty/ConcurrentQueue/
                            ../bfe-log/
                            . )

IF(WIN32)
    INSTALL (TARGETS bfe-lua
        RUNTIME DESTINATION lib)
ELSE()
    INSTALL (TARGETS bfe-lua
        LIBRARY DESTINATION lib)
ENDIF()

INSTALL (FILES ${HDRS} DESTINATION include)
