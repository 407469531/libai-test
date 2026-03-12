#ifndef GMSH_MESH_H
#define GMSH_MESH_H

#include <vector>
#include <string>

// 节点结构体
struct Point2D {
    double x, y;
    Point2D(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

// 边界边结构体（BEM核心）
struct BoundaryEdge {
    int p1, p2;   // 两个节点索引
    int tag;      // 物理标记（电极1/2/外边界）
    BoundaryEdge(int p1_ = 0, int p2_ = 0, int tag_ = 0) : p1(p1_), p2(p2_), tag(tag_) {}
};

// 网格数据结构体
struct MeshData {
    std::vector<Point2D> nodes;          // 所有节点
    std::vector<std::vector<int>> elements; // 三角形单元（节点索引）
    std::vector<BoundaryEdge> boundary_edges; // 边界边
};

// 生成Gmsh网格
void generateCapacitanceMesh(const std::string& mesh_file,
                           double elec_width, double elec_gap, double domain_size,
                           double mesh_size);

// 读取Gmsh网格
void readGmshMesh(const std::string& mesh_file, MeshData& mesh_data);

#endif // GMSH_MESH_H