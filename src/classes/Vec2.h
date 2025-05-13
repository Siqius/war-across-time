#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    int _x;
    int _y;
    float _rotation;

public:
    Vec2(int x = 0, int y = 0);

    // Setters
    void x(int value);
    void y(int value);
    void rotation(float value);

    // Getters
    int x() const;
    int y() const;
    float rotation() const;
};

#endif