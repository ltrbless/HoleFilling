cmake_minimum_required(VERSION 3.0)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

project(holefill)
# add_compile_options(-std=c++11)

add_executable(main main.cpp HoleFiller.cpp)

include_directories(./eigen)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/openmesh/include)

link_directories("${CMAKE_CURRENT_SOURCE_DIR}/openmesh/lib")

target_link_libraries( 

main

${CMAKE_CURRENT_SOURCE_DIR}/openmesh/lib/libOpenMeshCore.a
${CMAKE_CURRENT_SOURCE_DIR}/openmesh/lib/libOpenMeshTools.a)
# link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/openmesh/lib/libOpenMeshTools.so)