#ifndef CUBE_H
#define CUBE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <typeinfo>

#include "value.h"
#include "color.h"

typedef std::map< int, std::pair< char, char > > Color;
typedef std::map< char, std::vector< float > > Face;
typedef std::map< char, std::string > Texture;

typedef std::pair< char, std::string > Feature;

class Cube {
public:
    char id;

    // OpenGL
    unsigned int VBO[6];
    unsigned int VAO[6];    
    GLuint* textures;    

    // Atributos
    Face container_vertex;
    Color container_colors;             
    Texture container_textures;

    Cube(char cube_id, std::vector<Feature > features);

    // OpenGL
    void init_GL();
    void draw_GL();
    void delete_buffer_GL();
    void reset();

    char get_color(char group_id);
    int find_color(char group_id);
    int find_color(char color_id, char group_id);

    void info();
    void translation(glm::vec3 pos);
    void rotation(glm::vec3 axis, float angle);
    void transformation(glm::vec3 axis, glm::vec3 pos, bool rounded);

private:
    void define_features(std::vector<Feature > features);
    void update_vertex(glm::mat4 model);
    void update_vertex_rounded(glm::mat4 model);
};

Cube::Cube(char cube_id, std::vector<Feature > features) {    
    this->id = cube_id;
    textures = new GLuint[6];

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


void Cube::init_GL() {
    glGenVertexArrays(6, VAO);
    glGenBuffers(6, VBO);

    glGenTextures(6, textures);

    int counter = 0;
    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        // Cara del cubo 
        char key = i->first;        
                
        std::string texture = (container_textures.find(key) != container_textures.end()) 
                                ? params::texture_path + container_textures[key] 
                                : params::texture_path + "null/null.png";

        glBindVertexArray(VAO[counter]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[counter]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i->second.size(), static_cast<void*>(i->second.data()), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // Texturas
        glBindTexture(GL_TEXTURE_2D, textures[counter]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); 

        unsigned char* data = stbi_load(texture.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);                
        counter++;
    }
}

void Cube::draw_GL() {
    int counter = 0;
    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        char face_id = i->first;
        glBindBuffer(GL_ARRAY_BUFFER, VBO[counter]);
        glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(float) * container_vertex[face_id].size(), 
            static_cast<void*>(container_vertex[face_id].data()), 
            GL_STATIC_DRAW
        );

        glBindTexture(GL_TEXTURE_2D, textures[counter]);
        glBindVertexArray(VAO[counter]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        counter++;
    }
}

void Cube::delete_buffer_GL() {
    glDeleteVertexArrays(6, VAO);
    glDeleteBuffers(6, VBO);
}

void Cube::reset() {
    // Asignando a cada cara del cubo los vertices definidos en value.h
    //params::texture_path
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    std::string reset_img = params::texture_path + "O/5.png";
    unsigned char* data = stbi_load(reset_img.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

int Cube::find_color(char group_id) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;
        if (tmp_pair.second == group_id) {
            return iter->first;
        }
    }
    return 3;
}

int Cube::find_color(char color_id, char group_id) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;
        if (tmp_pair.first == color_id && tmp_pair.second == group_id) {
            return iter->first;
        }
    }
    return 3;
}

// Retorna el color que se esta mostrando en el grupo (group_id)
char Cube::get_color(char group_id) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp = iter->second;
        if (tmp.second == group_id)
            return tmp.first;
    }
    return 'X';
}


// Muestra informacion del cubo como su ID y colores
void Cube::info() {
    std::cout << "   + CUBO: " << id << std::endl;
    //for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        //std::pair<char, char > tmp_pair = iter->second;
        //std::cout << "   + Color: " << tmp_pair.first << " - " << " Posicion: " << tmp_pair.second << std::endl;
    //}    
    std::cout << "=============================================" << std::endl;
    for (auto iter = container_vertex.begin(); iter != container_vertex.end(); ++iter) {
        std::vector<float> current_face = iter->second;
        std::cout << "LADO: " << iter->first << std::endl;
        std::vector<float> tmp = container_vertex[iter->first];
        for (int i = 0; i < tmp.size(); i+=5) {
            std::cout << "Vertice (" << tmp[i] << " , " << tmp[i + 1] << " , " << tmp[i + 2];
            std::cout << " <=> Textura (" << tmp[i + 3] << " , " << tmp[i + 4] << ")" << std::endl;
        }
    }
}

// Recibe una matriz de transformacion que multiplcara a cada vertice del cubo
void Cube::update_vertex(glm::mat4 model) { 
    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        char key = i->first;
        std::vector <float> value = i->second;
        for (float j = 0; j < value.size(); j += 5) {
            glm::vec4 result = model * glm::vec4(value[j], value[j + 1], value[j + 2], 1.0f);
            container_vertex[key][j] = result.x;
            container_vertex[key][j + 1] = result.y;
            container_vertex[key][j + 2] = result.z;
        }
    }
}

// Recibe una matriz de transformacion que multiplcara a cada vertice del cubo
void Cube::update_vertex_rounded(glm::mat4 model) {
    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        char key = i->first;
        std::vector <float> value = i->second;
        for (float j = 0; j < value.size(); j += 5) {
            glm::vec4 result = model * glm::vec4(value[j], value[j + 1], value[j + 2], 1.0f);
            container_vertex[key][j] = glm::round(result.x);
            container_vertex[key][j + 1] = glm::round(result.y);
            container_vertex[key][j + 2] = glm::round(result.z);
        }
    }
}

void Cube::translation(glm::vec3 pos) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    update_vertex(model);
}

void Cube::rotation(glm::vec3 axis, float angle) {    
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
    update_vertex(model);
}

void Cube::transformation(glm::vec3 axis, glm::vec3 pos, bool rounded) {
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), axis);
    model = glm::translate(model, pos);
    if (!rounded) {
        update_vertex(model);
    }
    else {
        update_vertex_rounded(model);
    }
}

#endif