#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
    private:
        int _x;
        int _y;
        float _facing;
    public:
        void x(int value);
        int x() const { return _x; };

        void y(int value);
        int y() const;

        void facing(float value);
        float facing() const;
};

#endif //VECTOR2_H
