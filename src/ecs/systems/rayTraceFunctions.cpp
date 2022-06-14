#ifndef rayTraceFunctions_cpp
#define rayTraceFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to assist the RayTraceSystem
-----------------------------------------------------------------*/

#include <cmath>
#include <vector>
#include <algorithm>

#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <vector3_functions.cpp>
#include <sign.cpp>

#include "../../constants/static_variables.cpp"
#include "subsystems/spacePixelConversionFunctions.cpp"
#include "subsystems/pixelSpaceMappingFunctions.cpp"
#include "funks/checkIfLineVectorFormIntersectsSphere.cpp"


namespace pce {
namespace raytrace {

bool tracePixel(const pce::Radar radar,
                       const glm::dvec3& rotated_position,
                       double radius,
                       const double camera_pos_scalar,
                       std::vector<glm::dvec2>& pixel_trace_log) {

  const pce::math_objs::LineVectorForm wire = vfunc::getVector3ThroughVector3s(
                                                 radar.view_sphere_hitpoint,
                                                 glm::dvec3(0, 0, camera_pos_scalar));
  if (pce::math::checkIfLineVectorFormIntersectsSphere(wire, rotated_position, radius)) {
    return true;
  }
  return false;
}


void crawlTraceAtPixel(const pce::Radar radar,
                       const glm::dvec3& rotated_position,
                       double radius,
                       const double camera_pos_scalar,
                       std::vector<glm::dvec2>& pixel_trace_log) {

  // verify that pixel has not yet been traced to avoid rework 
  // ezp::print_item("performing crawl at ray trace");
  if (std::count(pixel_trace_log.begin(), pixel_trace_log.end(), radar.hitpoint_corresponding_pixel) == 0) {
    ezp::print_item("confirmed: pixel not yet in log");
    // calculate the wire
    const pce::math_objs::LineVectorForm wire = vfunc::getVector3ThroughVector3s(
                                                  radar.view_sphere_hitpoint,
                                                  glm::dvec3(0, 0, camera_pos_scalar));

    if (pce::math::checkIfLineVectorFormIntersectsSphere(wire, rotated_position, radius)) {
      pixel_trace_log.push_back(radar.hitpoint_corresponding_pixel);
      ezp::print_item("tracing pixel: ");
      vezp::print_dvec2(radar.hitpoint_corresponding_pixel);
      
      std::vector<double> signs = {0.0, 1.0, -1.0};
      for (int i = 0; i < 3; ++i) {
        for (int j = 2; j > -1; --j) {
          const double new_pixel_x = radar.hitpoint_corresponding_pixel.x + signs[i];
          const double new_pixel_y = radar.hitpoint_corresponding_pixel.y + signs[j];
          auto const new_pixel = glm::dvec2(new_pixel_x, new_pixel_y);

          if (std::count(pixel_trace_log.begin(), pixel_trace_log.end(), new_pixel) == 0
              && abs(new_pixel.x) < global_const::screen_x/5.0
              && abs(new_pixel.y) < global_const::screen_y/5.0) {
            // glm::dvec3 new_hitpoint = pce::pix_map::calculateHorizontalNeighborPixelVec3(
            //                             radar.view_sphere_hitpoint, signs[i]);
            // new_hitpoint = pce::pix_map::calculateVerticalNeighborPixelVec3(
            //                             radar.view_sphere_hitpoint, signs[j]);
            // auto new_radar = pce::Radar{
            //   .view_sphere_hitpoint = new_hitpoint,
            //   .hitpoint_corresponding_pixel = new_pixel
            // };
            ezp::print_item("crawl tracing pixel");
            vezp::print_dvec2(new_pixel);
            // crawlTraceAtPixel(new_radar, rotated_position, radius, camera_pos_scalar, pixel_trace_log);
          }
        }
      }
    }
  }
}

}
}


#endif /* rayTraceFunctions_cpp */
