#ifndef CUBE_H
#define CUBE_H

#include "cube_utils.h"

class Cube {
public:
    char cube_id;        
    std::vector<float> vertex;
    std::vector<unsigned int> index;    
    
    Cube(char cube_id, std::vector<char> colors);

    void translation(glm::vec3 move_to);
private:
    void set_colors(std::vector<char> colors);
};

Cube::Cube(char cube_id, std::vector<char> colors) {
    this->cube_id = cube_id;
    this->vertex = cube_utils::default_vertex;
    this->index = cube_utils::default_index;
    set_colors(colors);
}

void Cube::set_colors(std::vector<char> colors) {    
    cube_utils::ColorCodesMap codes = cube_utils::get_color_codes();

    for (int i = 0; i < colors.size(); i++) {
        std::vector<double> code = codes[colors[i]];
        double from = code[0] * 24;
        double to = from + 24;
        for (int j = from; j < to; j += 6) {
            vertex[j + 3] = code[1];
            vertex[j + 4] = code[2];
            vertex[j + 5] = code[3];
        }
    }
}

void Cube::translation(glm::vec3 move_to) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), move_to);
    for (float i = 0; i < vertex.size(); i += 6) {
        glm::vec4 traslacion = model * glm::vec4(vertex[i], vertex[i + 1], vertex[i + 2], 1.0f);
        vertex[i] = traslacion.x;
        vertex[i + 1] = traslacion.y;
        vertex[i + 2] = traslacion.z;
    }
}

#endif