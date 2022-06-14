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

extern ControlPanel control;

namespace pce {
class RayTraceSystem : public ISystem {
public:
  RayTraceSystem() { ezp::print_item("creating RayTraceSystem"); }

  void UpdateRayTrace(const double camera_pos_scalar) {
    // ezp::print_item("updating RayTraceSystem");
    for (auto const& entity : entities) {
      ezp::print_item("starting trace on entity");
      auto const& sphere_body = control.GetComponent<pce::SphereBody>(entity);
      auto const& rotated_location = control.GetComponent<pce::RotatedLocation>(entity);
      auto const& radar = control.GetComponent<pce::Radar>(entity);
      std::vector<glm::dvec2> trace_log = {};
      pce::raytrace::crawlTraceAtPixel(radar, rotated_location.rotated_position,
                                       sphere_body.radius, camera_pos_scalar, trace_log);
            
      for (int i = 0; i < trace_log.size(); ++i) {
        ezp::print_item("-------");
        vezp::print_dvec2(trace_log[i]);
      }
      pce::quickdraw::drawListOfPixels(trace_log); 
    }
  }

};
}
#endif /* RayTraceSystem_cpp */
