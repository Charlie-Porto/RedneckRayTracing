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
#include <rasterization_functions.cpp>
#include <sign.cpp>

#include "../../constants/static_variables.cpp"
#include "subsystems/spacePixelConversionFunctions.cpp"
#include "subsystems/pixelSpaceMappingFunctions.cpp"
#include "funks/checkIfLineVectorFormIntersectsSphere.cpp"
#include "funks/calculateClosestPointLineIntersectsSphere.cpp"


namespace pce {
namespace raytrace {

glm::dvec3 tracePixel(const pce::Radar radar,
                const glm::dvec3& rotated_position,
                double radius,
                const double camera_pos_scalar) {
  const pce::math_objs::LineVectorForm wire = vfunc::getVector3ThroughVector3s(
                                                 glm::dvec3(0, 0, camera_pos_scalar),
                                                 radar.view_sphere_hitpoint);
  // ezp::print_item("trace wire origin: ");
  // vezp::print_dvec3(wire.origin);
  // ezp::print_item("trace wire direction: ");
  // vezp::print_dvec3(wire.direction);
  // ezp::print_item("object rotated position: ");
  // vezp::print_dvec3(rotated_position);

  if (pce::math::checkIfLineVectorFormIntersectsSphere(wire, rotated_position, radius)) {
    // ezp::print_labeled_item("pixel trace log size: ", pixel_trace_log.size());
    return pce::math::calculateClosestPointLineIntersectsSphere(wire, rotated_position, radius);
  } return glm::dvec3(1000, 1000, 1000);
}


glm::dvec3 getObjectWireIntersection(const pce::math_objs::LineVectorForm& wire,
                               const glm::dvec3& sphere_center, const double radius) {
  return pce::math::calculateClosestPointLineIntersectsSphere(wire, sphere_center, radius);
}


void smarterCrawlTraceAtPixel(const pce::Radar radar,
                              const glm::dvec3& rotated_position,
                              double radius,
                              const double camera_pos_scalar,
                              std::vector<glm::dvec2>& pixel_trace_log) {
  const glm::dvec3 original_hit = tracePixel(radar, rotated_position, radius, camera_pos_scalar);
  if (original_hit != glm::dvec3(1000, 1000, 1000)) {
    // glm::dvec2 recalculated_pixel = pce::pix_map::convertPointOnViewSphereToPixel(original_hit, glm::dvec3(0, 0, camera_pos_scalar));
    pixel_trace_log.push_back(radar.hitpoint_corresponding_pixel);
    const std::vector<glm::dvec2> crawl_pixels = {
      glm::dvec2(0, 1),
      glm::dvec2(0, -1),
      glm::dvec2(1, 0),
      glm::dvec2(-1, 0)
    };
    
    for (auto const& crawl_pixel : crawl_pixels) {
      glm::dvec2 prev_pixel = radar.hitpoint_corresponding_pixel;
      std::vector<glm::dvec2> hit_pixels;
      // perform crawl along straight line
      while (true) {
        glm::dvec2 current_pixel = prev_pixel + crawl_pixel;
        prev_pixel = current_pixel;
        glm::dvec3 new_hitpoint = pce::pix_map::convertPixelToPointOnViewSphere(current_pixel, glm::dvec3(0, 0, camera_pos_scalar));
        auto new_radar = pce::Radar{
          .view_sphere_hitpoint = new_hitpoint,
          .hitpoint_corresponding_pixel = current_pixel
        };
        const glm::dvec3 new_hit = tracePixel(new_radar, rotated_position, radius, camera_pos_scalar);
        if (new_hit != glm::dvec3(1000, 1000, 1000)) {
          hit_pixels.push_back(current_pixel);
        } else {
          break;
        }
      }
      glm::dvec2 orthogonal_crawl_pixel = glm::dvec2(crawl_pixel.y, -crawl_pixel.x);
      for (auto const& hit_pixel : hit_pixels) {
        std::vector<glm::dvec2> sub_hit_pixels;
        glm::dvec2 sub_prev_pixel = hit_pixel;
        // int i = 1;
        // while (i < 3) {
        //   glm::dvec2 current_pixel = sub_prev_pixel + orthogonal_crawl_pixel;
        //   sub_prev_pixel = current_pixel;
        //   glm::dvec3 new_hitpoint = pce::pix_map::convertPixelToPointOnViewSphere(current_pixel, glm::dvec3(0, 0, camera_pos_scalar));
        //   auto new_radar = pce::Radar{
        //     .view_sphere_hitpoint = new_hitpoint,
        //     .hitpoint_corresponding_pixel = current_pixel
        //   };
        //   const glm::dvec3 new_hit = tracePixel(new_radar, rotated_position, radius, camera_pos_scalar);
        //   if (new_hit != glm::dvec3(1000, 1000, 1000)) {
        //     // sub_hit_pixels.push_back(current_pixel);
        //     hit_pixels.push_back(current_pixel);
        //   } else {
        //     break;
        //     // hit_pixels.insert(hit_pixels.end(), sub_hit_pixels.begin(), sub_hit_pixels.end());
        //   }
        //   ++i;
        // }
      }
      pixel_trace_log.insert(pixel_trace_log.end(), hit_pixels.begin(), hit_pixels.end());
    }

  }
}
// warning: this function is very slow
void smartCrawlTraceAtPixel(const pce::Radar radar,
                            const glm::dvec3& rotated_position,
                            double radius,
                            const double camera_pos_scalar,
                            std::vector<glm::dvec2>& pixel_trace_log) {

  // pixel_trace_log.push_back(radar.hitpoint_corresponding_pixel);
  const glm::dvec3 original_hit = tracePixel(radar, rotated_position, radius, camera_pos_scalar);
  if (original_hit != glm::dvec3(1000, 1000, 1000)) {
    glm::dvec2 recalculated_pixel = pce::pix_map::convertPointOnViewSphereToPixel(original_hit, glm::dvec3(0, 0, camera_pos_scalar));
    pixel_trace_log.push_back(recalculated_pixel);

    // the limit on this while loop is just for security;
    // do not want to find an error by having this loop run forever.
    int i_radius = 0;
    while (i_radius <= radius) {
      std::vector<std::vector<int>> circle_rasterization_points = pce::raster::getCircleRasterizationPoints(
                                                        int(radar.hitpoint_corresponding_pixel.x),
                                                        int(radar.hitpoint_corresponding_pixel.y),
                                                        i_radius);
      bool if_hit = false;
      // ezp::print_labeled_item("circle rasterization loop within while loop, radius: ", i_radius);
      for (auto const& pixel : circle_rasterization_points) {
        glm::dvec2 new_pixel = glm::dvec2(pixel[0], pixel[1]);
        glm::dvec3 new_hitpoint = pce::pix_map::convertPixelToPointOnViewSphere(new_pixel, glm::dvec3(0, 0, camera_pos_scalar));
        auto new_radar = pce::Radar{
          .view_sphere_hitpoint = new_hitpoint,
          .hitpoint_corresponding_pixel = new_pixel
        };
        const glm::dvec3 hitpoint = tracePixel(new_radar, rotated_position, radius, camera_pos_scalar);
        if (hitpoint != glm::dvec3(1000, 1000, 1000)) {
          // ezp::print_item("HIT ON PIXEL: ");
          // vezp::print_dvec2(new_pixel);
          pixel_trace_log.push_back(new_pixel);
          if_hit = true;
        }
      }
      if (if_hit == false) {i_radius += 1000; }
      else {++i_radius; }
    }
  }
}

}
}


#endif /* rayTraceFunctions_cpp */
