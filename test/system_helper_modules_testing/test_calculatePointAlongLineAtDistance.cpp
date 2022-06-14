#ifndef test_calculatePointAlongLineAtDistance_cpp
#define test_calculatePointAlongLineAtDistance_cpp

#include <gtest/gtest.h>
#include <iostream>
#include "../../src/ecs/systems/sphericalRadarFunctions.cpp"

namespace ktest {
namespace test_calculatePointAlongLineAtDistance {


auto ta_a = pce::math_objs::LineVectorForm{
  .origin = glm::dvec3(0.0, 0.0, 0.0),
  .direction = glm::dvec3(0.0, 0.0, -1.0)
};
double ta_b = 1.0;
auto result_a = pce::radar::calculatePointAlongLineAtDistance(ta_a, ta_b);
auto cr_a = glm::dvec3(0.0, 0.0, -1.0);
TEST(test_calculatePointAlongLineAtDistance, case1) {
  ASSERT_EQ(cr_a, result_a);
}

auto tb_a = pce::math_objs::LineVectorForm{
  .origin = glm::dvec3(0.0, 0.0, 0.0),
  .direction = glm::dvec3(0.0, 0.0, -1.0)
};
double tb_b = 3.0;
auto result_b = pce::radar::calculatePointAlongLineAtDistance(tb_a, tb_b);
auto cr_b = glm::dvec3(0.0, 0.0, -3.0);
TEST(test_calculatePointAlongLineAtDistance, case2) {
  ASSERT_EQ(cr_b, result_b);
}


auto tc_a = pce::math_objs::LineVectorForm{
  .origin = glm::dvec3(0.0, 0.0, 1.0),
  .direction = glm::dvec3(0.0, 0.0, -1.0)
};
double tc_b = -10.0;
auto result_c = pce::radar::calculatePointAlongLineAtDistance(tc_a, tc_b);
auto cr_c = glm::dvec3(-0.0, -0.0, 11.0);
TEST(test_calculatePointAlongLineAtDistance, case3) {
  ASSERT_EQ(cr_c, result_c) 
      << "result x: "<< result_c.x << std::endl
      << "result y: "<< result_c.y << std::endl
      << "result z: "<< result_c.z << std::endl;
}



}
}
#endif /* test_calculatePointAlongLineAtDistance_cpp */
