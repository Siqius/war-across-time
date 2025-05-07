#include "Vector2.h"
#include "raylib.h"
#ifndef TROOP_H
#define TROOP_H



class Troop {
    private:
        int width;
        int height;
        int speed;
        Texture2D texture;
        Vector2 position;
};



#endif //TROOP_H
