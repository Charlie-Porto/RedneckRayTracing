#ifndef test_calculateNeighborVectorIncrements_cpp
#define test_calculateNeighborVectorIncrements_cpp

#include <gtest/gtest.h>
#include "../../src/ecs/systems/subsystems/pixelSpaceMappingFunctions.cpp"
// #include <benchmark/benchmark.h>
#include <iostream>
#include <stdio.h>
#include <ezprint.cpp>

namespace ktest {
namespace test_calculateNeighborVectorIncrements {

double te_b = .000142506;
auto te_c = glm::dvec3(0.0, 1.0, 0.0);

// static void BM_test_funcA(benchmark::State& state) {
//   for (auto _ : state) {
//      pce::pix_map::calculateAdjacentPixelVector3(te_a, te_b, te_c);
//   }
// }

auto te_a = glm::dvec3(0.0, 0.0, 1.0);
// static void BM_calculateVerticalNeighborPixelVec3_A(benchmark::State& state) {
//   for (auto _ : state) {
//      pce::pix_map::calculateVerticalNeighborPixelVec3(te_a, 1.0);
//   }
// }
// BENCHMARK(BM_calculateVerticalNeighborPixelVec3_A);


// auto bm_b = glm::dvec3(.4, .3, .7);
// static void BM_calculateVerticalNeighborPixelVec3_B(benchmark::State& state) {
//   for (auto _ : state) {
//      pce::pix_map::calculateVerticalNeighborPixelVec3(bm_b, 1.0);
//   }
// }
// BENCHMARK(BM_calculateVerticalNeighborPixelVec3_B);

// static void BM_test_funcD(benchmark::State& state) {
  // for (auto _ : state) {
    //  pce::pix_map::calculateHorizontalNeighborPixelVec3(te_a);
  // }
// }


// BENCHMARK(BM_test_funcA);
// BENCHMARK(BM_test_funcD);

// static void BM_test_funcC(benchmark::State& state) {
//   for (auto _ : state) {
//      pce::pix_map::calculateStandardPixelDistance();
//   }
// }
// BENCHMARK(BM_test_funcC);

glm::dvec3 result_e = pce::pix_map::calculateAdjacentPixelVector3(te_a, te_b, te_c);
auto cr_e = glm::dvec3(0, 1.0, -0.0);
TEST(test_calculateAdjacentPixelVector3, case1) {
  ASSERT_EQ(cr_e, result_e);
}


// auto result_f = pce::pix_map::convertAngleToComplexNumber(90.0);
// auto cr_f = std::complex<double>(0, 1.0);
// TEST(test_convertAngleToComplexNumber, case1) {
  // ASSERT_EQ(cr_f, result_f);
// }

// static void BM_test_funcE(benchmark::State& state) {
//   for (auto _ : state) {
//      pce::pix_map::convertAngleToComplexNumber((.001));
//   }
// }


double result_b = pce::pix_map::calculateStandardPixelDistance();

double cr_b = .000142506;
TEST(test_calculateStandardPixelDistance, case1) {
  ASSERT_EQ(cr_b, result_b);
}

// double tXa_a = 90;
// auto tXa_b = glm::dvec3(1, 1, 1);
// double result_Xa = pce::pix_map::calculateNeighborVectorXIncrement(tXa_a, tXa_b);
// double cr_Xa = -1.0;
// TEST(test_calculateNeighborVectorXIncrement, case1) {
//   ASSERT_EQ(cr_Xa, result_Xa);
// }


// double tYa_a = 360;
// auto tYa_b = glm::dvec3(1.0, 1.0, 1.0);
// double result_Ya = pce::pix_map::calculateNeighborVectorYIncrement(tYa_a, tYa_b);
// double cr_Ya = 0.0;
// TEST(test_calculateNeighborVectorYIncrement, case1) {
//   ASSERT_EQ(cr_Ya, result_Ya);
// }


// double tZa_a = 0;
// auto tZa_b = glm::dvec3(1.0, 1.0, 1.0);
// double result_Za = pce::pix_map::calculateNeighborVectorZIncrement(tZa_a, tZa_b);
// double cr_Za = 0.0;
// TEST(test_calculateNeighborVectorZIncrement, case1) {
//   ASSERT_EQ(cr_Za, result_Za);
// }









}
}
#endif /* test_calculateNeighborVectorIncrements_cpp */
