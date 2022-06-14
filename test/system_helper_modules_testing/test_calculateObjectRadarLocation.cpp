#ifndef test_calculateObjectRadarLocation_cpp
#define test_calculateObjectRadarLocation_cpp

#include <gtest/gtest.h>
#include "../../src/ecs/systems/sphericalRadarFunctions.cpp"

namespace ktest {
namespace test_calculateObjectRadarLocation {


auto ta_a = glm::dvec3(0, 0, -10);
double ta_b = 1;
auto result_a = pce::radar::calculateObjectRadarLocation(ta_a, ta_b);
auto cr_a = glm::dvec3(0, 0, 0);


TEST(test_calculateObjectRadarLocation, case1) {
  ASSERT_EQ(cr_a, result_a)
      << "result x: "<< result_a.x << std::endl
      << "result y: "<< result_a.y << std::endl
      << "result z: "<< result_a.z << std::endl;
}

}
}
#endif /* test_calculateObjectRadarLocation_cpp */
