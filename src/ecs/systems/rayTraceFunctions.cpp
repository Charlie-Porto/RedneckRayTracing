#ifndef rayTraceFunctions_cpp
#define rayTraceFunctions_cpp

#include <cmath>
#include <vector>
#include <algorithm>
#include <glm/vec2.hpp>
#include <ezprint.cpp>
#include <vector3_functions.cpp>
#include <sign.cpp>

#include "funks/checkIfLineVectorFormIntersectsSphere.cpp"
#include "../../constants/static_variables.cpp"

extern ControlPanel control;

namespace pce {
namespace raytrace {

// bool checkIfWireHitsSphereBody(const pce::math_objs::LineVectorForm& line, 
                              //  const glm::dvec3& sphere_center,
                              //  const double sphere_radius) {
  // return pce::math::checkIfLineVectorFormIntersectsSphere(line, sphere_center, sphere_radius);
// }


pce::math_objs::LineVectorForm calculateCameraPixelWire(const double& camera_scalar,
                                                        const glm::dvec2& pixel) {
  const double pixel_x = pixel.x * global_const::screen_zoom_ratio / global_const::pixel_stretch_ratio;
  const double pixel_y = pixel.y * global_const::screen_zoom_ratio / global_const::pixel_stretch_ratio;
  // const double pixel_z = camera_scalar - global_const::distance_camera_to_viewplane;
  const double pixel_z = camera_scalar - 100.0;
  auto const pixel_vec3 = glm::dvec3(pixel_x, pixel_y, pixel_z);
  ezp::print_item("point of intersection per raytrace");
  vezp::print_dvec3(pixel_vec3);
  auto const camera_rotated_location = glm::dvec3(0.0, 0.0, camera_scalar);
  // ezp::print_item("camera location per raytrace");
  // vezp::print_dvec3(camera_rotated_location);
  return vfunc::getVector3ThroughVector3s(camera_rotated_location, pixel_vec3);
}


void crawlTraceAtPixel(const glm::dvec2& pixel,
                       const double& camera_scalar,
                       const uint32_t& radar_entity,
                       std::vector<glm::dvec2>& pixel_trace_log) {

  // verify that pixel has not yet been traced to avoid rework 
  if (pixel_trace_log.size() == 0) {
    auto const& location = control.GetComponent<RotatedLocation>(radar_entity);
    auto const& body = control.GetComponent<SphereBody>(radar_entity);
    
    const pce::math_objs::LineVectorForm wire = calculateCameraPixelWire(camera_scalar, pixel);
    // ezp::print_item("wire vector form per raytrace: (direction, origin)");
    // ezp::print_labeled_item("rotated position: ", );
    // vezp::print_dvec3(wire.direction);
    // vezp::print_dvec3(wire.origin);
    
    // ezp::print_item("tracing first pixel: ");
    // vezp::print_dvec2(pixel);
    // ezp::print_item("object location: ");
    // vezp::print_dvec3(location.rotated_position);
    bool if_hit = pce::math::checkIfLineVectorFormIntersectsSphere(wire, location.rotated_position, body.radius); 
    ezp::print_labeled_item("if hit: ", if_hit);
    /* Perform actual ray tracing here */
    // ezp::print_item("tracing pixel");
    // ezp::print_labeled_item("x: ", pixel.x);
    // ezp::print_labeled_item("y: ", pixel.y);

    pixel_trace_log.push_back(pixel);
    std::vector<int> signs = {0, 1, -1};
    for (int i = 0; i < 3; ++i) {
      for (int j = 2; j > -1; --j) {
        const int new_pixel_x = pixel.x + signs[i];
        const int new_pixel_y = pixel.y + signs[j];
        auto const new_pixel = glm::vec2(new_pixel_x, new_pixel_y);
        // ezp::print_item("recursively tracing an additional pixel:");
        // ezp::print_labeled_item("new x: ", new_pixel.x);
        // ezp::print_labeled_item("new y: ", new_pixel.y);
        crawlTraceAtPixel(new_pixel, camera_scalar, radar_entity, pixel_trace_log);
      }
    }
  } else {
    if (std::count(pixel_trace_log.begin(), pixel_trace_log.end(), pixel) == 0) {
      // must grab entity body center point and radius
      auto const& location = control.GetComponent<RotatedLocation>(radar_entity);
      auto const& body = control.GetComponent<SphereBody>(radar_entity);

      // ezp::print_item("pixel not in log -- checking if hit");
      const pce::math_objs::LineVectorForm wire = calculateCameraPixelWire(camera_scalar, pixel);
      // vezp::print_dvec3(wire.direction);
      // vezp::print_dvec3(wire.origin);
      
      if (pce::math::checkIfLineVectorFormIntersectsSphere(wire, location.rotated_position, body.radius)) {

        pixel_trace_log.push_back(pixel);
        /* trace neighboring pixels here (recursively) */
        std::vector<double> signs = {0.0, 1.0, -1.0};
        for (int i = 0; i < 3; ++i) {
          for (int j = 2; j > -1; --j) {
            const int new_pixel_x = pixel.x + signs[i];
            const int new_pixel_y = pixel.y + signs[j];
            auto const new_pixel = glm::dvec2(new_pixel_x, new_pixel_y);
            // ezp::print_item("recursively tracing an additional pixel:");
            // ezp::print_labeled_item("new x: ", new_pixel.x);
            // ezp::print_labeled_item("new y: ", new_pixel.y);
            if (std::count(pixel_trace_log.begin(), pixel_trace_log.end(), glm::dvec2(new_pixel_x, new_pixel_y)) == 0) {
              crawlTraceAtPixel(new_pixel, camera_scalar, radar_entity, pixel_trace_log);
            }
          }
        }
      }
    }
  }
}


}
}


#endif /* rayTraceFunctions_cpp */
