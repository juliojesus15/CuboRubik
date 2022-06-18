#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <map>

namespace color {    
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