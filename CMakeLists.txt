
cmake_minimum_required(VERSION 3.16)
project(mp3ME)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/taglib-2.1.1)
add_subdirectory(external/SFML-3.0.2)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)



add_executable(MP3ME ${PROJECT_SOURCES})

target_include_directories(MP3ME PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib-2.1.1/taglib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib-2.1.1/taglib/toolkit
)

target_link_libraries(MP3ME PRIVATE 
                        tag
                        SFML::Audio
                        SFML::System
                        SFML::Window
                        SFML::Graphics)