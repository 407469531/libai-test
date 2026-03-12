#include "gmsh_mesh.h"
#include <gmsh.h>
#include <iostream>

// 生成二维平板电容几何+网格（Gmsh API）
void generateCapacitanceMesh(const std::string& mesh_file, 
                           double elec_width, double elec_gap, double domain_size, 
                           double mesh_size) {
    // 初始化 Gmsh
    gmsh::initialize();
    gmsh::model::add("capacitance_2d");

    // 1. 定义几何点（单位：m，转换为μm方便输入）
    double scale = 1e-6; // 输入为μm，转换为米
    double x0 = -domain_size/2 * scale;
    double x1 = domain_size/2 * scale;
    double y_top = elec_gap * scale;
    double y_bot = 0.0;
    double elec_x0 = -elec_width/2 * scale;
    double elec_x1 = elec_width/2 * scale;

    // 外域点
    int p1 = gmsh::model::geo::addPoint(x0, y_bot, 0, mesh_size*scale);
    int p2 = gmsh::model::geo::addPoint(x1, y_bot, 0, mesh_size*scale);
    int p3 = gmsh::model::geo::addPoint(x1, y_top + elec_gap*scale, 0, mesh_size*scale);
    int p4 = gmsh::model::geo::addPoint(x0, y_top + elec_gap*scale, 0, mesh_size*scale);

    // 电极1（上电极）点
    int p5 = gmsh::model::geo::addPoint(elec_x0, y_top, 0, mesh_size*scale/2); // 加密电极网格
    int p6 = gmsh::model::geo::addPoint(elec_x1, y_top, 0, mesh_size*scale/2);
    // 电极2（下电极）点
    int p7 = gmsh::model::geo::addPoint(elec_x0, y_bot, 0, mesh_size*scale/2);
    int p8 = gmsh::model::geo::addPoint(elec_x1, y_bot, 0, mesh_size*scale/2);

    // 2. 定义线
    // 外域边界线
    int l1 = gmsh::model::geo::addLine(p1, p2);
    int l2 = gmsh::model::geo::addLine(p2, p3);
    int l3 = gmsh::model::geo::addLine(p3, p4);
    int l4 = gmsh::model::geo::addLine(p4, p1);
    // 电极1线
    int l5 = gmsh::model::geo::addLine(p5, p6);
    // 电极2线
    int l6 = gmsh::model::geo::addLine(p7, p8);

    // 3. 定义线环和面
    int outer_loop = gmsh::model::geo::addCurveLoop({l1, l2, l3, l4});
    int elec1_loop = gmsh::model::geo::addCurveLoop({l5});
    int elec2_loop = gmsh::model::geo::addCurveLoop({l6});

    // 物理分组（关键：标记电极/介质/边界）
    int domain_surface = gmsh::model::geo::addPlaneSurface({outer_loop});
    gmsh::model::addPhysicalGroup(2, {domain_surface}, 1); // 介质区域（FEM用）
    gmsh::model::setPhysicalName(2, 1, "dielectric");

    gmsh::model::addPhysicalGroup(1, {l5}, 10); // 电极1（边界，BEM/FEM用）
    gmsh::model::setPhysicalName(1, 10, "electrode1");
    gmsh::model::addPhysicalGroup(1, {l6}, 11); // 电极2（边界，BEM/FEM用）
    gmsh::model::setPhysicalName(1, 11, "electrode2");
    gmsh::model::addPhysicalGroup(1, {l2, l3, l4}, 12); // 外边界（接地）
    gmsh::model::setPhysicalName(1, 12, "far_field");

    // 同步几何
    gmsh::model::geo::synchronize();

    // 4. 生成网格（二维三角形网格）
    gmsh::model::mesh::generate(2);
    gmsh::model::mesh::refine(); // 网格细化

    // 5. 保存网格文件
    gmsh::write(mesh_file);
    std::cout << "Gmsh 网格已保存至：" << mesh_file << std::endl;

    // 结束 Gmsh
    gmsh::finalize();
}

// 读取 Gmsh 网格数据（简化版，仅提取FEM/BEM所需核心数据）
void readGmshMesh(const std::string& mesh_file,
                 MeshData& mesh_data) {
    // 实际工程中需解析 .msh 文件，此处简化：
    // 可使用 Gmsh API 或第三方解析库（如 gmshio）读取节点/单元/物理分组
    // 核心数据：
    // - mesh_data.nodes: 节点坐标（x,y）
    // - mesh_data.elements: 三角形单元（节点索引）
    // - mesh_data.boundary_edges: 边界边（电极1/2的边）
    // 此处省略解析逻辑，可参考 Gmsh 官方示例：https://gitlab.onelab.info/gmsh/gmsh/-/tree/master/examples/api
}