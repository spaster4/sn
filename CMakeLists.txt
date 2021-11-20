cmake_minimum_required(VERSION 3.21.2)
project(c17) 
add_executable(${PROJECT_NAME} c17.cpp)
add_subdirectory(routines)
add_subdirectory(external/glfw)
target_include_directories(${PROJECT_NAME} 
    PUBLIC include 
    PUBLIC external/glfw/include
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC routines
    PUBLIC external/glfw/src
)

add_compile_options(-std=c++17)
set(CMAKE_CXX_STANDARD 17)
message(STATUS "    PROJECT = ${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "    SOURCE = ${PROJECT_SOURCE_DIR}")
message(STATUS "    BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "    PROJ_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message(STATUS "    CXX STANDARD = ${CMAKE_CXX_STANDARD}")

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "$(PROJECT_SOURCE_DIR)./git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS " Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --rercursive 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
            RESULT_VARIABlE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR " git submodule update --init failed with ${GIT_SUBMOD_RESULT} please check out submodules")
        endif()
    endif()
endif()
