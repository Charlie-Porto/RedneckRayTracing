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
#include "subsystems/CameraOperatorSubsystem.cpp"
#include "subsystems/ObjectRadarDetectorSubsystem.cpp"
#include "rayTraceFunctions.cpp"
#include "subsystems/simpleDrawingFunctions.cpp"

extern ControlPanel control;
const int TOTAL_PIXELS = global_const::screen_x * global_const::screen_y;

namespace pce {
class RayTraceSystem : public ISystem {
public:
  RayTraceSystem() { ezp::print_item("creating RayTraceSystem"); }
  void Init() {
    camera_operator_.Init();
  }


  void SetupRayTrace() {
    camera_operator_.UpdateCamera(); 
    radar_detector_.UpdateRadar(entities, camera_operator_.camera_);
    // radar_detector_.PrintRadarMapContents();
  }
  


  void RayTrace() {
    // std::unordered_map<uint32_t, glm::vec2> master_pixel_trace_log;
    for (auto const& [key, value] : radar_detector_.radar_map_) {
      pce::quickdraw::drawCircleAtVec2(value); // temporary -- useful for testing

      // perform crawl tracing for this pixel
      std::vector<glm::dvec2> current_pixel_trace_log;
      pce::raytrace::crawlTraceAtPixel(value, camera_operator_.camera_.pov_scalar,
                                       key, current_pixel_trace_log);
      
      for (auto const& pixel : current_pixel_trace_log) {
        pce::quickdraw::drawPixelAtVec2(pixel);
      }
    }


  }

private:
  CameraOperatorSubsystem camera_operator_;
  ObjectRadarDetectorSubsystem radar_detector_;
  // TracerSubsystem tracer_;

};
}
#endif /* RayTraceSystem_cpp */
