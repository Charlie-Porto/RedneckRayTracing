#ifndef AxisGenerator_cpp
#define AxisGenerator_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
creates the x, y, and z axes using sphere objects
-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include "SphereObjectFactory.cpp"

class AxisGenerator {
public:
  AxisGenerator() {}

  void BuildXAxis() {
    const double x_axis_start = -200.0;
    const double x_axis_interval = 10.0;
    double current_x = x_axis_start;
    while (current_x <= -x_axis_start) {
      sphere_factory.MakeObjectAtLocation(glm::dvec3(current_x, 0, 0));
      current_x += x_axis_interval;
    }
  }

  void BuildYAxis() {
    const double y_axis_start = -200.0;
    const double y_axis_interval = 10.0;
    double current_y = y_axis_start;
    while (current_y <= -y_axis_start) {
      sphere_factory.MakeObjectAtLocation(glm::dvec3(0, current_y, 0));
      current_y += y_axis_interval;
    }
  }

  void BuildZAxis() {
    const double z_axis_start = -200.0;
    const double z_axis_interval = 10.0;
    double current_z = z_axis_start;
    while (current_z <= -z_axis_start) {
      sphere_factory.MakeObjectAtLocation(glm::dvec3(0, 0, current_z));
      current_z += z_axis_interval;
    }
  }

private:
  SphereObjectFactory sphere_factory;
};



#endif /* AxisGenerator_cpp */
