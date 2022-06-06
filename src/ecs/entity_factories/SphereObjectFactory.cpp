#ifndef SphereObjectFactory_cpp
#define SphereObjectFactory_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
factory class for making planet-like sphere entities.
-----------------------------------------------------------------*/
#include <ezprint.cpp>

extern ControlPanel control; 

class SphereObjectFactory {
public:
  SphereObjectFactory() { ezp::print_item("creating SphereObjectFactory"); }

  void MakeObject() {
    Entity object = control.CreateEntity();
    control.AddComponent(object, pce::Location{
      .position = glm::dvec3(0, 0, 0)
    });
    control.AddComponent(object, pce::RotatedLocation{});
    control.AddComponent(object, pce::SphereBody{.radius = 2});
    objects_.push_back(object);
  }

private:
  std::vector<Entity> objects_;
};




#endif /* SphereObjectFactory_cpp */
