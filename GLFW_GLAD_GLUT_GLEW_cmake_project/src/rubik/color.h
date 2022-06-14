#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <map>

namespace color {    
    typedef std::map<char, std::pair<int, std::vector<float> > > MapColor;
    typedef std::map<char, char> MapGroup;

    // Definimos la relacion color - grupo
    MapGroup encode_group() {
        MapGroup group;
        group['W'] = 'U'; // White  - Up
        group['B'] = 'L'; // Blue   - Left
        group['O'] = 'F'; // Orange - Front
        group['G'] = 'R'; // Green  - Right
        group['R'] = 'B'; // Red    - Back
        group['Y'] = 'D'; // Yellow - Down
        return group;
    }

    // Asignanos a cada color(char) un pair, que consta de un indice(int) y codigo RGB (vector)
    MapColor encode_RGB() {
        //encode[color] = < indice, <vec_RGB> >
        MapColor encode;
        encode.insert({ 'W', {0, { 1.00f, 1.00f, 1.00f }} });   // White
        encode.insert({ 'B', {1, { 0.00f, 0.26f, 0.68f }} });   // Blue
        encode.insert({ 'O', {2, { 1.00f, 0.34f, 0.00f }} });   // Orange
        encode.insert({ 'G', {3, { 0.00f, 0.61f, 0.27f }} });   // Green 
        encode.insert({ 'R', {4, { 0.72f, 0.04f, 0.19f }} });   // Red
        encode.insert({ 'Y', {5, { 1.00f, 0.83f, 0.00f }} });   // Yellow
        return encode;
    } 

    //Fuente: https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
    std::map<char, char*> console_colors = {
        {'W', "\x1B[37m %c\033[0m |"},
        {'O', "\x1B[35m %c\033[0m |"},
        {'B', "\x1B[34m %c\033[0m |"},
        {'G', "\x1B[32m %c\033[0m |"},
        {'R', "\x1B[31m %c\033[0m |"},
        {'Y', "\x1B[33m %c\033[0m |"}
    };
}

#endif