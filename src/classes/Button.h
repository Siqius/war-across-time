#ifndef BUTTON_H
#define BUTTON_H

#include "Gameobject.h"
#include "raylib.h"


class Button : public Gameobject {
    Sound _sound;
    bool _is_hovering = false;

public:
    Button(int x, int y, int width, int height, Texture2D image, Sound sound, void (*callback)());

    void (*callback)();

    bool is_hovering(int mouseX, int mouseY);
};


#endif