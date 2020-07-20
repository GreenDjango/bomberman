cmake_minimum_required(VERSION 3.11)
project(IndieStudio VERSION 0.1)

# set(CMAKE_VERBOSE_MAKEFILE ON)
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
set(Irrlicht_DIR "${CMAKE_SOURCE_DIR}/modules/Irrlicht/")
set(SFMLAudio_DIR "${CMAKE_SOURCE_DIR}/modules/SFMLAudio/")

find_package(Irrlicht REQUIRED)
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories (${Irrlicht_INCLUDE_DIRS})
if(NOT WIN32)
message("Linux")
    find_package(OpenGL REQUIRED)
    find_package(SFML 2.5 COMPONENTS audio REQUIRED)
    include_directories (${SFML_INCLUDE_DIR})
else()
    find_package(SFMLAudio REQUIRED)
    include_directories (${SFMLAudio_INCLUDE_DIRS})
endif()

# files
FILE(GLOB SRC
src/*.cpp
src/particle/*.cpp
src/interface/*.cpp
src/component/*.cpp
src/entity/*.cpp
src/class/*.cpp
src/scene/*.cpp
)

add_executable(bomberman
    ${SRC}
)

file(COPY "assets" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "save" DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    file(COPY "${Irrlicht_DIR}/Irrlicht.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFMLAudio_DIR}/sfml-audio-d-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFMLAudio_DIR}/sfml-system-d-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFMLAudio_DIR}/openal32.dll" DESTINATION ${CMAKE_BINARY_DIR})
    target_link_libraries(bomberman ${OPENGL_LIBRARIES} ${Irrlicht_LIBRARIES} ${SFMLAudio_LIBRARIES})
else()
    target_link_libraries(bomberman ${OPENGL_LIBRARIES} ${Irrlicht_LIBRARIES} sfml-audio)
endif()