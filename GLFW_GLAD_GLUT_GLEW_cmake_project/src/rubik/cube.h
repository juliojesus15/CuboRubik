#ifndef CUBE_H
#define CUBE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "value.h"
#include "color.h"

typedef std::map< char, std::string > Texture;
typedef std::map< int, std::pair< char, char > > Color;
typedef std::map< char, std::vector< float > > Face;
typedef std::pair< char, std::string > Feature;

class Cube {
public:
    char id;
    Color container_colors;             
    Texture container_textures;
    Face container_vertex;

    Cube(char cube_id, std::vector<Feature > features);

    //char get_color_by_group(char group_id);
    //int find_color_id(char group_id);
    //int find_color_id(char color_id, char group_id);

    void info();
    void translation(glm::vec3 move_to);
    void transformation(glm::vec3 r, glm::vec3 t);

private:
    void define_features(std::vector<Feature > features);
    //Color set_colors(std::vector<char> list_colors);
    //void update_vertex(glm::mat4 model);
};

Cube::Cube(char cube_id, std::vector<Feature > features) {    
    this->id = id;

    // Asignando a cada cara del cubo los vertices definidos en value.h
    container_vertex['U'] = values::vertex_up_face;
    container_vertex['D'] = values::vertex_down_face;
    container_vertex['L'] = values::vertex_left_face;
    container_vertex['R'] = values::vertex_right_face;
    container_vertex['F'] = values::vertex_front_face;
    container_vertex['B'] = values::vertex_back_face;

    // Inicializando los atributos color, textura y orietancion de cada cara del cubo
    define_features(features);    
}

// Recibe una lista de pares <Color(Char) - Textura(String)>
void Cube::define_features(std::vector< Feature > features) {
    color::MapGroup group_encode = color::encode_group();
    
    for (int i = 0; i < features.size(); i++) {        
        char color = features[i].first;
        std::string texture = features[i].second;            
        char group = group_encode[color];

        container_colors[i] = std::pair<char, char>(color, group);
        container_textures[group] = texture;
    }
}

/*
// Muestra informacion del cubo como su ID y colores
void Cube::info() {
    std::cout << "   + CUBO: " << id << std::endl;
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;
        std::cout << "   + Color: " << tmp_pair.first << " - " << " Posicion: " << tmp_pair.second << std::endl;
    }    
    std::cout << "=============================================" << std::endl;
}

int Cube::find_color_id(char group_id) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;        
        if (tmp_pair.second == group_id) {
            return iter->first;
        }
    }    
    return 3;
}

int Cube::find_color_id(char color_id, char group_id) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;
        if (tmp_pair.first==color_id && tmp_pair.second == group_id) {
            return iter->first;
        }
    }
    return 3;
}

// Retorna el color que se esta mostrando en el grupo (group_id)
char Cube::get_color_by_group(char group_id) {
    for (auto iter = container_colors.begin(); iter != colors.end(); ++iter) {
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
*/

void Cube::translation(glm::vec3 pos) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);

    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        char key = i->first;
        std::vector <float> value = i->second;
        for (float j= 0; j < value.size(); j += 5) {
            glm::vec4 result = model * glm::vec4(value[j], value[j + 1], value[j + 2], 1.0f);
            container_vertex[key][j] = result.x;
            container_vertex[key][j + 1] = result.y;
            container_vertex[key][j + 2] = result.z;
        }
    }
}

#endif