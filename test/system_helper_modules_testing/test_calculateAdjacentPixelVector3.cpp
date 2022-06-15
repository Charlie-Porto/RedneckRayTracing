#ifndef test_calculateAdjacentPixelVector3_cpp
#define test_calculateAdjacentPixelVector3_cpp

#include <gtest/gtest.h>
#include "../../src/ecs/systems/subsystems/pixelSpaceMappingFunctions.cpp"

namespace ktest {
namespace test_calculateAdjacentPixelVector3 {


auto ta_a = glm::dvec3(0, 0, -1.0);
double ta_b = global_const::pixel_angle_in_3space;
auto ta_c = glm::dvec3(1.0, 0, 0);
auto result_a = pce::pix_map::calculateAdjacentPixelVector3(ta_a, ta_b, ta_c);
auto cr_a = glm::dvec3(0, -1.0, -0.0);
TEST(test_calculateAdjacentPixelVector3, case1) {
  ASSERT_EQ(cr_a, result_a)
      << "result x: "<< result_a.x << std::endl
      << "result y: "<< result_a.y << std::endl
      << "result z: "<< result_a.z << std::endl;
}


auto tb_a = result_a;
double tb_b = ta_b;
auto tb_c = glm::dvec3(1.0, 0, 0);
auto result_b = pce::pix_map::calculateAdjacentPixelVector3(tb_a, tb_b, tb_c);
auto cr_b = glm::dvec3(0, 0.0, 1.0);
TEST(test_calculateAdjacentPixelVector3, case2) {
  ASSERT_EQ(cr_b, result_b)
      << "result x: "<< result_b.x << std::endl
      << "result y: "<< result_b.y << std::endl
      << "result z: "<< result_b.z << std::endl;
}


auto tc_a = result_b;
double tc_b = ta_b;
auto tc_c = glm::dvec3(1.0, 0, 0);
auto result_c = pce::pix_map::calculateAdjacentPixelVector3(tc_a, tc_b, tc_c);
auto cr_c = glm::dvec3(0, 0.0, 1.0);
TEST(test_calculateAdjacentPixelVector3, case3) {
  ASSERT_EQ(cr_c, result_c)
      << "result x: "<< result_c.x << std::endl
      << "result y: "<< result_c.y << std::endl
      << "result z: "<< result_c.z << std::endl;
}




}
}
#endif /* test_calculateAdjacentPixelVector3_cpp */
