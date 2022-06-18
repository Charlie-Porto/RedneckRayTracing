#ifndef traceLightFunctions_cpp
#define traceLightFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions specifically for determining the color of a pixel based
on (i) light conditions and (ii) object surface characteristics
-----------------------------------------------------------------*/

#include <glm/vec3.hpp>
#include <math_objects/LineVectorForm.cpp>
#include <vector3_functions.cpp>
#include <ezprint.cpp>

namespace pce {
namespace raytrace {

pce::math_objs::LineVectorForm getHitPointNormalVector(const glm::dvec3& hitpoint,
                                                       const glm::dvec3& object_center) {
  pce::math_objs::LineVectorForm normal_vector = vfunc::getVector3ThroughVector3s(hitpoint,
                                                                                  object_center);
  normal_vector.origin = hitpoint;                                                                                  
  return normal_vector;
}


pce::math_objs::LineVectorForm getLightWire(const glm::dvec3& hitpoint,
                                            const glm::dvec3& light_source_location) {
  return vfunc::getVector3ThroughVector3s(light_source_location, hitpoint);
}




}
}




#endif /* traceLightFunctions_cpp */
