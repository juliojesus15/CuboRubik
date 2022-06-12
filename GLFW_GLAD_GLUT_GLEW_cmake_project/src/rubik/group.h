#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <map>

namespace group {
    typedef std::map<char, glm::vec3 > MapGroup;
    typedef std::map<char, std::vector<char> > VecGroup;

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

    std::vector<char> neighborhood(char group_id) {
        VecGroup group;
        group['R'] = { 'U', 'B', 'D', 'F', 'U'};
        group['L'] = { 'U', 'F', 'D', 'B', 'U'};
        group['F'] = { 'U', 'R', 'D', 'L', 'U'};
        group['B'] = { 'U', 'L', 'D', 'R', 'U'};
        group['U'] = { 'B', 'R', 'F', 'L', 'B'}; 
        group['D'] = { 'F', 'R', 'B', 'L', 'F'}; 

        return group[group_id];
    }
}

#endif