#include "Button.h"

Button::Button(int x, int y, int width, int height, Texture2D texture, Sound sound, void (*callback)())
    : Gameobject(x, y, width, height, texture), _sound(sound), callback(callback) { }

