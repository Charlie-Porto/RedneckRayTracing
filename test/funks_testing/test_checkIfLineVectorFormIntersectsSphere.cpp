#ifndef test_check_if_linevectorform_intersects_sphere_cpp
#define test_check_if_linevectorform_intersects_sphere_cpp

#include <gtest/gtest.h>
#include "../../src/tools/math_objects/LineVectorForm.cpp"
#include "../../src/ecs/systems/funks/checkIfLineVectorFormIntersectsSphere.cpp"



namespace ktest {
namespace test_check_if_linevectorform_intersects_sphere {


// case 1
pce::math_objs::LineVectorForm ta_a{
  .origin = glm::dvec3(0.0, 0.0, 10.0),
  .direction = glm::dvec3(0.0, 0.0, -1.0)
};
auto ta_b = glm::dvec3(5.0, 1.0, 0.0);
double ta_c = 6.0;
bool result_a = pce::math::checkIfLineVectorFormIntersectsSphere(ta_a, ta_b, ta_c);
bool cr_a = true;

// case 2
// same as 6, just flip sign of z
pce::math_objs::LineVectorForm tb_a{
  .origin = glm::dvec3(0.0, 0.0, 10.0),
  .direction = glm::dvec3(0.0, 0.0, 1.0)
};
auto tb_b = glm::dvec3(5.0, 1.0, 0.0);
double tb_c = 6.0;
bool result_b = pce::math::checkIfLineVectorFormIntersectsSphere(tb_a, tb_b, tb_c);
bool cr_b = true;

// case 3
pce::math_objs::LineVectorForm tc_a{
  .origin = glm::dvec3(10.0, 0.0, 10.0),
  .direction = glm::dvec3(0.0, 0.0, 1.0)
};
auto tc_b = glm::dvec3(5.0, 1.0, 0.0);
double tc_c = 2.0;
bool result_c = pce::math::checkIfLineVectorFormIntersectsSphere(tc_a, tc_b, tc_c);
bool cr_c = false;

// case 4
pce::math_objs::LineVectorForm td_a{
  .origin = glm::dvec3(0.0, 0.0, 250.0),
  .direction = glm::dvec3(0.0, 0.0, 1.0)
};
auto td_b = glm::dvec3(5.0, 1.0, 0.0);
double td_c = 6.0;
bool result_d = pce::math::checkIfLineVectorFormIntersectsSphere(td_a, td_b, td_c);
bool cr_d = true;


// case 5
pce::math_objs::LineVectorForm te_a{
  .origin = glm::dvec3(0.0, 0.0, 250.0),
  .direction = glm::dvec3(0.0, 0.0, 1.0)
};
auto te_b = glm::dvec3(20.0, 20.0, -20);
double te_c = 55.0;
bool result_e = pce::math::checkIfLineVectorFormIntersectsSphere(te_a, te_b, te_c);
bool cr_e = true;

// case 5
pce::math_objs::LineVectorForm tf_a{
  .origin = glm::dvec3(0.0, 0.0, 250.0),
  .direction = glm::dvec3(0.0, 0.0, 1.0)
};
auto tf_b = glm::dvec3(20.0, 20.0, -20);
double tf_c = 15.0;
bool result_f = pce::math::checkIfLineVectorFormIntersectsSphere(tf_a, tf_b, tf_c);
bool cr_f = false;


TEST(test_check_if_linevectorform_intersects_sphere, case1) {
  ASSERT_EQ(cr_a, result_a);
}
TEST(test_check_if_linevectorform_intersects_sphere, case2) {
  ASSERT_EQ(cr_b, result_b);
}
TEST(test_check_if_linevectorform_intersects_sphere, case3) {
  ASSERT_EQ(cr_c, result_c);
}
TEST(test_check_if_linevectorform_intersects_sphere, case4) {
  ASSERT_EQ(cr_d, result_d);
}
TEST(test_check_if_linevectorform_intersects_sphere, case5) {
  ASSERT_EQ(cr_e, result_e);
}
TEST(test_check_if_linevectorform_intersects_sphere, case6) {
  ASSERT_EQ(cr_f, result_f);
}


}
}

#endif /* test_check_if_linevectorform_intersects_sphere_cpp */
