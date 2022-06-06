#ifndef cameraOperatorFunctions_cpp
#define cameraOperatorFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
camera operation helper functions
-----------------------------------------------------------------*/

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <virtual_keyboard.cpp>
#include <camera.cpp>
#include <camera_functions.cpp>
#include <vector3_functions.cpp>
#include <math_objects/Plane.cpp>
#include <math_objects/LineParamEq.cpp>

#include "../../../constants/static_variables.cpp"

namespace pce {
namespace cam_op {

const double PI = 3.14159265;

// NOTE: SIGNS (+-) ARE VERY IMPORTANT IN THIS FUNCTION
void updateCameraReverseRotationVersor(Camera& camera) {
  const glm::dquat vert_rot_versor = cam_func::getCameraVerticalRotationVersor(-camera.y_angle);
  const glm::dquat horiz_rot_versor = cam_func::getCameraHorizontalRotationVersor(camera.xz_angle);
  camera.rotation_versor = horiz_rot_versor * vert_rot_versor;
}


void updateCameraXZAngle(Camera& camera, const double& direction) {
  if (direction != 0.0) {
    camera.xz_angle += global_const::hop_angle * direction;
  }

  const double new_camera_xpos = camera.xz_circle_radius * sin(PI * camera.xz_angle/180.0);
  const double new_camera_zpos = camera.xz_circle_radius * cos(PI * camera.xz_angle/180.0);

  camera.location_vec3.x = new_camera_xpos;
  camera.location_vec3.z = new_camera_zpos;

  vezp::print_dvec3(camera.location_vec3);
  updateCameraReverseRotationVersor(camera);
}


void updateCameraYAngle(Camera& camera, const double& direction) {
  camera.y_angle += global_const::hop_angle * direction;
  const double new_camera_ypos = camera.pov_scalar * sin(PI * camera.y_angle/180.0);
  const double new_camera_xz_radius = camera.pov_scalar * cos(PI * camera.y_angle/180.0);

  camera.location_vec3.y = new_camera_ypos;
  camera.xz_circle_radius = new_camera_xz_radius;
  updateCameraXZAngle(camera, 0.0);
}


void updateCameraPositionScalar(Camera& camera, double direction) {
  camera.pov_scalar += direction * global_const::movement_speed;
  updateCameraYAngle(camera, 0.0);
}


JoystickReport pollVirtualKeyboard(VirtualKeyboard& keyboard) {
  return keyboard.check_buttons();
}


void updateCameraPosition(Camera& camera, VirtualKeyboard& keyboard) {
  JoystickReport joystick_report = pollVirtualKeyboard(keyboard);
  if (joystick_report.R_pressed == true) { 
    ezp::print_item("JOYSTICK: RIGHT");
    updateCameraXZAngle(camera, 1.0);
  }
  if (joystick_report.L_pressed == true) {
    ezp::print_item("JOYSTICK: LEFT");
    updateCameraXZAngle(camera, -1.0);
  }
  if (joystick_report.Up_pressed == true) {
    ezp::print_item("JOYSTICK: UP");
    updateCameraYAngle(camera, 1.0);
  }
  if (joystick_report.Down_pressed == true) {
    ezp::print_item("JOYSTICK: DOWN");
    updateCameraYAngle(camera, -1.0);
  }
  if (joystick_report.W_pressed == true) {
    ezp::print_item("JOYSTICK: W");
    updateCameraPositionScalar(camera, -1.0);
  }
  if (joystick_report.S_pressed == true) {
    ezp::print_item("JOYSTICK: S");
    updateCameraPositionScalar(camera, 1.0);
  }
}


}
}


#endif /* cameraOperatorFunctions_cpp */
