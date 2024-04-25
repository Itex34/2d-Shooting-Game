#include "Pellet.hpp"
#include "SDL.h"
#include "SDL_image.h"

Pellet::Pellet(float x, float y, float velX, float velY)
    : posX(x), posY(y), velocityX(velX), velocityY(velY) {
}

void Pellet::update(float deltaTime) {
    // Update the position of the pellet based on its velocity
    posX += velocityX * deltaTime;
    posY += velocityY * deltaTime;
}

void Pellet::render(SDL_Renderer* renderer) {


    if (texture == nullptr) {
        SDL_Surface* imageSurface = IMG_Load("ball.png");
        if (imageSurface == NULL) {
            printf("Unable to load image: %s\n", IMG_GetError());
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
    }

    if (texture == nullptr) {
        printf("Failed to create pellet texture: %s\n", SDL_GetError());
        return;
    }
    SDL_Rect rect{ posX, posY, radius, radius };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

}

void Pellet::addForce(float deltaTime) {

}
