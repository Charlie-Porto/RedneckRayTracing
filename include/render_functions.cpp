#ifndef render_functions_cpp
#define render_functions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to assist with SDL rendering.
Requirements: an SDL_Renderer must be active.
-----------------------------------------------------------------*/

#include <vector>
#include <glm/vec2.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <ezprint.cpp>

namespace pce {
namespace render {

void renderVec2PixelList(const std::vector<glm::dvec2>& pixels,
                         const std::vector<int>& color,
                         SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
  for (int i = 0; i < pixels.size(); i++) {
    SDL_RenderDrawPoint(renderer, pixels[i].x, pixels[i].y);
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

}
}


#endif /* render_functions_cpp */
