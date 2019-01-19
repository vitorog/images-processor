# Real-time Image Effects
Applies image effects in real-time

# Description

This application reads the user's WebCam and applies real-time image effects created in GLSL. Useful for testing some 2D image processing effects in GLSL.

The application scans the execution folder for fragment shaders, therefore new effects can be added just by creating new shaders that follow the same structure.

Depends on the [Shade Framework](https://github.com/vitorog/shade-framework), a framework I created that contains useful functions (e.g. OpenGL related utility functions, OBJ file loading, shader management, etc)

# Tools
C++
OpenCV for WebCam capturing
OpenGL for image rendering
GLSL for the image effects
Qt for the GUI and some utility functions
Shade Framework for some OpenGL related functions and shader loading/management
CMake for project management

# Screenshots
![ScreenShot](https://raw.github.com/vitorog/images-processor/master/screenshots/edges.png "Edges Filter")

Edges filter

![ScreenShot](https://raw.github.com/vitorog/images-processor/master/screenshots/night_vision.png "Night Vision Filter")

Night vision filter
