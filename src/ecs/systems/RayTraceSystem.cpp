#ifndef RayTraceSystem_cpp
#define RayTraceSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
System for performing raytracing.
-----------------------------------------------------------------*/
#include <vector>
#include <unordered_map>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>

#include "../System.cpp"
#include "rayTraceFunctions.cpp"
#include "subsystems/simpleDrawingFunctions.cpp"
#include "subsystems/spacePixelConversionFunctions.cpp"

extern ControlPanel control;

namespace pce {
class RayTraceSystem : public ISystem {
public:
  RayTraceSystem() { ezp::print_item("creating RayTraceSystem"); }


  void PerformInitialEntitySift() {
    for (auto const& entity : entities) {
      auto const& surface = control.GetComponent<pce::Surface>(entity);
      auto const& rotated_location = control.GetComponent<pce::RotatedLocation>(entity);
      if (surface.superimposed) {
        superimposed_entities_.insert(entity);
      } else if (surface.luminosity > 0.0) {
        luminous_entities_[entity] = rotated_location.rotated_position;
      } else {
        non_luminous_entities_.insert(entity);
      }
    }
  }

  
  void TraceSuperimposedEntities(const double camera_pos_scalar) {
    for (auto const& entity : superimposed_entities_) {
      auto const& rotated_location = control.GetComponent<pce::RotatedLocation>(entity);
      auto const& radar = control.GetComponent<pce::Radar>(entity);
      auto const& surface = control.GetComponent<pce::Surface>(entity);
      glm::dvec3 intersection = pce::raytrace::tracePixel(radar, rotated_location.rotated_position,
                                1.0, camera_pos_scalar);
      glm::dvec2 pixel = pce::pix_map::convertPointOnViewSphereToPixel(intersection, glm::dvec3(0, 0, camera_pos_scalar));
      pce::quickdraw::drawPixelAtVec2(pixel, surface.natural_color); 
    }
  }


  void TraceObjectCenters(const double camera_pos_scalar) {
    for (auto const& entity : non_luminous_entities_) {
      // ezp::print_item("starting trace on entity");
      auto const& sphere_body = control.GetComponent<pce::SphereBody>(entity);
      auto const& rotated_location = control.GetComponent<pce::RotatedLocation>(entity);
      auto const& radar = control.GetComponent<pce::Radar>(entity);
      auto const& surface = control.GetComponent<pce::Surface>(entity);
      glm::dvec3 intersection = pce::raytrace::tracePixel(radar, rotated_location.rotated_position,
                                sphere_body.radius, camera_pos_scalar);
      // ezp::print_labeled_item("if draw: ", if_draw);
      // ezp::print_labeled_item("trace log size: ", trace_log.size());
      // vezp::print_dvec3(intersection);
      glm::dvec2 pixel = pce::pix_map::convertPointOnViewSphereToPixel(intersection, glm::dvec3(0, 0, camera_pos_scalar));
      // pce::quickdraw::drawPixelAtVec2(radar.hitpoint_corresponding_pixel); 
      // pce::quickdraw::drawPixelAtVec2(pixel); 
      pce::quickdraw::drawSmallCircleAtVec2(pixel, surface.natural_color); 
    }
  }


  void UpdateRayTrace(const double camera_pos_scalar) {
    for (auto const& entity : non_luminous_entities_) {
      // ezp::print_item("starting trace on entity");
      auto const& sphere_body = control.GetComponent<pce::SphereBody>(entity);
      auto const& rotated_location = control.GetComponent<pce::RotatedLocation>(entity);
      auto const& radar = control.GetComponent<pce::Radar>(entity);
      std::vector<glm::dvec2> trace_log = {};
      pce::raytrace::smarterCrawlTraceAtPixel(radar, rotated_location.rotated_position,
                                       sphere_body.radius, camera_pos_scalar, trace_log);
            
      ezp::print_labeled_item("*******Trace Log Count *********   ", trace_log.size());
      // ezp::print_item("*******Trace Log*********");
      // for (int i = 0; i < trace_log.size(); ++i) {
        // ezp::print_item("-------");
        // vezp::print_dvec2(trace_log[i]);
      // }
      pce::quickdraw::drawListOfPixels(trace_log); 
      // ezp::print_labeled_item("trace log size: ", trace_log.size());
      // pce::quickdraw::drawPixelAtVec2(trace_log[0]); 
    }
  }

private:
  std::unordered_map<Entity, glm::dvec3> luminous_entities_;
  std::set<Entity> non_luminous_entities_;
  std::set<Entity> superimposed_entities_;
  

};
}
#endif /* RayTraceSystem_cpp */
