# TODO
- [x] fix glm (done?)
- [x] fix normals
    - [x] fixed parenthesis causing incorrect color ramping in vertex shaderCPU
    - [x] CPU pipeline causes normals to be manipulated when model is rotated? using world coordinates perhaps
        - lol who knew that multiplying the normals by the transform would... multiply the normals.
    
- Create a pdf for report not a .md file.
- Add pictures in the report.
- When comparing the model transformations in CPU and GPU report the time difference in calculations or the FPS or some sort of numeric comparison on larger meshes.


## Setup
Makefile assumes installation of GLEW/GLFW3, glm is included in the files.

The program is built to build/modelViewer.exe

Run `make` in the same directory as the make file to build. (Run `make clean` if build/ already exists.)

Then, run `./build/modelViewer.exe`.


## CONFIGURATIONS
There are 3 variables in `main.cpp` that you can edit to alter the program. 
- The default directory for an obj file.
- Screen width/height
- A boolean that defers transformation from the CPU to the GPU.


## CONTROLS
The program has a few keyboard controls to manipulate the model view.

SHIFT/ENTER to zoom in/out.
WASD to translate.
Arrow keys to rotate.