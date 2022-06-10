#ifndef GLOBAL_H
#define GLOBAL_H

#include <thread>
#include <chrono>
#include <iostream>

namespace params {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    
    std::string vertex_shader = "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/vertex_shader.vs";
    std::string fragment_shader = "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/fragment_shader.fs";

    const int CUBES = 26;
    
    void sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(40)); }

}

#endif