#include "bem_solver.h"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

// BEM 求解电容核心函数（基于边界积分方程）
double solveCapacitanceBEM(const MeshData& mesh_data, double eps_r) {
    const double eps0 = 8.854e-12; // 真空介电常数 (F/m)
    const double PI = 3.14159265358979323846;

    // 1. 提取电极边界（仅处理电极1/2的边界边，BEM无需内域）
    std::vector<BoundaryEdge> bem_edges;
    int n_edges = 0;
    int elec1_start = 0, elec1_end = 0, elec2_start = 0, elec2_end = 0;

    for (const auto& edge : mesh_data.boundary_edges) {
        if (edge.tag == 10 || edge.tag == 11) { // 仅电极边界
            bem_edges.push_back(edge);
            if (edge.tag == 10) { // 电极1
                if (elec1_start == 0) elec1_start = n_edges;
                elec1_end = n_edges;
            } else { // 电极2
                if (elec2_start == 0) elec2_start = n_edges;
                elec2_end = n_edges;
            }
            n_edges++;
        }
    }

    // 2. 构建边界积分方程矩阵 A (n_edges x n_edges)
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n_edges, n_edges);
    Eigen::VectorXd phi = Eigen::VectorXd::Zero(n_edges);

    // 初始化电位边界条件（电极1:1V，电极2:0V）
    for (int i = 0; i < n_edges; ++i) {
        if (i >= elec1_start && i <= elec1_end) phi(i) = 1.0;
        else phi(i) = 0.0;
    }

    // 3. 计算边界积分核（二维 Laplace 方程基本解：G = 1/(2πr)）
    for (int i = 0; i < n_edges; ++i) {
        // 第i个边的中点（配点法）
        const auto& ei = bem_edges[i];
        const auto& pi1 = mesh_data.nodes[ei.p1];
        const auto& pi2 = mesh_data.nodes[ei.p2];
        double xi = (pi1.x + pi2.x) / 2.0;
        double yi = (pi1.y + pi2.y) / 2.0;
        double li = std::sqrt(std::pow(pi2.x - pi1.x, 2) + std::pow(pi2.y - pi1.y, 2));

        for (int j = 0; j < n_edges; ++j) {
            if (i == j) {
                // 对角项（自积分）
                A(i, j) = 0.5; // 二维边界元自积分系数
            } else {
                // 第j个边的中点
                const auto& ej = bem_edges[j];
                const auto& pj1 = mesh_data.nodes[ej.p1];
                const auto& pj2 = mesh_data.nodes[ej.p2];
                double xj = (pj1.x + pj2.x) / 2.0;
                double yj = (pj1.y + pj2.y) / 2.0;
                double r = std::sqrt(std::pow(xi - xj, 2) + std::pow(yi - yj, 2));

                // 计算积分核 G = 1/(2πr) * 长度
                double lj = std::sqrt(std::pow(pj2.x - pj1.x, 2) + std::pow(pj2.y - pj1.y, 2));
                A(i, j) = (1.0 / (2 * PI * r)) * lj;
            }
        }
    }

    // 4. 求解边界电通量密度 q = A^{-1} * phi
    Eigen::VectorXd q = A.inverse() * phi;

    // 5. 计算电极1的总电荷
    double Q = 0.0;
    for (int i = elec1_start; i <= elec1_end; ++i) {
        const auto& ej = bem_edges[i];
        const auto& pj1 = mesh_data.nodes[ej.p1];
        const auto& pj2 = mesh_data.nodes[ej.p2];
        double lj = std::sqrt(std::pow(pj2.x - pj1.x, 2) + std::pow(pj2.y - pj1.y, 2));
        Q += eps0 * eps_r * q(i) * lj;
    }

    double C = std::abs(Q) / 1.0; // U=1V
    std::cout << "\nBEM 求解结果：" << std::endl;
    std::cout << "电极1电荷 Q = " << Q * 1e12 << " pC" << std::endl;
    std::cout << "电容 C = " << C * 1e12 << " pF" << std::endl;

    return C;
}