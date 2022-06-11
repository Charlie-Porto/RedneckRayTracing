#ifndef simpleDrawingFunctions_cpp
#define simpleDrawingFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
simple drawing functions to assist the ray trace system
-----------------------------------------------------------------*/
#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <drawing_functions.cpp>
#include "../../../SDL_core/simulation_manager.cpp"
#include "../../../constants/static_variables.cpp"

namespace pce {
namespace quickdraw {

glm::vec2 ConvertCartesianCoordinatesToSDL(glm::vec2 point) {
  const int sdl_x = point.x + int(global_const::screen_x/2);
  const int sdl_y = -point.y + int(global_const::screen_y/2);
  return glm::vec2(sdl_x, sdl_y);
}

const std::vector<int> rcolor = {250, 10, 100, 255};
void drawPixelAtVec2(glm::vec2 pixel) {
  const glm::vec2 sdl_transform = ConvertCartesianCoordinatesToSDL(pixel);
  // ezp::print_item("drawing pixel at Vec2");
  // vezp::print_dvec2(pixel);
  drawPixelVec2(sdl_transform, rcolor, Simulation::renderer);
}

const std::vector<int> mcolor = {5, 140, 15, 255};
void drawCircleAtVec2(glm::vec2 point) {
  const glm::vec2 sdl_transform = ConvertCartesianCoordinatesToSDL(point);
  drawCircle(sdl_transform.x, sdl_transform.y, 15, mcolor, Simulation::renderer);
}

}
}

#endif /* simpleDrawingFunctions_cpp */
