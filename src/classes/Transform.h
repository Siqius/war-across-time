#ifndef TRANSFORM_H
#define TRANSFORM_H



class Transform {
    private:
        int _width;
        int _height;
    public:
        int height() const;
        void height(int value);

        int width() const;
        void width(int value);
};



#endif //TRANSFORM_H
