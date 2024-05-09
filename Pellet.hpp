#ifndef PELLET_HPP
#define PELLET_HPP

#include "SDL.h"
#include <iostream>

class Pellet {
public:
    ~Pellet();
    Pellet(float x, float y, float velX, float velY);
    void update(float x, float y, int windowWidth, int windowHieght);
    void render(SDL_Renderer* renderer, float x, float y, SDL_Texture* texture);
    void deleteTexture(SDL_Texture* texture);
    SDL_Texture* getTexture() const;
    bool isOutOfBoundaries = false;

private:
    float posX;
    float posY;
    float velocityX;
    float velocityY;
    float radius = 20;

    SDL_Texture* texture = nullptr;
};

#endif // PELLET_HPP
