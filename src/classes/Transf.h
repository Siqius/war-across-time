#ifndef TRANSF_H
#define TRANSF_H



class Transf {
    private:
        int _width;
        int _height;
    public:
        Transf(int width, int height);
        int height() const;
        void height(int value);

        int width() const;
        void width(int value);
};



#endif
