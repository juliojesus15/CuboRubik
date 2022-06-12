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
    size_t type;       // 1: centro 2: Borde 3: Esquina
    Colors colors;
    std::vector<float> vertex;
            
    Cube(char cube_id, std::vector<char> colors);

    char get_color(char group_id);
    void translation(glm::vec3 move_to);
    void transformation(glm::vec3 r, glm::vec3 t);

private:
    Colors set_colors(std::vector<char> list_colors);
    void update_vertex(glm::mat4 model);
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
        int from = idx * 36;
        int to = from + 36;
        
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

char Cube::get_color(char group_id) {
    for (auto iter = colors.begin(); iter != colors.end(); ++iter) {
        std::pair<char, char > current = iter->second;
        if (current.second == group_id) {
            return current.first;
        }
    }
    return 'X';
}

void Cube::update_vertex(glm::mat4 model) {
    for (float i = 0; i < vertex.size(); i += 6) {
        glm::vec4 result = model * glm::vec4(vertex[i], vertex[i + 1], vertex[i + 2], 1.0f);
        vertex[i] = result.x;
        vertex[i + 1] = result.y;
        vertex[i + 2] = result.z;
    }
}

void Cube::translation(glm::vec3 pos) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    update_vertex(model);
}

void Cube::transformation(glm::vec3 axis, glm::vec3 pos) {
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), axis);
    model = glm::translate(model, pos);
    update_vertex(model);
}

#endif