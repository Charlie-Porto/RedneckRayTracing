#ifndef bmark_calculateHorizontalNeighborPixelVec3_cpp
#define bmark_calculateHorizontalNeighborPixelVec3_cpp

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "../../src/ecs/systems/subsystems/pixelSpaceMappingFunctions.cpp"

namespace kbmark {
namespace bmark_calculateHorizontalNeighborPixelVec3 {


auto bm_a = glm::dvec3(0.0, 0.0, 1.0);
// double bm_b = 90.0;

static void BM_calculateHorizontalNeighborPixelVec3_A(benchmark::State& state) {
  for (auto _ : state) {
    // pce::pix_map::calculateHorizontalNeighborPixelVec3(bm_a, bm_b);
    pce::pix_map::calculateHorizontalNeighborPixelVec3(bm_a, 1.0);
  }
}
BENCHMARK(BM_calculateHorizontalNeighborPixelVec3_A);

static void BM_calculateHorizontalNeighborPixelVec3_old_A(benchmark::State& state) {
  for (auto _ : state) {
    // pce::pix_map::calculateHorizontalNeighborPixelVec3(bm_a, bm_b);
    pce::pix_map::calculateHorizontalNeighborPixelVec3_old(bm_a);
  }
}
BENCHMARK(BM_calculateHorizontalNeighborPixelVec3_old_A);

auto bm_b = glm::dvec3(.4, .3, .7);
static void BM_calculateHorizontalNeighborPixelVec3_B(benchmark::State& state) {
  for (auto _ : state) {
    // pce::pix_map::calculateHorizontalNeighborPixelVec3(bm_a, bm_b);
    pce::pix_map::calculateHorizontalNeighborPixelVec3(bm_b, 1.0);
  }
}
BENCHMARK(BM_calculateHorizontalNeighborPixelVec3_B);

static void BM_calculateHorizontalNeighborPixelVec3_old_B(benchmark::State& state) {
  for (auto _ : state) {
    // pce::pix_map::calculateHorizontalNeighborPixelVec3(bm_a, bm_b);
    pce::pix_map::calculateHorizontalNeighborPixelVec3_old(bm_a);
  }
}

BENCHMARK(BM_calculateHorizontalNeighborPixelVec3_old_B);
}
}
#endif /* bmark_calculateHorizontalNeighborPixelVec3_cpp */
