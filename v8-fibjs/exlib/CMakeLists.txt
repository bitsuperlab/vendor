cmake_minimum_required(VERSION 2.6)

set(name exlib)

include(${CMAKE_CURRENT_SOURCE_DIR}/../tools/basic.cmake)

#   Note for windows 64 build:
#
#   Below is a workaround to link fb_siwtch.asm to fb_switch.obj for windows 64 build, just append this to the generated exlib.vcxproj
#   As currently I haven't find the method to generate Visual Studio's CustomBuild using CMake's language
#
#   TODO: 
#       Need to investigate how to generate CustomBuild section
#
#  <ItemGroup>
#      <CustomBuild Include="e:\workspace\bitshares_play\vendor\v8-fibjs\exlib\src\fb_switch.asm">
#          <FileType>Document</FileType>
#          <Command Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">ml64 /c /Fo$(SolutionDir)vendor\v8-fibjs\exlib\exlib.dir\Debug\fb_switch.obj e:\workspace\bitshares_play\vendor\v8-fibjs\exlib\src\fb_switch.asm</Command>
#          <Command Condition="'$(Configuration)|$(Platform)'=='Release|x64'">ml64 /c /Fo$(SolutionDir)vendor\v8-fibjs\exlib\exlib.dir\Release\fb_switch.obj e:\workspace\bitshares_play\vendor\v8-fibjs\exlib\src\fb_switch.asm</Command>
#          <Command Condition="'$(Configuration)|$(Platform)'=='RelWithDebInfo|x64'">ml64 /c /Fo$(SolutionDir)vendor\v8-fibjs\exlib\exlib.dir\RelWithDebInfo\fb_switch.obj e:\workspace\bitshares_play\vendor\v8-fibjs\exlib\src\fb_switch.asm</Command>
#          <Outputs Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">$(SolutionDir)vendor\v8-fibjs\exlib\exlib.dir\Debug\fb_switch.obj</Outputs>
#          <Outputs Condition="'$(Configuration)|$(Platform)'=='Release|x64'">$(SolutionDir)vendor\v8-fibjs\exlib\exlib.dir\Release\fb_switch.obj</Outputs>
#          <Outputs Condition="'$(Configuration)|$(Platform)'=='RelWithDebInfo|x64'">$(SolutionDir)vendor\v8-fibjs\exlib\exlib.dir\RelWithDebInfo\fb_switch.obj</Outputs>
#      </CustomBuild>
#  </ItemGroup>
#

IF( WIN32 )
    target_link_libraries(exlib)
ELSE(WIN32)
    IF(NOT APPLE)
        target_link_libraries( exlib pthread )
    ENDIF(NOT APPLE)
ENDIF(WIN32)

