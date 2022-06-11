#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

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

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Blue)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Blue)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Blue)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Blue)
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Blue)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Blue)

        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Orange)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Orange)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Orange)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Orange)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Orange)
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Orange)

         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Green)
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Green)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Green)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Green)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Green)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Green)

        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Red) 
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Red) 
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Red) 
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Red)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Red) 
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Red)

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
        { 'B', 'R', 'W' },  { 'R', 'W' },   { 'G', 'R', 'W' },
        { 'B', 'R' },       { 'R' },        { 'G', 'R' },
        { 'B', 'R', 'Y' },  { 'R', 'Y' },   { 'G', 'R', 'Y' },

        { 'B', 'W'},        { 'W'},         { 'G', 'W' },
        { 'B'},                             { 'G'},
        { 'B', 'Y'},        { 'Y'},         { 'G', 'Y' },

        { 'B', 'O', 'W' },  { 'O', 'W' },   { 'G', 'O', 'W' },
        { 'B', 'O' },       { 'O' },        { 'G', 'O' },
        { 'B', 'O', 'Y' },  { 'O', 'Y' },   { 'G', 'O', 'Y' }
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