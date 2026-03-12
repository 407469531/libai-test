#include "gmsh_mesh.h"
#include "fem_solver.h"
#include "bem_solver.h"
#include <iostream>

int main() {
    // 1. 仿真参数设置（单位：μm）
    double elec_width = 10.0;   // 电极宽度
    double elec_gap = 2.0;      // 电极间距
    double domain_size = 50.0;  // 求解域尺寸
    double mesh_size = 0.5;     // 网格尺寸
    double eps_r = 3.9;         // 氧化层相对介电常数
    std::string mesh_file = "capacitance.msh";

    // 2. Gmsh 生成网格
    c(mesh_file, elec_width, elec_gap, domain_size, mesh_size);

    // 3. 读取网格数据（简化版，实际需解析 .msh 文件）
    MeshData mesh_data;
    readGmshMesh(mesh_file, mesh_data);

    // 4. FEM 求解
    double C_fem = solveCapacitanceFEM(mesh_data, eps_r);

    // 5. BEM 求解
    double C_bem = solveCapacitanceBEM(mesh_data, eps_r);

    // 6. 结果对比
    std::cout << "\n===== 结果对比 =====" << std::endl;
    std::cout << "FEM 电容值：" << C_fem * 1e12 << " pF" << std::endl;
    std::cout << "BEM 电容值：" << C_bem * 1e12 << " pF" << std::endl;
    std::cout << "相对误差：" << std::abs(C_fem - C_bem)/((C_fem + C_bem)/2) * 100 << " %" << std::endl;

    return 0;
}