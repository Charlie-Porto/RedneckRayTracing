#ifndef spacePixelConversionFunctions_cpp
#define spacePixelConversionFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions for converting 2d pixels to 3space and vice versa 
(some overlap in discription with cameraPixel Mapper -- to fix this)
-----------------------------------------------------------------*/

#include <cmath>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <ezprint.cpp>
#include <sign.cpp>
#include "pixelSpaceMappingFunctions.cpp"

namespace pce {
namespace pix_map {


glm::dvec3 convertPixelToPointOnViewSphere(const glm::dvec2& pixel,
                                           const glm::dvec3& view_sphere_center) {
  auto base_vector = glm::dvec3(0.0, 0.0, -1.0);
  // crawl along x, then y pixel axes to arrive at point in 3space
  for (int i = 0; i < abs(pixel.x); ++i) {
    base_vector = pce::pix_map::calculateHorizontalNeighborPixelVec3(base_vector, pce::math::sign(pixel.x));
  }
  for (int i = 0; i < abs(pixel.y); ++i) {
    base_vector = pce::pix_map::calculateVerticalNeighborPixelVec3(base_vector, -pce::math::sign(pixel.y));
  }
  auto b = (view_sphere_center + base_vector);
  // ezp::print_item("point result: ");
  // vezp::print_dvec3(b);
  return b;
}


glm::dvec2 convertPointOnViewSphereToPixel(const glm::dvec3& point,
                                           const glm::dvec3& view_sphere_center) {
  // ezp::print_item("point to pixel input: ");
  // vezp::print_dvec3(point);
  auto mpoint = glm::dvec3(point.x, point.y, point.z);
  int i = 0;
  while (abs(mpoint.y) >= 0.0001 && i <= 2000) {
    mpoint = pce::pix_map::calculateVerticalNeighborPixelVec3(mpoint, pce::math::sign(point.y));
    // vezp::print_dvec3(mpoint);
    // ezp::print_item("----------");
    ++i;
  }
  int j = 0;
  while (abs(mpoint.x) >= 0.0001 && j <= 2000) {
    mpoint = pce::pix_map::calculateHorizontalNeighborPixelVec3(mpoint, -pce::math::sign(point.x));
    ++j;
  }
  auto v = glm::dvec2(double(j) * pce::math::sign(point.x), double(i) * pce::math::sign(point.y));
  // ezp::print_item("pixel result");
  // vezp::print_dvec2(v);
  return v;
}

}
}



#endif /* spacePixelConversionFunctions_cpp */
