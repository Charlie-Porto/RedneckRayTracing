#ifndef RayTraceSystem_cpp
#define RayTraceSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
System for performing raytracing.

-----------------------------------------------------------------*/
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>

#include "../System.cpp"
#include "subsystems/CameraOperatorSubsystem.cpp"
#include "subsystems/ObjectRadarDetectorSubsystem.cpp"
#include "subsystems/simpleDrawingFunctions.cpp"

extern ControlPanel control;
const int TOTAL_PIXELS = global_const::screen_x * global_const::screen_y;

namespace pce {
class RayTraceSystem : public ISystem {
public:
  RayTraceSystem() { ezp::print_item("creating RayTraceSystem"); }
  void Init() {
    camera_operator_.Init();
  }

  void SetupRayTrace() {
    camera_operator_.UpdateCamera(); 
    radar_detector_.UpdateRadar(entities, camera_operator_.camera_);
    radar_detector_.PrintRadarMapContents();
  }

  void RayTrace() {
    for (auto const& [key, value] : radar_detector_.radar_map_) {
      pce::quickdraw::drawCircleAtVec2(value);
    }
  }

private:
  CameraOperatorSubsystem camera_operator_;
  ObjectRadarDetectorSubsystem radar_detector_;

};
}
#endif /* RayTraceSystem_cpp */
