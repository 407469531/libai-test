cmake_minimum_required(VERSION 3.10)
project(CapacitanceFEMBEM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# 包含头文件
include_directories(
    ${CMAKE_SOURCE_DIR}/eigen
    ${CMAKE_SOURCE_DIR}/gmsh/include
)

# 链接库
link_directories(${CMAKE_SOURCE_DIR}/gmsh/lib)

# 可执行文件
add_executable(capacitance_solver 
    main.cpp
    fem_solver.cpp
    bem_solver.cpp
    gmsh_mesh.cpp
)

# 链接 Gmsh 和数学库
target_link_libraries(capacitance_solver gmsh m)