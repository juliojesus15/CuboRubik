#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <map>

namespace color {

    typedef std::map<char, std::vector<float> > MapCode;
    typedef std::map<char, int> MapColor;

    MapColor define_ids() {
        MapColor codes;
        codes['W'] = 0; // White
        codes['B'] = 1; // Blue
        codes['O'] = 2; // Orange
        codes['G'] = 3; // Green
        codes['R'] = 4; // Red
        codes['Y'] = 5; // Yellow
        return codes;
    }

    MapColor define_encode() {
        MapColor codes;
        codes['W'] = 1; // White
        codes['B'] = 2; // Blue
        codes['O'] = 3; // Orange
        codes['G'] = 4; // Green
        codes['R'] = 5; // Red
        codes['Y'] = 6; // Yellow
        return codes;
    }

    MapCode define_codes() {
        MapCode codes;
        codes['W'] = { 1.00f, 1.00f, 1.00f }; // White
        codes['O'] = { 1.00f, 0.34f, 0.00f }; // Orange
        codes['G'] = { 0.00f, 0.61f, 0.27f }; // Green
        codes['R'] = { 0.72f, 0.04f, 0.19f }; // Red
        codes['B'] = { 0.00f, 0.26f, 0.68f }; // Blue
        codes['Y'] = { 1.00f, 0.83f, 0.00f }; // Yellow
        return codes;
    } 
}

#endif