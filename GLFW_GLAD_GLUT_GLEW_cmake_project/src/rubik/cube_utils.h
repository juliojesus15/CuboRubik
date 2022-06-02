#ifndef CUBE_UTILS_H
#define CUBE_UTILS_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <map>

namespace cube_utils {    
    typedef std::map<char, std::vector<double> > ColorCodesMap;
    typedef std::map<char, char > FaceColorsMap;
    
    FaceColorsMap get_face_colors() {
        FaceColorsMap faces;
        faces['L'] = 'N';
        faces['R'] = 'N';
        faces['D'] = 'N';
        faces['U'] = 'N';
        faces['B'] = 'N';
        faces['F'] = 'N';        
        return faces;
    }

    ColorCodesMap get_color_codes() {
        ColorCodesMap codes;
        codes['O'] = { 0, 1.00f, 0.34f, 0.00f };
        codes['R'] = { 1, 0.72f, 0.04f, 0.19f };
        codes['Y'] = { 2, 1.00f, 0.83f, 0.00f };
        codes['W'] = { 3, 1.00f, 1.00f, 1.00f };
        codes['B'] = { 4, 0.00f, 0.26f, 0.68f };
        codes['G'] = { 5, 0.00f, 0.61f, 0.27f };
        return codes;
    }
            
    std::vector<float> default_vertex = {        
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Left (Orange)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Right (Red)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Down (Yellow)
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Up (White)
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue) 
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue) 
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue) 
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Back (Blue)        
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // Front (Green)
    };

    std::vector<unsigned int> default_index = {
        0, 1, 2, 2, 3, 0,           // Left 
        4, 5, 6, 6, 7, 4,           // Right
        8, 9, 10, 10, 11, 8,        // Down
        12, 13, 14, 14, 15, 12,     // Up
        16, 17, 18, 18, 19, 16,     // Back
        20, 21, 22, 22, 23, 20,     // Front
    };
}

#endif