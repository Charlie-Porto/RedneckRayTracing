#ifndef test_convertPixelToPointOnViewSphere_cpp
#define test_convertPixelToPointOnViewSphere_cpp

#include <gtest/gtest.h>
#include "../../src/ecs/systems/subsystems/spacePixelConversionFunctions.cpp"
#include <ezprint.cpp>
#include <vezprint.cpp>

namespace ktest {
namespace test_convertPixelToPointOnViewSphere {


auto ta_a = glm::dvec2(450, 301);
auto ta_b = glm::dvec3(0, 0, 0);
auto result_a = pce::pix_map::convertPixelToPointOnViewSphere(ta_a, ta_b);
auto cr_a = glm::dvec3(0, 0, -1);
// TEST(test_convertPixelToPointOnViewSphere, case1) {
  // ASSERT_EQ(cr_a, result_a);
// }

auto result_b = pce::pix_map::convertPointOnViewSphereToPixel(result_a, ta_b);
auto cr_b = ta_a;
TEST(test_convertPointOnViewSphereToPixel, case2) {
  ASSERT_EQ(cr_b, result_b);
}

// auto tb_a = glm::dvec2(100, 100);
// auto tb_b = glm::dvec3(0, 0, 0);
// auto result_b = pce::pix_map::convertPixelToPointOnViewSphere(tb_a, tb_b);
// auto cr_b = glm::dvec3(0.0174524, 0.0174497, -0.999695);
// TEST(test_convertPixelToPointOnViewSphere, case2) {
  // ASSERT_EQ(cr_b, result_b);
// }


}
}
#endif /* test_convertPixelToPointOnViewSphere_cpp */
