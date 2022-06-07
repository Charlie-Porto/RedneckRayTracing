#ifndef simpleDrawingFunctions_cpp
#define simpleDrawingFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
simple drawing functions to assist the ray trace system
-----------------------------------------------------------------*/
#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <drawing_functions.cpp>
#include "../../../SDL_core/simulation_manager.cpp"
#include "../../../constants/static_variables.cpp"

namespace pce {
namespace quickdraw{

glm::vec2 ConvertCartesianCoordinatesToSDL(glm::dvec2 point) {
  glm::vec2 int_point = point;
  const int sdl_x = int_point.x + int(global_const::screen_x/2);
  const int sdl_y = -int_point.y + int(global_const::screen_y/2);
  return glm::vec2(sdl_x, sdl_y);
}


const std::vector<int> mcolor = {5, 140, 15, 255};

void drawCircleAtVec2(glm::dvec2 point) {
  const glm::vec2 sdl_transform = ConvertCartesianCoordinatesToSDL(point);
  drawCircle(sdl_transform.x, sdl_transform.y, 2, mcolor, Simulation::renderer);
}

}
}

#endif /* simpleDrawingFunctions_cpp */
