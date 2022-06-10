#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <map>

namespace values {
    std::vector<float> vertex = {
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)

        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)

         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)

        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue) 
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue) 
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue) 
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue) 
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue)

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
    };

    std::vector<char> cube_ids = {
        'A', 'B', 'C',
        'D', 'E', 'F',
        'G', 'H', 'I',
        'J', 'K', 'L',
        'M',      'N',
        'O', 'P', 'Q',
        'R', 'S', 'T',
        'U', 'V', 'W',
        'X', 'Y', 'Z'
    };

    std::vector<std::vector<char> > cube_colors = {
        { 'O', 'B', 'W' },  { 'B', 'W' },   { 'B', 'R', 'W' },
        { 'B', 'O' },       { 'B' },        { 'B', 'R' },
        { 'B', 'Y', 'O' },  { 'B', 'Y' },   { 'B', 'Y', 'R' },

        { 'W', 'O'},        { 'W'},         { 'R', 'W' },
        { 'O'},                             { 'R'},
        { 'Y', 'O'},        { 'Y'},         { 'R', 'Y' },

        { 'O', 'G', 'W' },  { 'G', 'W' },   { 'G', 'R', 'W' },
        { 'G', 'O' },       { 'G' },        { 'G', 'R' },
        { 'O', 'G', 'Y' },  { 'G', 'Y' },   { 'G', 'Y', 'R' }
    };

    std::vector<glm::vec3> cube_positions = {
        glm::vec3(-0.50f,  0.50f, -0.50f), glm::vec3(0.50f,  0.50f, -0.50f), glm::vec3(1.50f,  0.50f, -0.50f),
        glm::vec3(-0.50f, -0.50f, -0.50f), glm::vec3(0.50f, -0.50f, -0.50f), glm::vec3(1.50f, -0.50f, -0.50f),
        glm::vec3(-0.50f, -1.50f, -0.50f), glm::vec3(0.50f, -1.50f, -0.50f), glm::vec3(1.50f, -1.50f, -0.50f),

        glm::vec3(-0.50f,  0.50f,  0.50f), glm::vec3(0.50f,  0.50f,  0.50f), glm::vec3(1.50f,  0.50f,  0.50f),
        glm::vec3(-0.50f, -0.50f,  0.50f),                                    glm::vec3(1.50f, -0.50f,  0.50f),
        glm::vec3(-0.50f, -1.50f,  0.50f), glm::vec3(0.50f, -1.50f,  0.50f), glm::vec3(1.50f, -1.50f,  0.50f),

        glm::vec3(-0.50f,  0.50f,  1.50f), glm::vec3(0.50f,  0.50f,  1.50f), glm::vec3(1.50f,  0.50f,  1.50f),
        glm::vec3(-0.50f, -0.50f,  1.50f), glm::vec3(0.50f, -0.50f,  1.50f), glm::vec3(1.50f, -0.50f,  1.50f),
        glm::vec3(-0.50f, -1.50f,  1.50f), glm::vec3(0.50f, -1.50f,  1.50f), glm::vec3(1.50f, -1.50f,  1.50f)
    };

}

#endif