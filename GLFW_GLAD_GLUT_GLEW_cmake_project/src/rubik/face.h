#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

class Color {
public:
	Color(int encode, int id, std::vector<float> color);
	
	std::vector<float> color;
	int encode;
	int id;

};

Color::Color(int encode, int id, std::vector<float> color) {
	this->encode = encode;
	this->color = color;
	this->id = id;
}

#endif