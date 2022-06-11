#ifndef ObjectRadarDetectorSubsystem_cpp
#define ObjectRadarDetectorSubsystem_cpp

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

Inputs:
 * std::vector<glm::dvec3> array of all object centers
 * glm::dvec3 camera's rotation versor (for reverse-rotating objects)
 * double camera position scalar 
 
Const inputs:
 * double global::screen zoom 
 * double distance from camera to viewplane (traditionally just 1)
-----------------------------------------------------------------*/
#include <vector>
#include <set>
#include <unordered_map>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <ezprint.cpp>

#include "objectRadarDetectorFunctions.cpp"

extern ControlPanel control;

namespace pce {
class ObjectRadarDetectorSubsystem {
public:
  ObjectRadarDetectorSubsystem() { ezp::print_item("creating ObjectRadarDetectionSubsystem"); }

  void PrintRadarMapContents() {
    ezp::print_item("PRINTING ALL OBJECT RADAR LOCATIONS");
    for (auto const& [key, value] : radar_map_) {
      ezp::print_labeled_item("object radar x:", value.x);
      ezp::print_labeled_item("object radar y:", value.y);
    }
  }

  void UpdateRadar(const std::set<uint32_t>& entities, const Camera& camera) {
    // ezp::print_item("RadarSystem: updating radar");
    radar_map_.clear();
    for (auto const& entity : entities) {
      auto const& location = control.GetComponent<pce::Location>(entity);
      auto& rotated_location = control.GetComponent<pce::RotatedLocation>(entity);
      const bool if_object_in_radar_view = pce::radar::checkIfObjectIsInFrontOfCamera(
                                               location.position,
                                               camera.location_vec3,
                                               camera.pov_scalar);
      if (if_object_in_radar_view == true) {
        rotated_location.rotated_position = pce::radar::rotateObjectCenterPoint(location.position,
                                                                                camera.rotation_versor);
        const glm::dvec2 radar = pce::radar::calculateObjectLocationOnRadar(
                                              rotated_location.rotated_position,
                                              if_object_in_radar_view,
                                              camera.pov_scalar);
        radar_map_[entity] = radar;
      }
    }
  }        
     
  std::unordered_map<uint32_t, glm::dvec2> radar_map_; // public so easily pass-able to Tracer Subsystem
 
};
}


#endif /* ObjectRadarDetectorSubsystem_cpp */
