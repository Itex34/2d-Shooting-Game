#ifndef PELLET_HPP
#define PELLET_HPP

#include "SDL.h"
#include <iostream>

class Pellet {
public:
    Pellet(float x, float y, float velX, float velY);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void addForce(float deltaTime);

private:
    float posX;
    float posY;
    float velocityX;
    float velocityY;
    float radius = 20;

    SDL_Texture* texture = nullptr;
};

#endif // PELLET_HPP
