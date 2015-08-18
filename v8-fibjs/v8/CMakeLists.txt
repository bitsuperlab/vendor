cmake_minimum_required(VERSION 2.6)

set(name v8)

if(MSVC)
else()
    set(flags "-std=gnu++0x")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/../tools/basic.cmake)


IF( WIN32 )
    target_link_libraries(v8 exlib winmm)
ELSE(WIN32)
    IF(NOT APPLE)
        target_link_libraries( v8 exlib dl )
    ENDIF(NOT APPLE)
ENDIF(WIN32)

if(MSVC)
add_definitions(-DV8_NO_FAST_TLS=1 -DV8_DEPRECATION_WARNINGS=1 -DENABLE_HANDLE_ZAPPING=1)
else()
add_definitions(-DV8_NO_FAST_TLS=1 -DV8_DEPRECATION_WARNINGS=1 -DENABLE_GDB_JIT_INTERFACE=1 -DENABLE_HANDLE_ZAPPING=1)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_definitions(-DVERIFY_HEAP=1 -DOBJECT_PRINT=1 -DENABLE_DISASSEMBLER=1 -DV8_ENABLE_CHECKS=1 -DTRACE_MAPS=1 -DENABLE_SLOW_DCHECKS=1)
endif()
