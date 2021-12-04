cmake_minimum_required(VERSION 3.21.2)
project(c17 VERSION 1.0) 

configure_file(c17Config.h.in c17Config.h)

add_executable(${PROJECT_NAME} c17.cpp)
add_subdirectory(routines)
list(APPEND MAIN_INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
list(APPEND MAIN_LIB_DIR "${CMAKE_BINARY_DIR}/routines")

option(USE_GLFW "GL Graphics Library" ON)
if(USE_GLFW)
    message(STATUS "    Generating glfw library")
    add_subdirectory(external/glfw)
    list(APPEND EXTRA_INCLUDES_DIRS "external/glfw/include")
    list(APPEND EXTRA_LINK_DIRS "external/glfw/")
    list(APPEND EXTRA_LINK_LIBS "glfw")
endif()

target_include_directories(${PROJECT_NAME} 
    PUBLIC include 
    PUBLIC ${PROJECT_BINARY_DIR}
    ${EXTRA_INCLUDES_DIRS}
)

target_link_directories(${PROJECT_NAME}
    PUBLIC include
    PUBLIC routines 
    PUBLIC ${PROJECT_BINARY_DIR}
    ${EXTRA_LINK_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC routines
    ${EXTRA_LINK_LIBS}
)

SET(CMAKE_MODULE_PATH cmake)

add_compile_options(-std=c++17)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_CXX_STANDARD 17)
message(STATUS "    PROJECT_NAME = ${PROJECT_NAME}")
message(STATUS "    CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "    SOURCE = ${PROJECT_SOURCE_DIR}")
message(STATUS "    CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "    PROJ_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message(STATUS "    CMAKE_CXX STANDARD = ${CMAKE_CXX_STANDARD}")
message(STATUS "    MAIN_INCLUDES_DIR = ${MAIN_INCLUDES_DIR}")
message(STATUS "    MAIN_LIB_DIR = ${MAIN_LIB_DIR}")
message(STATUS "    CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
# message(STATUS "    EXTRA_LINK_LIBS = ${EXTRA_LINK_LIBS}")

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
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES  ${MAIN_INCLUDES_DIR}/c17.h DESTINATION include) 
install(FILES  ${MAIN_LIB_DIR}/libroutines.a DESTINATION lib) 
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${tutorial_VERSION_MINOR}")
include (CPack)