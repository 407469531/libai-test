#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
#include <execution> // C++17引入，包含执行策略
#include "pub.h"

void parallelTest1() {
    std::vector<int> vec(200000000, 1); // 创建一个包含100万个元素的向量
    auto start = std::chrono::high_resolution_clock::now();
    std::for_each(vec.begin(), vec.end(), [](int& x) { x *= 2; }); // 串行版本
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Serial time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    vec = std::vector<int>(200000000, 1); // 重置向量以进行下一次测试
    start = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::par, vec.begin(), vec.end(), [](int& x) { x *= 2; }); // 并行版本
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

TEST(parallel_test, stl_parallel){
    parallelTest1();
}
