#ifndef ObjectRadarDetectorSystem_cpp
#define ObjectRadarDetectorSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
class for monitoring the general positions of on-screen objects
(purpose of this class is to reduce computation needed for raytracing
by obtaining a general idea of where on the screen tracing 
needs to happen in order to correctly render all objects, instead of 
tracing every pixel on the screen by way of brute-force.

returns a list of the points on the view plane which are intersection
points for the centers of all on-screen objects. ray tracing will begin
with these points and "crawl" outward.
-----------------------------------------------------------------*/
#include <vector>
#include <set>
#include <unordered_map>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "glm/ext/quaternion_double.hpp"

#include <ezprint.cpp>
#include <vezprint.cpp>

#include "../System.cpp"
#include "subsystems/spacePixelConversionFunctions.cpp"
#include "subsystems/simpleDrawingFunctions.cpp"
#include "objectRadarDetectorFunctions.cpp"

extern ControlPanel control;

namespace pce {
class ObjectRadarDetectorSystem : public ISystem {
public:
  ObjectRadarDetectorSystem() { ezp::print_item("creating ObjectRadarDetectionSubsystem"); }

  void UpdateRadar(const double camera_pos_scalar, const glm::dquat rotation_versor) {
    // ezp::print_item("updating Radar");
    for (auto const& entity : entities) {
      auto const& location = control.GetComponent<pce::Location>(entity);
      auto& rotated_location = control.GetComponent<pce::RotatedLocation>(entity);
      auto& radar = control.GetComponent<pce::Radar>(entity);

      rotated_location.rotated_position = pce::radar::rotateObjectCenterPoint(location.position,
                                                                              rotation_versor);
      const glm::dvec3 sphere_viewplane_hitpoint = pce::radar::calculateWhereWireIntersectsViewSphere(
                                                      rotated_location.rotated_position,
                                                      camera_pos_scalar);
      radar.view_sphere_hitpoint = sphere_viewplane_hitpoint;
      radar.hitpoint_corresponding_pixel = pce::pix_map::convertPointOnViewSphereToPixel(
                                               sphere_viewplane_hitpoint, glm::dvec3(0, 0, camera_pos_scalar));
      pce::quickdraw::drawCircleAtVec2(radar.hitpoint_corresponding_pixel);
    }
  }        
 
};
}


#endif /* ObjectRadarDetectorSystem_cpp */
