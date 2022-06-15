#ifndef test_calculateVerticalNeighborPixelVec3_cpp
#define test_calculateVerticalNeighborPixelVec3_cpp

#include <gtest/gtest.h>
#include "../../src/ecs/systems/subsystems/pixelSpaceMappingFunctions.cpp"

namespace ktest {
namespace test_calculateVerticalNeighborPixelVec3 {


auto ta_a = glm::dvec3(4.91941, 4.78118, -0.999456);
auto ta_b = 1.0;
auto result_a = pce::pix_map::calculateVerticalNeighborPixelVec3_new(ta_a, ta_b);
// auto result_a = pce::pix_map::calculateVerticalNeighborPixelVec3(ta_a, ta_b);
auto cr_a = glm::dvec3(4.91941, 4.781, -1.00029);
TEST(test_calculateVerticalNeighborPixelVec3, case1) {
  ASSERT_EQ(cr_a, result_a)
     << "result x: " << result_a.x << std::endl
     << "result y: " << result_a.y << std::endl
     << "result z: " << result_a.z << std::endl;
}


auto tb_a = glm::dvec3(4.91941, 4.781, -1.00029);
auto tb_b = 1.0;
auto result_b = pce::pix_map::calculateVerticalNeighborPixelVec3_new(tb_a, tb_b);
// auto result_b = pce::pix_map::calculateVerticalNeighborPixelVec3(tb_a, tb_b);
auto cr_b = glm::dvec3(0, -0.000349066, -1);
TEST(test_calculateVerticalNeighborPixelVec3, case2) {
  ASSERT_EQ(cr_b, result_b)
     << "result x: " << result_b.x << std::endl
     << "result y: " << result_b.y << std::endl
     << "result z: " << result_b.z << std::endl;
}


}
}
#endif /* test_calculateVerticalNeighborPixelVec3_cpp */
