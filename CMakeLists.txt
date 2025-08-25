cmake_minimum_required(VERSION 3.10)
project(epi_ktane)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(UNIX)
    set(OS_LIBS dl pthread)
endif()

find_package(raylib REQUIRED)

file(GLOB_RECURSE ALL_SOURCES src/*.cpp)

set(CORE_SOURCES "")
foreach(file ${ALL_SOURCES})
list(APPEND CORE_SOURCES ${file})
endforeach()

add_executable(epi_ktane ${CORE_SOURCES})
target_link_libraries(epi_ktane PRIVATE raylib ${OS_LIBS})
target_include_directories(epi_ktane PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(epi_ktane PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN"
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_command(TARGET epi_ktane POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:epi_ktane> ${CMAKE_SOURCE_DIR}/
)
