#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/glm.hpp>

#include <vector>
#include <map>

namespace values {
    typedef std::pair<char, std::string> Feature;    

    // Vertices pre definidos 
    std::vector<float> vertex_left_face = {
        -0.50f, -0.50f,  0.50f, 0.0f, 1.0f, // Left (Blue)
        -0.50f, -0.50f, -0.50f, 0.0f, 0.0f, // Left (Blue)
        -0.50f,  0.50f, -0.50f, 1.0f, 0.0f, // Left (Blue)
        -0.50f,  0.50f, -0.50f, 1.0f, 0.0f, // Left (Blue)
        -0.50f,  0.50f,  0.50f, 1.0f, 1.0f, // Left (Blue)
        -0.50f, -0.50f,  0.50f, 0.0f, 1.0f, // Left (Blue)
    };

    std::vector<float> vertex_down_face = {
        -0.50f, -0.50f,  0.50f, 0.0f, 1.0f, // Down (Yellow)
        -0.50f, -0.50f, -0.50f, 0.0f, 0.0f, // Down (Yellow)
         0.50f, -0.50f, -0.50f, 1.0f, 0.0f, // Down (Yellow)
         0.50f, -0.50f, -0.50f, 1.0f, 0.0f, // Down (Yellow)
         0.50f, -0.50f,  0.50f, 1.0f, 1.0f, // Down (Yellow)
        -0.50f, -0.50f,  0.50f, 0.0f, 1.0f, // Down (Yellow)
    };

    std::vector<float> vertex_right_face = {
        0.50f, -0.50f,  0.50f, 0.0f, 1.0f, // Right (Green)
        0.50f, -0.50f, -0.50f, 0.0f, 0.0f, // Right (Green)
        0.50f,  0.50f, -0.50f, 1.0f, 0.0f, // Right (Green)
        0.50f,  0.50f, -0.50f, 1.0f, 0.0f, // Right (Green)
        0.50f,  0.50f,  0.50f, 1.0f, 1.0f, // Right (Green)
        0.50f, -0.50f,  0.50f, 0.0f, 1.0f, // Right (Green)
    };

    std::vector<float> vertex_back_face = {
        -0.50f,  0.50f, -0.50f, 0.0f, 1.0f, // Back (Red) 
        -0.50f, -0.50f, -0.50f, 0.0f, 0.0f, // Back (Red) 
         0.50f, -0.50f, -0.50f, 1.0f, 0.0f, // Back (Red) 
         0.50f, -0.50f, -0.50f, 1.0f, 0.0f, // Back (Red)
         0.50f,  0.50f, -0.50f, 1.0f, 1.0f, // Back (Red) 
        -0.50f,  0.50f, -0.50f, 0.0f, 1.0f, // Back (Red)
    };

    std::vector<float> vertex_front_face = {
        -0.50f,  0.50f,  0.50f, 0.0f, 1.0f, // Front (Orange)
        -0.50f, -0.50f,  0.50f, 0.0f, 0.0f, // Front (Orange)
         0.50f, -0.50f,  0.50f, 1.0f, 0.0f, // Front (Orange)
         0.50f, -0.50f,  0.50f, 1.0f, 0.0f, // Front (Orange)
         0.50f,  0.50f,  0.50f, 1.0f, 1.0f, // Front (Orange)
        -0.50f,  0.50f,  0.50f, 0.0f, 1.0f  // Front (Orange)
    };

    std::vector<float> vertex_up_face = {
        -0.50f,  0.50f,  0.50f, 0.0f, 1.0f,   // Up (White)
        -0.50f,  0.50f, -0.50f, 0.0f, 0.0f,   // Up (White)
         0.50f,  0.50f, -0.50f, 1.0f, 0.0f,   // Up (White)
         0.50f,  0.50f, -0.50f, 1.0f, 0.0f,   // Up (White)
         0.50f,  0.50f,  0.50f, 1.0f, 1.0f,   // Up (White)
        -0.50f,  0.50f,  0.50f, 0.0f, 1.0f,   // Up (White)
    };

