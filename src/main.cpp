
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constants/static_variables.cpp"
#include "SDL_core/simulation_manager.cpp"

#include "ecs/ControlPanel.cpp"

/* components */
#include "ecs/components/location_component.cpp"
#include "ecs/components/rotated_location_component.cpp"
#include "ecs/components/sphere_body_component.cpp"
#include "ecs/components/radar_component.cpp"
#include "ecs/components/surface_component.cpp"

/* systems */
#include "ecs/systems/RayTraceSystem.cpp"
#include "ecs/systems/ObjectRadarDetectorSystem.cpp"
#include "ecs/systems/CameraOperatorSystem.cpp"

/* factories */
#include "ecs/entity_factories/SphereObjectFactory.cpp"
#include "ecs/entity_factories/AxisGenerator.cpp"

/* other */
#include <simple_framerate_timer.cpp>


/*---------- screen dimensions ----------*/
const int screenx = global_const::screen_x;
const int screeny = global_const::screen_y;
/*---------------------------------------*/
ControlPanel control;
int main(int argc, const char * argv[]) {
    /*------------------------- SDL setup ----------------------------*/ 
    /* set up time and frames */
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;    
    int frameStart;
    int frameTime;
    
    /* create simulation class instance */ 
    Simulation* simulation = new Simulation;
    simulation->init("PineconeEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenx, screeny, false);
    std::cout << "SDL Simulation successfully initialized." << std::endl;

    /* set randomness seed */
    set_srand();

    /* Ordinary Setup items */
    control.Init();

    /* Register Components */
    control.RegisterComponent<pce::Location>();
    control.RegisterComponent<pce::RotatedLocation>();
    control.RegisterComponent<pce::SphereBody>();
    control.RegisterComponent<pce::Radar>();
    control.RegisterComponent<pce::Surface>();

    /* Register Systems */
    auto ray_trace_system = control.RegisterSystem<pce::RayTraceSystem>();
    Signature ray_trace_sig;
    ray_trace_sig.set(control.GetComponentType<pce::RotatedLocation>());
    ray_trace_sig.set(control.GetComponentType<pce::Radar>());
    ray_trace_sig.set(control.GetComponentType<pce::SphereBody>());
    ray_trace_sig.set(control.GetComponentType<pce::Surface>());
    control.SetSystemSignature<pce::RayTraceSystem>(ray_trace_sig);

    auto object_radar_system = control.RegisterSystem<pce::ObjectRadarDetectorSystem>();
    Signature object_radar_sig;
    object_radar_sig.set(control.GetComponentType<pce::Location>());
    object_radar_sig.set(control.GetComponentType<pce::RotatedLocation>());
    object_radar_sig.set(control.GetComponentType<pce::Radar>());
    control.SetSystemSignature<pce::ObjectRadarDetectorSystem>(object_radar_sig);

    auto camera_system = control.RegisterSystem<pce::CameraOperatorSystem>();
    Signature camera_sig;
    control.SetSystemSignature<pce::CameraOperatorSystem>(camera_sig);

    camera_system->Init();
    
    /* Create Factories */
    auto sphere_object_factory = SphereObjectFactory();
    // sphere_object_factory.MakeTestObject();
    sphere_object_factory.MakeMoon();
    // for (int i = 0; i < 2; ++i) {
    //   sphere_object_factory.MakeObject();
    // }
    
    auto axis_generator = AxisGenerator();
    axis_generator.BuildXAxis();
    axis_generator.BuildYAxis();
    axis_generator.BuildZAxis();

    ray_trace_system->PerformInitialEntitySift();
    
    simple_framerate_timer simple_timer = simple_framerate_timer();

    /*----------Main Loop---------------------*/
    while (simulation->running()) {
        
        /* SDL events and updating */ 
        int frameStart = SDL_GetTicks();       
        simulation->handleEvents();
        simulation->update();
        simulation->clearRenderer();

        double t = frameStart/1000.0;

        // update timer 
        int time = int(t);
        simple_timer.update_timer(time);


        /*~~~~~~~~~------------- Do Stuff and Update ----------------*/
        double ticks = (SDL_GetTicks()/1000.0);
        camera_system->UpdateCamera();
        const double cam_position_scalar = camera_system->ProvideCameraPositionScalar();
        object_radar_system->UpdateRadar(cam_position_scalar,
                                         camera_system->ProvideCameraVersor(),
                                         camera_system->ProvideCameraFocusPosition());
        ray_trace_system->TraceSuperimposedEntities(cam_position_scalar);
        // ray_trace_system->TraceObjectCenters(cam_position_scalar);
        ray_trace_system->UpdateRayTrace(cam_position_scalar);


        /*~~~~~~~~~-------------- Draw and Render --------------------*/
        simulation->render();

        /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
        /* Clear events list */
        simulation->clear_frame_events();

        /* check how much time has passed during frame */
        frameTime = SDL_GetTicks() - frameStart;

        /* if frame too fast, delay the frame */
        if ( frameDelay > frameTime )
        {
            SDL_Delay( frameDelay - frameTime );
        }
    }

    simulation->clean();

    delete simulation;
    
    return 0;
}

