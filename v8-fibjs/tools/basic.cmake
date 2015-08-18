include(../tools/arch.cmake)
include(../tools/os.cmake)

project(${name})

file(GLOB_RECURSE src_list "*.c*")

add_library(${name} ${src_list})

#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${OS}_${BUILD_TYPE})

if (NOT CMAKE_BUILD_TYPE)
  if (WIN32)
    set (DEFAULT_BUILD_TYPE MinSizeRel)
  else (WIN32)
    set (DEFAULT_BUILD_TYPE RelWithDebInfo)
  endif(WIN32)

  set (CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE} CACHE STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_definitions (-DMACOSX -D_DARWIN_C_SOURCE)
endif ()

if(NOT flags)
	set(flags " ")
endif()

if(MSVC)
else()
    set(flags "${flags} -fshort-wchar -fsigned-char -fmessage-length=0 -Wno-long-long -fdata-sections -Wno-strict-aliasing -ffunction-sections -fno-exceptions -fvisibility=hidden -D_FILE_OFFSET_BITS=64")
endif()

set(link_flags " ")

if(${OS} STREQUAL "Darwin")
#	set(flags "${flags} -mmacosx-version-min=10.6")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release32")
	set(flags "${flags} -m32")
	set(link_flags "${link_flags} -m32")
	set(BUILD_TYPE "Release")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug32")
	set(flags "${flags} -m32")
	set(link_flags "${link_flags} -m32")
	set(BUILD_TYPE "Debug")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	set(flags "${flags} -O3")
	add_definitions(-DNDEBUG=1)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(flags "${flags} -g -O0")
	add_definitions(-DDEBUG=1)
endif()

set_target_properties(${name} PROPERTIES COMPILE_FLAGS ${flags})

if(link_flags)
	set_target_properties(${name} PROPERTIES LINK_FLAGS ${link_flags})
endif()

include_directories(${PROJECT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/../" "/usr/local/include/")
