#ifndef radar_component_cpp
#define radar_component_cpp

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace pce {

struct Radar {
  glm::dvec3 view_sphere_hitpoint;
  glm::dvec2 hitpoint_corresponding_pixel; // expensive calculation. determine where/how to make
};

}

#endif /* radar_component_cpp */
