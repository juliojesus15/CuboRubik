#ifndef CUBE_H
#define CUBE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "value.h"
#include "color.h"

typedef std::map<int, std::pair<char, char > > Colors;

class Cube {
public:
    char id;   
    int type;       // 0: centro 1: Borde 2: Esquina
    Colors colors;
    std::vector<float> vertex;
            
    Cube(char cube_id, std::vector<char> colors);    
    void translation(glm::vec3 move_to);
    void rotation(glm::vec3 r, glm::vec3 t);

private:
    Colors set_colors(std::vector<char> list_colors);
    void applying_transformation(glm::mat4 model);
};

Cube::Cube(char cube_id, std::vector<char> list_colors) {
    this->id = cube_id;
    this->type = list_colors.size();
    this->vertex = values::vertex;
    this->colors = set_colors(list_colors);
}

Colors Cube::set_colors(std::vector<char> list_colors) {
    color::MapColor color_encode = color::encode_RGB();
    color::MapGroup group_encode = color::encode_group();
    Colors buffer;

    for (int i = 0; i < list_colors.size(); i++) {
        char current_color = list_colors[i];

        int idx = color_encode[current_color].first;
        std::vector<float> RGB = color_encode[current_color].second;
        
        // Configurando el color en cada vertice
        double from = idx * 36;
        double to = from + 36;
        
        for (int j = from; j < to; j += 6) {
            vertex[j + 3] = RGB[0];
            vertex[j + 4] = RGB[1];
            vertex[j + 5] = RGB[2];
        }

        // Guardando los ids del color        
        buffer[i] = std::pair<char, char>(current_color, group_encode[current_color]);        
    }
    return buffer;
}

void Cube::applying_transformation(glm::mat4 model) {
    for (float i = 0; i < vertex.size(); i += 6) {
        glm::vec4 result = model * glm::vec4(vertex[i], vertex[i + 1], vertex[i + 2], 1.0f);
        vertex[i] = result.x;
        vertex[i + 1] = result.y;
        vertex[i + 2] = result.z;
    }
}

void Cube::translation(glm::vec3 move_to) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), move_to);
    applying_transformation(model);
}

void Cube::rotation(glm::vec3 r, glm::vec3 t) {
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), r);
    model = glm::translate(model, t);
    applying_transformation(model);
}

#endif