    // Ids que asignaremos a cada cubo
    std::vector<char> cube_ids = {
        'A', 'B', 'C', // Para lado posterior
        'D', 'E', 'F', // Para lado posterior
        'G', 'H', 'I', // Para lado posterior
        'J', 'K', 'L', // Para lado intermedio
        'M',      'N', // Para lado intermedio
        'O', 'P', 'Q', // Para lado intermedio
        'R', 'S', 'T', // Para lado frontal
        'U', 'V', 'W', // Para lado frontal
        'X', 'Y', 'Z'  // Para lado frontal
    };
    
    std::vector<std::vector<Feature> > cube_features = {
        {   // A
            std::make_pair('B', "B/1.png"), 
            std::make_pair('R', "R/3.png"),
            std::make_pair('W', "W/1.png")
        },
        {   // B
            std::make_pair('R', "R/2.png"),
            std::make_pair('W', "W/2.png")
        },
        {   // C
            std::make_pair('G', "G/3.png"),
            std::make_pair('R', "R/1.png"),
            std::make_pair('W', "W/3.png")
        },
        {   // D
            std::make_pair('B', "B/4.png"),
            std::make_pair('R', "R/6.png")
        },
        {   // E
            std::make_pair('R', "R/5.png")
        },
        {   // F
            std::make_pair('G', "G/6.png"),
            std::make_pair('R', "R/4.png")
        },
        {   // G
            std::make_pair('B', "B/7.png"),
            std::make_pair('R', "R/9.png"),
            std::make_pair('Y', "Y/7.png")
        },
        {   // H
            std::make_pair('R', "R/8.png"),
            std::make_pair('Y', "Y/8.png")
        },
        {   // I
            std::make_pair('G', "G/9.png"),
            std::make_pair('R', "R/7.png"),
            std::make_pair('Y', "Y/9.png")
        },
        {   // J
            std::make_pair('B', "B/2.png"),
            std::make_pair('W', "W/4.png")
        },
        {   // K
            std::make_pair('W', "W/5.png")
        },
        {   // L
            std::make_pair('G', "G/2.png"),
            std::make_pair('W', "W/6.png")
        },
        {   // M
            std::make_pair('B', "B/5.png"),
        },
        {   // N
            std::make_pair('G', "G/5.png"),
        },
        {   // O
            std::make_pair('B', "B/8.png"),
            std::make_pair('Y', "Y/4.png")
        },
        {   // P
            std::make_pair('Y', "Y/5.png")
        },
        {   // Q
            std::make_pair('G', "G/8.png"),
            std::make_pair('Y', "Y/6.png")
        },
        {   // R
            std::make_pair('B', "B/3.png"),
            std::make_pair('O', "O/1.png"),
            std::make_pair('W', "W/7.png")
        },
        {   // S
            std::make_pair('O', "O/2.png"),
            std::make_pair('W', "W/8.png")
        },
        {   // T
            std::make_pair('G', "G/1.png"),
            std::make_pair('O', "O/3.png"),
            std::make_pair('W', "W/9.png")
        },
        {   // U
            std::make_pair('B', "B/6.png"),
            std::make_pair('O', "O/4.png")
        },
        {   // V
            std::make_pair('O', "O/5.png")
        },
        {   // W
            std::make_pair('G', "G/4.png"),
            std::make_pair('O', "O/6.png")
        },
        {   // X
            std::make_pair('B', "B/9.png"),
            std::make_pair('O', "O/7.png"),
            std::make_pair('Y', "Y/1.png")
        },
        {   // Y
            std::make_pair('O', "O/8.png"),
            std::make_pair('Y', "Y/2.png")
        },
        {   // Z
            std::make_pair('G', "G/7.png"),
            std::make_pair('O', "O/9.png"),
            std::make_pair('Y', "Y/3.png")
        }
    };

