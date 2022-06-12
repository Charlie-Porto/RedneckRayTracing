#ifndef test_calculateHorizontalNeighborPixelVec3_cpp
#define test_calculateHorizontalNeighborPixelVec3_cpp

#include <gtest/gtest.h>
#include "../../src/ecs/systems/subsystems/pixelSpaceMappingFunctions.cpp"

namespace ktest {
namespace test_calculateHorizontalNeighborPixelVec3 {


auto ta_a = glm::dvec3(0, 0, 1);
double ta_b = 90.0;
auto result_a = pce::pix_map::calculateHorizontalNeighborPixelVec3(ta_a, ta_b);
auto cr_a = glm::dvec3(-1, 0, 0);


TEST(test_calculateHorizontalNeighborPixelVec3, case1) {
  ASSERT_EQ(cr_a, result_a);
}

}
}
#endif /* test_calculateHorizontalNeighborPixelVec3_cpp */
