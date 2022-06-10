#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <map>

namespace group {
    typedef std::map<char, glm::vec3 > MapGroup;
    typedef std::map<char, std::vector<char> > VecGroup;

    MapGroup define_rotation_axis() {
        MapGroup groups;
        groups['R'] = glm::vec3(1.0f, 0.0f, 0.0f); // Right
        groups['L'] = glm::vec3(1.0f, 0.0f, 0.0f); // Left
        groups['F'] = glm::vec3(0.0f, 0.0f, 1.0f); // Front
        groups['B'] = glm::vec3(0.0f, 0.0f, 1.0f); // Bottom
        groups['T'] = glm::vec3(0.0f, 1.0f, 0.0f); // Top
        groups['D'] = glm::vec3(0.0f, 1.0f, 0.0f); // Down
        return groups;
    }

    MapGroup define_translation_pos() {
        MapGroup groups;
        groups['R'] = glm::vec3( 0.000f,  0.095f, 0.080f); // Right
        groups['L'] = glm::vec3( 0.000f,  0.095f, 0.080f); // Left
        groups['F'] = glm::vec3(-0.095f, -0.080f, 0.000f); // Front
        groups['B'] = glm::vec3(-0.095f, -0.080f, 0.000f); // Bottom
        groups['T'] = glm::vec3(-0.095f,  0.000f, 0.080f); // Top
        groups['D'] = glm::vec3(-0.095f,  0.000f, 0.080f); // Down
        return groups;
    }

    VecGroup default_groups() {
        VecGroup group;
        group['R'] = { 'T', 'W', 'Z', 'L', 'N', 'Q', 'C', 'F', 'I' }; // Right
        group['L'] = { 'R', 'U', 'X', 'J', 'M', 'O', 'A', 'D', 'G' }; // Left
        group['F'] = { 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' }; // Front        
        group['B'] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' }; // Bottom
        group['T'] = { 'R', 'S', 'T', 'J', 'K', 'L', 'A', 'B', 'C' }; // Top
        group['D'] = { 'X', 'Y', 'Z', 'O', 'P', 'Q', 'G', 'H', 'I' }; // Down
        return group;
    }
}

#endif