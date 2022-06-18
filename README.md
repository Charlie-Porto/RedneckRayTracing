# RedneckRayTracing
attempting to do some primitive ray tracing-type rendering of 3D space on a 2D screen

## how to compile
#### to compile the main executable, run the following command from the project root with the angle-bracketed text updated based on your configuration:
`g++ src/main.cpp -o main.o -std=c++17 \
 -I<path to SDL2 include files> \
 -Iinclude \
 -L<path to SDL2 dynamic lib files> \
 -lSDL2-2.0.0 \
 -lSDL2_image-2.0.0 \`
 
 
 
