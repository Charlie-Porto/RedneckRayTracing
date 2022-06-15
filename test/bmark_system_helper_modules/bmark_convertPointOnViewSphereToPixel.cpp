#ifndef bmark_convertPointOnViewSphereToPixel_cpp
#define bmark_convertPointOnViewSphereToPixel_cpp

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "../../src/ecs/systems/subsystems/spacePixelConversionFunctions.cpp"

namespace kbmark {
namespace bmark_convertPointOnViewSphereToPixel {


auto bma_a = glm::dvec3(0, 0, -1);
auto bma_b = glm::dvec3(0, 0, 0);
static void BM_convertPointOnViewSphereToPixel_A(benchmark::State& state) {
  for (auto _ : state) {
    pce::pix_map::convertPointOnViewSphereToPixel(bma_a, bma_b);
  }
}
BENCHMARK(BM_convertPointOnViewSphereToPixel_A);

auto bmb_a = glm::dvec3(0.0174524, 0.0174497, -0.999695);
auto bmb_b = glm::dvec3(0, 0, 0);
static void BM_convertPointOnViewSphereToPixel_B(benchmark::State& state) {
  for (auto _ : state) {
    pce::pix_map::convertPointOnViewSphereToPixel(bmb_a, bmb_b);
  }
}
BENCHMARK(BM_convertPointOnViewSphereToPixel_B);

auto bmc_a = glm::dvec3(0.0523344, 0.0522671, -0.997261);
auto bmc_b = glm::dvec3(0, 0, 0);
static void BM_convertPointOnViewSphereToPixel_C(benchmark::State& state) {
  for (auto _ : state) {
    pce::pix_map::convertPointOnViewSphereToPixel(bmc_a, bmc_b);
  }
}
BENCHMARK(BM_convertPointOnViewSphereToPixel_C);


}
}
#endif /* bmark_convertPointOnViewSphereToPixel_cpp */
