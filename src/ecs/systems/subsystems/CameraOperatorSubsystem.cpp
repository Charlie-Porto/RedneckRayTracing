#ifndef CameraOperatorSubsystem_cpp
#define CameraOperatorSubsystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
class for operating the camera
-----------------------------------------------------------------*/
#include "glm/ext/quaternion_double.hpp"

#include <camera.cpp>
#include <camera_functions.cpp>
#include <virtual_keyboard.cpp>

#include "cameraOperatorFunctions.cpp"

namespace pce {
class CameraOperatorSubsystem {
public:
  void Init() {
    camera_.location_vec3 = glm::dvec3(0.0, 0.0, 10.0);
    camera_.xz_angle = 0.0;
    camera_.y_angle = 0.0;
    camera_.pov_scalar = 10.0;
    camera_.xz_circle_radius = camera_.pov_scalar;
    camera_.rotation_versor = glm::dquat(1.0, 0.0, 0.0, 0.0);
    // camera_.focus_distance = 30.0; 
  }

  void UpdateCamera() {
    pce::cam_op::updateCameraPosition(camera_, keyboard_);
  }

Camera camera_; // making this public for now for easy & quick pass to the 
                // radar system
private:
VirtualKeyboard keyboard_;

};
}
#endif /* CameraOperatorSubsystem_cpp */
