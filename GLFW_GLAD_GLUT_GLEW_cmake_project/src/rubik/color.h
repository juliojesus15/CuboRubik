#ifndef COLOR_H
#define COLOR_H

#include <map>

namespace color {    
    std::map<char, char> encode_color = {
        {'W','U'},  // White  - Up
        {'B','L'},  // Blue   - Left
        {'O','F'},  // Orange - Front
        {'G','R'},  // Green  - Right
        {'R','B'},  // Red    - Back
        {'Y','D'}   // Yellow - Down
    };

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