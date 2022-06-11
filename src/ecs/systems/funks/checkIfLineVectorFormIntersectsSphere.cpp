#ifndef if_LineVectorForm_intersects_Sphere_cpp
#define if_LineVectorForm_intersects_Sphere_cpp


#include <cmath>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <ezprint.cpp>
#include <math_objects/LineVectorForm.cpp>

namespace pce {
namespace math {


bool checkIfLineVectorFormIntersectsSphere(const pce::math_objs::LineVectorForm& line, 
                                           const glm::dvec3& sphere_center,
                                           const double sphere_radius) {
  // solve for line's d value by plugging line into circle equation
  // ad^2 + bd + c = 0  ===> use the quadratic equation
  // note: direction of line DOES NOT MATTER in calculation;
  //       still need to calculate whether point of contact is
  //       behind or in front of the POV 
  glm::dvec3 o_less_c = line.origin - sphere_center;
  double a = dot(line.direction, line.direction);
  double b = 2.0 * dot(line.direction, (o_less_c));
  double c = dot(o_less_c, o_less_c) - pow(sphere_radius, 2.0);

  double discriminant = pow(b, 2.0) - 4 * a * c;
  // ezp::print_labeled_item("quad eq discriminant: ", discriminant);

  if (discriminant > 0) {
    return true;
  } else {
    return false;
  }
}

}
}

#endif /* if_LineVectorForm_intersets_Sphere_cpp */
