
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

/* systems */
#include "ecs/systems/RayTraceSystem.cpp"

/* factories */
#include "ecs/entity_factories/SphereObjectFactory.cpp"

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

    /* Register Systems */
    auto ray_trace_system = control.RegisterSystem<pce::RayTraceSystem>();
    Signature ray_trace_sig;
    ray_trace_sig.set(control.GetComponentType<pce::Location>());
    ray_trace_sig.set(control.GetComponentType<pce::RotatedLocation>());
    control.SetSystemSignature<pce::RayTraceSystem>(ray_trace_sig);

    ray_trace_system->Init();
    
    /* Create Factories */
    auto sphere_object_factory = SphereObjectFactory();
    sphere_object_factory.MakeTestObject();
    for (int i = 0; i < 2; ++i) {
    //   sphere_object_factory.MakeObject();
    }

    
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
        ray_trace_system->SetupRayTrace();
        ray_trace_system->RayTrace();


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

