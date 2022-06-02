#ifndef rayTraceSystemFunctions_cpp
#define rayTraceSystemFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to assist the ray trace system.
-----------------------------------------------------------------*/

#include <utility>
#include <vector>
#include <unordered_map>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <ezprint.cpp>

#include "../../tools/math_objects/Plane.cpp"
#include "../../tools/math_objects/LineParamEq.cpp"
#include "../../tools/math_functions/vector_functions.cpp"



namespace pce {
namespace trace {


pce::math_objs::LineVectorForm calculateTraceWire(const glm::dvec3& pixel_center,
                                                  const glm::dvec3& camera_pos) {
  return vfunc::getVector3ThroughVector3s(pixel_center, camera_pos);
}



bool checkIfObjectIsInFrontOfPOV(const glm::dvec3& obj_pos, const glm::dvec3& camera_pos,
                                                            const double camera_pos_scalar) {
  const double distance_obj_to_POV = vfunc::calculateDistanceBetweenPosition3Vectors(camera_pos, obj_pos);
  const double distance_obj_to_origin = vfunc::calculateMagnitude(obj_pos);

  if (distance_obj_to_origin < distance_obj_to_POV) {
    return true;
  } else {
    if (distance_obj_to_origin < camera_pos_scalar) {
      return true;
    }
  }
  return false;
}

bool checkIfTraceWireIntersectsSphere(const pce::math_objs::LineVectorForm& wire, 
                                      const glm::dvec3& sphere_center,
                                      const double sphere_radius) {
  
  return false;
}


}
}



#endif /* rayTraceSystemFunctions_cpp */
