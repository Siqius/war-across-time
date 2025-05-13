#ifndef TRANSF_H
#define TRANSF_H



class Transf {
    int _width;
    int _height;
public:
    Transf(int width, int height);

    // Getters
    int height() const;
    int width() const;

    // Setters
    void height(int value);
    void width(int value);
};



#endif
