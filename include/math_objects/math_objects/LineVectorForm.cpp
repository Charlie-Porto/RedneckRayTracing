#ifndef LineVectorForm_cpp
#define LineVectorForm_cpp


#include <glm/vec3.hpp>

namespace pce {
namespace math_objs {

struct LineVectorForm {
  glm::dvec3 origin;
  glm::dvec3 direction;
  double d;
};

}
}


#endif /* LineVectorForm_cpp */
