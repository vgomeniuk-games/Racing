cmake_minimum_required(VERSION 2.8)
project(Racing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp input.cpp input.h car.cpp car.h map.cpp map.h ai.cpp ai.h globals.h)
add_executable(Racing ${SOURCE_FILES})
add_custom_command(TARGET Racing PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Racing>/assets)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Racing ${SFML_LIBRARIES})
endif()