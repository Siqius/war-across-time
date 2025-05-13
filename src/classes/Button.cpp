#include "Button.h"

#include <iostream>

#include "Game.h"

Button::Button(int x, int y, int width, int height, Texture2D texture, Sound sound, void (*callback)())
    : Gameobject(x, y, width, height, texture), callback(callback), _sound(sound) {
    Game::add_button(*this);
}

bool Button::is_hovering(int mouseX, int mouseY) {
    if (mouseX > vector2().x() - (transform().width() / 2) &&
        mouseX < vector2().x() + (transform().width() / 2) &&
        mouseY > vector2().y() - (transform().height() / 2) &&
        mouseY < vector2().y() + (transform().height() / 2)) {
        _is_hovering = true;
    }else {
        _is_hovering = false;
    }
    return _is_hovering;
}