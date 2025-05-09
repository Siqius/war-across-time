#ifndef BUTTON_H
#define BUTTON_H
#include "Gameobject.h"
#include "raylib.h"


class Button : public Gameobject {
    void (*callback)();
    Sound _sound;

    public:
        Button(int x, int y, int width, int height, Texture2D image, Sound sound, void (*callback)());
};


#endif