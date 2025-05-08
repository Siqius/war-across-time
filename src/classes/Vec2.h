#ifndef VEC2_H
#define VEC2_H

class Vec2 {
private:
    int _x;
    int _y;
    float _facing;

public:
    Vec2(int x = 0, int y = 0); // Constructor with default values

    // Setters
    void x(int value);
    void y(int value);
    void facing(float value);

    // Getters
    int x() const;
    int y() const;
    float facing() const;
};

#endif // VEC2_H