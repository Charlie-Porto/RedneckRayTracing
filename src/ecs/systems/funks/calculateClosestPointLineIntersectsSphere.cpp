#ifndef calculateClosestPointLineIntersectsSphere_cpp
#define calculateClosestPointLineIntersectsSphere_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
function that finds the point(s) where a LineVec3 intersects a sphere
-----------------------------------------------------------------*/
#include <stdexcept>
#include <cmath>
#include <algorithm>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>

namespace pce {
namespace math {

glm::dvec3 calculateClosestPointLineIntersectsSphere(
                            const pce::math_objs::LineVectorForm& line, 
                            const glm::dvec3& sphere_center,
                            const double sphere_radius) {
  // solve for line's d value by plugging line into circle equation
  // ad^2 + bd + c = 0  ===> use the quadratic equation
  // note: direction of line DOES NOT MATTER in calculation;
  //       still need to calculate whether point of contact is
  //       behind or in front of the POV 
  const glm::dvec3 o_less_c = line.origin - sphere_center;
  double a = dot(line.direction, line.direction);
  double b = 2.0 * dot(line.direction, (o_less_c));
  double c = dot(o_less_c, o_less_c) - pow(sphere_radius, 2.0);
  double discriminant = pow(b, 2.0) - 4 * a * c; 
  ezp::print_labeled_item("discriminant: ", discriminant);
  
  if (discriminant < 0) {
    throw std::domain_error("Line does not intersect Sphere at any point (discriminant < 0)");
  }
  const double distance_a = (-b - sqrt(discriminant)) / (2 * a);
  const double distance_b = (-b + sqrt(discriminant)) / (2 * a);  

  const double closest_intersection_distance = std::min(distance_a, distance_b);
  const glm::dvec3 travel_vector = closest_intersection_distance * line.direction;
  const glm::dvec3 intersection_point = line.origin + travel_vector;
  vezp::print_dvec3(intersection_point);
  return intersection_point;
}

}
}



#endif /* calculatePointsWhereLineIntersectsSphere_cpp */
