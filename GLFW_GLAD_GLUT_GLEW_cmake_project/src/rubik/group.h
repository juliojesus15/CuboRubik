#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <map>

namespace group {
    typedef std::vector<char> VecChar;
    typedef std::map<char, VecChar > ContainerVecChar;

    // Orden de los cubos asignados a cada grupo (camada) en un inicio
    // -------------------------------------------------------------------------------------
    ContainerVecChar default_groups = {
        {'R', { 'T', 'L', 'C', 'F', 'I', 'Q', 'Z', 'W', 'N' }}, // Right
        {'L', { 'A', 'J', 'R', 'U', 'X', 'O', 'G', 'D', 'M' }}, // Left
        {'F', { 'R', 'S', 'T', 'W', 'Z', 'Y', 'X', 'U', 'V' }}, // Front
        {'B', { 'C', 'B', 'A', 'D', 'G', 'H', 'I', 'F', 'E' }}, // Bottom
        {'U', { 'A', 'B', 'C', 'L', 'T', 'S', 'R', 'J', 'K' }}, // Top
        {'D', { 'X', 'Y', 'Z', 'Q', 'I', 'H', 'G', 'O', 'P' }}  // Down
    };

    
    // Valores para realizar la rotacion y traslacion de un grupo
    // -------------------------------------------------------------------------------------
    // Valores para realizar las rotaciones sobre los grupos(camadas)
    std::map<char, glm::vec3 > rotation_axis_inverted = {
        {'L', glm::vec3(-1.0f,  0.0f,  0.0f) }, // Left
        {'R', glm::vec3( 1.0f,  0.0f,  0.0f) }, // Right
        {'F', glm::vec3( 0.0f,  0.0f,  1.0f) }, // Front
        {'B', glm::vec3( 0.0f,  0.0f, -1.0f) }, // Bottom
        {'U', glm::vec3( 0.0f,  1.0f,  0.0f) }, // Top
        {'D', glm::vec3( 0.0f, -1.0f,  0.0f) }  // Down
    };

    std::map<char, glm::vec3 > rotation_axis_clockwise = {
        {'L', glm::vec3( 1.0f,  0.0f,  0.0f)}, // Left
        {'R', glm::vec3(-1.0f,  0.0f,  0.0f)}, // Right
        {'F', glm::vec3( 0.0f,  0.0f, -1.0f)}, // Front
        {'B', glm::vec3( 0.0f,  0.0f,  1.0f)}, // Bottom
        {'U', glm::vec3( 0.0f, -1.0f,  0.0f)}, // Top
        {'D', glm::vec3( 0.0f,  1.0f,  0.0f)}  // Down
    };

    std::map<char, glm::vec3 > translation_pos_inverted = {
        {'L', glm::vec3( 0.000f, -0.080f, -0.095f)}, // Left
        {'R', glm::vec3( 0.000f,  0.095f,  0.080f)}, // Right
        {'F', glm::vec3(-0.095f, -0.080f,  0.000f)}, // Front
        {'B', glm::vec3( 0.080f,  0.095f,  0.000f)}, // Bottom
        {'U', glm::vec3(-0.095f,  0.000f,  0.080f)}, // Top
        {'D', glm::vec3( 0.080f,  0.000f, -0.095f)}  // Down
    };

    std::map<char, glm::vec3 > translation_pos_clockwise = {
        {'L', glm::vec3( 0.000f,  0.095f,  0.080f)}, // Left
        {'R', glm::vec3( 0.000f, -0.080f, -0.095f)}, // Right
        {'F', glm::vec3( 0.080f,  0.095f,  0.000f)}, // Front
        {'B', glm::vec3(-0.095f, -0.080f,  0.000f)}, // Bottom
        {'U', glm::vec3( 0.080f,  0.000f, -0.095f)}, // Top
        {'D', glm::vec3(-0.095f,  0.000f,  0.080f)}  // Down
    };

    
    // Valores para realizar la actualizacion de los grupos luego de una rotacion y traslacion
    // -------------------------------------------------------------------------------------
    // Orden de rotacion en sentido horario
    VecChar rotation_clockwise(char group_id) {
        ContainerVecChar group;
        group['R'] = { 'U', 'U', 'U', 'B', 'B', 'B', 'D', 'D', 'D', 'F', 'F', 'F', 'U', 'U', 'U' };
        group['L'] = { 'U', 'U', 'U', 'F', 'F', 'F', 'D', 'D', 'D', 'B', 'B', 'B', 'U', 'U', 'U' };
        group['F'] = { 'U', 'U', 'U', 'R', 'R', 'R', 'D', 'D', 'D', 'L', 'L', 'L', 'U', 'U', 'U' };
        group['B'] = { 'U', 'U', 'U', 'L', 'L', 'L', 'D', 'D', 'D', 'R', 'R', 'R', 'U', 'U', 'U' };
        group['U'] = { 'B', 'B', 'B', 'R', 'R', 'R', 'F', 'F', 'F', 'L', 'L', 'L', 'B', 'B', 'B' };
        group['D'] = { 'F', 'F', 'F', 'R', 'R', 'R', 'B', 'B', 'B', 'L', 'L', 'L', 'F', 'F', 'F' };
        return group[group_id];
    }

    // Orden de rotacion en sentido anti horario
    VecChar rotation_inverted(char group_id) {
        ContainerVecChar group;
        group['R'] = { 'U', 'U', 'U', 'F', 'F', 'F', 'D', 'D', 'D', 'B', 'B', 'B', 'U', 'U', 'U' };
        group['L'] = { 'U', 'U', 'U', 'B', 'B', 'B', 'D', 'D', 'D', 'F', 'F', 'F', 'U', 'U', 'U' };
        group['F'] = { 'U', 'U', 'U', 'L', 'L', 'L', 'D', 'D', 'D', 'R', 'R', 'R', 'U', 'U', 'U' };
        group['B'] = { 'U', 'U', 'U', 'R', 'R', 'R', 'D', 'D', 'D', 'L', 'L', 'L', 'U', 'U', 'U' };
        group['U'] = { 'B', 'B', 'B', 'L', 'L', 'L', 'F', 'F', 'F', 'R', 'R', 'R', 'B', 'B', 'B' };
        group['D'] = { 'F', 'F', 'F', 'L', 'L', 'L', 'B', 'B', 'B', 'R', 'R', 'R', 'F', 'F', 'F' };
        return group[group_id];
    }


    // Valores para mapear la salida del solver a una rotacion de un grupo
    // -------------------------------------------------------------------------------------
    std::map<std::string, std::pair<char, bool> > movements = {        
        // Doble rotacion
        { "L2", {'L', true }}, 
        { "R2", {'R', true }}, 
        { "F2", {'F', true }},
        { "B2", {'B', true }}, 
        { "U2", {'U', true }}, 
        { "D2", {'D', true }},      
        // Sentido horario
        { "L", { 'L', true }}, 
        { "R", { 'R', true }}, 
        { "F", { 'F', true }},
        { "B", { 'B', true }}, 
        { "U", { 'U', true }}, 
        { "D", { 'D', true }},
        // Sentido inverso
        { "L'", {'L', false }}, 
        { "R'", {'R', false }}, 
        { "F'", {'F', false }},
        { "B'", {'B', false }}, 
        { "U'", {'U', false }}, 
        { "D'", {'D', false }},
    };
}

#endif