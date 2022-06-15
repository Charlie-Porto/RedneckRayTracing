#ifndef test_convertPointOnViewSphereToPixel_cpp
#define test_convertPointOnViewSphereToPixel_cpp

#include <gtest/gtest.h>
#include "../../src/ecs/systems/subsystems/spacePixelConversionFunctions.cpp"

namespace ktest {
namespace test_convertPointOnViewSphereToPixel {


// auto ta_a = glm::dvec3(0, 0, -1);
// auto ta_b = glm::dvec3(0, 0, 0);
// auto result_a = pce::pix_map::convertPointOnViewSphereToPixel(ta_a, ta_b);
// auto cr_a = glm::dvec2(0, 0);
// TEST(test_convertPointOnViewSphereToPixel, case1) {
//   ASSERT_EQ(cr_a, result_a);
// }

// auto tb_a = glm::dvec3(0.0174524, 0.0174497, -0.999695);
// auto tb_b = glm::dvec3(0, 0, 0);
// auto result_b = pce::pix_map::convertPointOnViewSphereToPixel(tb_a, tb_b);
// auto cr_b = glm::dvec2(100.0, -100.0);
// TEST(test_convertPointOnViewSphereToPixel, case2) {
//   ASSERT_EQ(cr_b, result_b);
// }

auto tb_a = glm::dvec3(0.0523344, 0.0522671, -0.997261);
auto tb_b = glm::dvec3(0, 0, 0);
auto result_b = pce::pix_map::convertPointOnViewSphereToPixel(tb_a, tb_b);
auto cr_b = glm::dvec2(300.0, 300.0);
TEST(test_convertPointOnViewSphereToPixel, case2) {
  ASSERT_EQ(cr_b, result_b);
}


}
}
#endif /* test_convertPointOnViewSphereToPixel_cpp */
