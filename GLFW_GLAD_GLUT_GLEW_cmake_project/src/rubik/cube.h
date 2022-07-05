#ifndef CUBE_H
#define CUBE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "value.h"
#include "color.h"

typedef std::map< int, std::pair< char, char > > MapColor;
typedef std::map< char, std::vector< float > > MapFace;
typedef std::map< char, std::string > MapTexture;

typedef std::pair< char, std::string > Feature;

class Cube {
public:
    char id;

    // OpenGL 
    unsigned int VBO[6];
    unsigned int VAO[6];    
    GLuint* textures;    

    // Atributos
    MapFace container_vertex;       // Aplicamos las transformaciones
    MapColor container_colors;      // Indetificar el color para enviar al solver
    MapTexture container_textures;  // Texturas de cada cara del cubo (L, R, ...)

    Cube(char cube_id, std::vector<Feature > features);

    // OpenGL*
    void init_GL();
    void draw_GL();
    void delete_buffer_GL();

    // Transformaciones*
    void transformation_t(glm::vec3 pos);
    void transformation_ts(glm::vec3 pos, float threshold, bool dir, bool rounded);
    void transformation_rt(glm::vec3 axis, glm::vec3 pos, bool rounded);

    // Metodos usado para actualizar las camadas
    char get_color(char face);
    int find_color(char group_id);
    int find_color(char color_id, char group_id);

    void info() {
        std::cout << "   + CUBO: " << id << std::endl;
        //for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
            //std::pair<char, char > tmp_pair = iter->second;
            //std::cout << "   + Color: " << tmp_pair.first << " - " << " Posicion: " << tmp_pair.second << std::endl;
        //}    
        std::cout << "=============================================" << std::endl;
        for (auto iter = container_vertex.begin(); iter != container_vertex.end(); ++iter) {
            std::vector<float> current_face = iter->second;
            if (iter->first == 'L') {
                std::cout << "LADO: " << iter->first << std::endl;
                std::vector<float> tmp = container_vertex[iter->first];
                std::cout << "Vertice (" << tmp[5] << " , " << tmp[6] << " , " << tmp[7] << " )" << std::endl;
            }
            //std::vector<float> tmp = container_vertex[iter->first];
            /*for (int i = 0; i < tmp.size(); i += 5) {
                if(iter->first == 'L')
                    std::cout << "Vertice (" << tmp[i] << " , " << tmp[i + 1] << " , " << tmp[i + 2] << " )" << std::endl;
                //std::cout << " <=> Textura (" << tmp[i + 3] << " , " << tmp[i + 4] << ")" << std::endl;
            }*/
        }
    }

private:
    void set_features(std::vector<Feature > features);
    void update_vertex(glm::mat4 model, bool rounded);
};

Cube::Cube(char cube_id, std::vector<Feature > features) {    
    this->id = cube_id;
    textures = new GLuint[6];

    // Asignando a cada cara del cubo los vertices pre definidos en value.h
    container_vertex['F'] = values::vertex_front_face;
    container_vertex['B'] = values::vertex_back_face;
    container_vertex['R'] = values::vertex_right_face;
    container_vertex['L'] = values::vertex_left_face;
    container_vertex['D'] = values::vertex_down_face;
    container_vertex['U'] = values::vertex_up_face;

    set_features(features);
}

// Almacenamos las texturas, colores y caras de cada elemento de la lista en su respectivo contenedor
void Cube::set_features(std::vector< Feature > features) {
    std::map<char, char> color_encode = color::encode_color;
    
    for (int i = 0; i < features.size(); i++) {
        char color = features[i].first;
        char face = color_encode[color];
        container_colors[i] = std::pair<char, char>(color, face);

        std::string texture = features[i].second;            
        container_textures[face] = texture;
    }
}

// Utils* 
// -------------------------------------------------------------------------------
int Cube::find_color(char face) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;
        if (tmp_pair.second == face)
            return iter->first;
    }
    return 3;
}

int Cube::find_color(char color, char face) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;
        if (tmp_pair.first == color && tmp_pair.second == face)
            return iter->first;
    }
    return 3;
}

char Cube::get_color(char face) {
    for (auto iter = container_colors.begin(); iter != container_colors.end(); ++iter) {
        std::pair<char, char > tmp_pair = iter->second;
        if (tmp_pair.second == face)
            return tmp_pair.first;
    }
    return 'X';
}

// TRANFFORMACIONES* 
// -------------------------------------------------------------------------------

// Recibe una matriz de transformacion que se aplicara a cada vertice del cubo
void Cube::update_vertex(glm::mat4 model, bool rounded) { 
    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        char key = i->first;
        std::vector <float> value = i->second;
        for (float j = 0; j < value.size(); j += 5) {
            glm::vec4 result = model * glm::vec4(value[j], value[j + 1], value[j + 2], 1.0f);
            container_vertex[key][j] = !rounded ? result.x : glm::round(result.x);
            container_vertex[key][j + 1] = !rounded ? result.y : glm::round(result.y);
            container_vertex[key][j + 2] = !rounded ? result.z : glm::round(result.z);
        }
    }
}

// Realiza una traslacion en base al parametro pos
void Cube::transformation_t(glm::vec3 pos) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    update_vertex(model, false);
}

// Realiza una traslacion en base al parametro pos
// Threshold es el tamaño de la escala 
// Dir indica si el objeto escala a un mayor o menor tamaño (True +, False -)
void Cube::transformation_ts(glm::vec3 pos, float threshold, bool dir, bool rounded) {
    glm::vec3 scale = dir 
                      ? glm::vec3(1.0f + threshold, 1.0f + threshold, 1.0f + threshold) 
                      : glm::vec3(1.0f - threshold, 1.0f - threshold, 1.0f - threshold);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::scale(model, scale);       
    update_vertex(model, rounded);
}

// Realiza una rotacion en base al parametro axis
// Realiza una traslacion en base al parametro pos
void Cube::transformation_rt(glm::vec3 axis, glm::vec3 pos, bool rounded) {
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), axis);
    model = glm::translate(model, pos);    
    update_vertex(model, rounded);
}

// OPENGL*  
// -------------------------------------------------------------------------------

// Inicializamos la configuracion del VBO, VAO y texturas
void Cube::init_GL() {
    glGenVertexArrays(6, VAO);
    glGenBuffers(6, VBO);
    glGenTextures(6, textures);

    int num_texture = 0;
    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        // Cara del cubo 
        char key = i->first;        
                
        std::string texture = (container_textures.find(key) != container_textures.end()) 
                                ? params::texture_path + container_textures[key] 
                                : params::texture_path + "null/null.png";

        glBindVertexArray(VAO[num_texture]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[num_texture]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i->second.size(), static_cast<void*>(i->second.data()), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // Texture
        glBindTexture(GL_TEXTURE_2D, textures[num_texture]);
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
        num_texture++;
    }
}

// Render cubo
void Cube::draw_GL() {
    int counter = 0;
    for (auto i = container_vertex.begin(); i != container_vertex.end(); ++i) {
        // Actualizando los valores del VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO[counter]);        
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i->second.size(), static_cast<void*>(i->second.data()), GL_STATIC_DRAW);
        
        // Render
        glBindTexture(GL_TEXTURE_2D, textures[counter]);        
        glBindVertexArray(VAO[counter]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        counter++;
    }
}

// Desasignar todos los recursos una vez que hayan superado su propósito
void Cube::delete_buffer_GL() {
    glDeleteVertexArrays(6, VAO);
    glDeleteBuffers(6, VBO);
}

#endif