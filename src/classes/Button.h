#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "Gameobject.h"
#include "raylib.h"


class Button : public Gameobject {
    const Sound* _sound;
    bool _is_hovering = false;
    int _callback_param;

public:
    Button(int x, int y, int width, int height, const Texture2D* texture, const Sound* sound, std::function<void()> callback);

    std::function<void()> callback;

    bool is_hovering(int mouseX, int mouseY);
};


#endif