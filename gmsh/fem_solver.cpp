#include "fem_solver.h"
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <cmath>

// FEM 求解电容核心函数
double solveCapacitanceFEM(const MeshData& mesh_data, double eps_r) {
    const double eps0 = 8.854e-12; // 真空介电常数 (F/m)
    int n_nodes = mesh_data.nodes.size();

    // 1. 初始化稀疏刚度矩阵 K 和载荷向量 F
    Eigen::SparseMatrix<double> K(n_nodes, n_nodes);
    Eigen::VectorXd F = Eigen::VectorXd::Zero(n_nodes);

    // 2. 组装刚度矩阵（二维三角形单元）
    for (const auto& elem : mesh_data.elements) {
        // 单元节点坐标
        const auto& p1 = mesh_data.nodes[elem[0]];
        const auto& p2 = mesh_data.nodes[elem[1]];
        const auto& p3 = mesh_data.nodes[elem[2]];

        // 计算单元面积
        double area = 0.5 * std::abs(
            (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)
        );

        // 单元刚度矩阵系数（二维线性三角形单元）
        double b1 = p2.y - p3.y;
        double b2 = p3.y - p1.y;
        double b3 = p1.y - p2.y;
        double c1 = p3.x - p2.x;
        double c2 = p1.x - p3.x;
        double c3 = p2.x - p1.x;

        Eigen::Matrix3d Ke;
        double coeff = eps0 * eps_r / (4 * area);
        Ke << b1*b1 + c1*c1, b1*b2 + c1*c2, b1*b3 + c1*c3,
              b2*b1 + c2*c1, b2*b2 + c2*c2, b2*b3 + c2*c3,
              b3*b1 + c3*c1, b3*b2 + c3*c2, b3*b3 + c3*c3;
        Ke *= coeff;

        // 组装到全局矩阵
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                K.coeffRef(elem[i], elem[j]) += Ke(i, j);
            }
        }
    }

    // 3. 施加边界条件（电极1: 1V，电极2: 0V，外边界: 0V）
    // 标记电极节点
    std::vector<bool> is_electrode1(n_nodes, false);
    std::vector<bool> is_electrode2(n_nodes, false);
    for (const auto& edge : mesh_data.boundary_edges) {
        if (edge.tag == 10) { // 电极1
            is_electrode1[edge.p1] = true;
            is_electrode1[edge.p2] = true;
        } else if (edge.tag == 11) { // 电极2
            is_electrode2[edge.p1] = true;
            is_electrode2[edge.p2] = true;
        } else if (edge.tag == 12) { // 外边界
            is_electrode2[edge.p1] = true;
            is_electrode2[edge.p2] = true;
        }
    }

    // 修改 K 和 F
    Eigen::SparseMatrix<double> K_bak = K;
    for (int i = 0; i < n_nodes; ++i) {
        if (is_electrode1[i]) {
            // 电极1: 电位=1V
            K.row(i).setZero();
            K.coeffRef(i, i) = 1.0;
            F(i) = 1.0;
        } else if (is_electrode2[i]) {
            // 电极2/外边界: 电位=0V
            K.row(i).setZero();
            K.coeffRef(i, i) = 1.0;
            F(i) = 0.0;
        }
    }
    // 修正载荷向量
    for (int i = 0; i < n_nodes; ++i) {
        if (!is_electrode1[i] && !is_electrode2[i]) {
            for (int j = 0; j < n_nodes; ++j) {
                if (is_electrode1[j]) F(i) -= K_bak.coeff(i, j) * 1.0;
                if (is_electrode2[j]) F(i) -= K_bak.coeff(i, j) * 0.0;
            }
        }
    }

    // 4. 求解电位
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver;
    solver.compute(K);
    if (solver.info() != Eigen::Success) {
        std::cerr << "FEM 矩阵分解失败！" << std::endl;
        return -1;
    }
    Eigen::VectorXd phi = solver.solve(F);

    // 5. 计算电荷和电容
    double Q = 0.0;
    for (const auto& edge : mesh_data.boundary_edges) {
        if (edge.tag == 10) { // 电极1边界
            const auto& p1 = mesh_data.nodes[edge.p1];
            const auto& p2 = mesh_data.nodes[edge.p2];
            double phi1 = phi[edge.p1];
            double phi2 = phi[edge.p2];

            // 计算边界法向量和电通量
            double dx = p2.x - p1.x;
            double dy = p2.y - p1.y;
            double len = std::sqrt(dx*dx + dy*dy);
            // 法向量（指向域内）
            double nx = dy / len;
            double ny = -dx / len;

            // 电位梯度近似
            double dphi_dn = (phi2 - phi1) / len;
            double Dn = eps0 * eps_r * dphi_dn; // 电通量密度法向分量
            Q += Dn * len; // 电荷积分
        }
    }

    double C = std::abs(Q) / 1.0; // U=1V
    std::cout << "FEM 求解结果：" << std::endl;
    std::cout << "电极1电荷 Q = " << Q * 1e12 << " pC" << std::endl;
    std::cout << "电容 C = " << C * 1e12 << " pF" << std::endl;

    return C;
}