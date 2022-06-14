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
    Colors colors;  
    std::vector<float> vertex;

    Cube(char cube_id, std::vector<char> colors);

    char get_color_by_group(char group_id);
    Colors find_and_update_color(char current_face, char new_face);

    void translation(glm::vec3 move_to);
    void transformation(glm::vec3 r, glm::vec3 t);

private:
    Colors set_colors(std::vector<char> list_colors);
    void update_vertex(glm::mat4 model);
};

Cube::Cube(char id, std::vector<char> list_colors) {
    this->id = id;
    this->vertex = values::vertex;
    this->colors = set_colors(list_colors);
}

// Recibe lista de colores, cada color accede a los maps definidos en color.h para obtener su indice y valor RGB
Colors Cube::set_colors(std::vector<char> list_colors) {
    color::MapColor color_encode = color::encode_RGB();
    color::MapGroup group_encode = color::encode_group();    
    Colors tmp_buffer;

    for (int i = 0; i < list_colors.size(); i++) {
        char color = list_colors[i];
        int index = color_encode[color].first;
        std::vector<float> RGB = color_encode[color].second;      

        // Configurando el color en cada vertice
        int from = index * 36;
        int to = from + 36;
        for (int j = from; j < to; j += 6) {
            vertex[j + 3] = RGB[0];
            vertex[j + 4] = RGB[1];
            vertex[j + 5] = RGB[2];
        }
        // Guardando los ids del color
        tmp_buffer[i] = std::pair<char, char>(color, group_encode[color]);
    }
    return tmp_buffer;
}

Colors Cube::find_and_update_color(char current_face, char new_face) {
    Colors tmp_colors = colors;
    for (auto iter = tmp_colors.begin(); iter != tmp_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;        
        if (tmp_pair.second == current_face) {
            tmp_pair.second = new_face;
            tmp_colors[iter->first] = tmp_pair;            
        }
    }    
    return tmp_colors;
}

// Retorna el color que se esta mostrando en el grupo (group_id)
char Cube::get_color_by_group(char group_id) {
    for (auto iter = colors.begin(); iter != colors.end(); ++iter) {
        std::pair<char, char > tmp = iter->second;
        if (tmp.second == group_id)
            return tmp.first;
    }
    return 'X';
}

// Recibe una matriz de transformacion que multiplcara a cada vertice
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