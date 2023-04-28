cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(minotaur_maze)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

#--------------------------------------------------------------------------------
# NOTE that add_sources should be called AFTER add_subdirectory
#--------------------------------------------------------------------------------

macro (add_sources)
    file (RELATIVE_PATH _relPath "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND SOURCES_LIST "${_relPath}/${_src}")
        else()
            list (APPEND SOURCES_LIST "${_src}")
        endif()
    endforeach()
    if (_relPath)
        set (SOURCES_LIST ${SOURCES_LIST} PARENT_SCOPE)
    endif()
endmacro()

#--------------------------------------------------------------------------------

add_subdirectory(src)
add_executable(${PROJECT_NAME} ${SOURCES_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
