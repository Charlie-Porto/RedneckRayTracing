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
const int TOTAL_PIXELS = global_const::screen_x * global_const::screen_y;

namespace pce {
class RayTraceSystem : public ISystem {
public:
  RayTraceSystem() { ezp::print_item("creating RayTraceSystem"); }

  void RayTrace(const double camera_pos_scalar) {
    // std::unordered_map<uint32_t, glm::vec2> master_pixel_trace_log;

      // perform crawl tracing for this pixel
      // std::vector<glm::dvec2> current_pixel_trace_log;
      // pce::raytrace::crawlTraceAtPixel(value, camera_operator_.camera_.pov_scalar,
                                      //  key, current_pixel_trace_log);
      
      // for (auto const& pixel : current_pixel_trace_log) {
        // pce::quickdraw::drawPixelAtVec2(pixel);
      // }
    }

};
}
#endif /* RayTraceSystem_cpp */
