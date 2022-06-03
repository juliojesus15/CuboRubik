#ifndef CUBE_H
#define CUBE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "default_values.h"
#include "color.h"

class Cube {
public:
    char cube_id;        
    std::vector<float> vertex;
    
    
    Cube(char cube_id, std::vector<char> colors);

    void translation(glm::vec3 move_to);
    void rotation(float angle);
private:
    void set_colors(std::vector<char> colors);
};

Cube::Cube(char cube_id, std::vector<char> colors) {
    this->cube_id = cube_id;
    this->vertex = default_values::vertex;
    set_colors(colors);
}

void Cube::set_colors(std::vector<char> colors) {    

    color::MapCode codes = color::define_codes();
    color::MapColor ids  = color::define_ids();

    for (int i = 0; i < colors.size(); i++) {
        
        char current_color = colors[i];

        std::vector<float> RGB = codes[current_color];
        
        double from = ids[current_color] * 36;
        double to = from + 36;
        
        for (int j = from; j < to; j += 6) {
            vertex[j + 3] = RGB[0];
            vertex[j + 4] = RGB[1];
            vertex[j + 5] = RGB[2];
        }
    }
}

void Cube::translation(glm::vec3 move_to) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), move_to);
    for (float i = 0; i < vertex.size(); i += 6) {
        glm::vec4 result = model * glm::vec4(vertex[i], vertex[i + 1], vertex[i + 2], 1.0f);
        vertex[i] = result.x;
        vertex[i + 1] = result.y;
        vertex[i + 2] = result.z;
    }
}

void Cube::rotation(float angle) {
    //glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    for (float i = 0; i < vertex.size(); i += 6) {
        glm::vec4 result = model * glm::vec4(vertex[i], vertex[i + 1], vertex[i + 2], 1.0f);
        vertex[i] = result.x;
        vertex[i + 1] = result.y;
        vertex[i + 2] = result.z;
    }        
    //std::cout << "Time: " << (float)glfwGetTime() << std::endl;
}

#endif