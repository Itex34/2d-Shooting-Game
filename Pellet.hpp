#ifndef PELLET_HPP
#define PELLET_HPP

#include "SDL2/SDL.h"
#include <iostream>
class Gun;
class Pellet {
public:
    ~Pellet();
    Pellet(float x, float y);
    void update(float x, float y, int windowWidth, int windowHieght);
    void render(SDL_Renderer* renderer, float x, float y, SDL_Texture* texture);
    void deleteTexture(SDL_Texture* texture);
    SDL_Texture* getTexture() const;
    bool isOutOfBoundaries = false;// <- this boolean will be set to true if the pellet is out of the "reload boundaries", this way we can shoot again once the bool is true
    //albeit bad, it's basically a way of having a reload time, see how it works in pellet.cpp at lines 21 to 26
    //i couldn't find a better and more precise way of doing this, if you have any idea, tell me on github

    float radius = 20;
private:
    float posX;
    float posY;


    SDL_Texture* texture = nullptr;
};

#endif // PELLET_HPP
