
#ifndef SphereObjectFactory_cpp
#define SphereObjectFactory_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
factory class for making planet-like sphere entities.
-----------------------------------------------------------------*/
#include <ezprint.cpp>
#include <randomness_functions.cpp>

extern ControlPanel control; 

const double min_z = -90.0;
const double max_z = 0.0;
const double min_x = 0.0;
const double max_x = 90.0;
const double min_y = 0.0;
const double max_y = 90.0;
const double min_r = 5.0;
const double max_r = 20.0;


class SphereObjectFactory {
public:
  SphereObjectFactory() { ezp::print_item("creating SphereObjectFactory"); }


  glm::dvec3 GetRandomLocation() {
    const double z = -1.0 * get_rand_double_between_zero_and_input(min_z);
    const double x = get_rand_signed_double_between_two_doubles(min_x, max_x);
    const double y = get_rand_signed_double_between_two_doubles(min_y, max_y);
    const auto location = glm::dvec3(x, y, z);
    return location;
  }


  double GetRandomRadius() {
    const double rand_radius = get_rand_double_between_two_doubles(min_r, max_r);
    return rand_radius;
  }

  void MakeTestObject() {
    ezp::print_item("making object");
    const double new_object_radius = 10.0;
    glm::dvec3 new_object_location = glm::dvec3(2, 2, -2);
    Entity object = control.CreateEntity();
    control.AddComponent(object, pce::Location{
      .position = new_object_location
    });
    control.AddComponent(object, pce::RotatedLocation{});
    control.AddComponent(object, pce::SphereBody{.radius = new_object_radius});
    objects_.push_back(object);
  }

  void MakeObject() {
    ezp::print_item("making object");
    const double new_object_radius = GetRandomRadius();
    // const double new_object_radius = 10.0;
    glm::dvec3 new_object_location = GetRandomLocation();
    // glm::dvec3 new_object_location = glm::dvec3(2, 2, -2);
    Entity object = control.CreateEntity();
    control.AddComponent(object, pce::Location{
      .position = new_object_location
    });
    control.AddComponent(object, pce::RotatedLocation{});
    control.AddComponent(object, pce::SphereBody{.radius = new_object_radius});
    objects_.push_back(object);
  }

private:
  std::vector<Entity> objects_;
};




#endif /* SphereObjectFactory_cpp */
