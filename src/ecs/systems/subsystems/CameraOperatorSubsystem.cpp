#ifndef CameraOperatorSubsystem_cpp
#define CameraOperatorSubsystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
class for operating the camera
-----------------------------------------------------------------*/

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
  }

  void UpdateCamera() {
    pce::cam_op::updateCameraPosition(camera_, keyboard_);
  }

private:
Camera camera_;
VirtualKeyboard keyboard_;

};
}
#endif /* CameraOperatorSubsystem_cpp */
