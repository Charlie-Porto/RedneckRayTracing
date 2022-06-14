#ifndef sphericalRadarFunctions_cpp
#define sphericalRadarFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
object radar detector subsystem, but for a spherical
viewplane instead of a flat viewplane like the original version 
of this module -- objectRadarDetectorFunctions.
-----------------------------------------------------------------*/

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <vector3_functions.cpp>
#include <ezprint.cpp>
#include <math_objects/LineVectorForm.cpp>

#include "../components/radar_component.cpp"

namespace pce {
namespace radar {

glm::dvec3 calculatePointAlongLineAtDistance(const pce::math_objs::LineVectorForm& line,
                                             const double& distance) {
  return glm::dvec3(line.direction * distance + line.origin);
}


glm::dvec3 calculateObjectRadarLocation(const glm::dvec3& object_center,
                                        const double& camera_position_scalar) {
  // calc wire
  pce::math_objs::LineVectorForm wire = vfunc::getVector3ThroughVector3s(
                                        glm::dvec3(0, 0, camera_position_scalar),
                                        object_center);
  const glm::dvec3 intersection_point = glm::dvec3(0, 0, camera_position_scalar) - wire.origin;
  return intersection_point;
  
}


}
}




#endif /* sphericalRadarFunctions_cpp */
