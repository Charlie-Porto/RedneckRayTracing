#ifndef raytrace_system_cpp
#define raytrace_system_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
class for performing ray tracing
-----------------------------------------------------------------*/
#include <utility>
#include <vector>
#include <unordered_map>

#include <glm/vec3.hpp>
#include <ezprint.cpp>
#include <virtual_keyboard.cpp>

#include "rayTraceSystemFunctions.cpp"
#include "funks/checkIfPairInVector.cpp"
#include "../System.cpp"
#include "../../constants/static_variables.cpp"
#include "../../tools/math_objects/LineVectorForm.cpp"

extern ControlPanel control;
const int TOTAL_PIXELS = global_const::screen_x * global_const::screen_y;

namespace pce {

class RayTraceSystem : public ISystem {
public:
  RayTraceSystem() { ezp::print_item("creating Ray Trace System"); }
  void Init() {
    ezp::print_item("initializing Ray Trace System");
    camera_position_ = glm::dvec3(0.0, 0.0, 10.0);
  }


  bool TracePixel(const std::pair<int, int>& pixel,
                  std::vector<std::pair<int, int>>& pixel_trace_log) {
    if (pce::vfunc::if_pair_in_vector<int, int>(pixel, pixel_trace_log)) {
      return false;
    }
      // ezp::print_item("tracing pixel");
      pixel_trace_log.push_back({pixel.first, pixel.second});
      auto const test_pixel_center = glm::dvec3(1.0, 1.0, 9.0);
      auto const test_sphere_center = glm::dvec3(0.0, 0.0, 0.0);
      const double test_r = 5.0;
      pce::math_objs::LineVectorForm wire = pce::trace::calculateTraceWire(test_pixel_center,
                                                                           camera_position_);
      bool if_hit = pce::trace::checkIfTraceWireIntersectsSphere(wire, test_sphere_center, test_r);
      return if_hit;
  }

  
  void TraceAllPixels() {
    // ezp::print_item("tracing all pixels");
    std::vector<std::pair<int, int>> pixel_trace_log{};
    auto this_pixel = std::pair<int, int>(2, 2);
    bool if_drawing_pixel = TracePixel(this_pixel, pixel_trace_log);
  }

private:
  glm::dvec3 camera_position_; 
  VirtualKeyboard keyboard_;
   
};
}
#endif /* raytrace_system_cpp */
