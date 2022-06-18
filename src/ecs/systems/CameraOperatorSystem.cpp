#ifndef CameraOperatorSystem_cpp
#define CameraOperatorSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
class for operating the camera
-----------------------------------------------------------------*/
#include "glm/ext/quaternion_double.hpp"

#include <camera.cpp>
#include <camera_functions.cpp>
#include <virtual_keyboard.cpp>

#include "../System.cpp"
#include "cameraOperatorFunctions.cpp"

namespace pce {
class CameraOperatorSystem : public ISystem {
public:
  void Init() {
    camera_.location_vec3 = glm::dvec3(0.0, 0.0, 250.0);
    camera_.focus_point = glm::dvec3(0.0, 0.0, 0.0);
    camera_.xz_angle = 0.0;
    camera_.y_angle = 0.0;
    camera_.pov_scalar = camera_.location_vec3.z;
    camera_.xz_circle_radius = camera_.pov_scalar;
    camera_.rotation_versor = glm::dquat(1.0, 0.0, 0.0, 0.0);
    // camera_.in_origin_focus_mode = true;
    // camera_.in_free_roam_mode = false;
    camera_.in_origin_focus_mode = false;
    camera_.in_free_roam_mode = true;
  }

  const glm::dquat& ProvideCameraVersor() const {
    return camera_.rotation_versor;
  }

  const glm::dvec3& ProvideCameraFocusPosition() const {
    return camera_.focus_point;
  }

  const double ProvideCameraPositionScalar() const {
    return camera_.pov_scalar;
  }

  void ToggleCameraMode() {
    // to write this function
  }

  void UpdateCamera() {
    if (camera_.in_origin_focus_mode) {
      pce::cam_op::updateCameraPositionOriginFocus(camera_, keyboard_);
      ezp::print_labeled_item("camera position scalar: ", camera_.pov_scalar);
    } else if (camera_.in_free_roam_mode) {
      pce::cam_op::updateCameraPositionFreeRoam(camera_, keyboard_);
    }
  }

private:
Camera camera_;
VirtualKeyboard keyboard_;

};
}
#endif /* CameraOperatorSystem_cpp */
