#ifndef pixelSpaceMappingFunctions_cpp
#define pixelSpaceMappingFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to assist in the translating of 'real' 3-space into pixel 2-space
and vice versa
-----------------------------------------------------------------*/

#include <cmath>
#include <complex>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_double.hpp>
#include <quaternion_funktions.cpp>
#include <ezprint.cpp>
#include <vezprint.cpp>
#include <vector3_functions.cpp>
#include <sign.cpp>
#include "../../../constants/static_variables.cpp"

namespace pce {
namespace pix_map {

const double PI = 3.14159265;


glm::dvec3 calculateAdjacentPixelVector3(const glm::dvec3& base_vector,
                                         const double& angle,
                                         const glm::dvec3& axis_of_rotation) {
  // can use either x or y axis as axis of rotation because we are calculating
  // increment distance which will be same in either case
  const glm::dquat rotation_quaternion = qfunc::convertAngleAxisToQuaternion(
                                             angle, axis_of_rotation);
  auto const result = qfunc::rotateVector3byQuaternion(base_vector, rotation_quaternion);
  // ezp::print_item("Adjacent Pixel Result: ");
  // vezp::print_dvec3(result); 
  return result;
}


glm::dvec3 calculateVerticalNeighborPixelVec3(const glm::dvec3& base_vector, double direction) {
  if (direction == 0.0) {return base_vector;}
  const double angle_of_axis = acos(dot(glm::dvec2(base_vector.x, base_vector.z), glm::dvec2(0, -1.0)));
  // ezp::print_labeled_item("angle of axis: ", angle_of_axis);
  const glm::dquat rotation_quaternion = qfunc::convertAngleAxisToQuaternion(
                                             angle_of_axis, glm::dvec3(0.0, 1.0, 0.0));
  const glm::dvec3 axis = qfunc::rotateVector3byQuaternion(glm::dvec3(1.0, 0.0, 0.0), rotation_quaternion);
  return calculateAdjacentPixelVector3(base_vector, global_const::pixel_angle_in_3space * direction, 
                                       axis);
}

glm::dvec3 calculateHorizontalNeighborPixelVec3(const glm::dvec3& base_vector, double direction) {
  if (direction == 0.0) {return base_vector;}
  return calculateAdjacentPixelVector3(base_vector, global_const::pixel_angle_in_3space * direction, 
                                       glm::dvec3(0.0, 1.0, 0.0));
}

std::complex<double> convertAngleToComplexNumber(const double& angle) {
  return std::complex<double>(cos(angle * PI/180.0), sin(angle * PI/180.0));
}


glm::dvec3 calculateHorizontalNeighborPixelVec3_old(const glm::dvec3& base_vector) {
                                                // const double& angle) {
  // copy this technique from other 3d rendering project 
  const double xz_hypotenuse = sqrt(pow(base_vector.x, 2.0) + pow(base_vector.z, 2.0));
  const double xz_circle_radius = sqrt(pow(xz_hypotenuse, 2.0) + pow(base_vector.y, 2.0));
  // get angle with z-axis
  const double angle_with_z_axis = cos(dot(glm::dvec2(base_vector.x, base_vector.z),
                                           glm::dvec2(0, -1.0)));
  std::complex<double> const pixel_complex = xz_circle_radius * convertAngleToComplexNumber(angle_with_z_axis);
  std::complex<double> const angle_complex = convertAngleToComplexNumber(global_const::pixel_angle_in_3space);
  std::complex<double> const new_xz_coordinates = pixel_complex * angle_complex;
  double const theta = atan(std::imag(new_xz_coordinates)/std::real(new_xz_coordinates));
  return glm::dvec3(xz_circle_radius*sin(theta), base_vector.y, xz_circle_radius*cos(theta));
}


// glm::dvec2 calculateAdjacentPixelNewCoordinates(const glm::dvec2& base_vector,
//                                                 const double& pixel_distance,
//                                                 const double& angle) {
//   // as part of method, only two coordinates will change
//   // each movement (x or y, and z.)
//   const double angle_of_movement = (90.0 - abs(angle)) * pce::math::sign(angle);
//   const double new_point_a = cos(angle_of_movement);
//   const double new_z = sin(angle_of_movement);
//   auto const new_coordinates = glm::dvec2(new_point_a, new_z);
//   ezp::print_item("new 2d coordinates: ");
//   vezp::print_dvec2(new_coordinates);
//   return new_coordinates;
// }

// glm::dvec3 calculateHorizontalNeighborPixelOld(const glm::dvec3& base_vector,
//                                             const double& pixel_distance,
//                                             const double& angle) {
//   auto const vector_2d = glm::dvec2(base_vector.y, base_vector.z);
//   const glm::dvec2 updated_coordinates = calculateAdjacentPixelNewCoordinates(
//                                              vector_2d, pixel_distance, angle);
//                                                      // x and y below correspond to y and z
//   auto const new_vector3 = glm::dvec3(base_vector.x, updated_coordinates.x, updated_coordinates.y);
//   ezp::print_item("new vector3: ");
//   vezp::print_dvec3(new_vector3);
//   return new_vector3;
// }


double calculateStandardPixelDistance() {
  auto base_vector = normalize(glm::dvec3(1.0, 1.0, 1.0));
  const auto axis_of_rotation = glm::dvec3(0.0, 1.0, 0.0);
  const glm::dvec3 adjacent_pixel = pce::pix_map::calculateAdjacentPixelVector3(
                                        base_vector,
                                        global_const::pixel_angle_in_3space,
                                        axis_of_rotation);
  double dist = vfunc::calculateDistanceBetweenPosition3Vectors(base_vector, adjacent_pixel);
  // ezp::print_labeled_item("distance: ", dist);
  return dist;
}

}
}

#endif /* pixelSpaceMappingFunctions_cpp */
