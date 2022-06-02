#ifndef surface_component_cpp
#define surface_component_cpp


#include <vector>

namespace pce {

struct Surface {
  std::vector<int> natural_color:
  double reflection_index; // 0 < reflection_index < 1 
  double transparency_index; // 0 < transparency_index < 1 
  double luminosity; // 0 for non-luminous objects
};

}

#endif /* surface_component_cpp */