    // Posicion para cada cubo, esta transformacion se aplica en el constructor del cubo rubik
    std::vector<glm::vec3> cube_positions = {
        glm::vec3(-0.50f,  0.50f, -0.50f), glm::vec3(0.50f,  0.50f, -0.50f), glm::vec3(1.50f,  0.50f, -0.50f),        
        glm::vec3(-0.50f, -0.50f, -0.50f), glm::vec3(0.50f, -0.50f, -0.50f), glm::vec3(1.50f, -0.50f, -0.50f),
        glm::vec3(-0.50f, -1.50f, -0.50f), glm::vec3(0.50f, -1.50f, -0.50f), glm::vec3(1.50f, -1.50f, -0.50f),

        glm::vec3(-0.50f,  0.50f,  0.50f), glm::vec3(0.50f,  0.50f,  0.50f), glm::vec3(1.50f,  0.50f,  0.50f),
        glm::vec3(-0.50f, -0.50f,  0.50f),                                   glm::vec3(1.50f, -0.50f,  0.50f),
        glm::vec3(-0.50f, -1.50f,  0.50f), glm::vec3(0.50f, -1.50f,  0.50f), glm::vec3(1.50f, -1.50f,  0.50f),

        glm::vec3(-0.50f,  0.50f,  1.50f), glm::vec3(0.50f,  0.50f,  1.50f), glm::vec3(1.50f,  0.50f,  1.50f),
        glm::vec3(-0.50f, -0.50f,  1.50f), glm::vec3(0.50f, -0.50f,  1.50f), glm::vec3(1.50f, -0.50f,  1.50f),
        glm::vec3(-0.50f, -1.50f,  1.50f), glm::vec3(0.50f, -1.50f,  1.50f), glm::vec3(1.50f, -1.50f,  1.50f)        
    };

    //glm::linearRand(-1.0f, 1.0f)
    std::vector<glm::vec3> random_cube_positions(float deep, float min, float max) {
        std::vector<glm::vec3> random_position = {            
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            //glm::vec3(0.50f, 0.50f, -0.50f),
            //glm::vec3(1.50f, 0.50f, -0.50f),            

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),

            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
            glm::vec3(glm::linearRand(min, max), deep, glm::linearRand(min, max)),
        };
        return random_position;
    };

    std::map<char, glm::vec3> pos_targets = {
        {'A', glm::vec3(-1 ,  0 , -1)}, {'B', glm::vec3( 0 ,  0 , -1)}, {'C', glm::vec3( 1 ,  0 , -1)},
        {'D', glm::vec3(-1 , -1 , -1)}, {'E', glm::vec3( 0 , -1 , -1)}, {'F', glm::vec3( 1 , -1 , -1)},
        {'G', glm::vec3(-1 , -2 , -1)}, {'H', glm::vec3( 0 , -2 , -1)}, {'I', glm::vec3( 1 , -2 , -1)},
        
        {'J', glm::vec3(-1 ,  0 ,  0)}, {'K', glm::vec3( 0 ,  0 ,  0)}, {'L', glm::vec3( 1 ,  0 , 0)},
        {'M', glm::vec3(-1 , -1 ,  0)},                                 {'N', glm::vec3( 1 , -1 , 0)},
        {'O', glm::vec3(-1 , -2 ,  0)}, {'P', glm::vec3( 0 , -2 ,  0)}, {'Q', glm::vec3( 1 , -2 , 0)},
         
        {'R', glm::vec3(-1 ,  0 ,  1)}, {'S', glm::vec3( 0 ,  0 ,  1)}, {'T', glm::vec3( 1 ,  0 , 1)},
        {'U', glm::vec3(-1 , -1 ,  1)}, {'V', glm::vec3( 0 , -1 ,  1)}, {'W', glm::vec3( 1 , -1 , 1)},
        {'X', glm::vec3(-1 , -2 ,  1)}, {'Y', glm::vec3( 0 , -2 ,  1)}, {'Z', glm::vec3( 1 , -2 , 1)}
    };
}

#endif