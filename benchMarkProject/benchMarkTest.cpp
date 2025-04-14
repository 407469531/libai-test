#include <benchmark/benchmark.h>
#include <chrono>
#include <thread>

void BM_Sleep(benchmark::State& state) {
    for (auto _ : state) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

BENCHMARK(BM_Sleep);

//BENCHMARK_MAIN();

/////////////////////////////////////////////////////////////////
//#include <benchmark/benchmark.h>
//#include <vector>

void BM_VectorPushBack(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        for (int i = 0; i < state.range(0); ++i) {
            v.push_back(i);
        }
    }
}

BENCHMARK(BM_VectorPushBack)->Range(8, 8<<10);

//BENCHMARK_MAIN();

//////////////////////////////////////////////////////////////////////

//#include <benchmark/benchmark.h>
//#include <vector>

void BM_MemoryUsage(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v(state.range(0), 0);
        benchmark::DoNotOptimize(v.data());
    }
    state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(int));
}

BENCHMARK(BM_MemoryUsage)->Range(8, 8<<10);

BENCHMARK_MAIN();
