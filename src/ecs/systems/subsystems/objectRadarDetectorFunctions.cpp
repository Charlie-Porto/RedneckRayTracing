#ifndef objectRadarDetectorFunctions_cpp
#define objectRadarDetectorFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the Object Radar Detection Subsystem
-----------------------------------------------------------------*/
#include <cmath>

#include <glm/vec3.hpp>

#include <ezprint.cpp>
#include <quaternion_funktions.cpp>
#include <vector3_functions.cpp>
#include <math_objects/Plane.cpp>
#include <math_objects/LineParamEq.cpp>


namespace pce {
namespace radar {

template <typename T> T sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

glm::dvec3 rotateObjectCenterPoint(const glm::dvec3& point, const glm::dquat& cam_rotation_versor) {
  /* need to "normalize" object center point via rotation by inverse of camera rotation versor */
  return qfunc::rotateVector3byQuaternion(point, cam_rotation_versor);
}


pce::math_objs::LineParametricEquation calculateObjectWire(const glm::dvec3& object_rotated_pos,
                                                           const glm::dvec3& camera_pos) {
  return vfunc::getLineThrough3dVectors(object_rotated_pos, camera_pos);
}


glm::dvec3 calculatePointWireIntersectsViewPlane(pce::math_objs::LineParametricEquation wire,
                                                 pce::math_objs::Plane viewplane) {
  return vfunc::getPointAtWhichLineIntersectsPlane(wire, viewplane);
}


bool checkIfObjectIsInFrontOfCamera(const glm::dvec3& obj_pos, const glm::dvec3& camera_pos,
                                    const double camera_pov_scalar) {
  const double distance_obj_to_POV = vfunc::calculateDistanceBetweenPosition3Vectors(camera_pos,
                                                                                     obj_pos);
  const double distance_obj_to_origin = vfunc::calculateMagnitude(obj_pos);

  if (distance_obj_to_origin < distance_obj_to_POV) {
    return true;
  } else {
    if (distance_obj_to_origin < camera_pov_scalar) {
      return true;
    }
  }
  return false;
}

glm::dvec2 calculateObjectLocationOnRadar(const glm::dvec3& rotated_pos, 
                                          const bool& if_in_front_of_camera,
                                          double camera_pos_scalar) {
     
  const auto camera_pos = glm::dvec3(0.0, 0.0, 1.0) * camera_pos_scalar;
  pce::math_objs::LineParametricEquation object_wire = vfunc::getLineThrough3dVectors(
                                                           camera_pos, rotated_pos);
  auto view_plane = pce::math_objs::Plane{.x=0.0, .y=0.0, .z=1.0, .c=0.0};
  view_plane.z = (abs(camera_pos_scalar)-1.0) * pce::radar::sgn<double>(camera_pos_scalar);
  glm::dvec3 point_wire_intersects_viewplane = vfunc::getPointAtWhichLineIntersectsPlane(
                                                   object_wire, view_plane);
  if (if_in_front_of_camera == true) {
    auto const radar_location = glm::dvec2(point_wire_intersects_viewplane.x * 2.0,
                                           point_wire_intersects_viewplane.y * 2.0);
    return radar_location;
  }
  return glm::dvec2(0, 0);
}


}
}

#endif /* objectRadarDetectorFunctions_cpp */
