#ifndef Ellipsoid_cpp
#define Ellipsoid_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
Ellipsoid struct

read about ellipsoids:
https://en.wikipedia.org/wiki/Ellipsoid#:~:text=An%20ellipsoid%20is%20a%20surface,generally%2C%20of%20an%20affine%20transformation.

-----------------------------------------------------------------*/

#include <glm/vec3.hpp>
#include <ezprint.cpp>

namespace pce {
namespace math_objs {

struct Ellipsoid {
  glm::dvec3 center_point;
  double a;
  double b;
  double c;
};

}
}

#endif /* Ellipsoid_cpp */
