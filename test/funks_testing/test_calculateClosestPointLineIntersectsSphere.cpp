#ifndef test_calculateClosestPointLineIntersectsSphere_cpp
#define test_calculateClosestPointLineIntersectsSphere_cpp

#include <gtest/gtest.h>
#include "../../src/tools/math_objects/LineVectorForm.cpp"
#include "../../src/ecs/systems/funks/calculateClosestPointLineIntersectsSphere.cpp"

namespace ktest {
namespace test_calculateClosestPointLineIntersectsSphere {

pce::math_objs::LineVectorForm ta_a{
  .origin = glm::dvec3(0.0, 0.0, 10.0),
  .direction = glm::dvec3(0.0, 0.0, -1.0)
};
auto ta_b = glm::dvec3(0.0, 0.0, -2.0);
double ta_c = 2.0;
auto result_a = pce::math::calculateClosestPointLineIntersectsSphere(ta_a, ta_b, ta_c);
auto cr_a = glm::dvec3(0.0, 0.0, 0.0);

pce::math_objs::LineVectorForm tb_a{
  .origin = glm::dvec3(0.0, 0.0, 10.0),
  .direction = glm::dvec3(0.0, 0.0, -1.0)
};
auto tb_b = glm::dvec3(0.0, 0.0, -10.0);
double tb_c = 2.0;
auto result_b = pce::math::calculateClosestPointLineIntersectsSphere(tb_a, tb_b, tb_c);
auto cr_b = glm::dvec3(0.0, 0.0, -8.0);

TEST(test_calculateClosestPointLineIntersectsSphere, case1) {
  ASSERT_EQ(cr_a, result_a);
}
TEST(test_calculateClosestPointLineIntersectsSphere, case2) {
  ASSERT_EQ(cr_b, result_b);
}

}
}
#endif /* test_calculateClosestPointLineIntersectsSphere_cpp */
