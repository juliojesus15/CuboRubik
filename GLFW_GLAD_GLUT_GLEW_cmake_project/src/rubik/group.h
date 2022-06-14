#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <map>

namespace group {
    typedef std::map<char, glm::vec3 > MapGroup;
    typedef std::map<char, std::vector<char> > VecGroup;

    // Vec3 representa el eje donde se realizara la rotacion 
    MapGroup rotation_axis_inverted() {
        MapGroup groups;
        groups['L'] = glm::vec3(-1.0f,  0.0f,  0.0f); // Left
        groups['R'] = glm::vec3( 1.0f,  0.0f,  0.0f); // Right
        groups['F'] = glm::vec3( 0.0f,  0.0f,  1.0f); // Front
        groups['B'] = glm::vec3( 0.0f,  0.0f, -1.0f); // Bottom
        groups['U'] = glm::vec3( 0.0f,  1.0f,  0.0f); // Top
        groups['D'] = glm::vec3( 0.0f, -1.0f,  0.0f); // Down
        return groups;
    }

    MapGroup rotation_axis_clockwise() {
        MapGroup groups;
        groups['L'] = glm::vec3( 1.0f,  0.0f,  0.0f); // Left
        groups['R'] = glm::vec3(-1.0f,  0.0f,  0.0f); // Right
        groups['F'] = glm::vec3( 0.0f,  0.0f, -1.0f); // Front
        groups['B'] = glm::vec3( 0.0f,  0.0f,  1.0f); // Bottom
        groups['U'] = glm::vec3( 0.0f, -1.0f,  0.0f); // Top
        groups['D'] = glm::vec3( 0.0f,  1.0f,  0.0f); // Down
        return groups;
    }

    // Vec3 representa la posicion donde se realizara la traslacion 
    MapGroup translation_pos_inverted() {
        MapGroup groups;
        groups['L'] = glm::vec3( 0.000f, -0.080f, -0.095f); // Left
        groups['R'] = glm::vec3( 0.000f,  0.095f,  0.080f); // Right
        groups['F'] = glm::vec3(-0.095f, -0.080f,  0.000f); // Front
        groups['B'] = glm::vec3( 0.080f,  0.095f,  0.000f); // Bottom
        groups['U'] = glm::vec3(-0.095f,  0.000f,  0.080f); // Top
        groups['D'] = glm::vec3( 0.080f,  0.000f, -0.095f); // Down
        return groups;
    }

    MapGroup translation_pos_clockwise() {
        MapGroup groups;
        groups['L'] = glm::vec3( 0.000f,  0.095f,  0.080f); // Left
        groups['R'] = glm::vec3( 0.000f, -0.080f, -0.095f); // Right
        groups['F'] = glm::vec3( 0.080f,  0.095f,  0.000f); // Front
        groups['B'] = glm::vec3(-0.095f, -0.080f,  0.000f); // Bottom
        groups['U'] = glm::vec3( 0.080f,  0.000f, -0.095f); // Top
        groups['D'] = glm::vec3(-0.095f,  0.000f,  0.080f); // Down
        return groups;
    }

    // Orden de los cubos asignados a cada grupo o camada en un inicio
    VecGroup default_groups() {
        VecGroup group;        
        group['R'] = { 'T', 'L', 'C', 'F', 'I', 'Q', 'Z', 'W', 'N' }; // Right
        group['L'] = { 'A', 'J', 'R', 'U', 'X', 'O', 'G', 'D', 'M' }; // Left
        group['F'] = { 'R', 'S', 'T', 'W', 'Z', 'Y', 'X', 'U', 'V' }; // Front
        group['B'] = { 'C', 'B', 'A', 'D', 'G', 'H', 'I', 'F', 'E' }; // Bottom
        group['U'] = { 'A', 'B', 'C', 'L', 'T', 'S', 'R', 'J', 'K' }; // Top
        group['D'] = { 'X', 'Y', 'Z', 'Q', 'I', 'H', 'G', 'O', 'P' }; // Down
        
        return group;
    }

    // Orden de rotacion en sentido horario
    std::vector<char> rotation_clockwise(char group_id) {
        VecGroup group;
        group['R'] = { 'U', 'U', 'U', 'B', 'B', 'B', 'D', 'D', 'D', 'F', 'F', 'F', 'U', 'U', 'U' };
        group['L'] = { 'U', 'U', 'U', 'F', 'F', 'F', 'D', 'D', 'D', 'B', 'B', 'B', 'U', 'U', 'U' };
        group['F'] = { 'U', 'U', 'U', 'R', 'R', 'R', 'D', 'D', 'D', 'L', 'L', 'L', 'U', 'U', 'U' };
        group['B'] = { 'U', 'U', 'U', 'L', 'L', 'L', 'D', 'D', 'D', 'R', 'R', 'R', 'U', 'U', 'U' };
        group['U'] = { 'B', 'B', 'B', 'R', 'R', 'R', 'F', 'F', 'F', 'L', 'L', 'L', 'B', 'B', 'B' };
        group['D'] = { 'F', 'F', 'F', 'R', 'R', 'R', 'B', 'B', 'B', 'L', 'L', 'L', 'F', 'F', 'F' };
        return group[group_id];
    }

    // Orden de rotacion en sentido anti horario
    std::vector<char> rotation_inverted(char group_id) {
        VecGroup group;
        group['R'] = { 'U', 'U', 'U', 'F', 'F', 'F', 'D', 'D', 'D', 'B', 'B', 'B', 'U', 'U', 'U' };
        group['L'] = { 'U', 'U', 'U', 'B', 'B', 'B', 'D', 'D', 'D', 'F', 'F', 'F', 'U', 'U', 'U' };
        group['F'] = { 'U', 'U', 'U', 'L', 'L', 'L', 'D', 'D', 'D', 'R', 'R', 'R', 'U', 'U', 'U' };
        group['B'] = { 'U', 'U', 'U', 'R', 'R', 'R', 'D', 'D', 'D', 'L', 'L', 'L', 'U', 'U', 'U' };
        group['U'] = { 'B', 'B', 'B', 'L', 'L', 'L', 'F', 'F', 'F', 'R', 'R', 'R', 'B', 'B', 'B' };
        group['D'] = { 'F', 'F', 'F', 'L', 'L', 'L', 'B', 'B', 'B', 'R', 'R', 'R', 'F', 'F', 'F' };
        return group[group_id];
    }
}

#endif