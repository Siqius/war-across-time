#include "Transf.h"

Transf::Transf(const int width, const int height) : _width(width), _height(height) { }

// Getters

int Transf::width() const {
    return _width;
}

int Transf::height() const {
    return _height;
}

// Setters

void Transf::width(int value) {
    _width = value;
}

void Transf::height(int value) {
    _height = value;
}