#ifndef RayTraceSystem_cpp
#define RayTraceSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|

-----------------------------------------------------------------*/

#include <ezprint.cpp>

#include "../System.cpp"
#include "subsystems/CameraOperatorSubsystem.cpp"
#include "subsystems/ObjectRadarDetectorSubsystem.cpp"

extern ControlPanel control;
const int TOTAL_PIXELS = global_const::screen_x * global_const::screen_y;

namespace pce {
class RayTraceSystem : public ISystem {
public:
  RayTraceSystem() { ezp::print_item("creating RayTraceSystem"); }


private:
  CameraOperatorSubsystem camera_operator_;
  ObjectRadarDetectorSubsystem radar_detector_;

};
}
#endif /* RayTraceSystem_cpp */
