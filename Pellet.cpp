#include "Pellet.hpp"
#include "SDL.h"
#include "SDL_image.h"

Pellet::~Pellet() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
Pellet::Pellet(float x, float y, float velX, float velY)
    : posX(x), posY(y), velocityX(velX), velocityY(velY){

}

void Pellet::update(float x, float y, int windowWidth, int windowHeight) {
    posX = x;
    posY = y;
    std::cout << posX << "\n";
    std::cout << posY << "\n";
    if (posX > (windowWidth) || posY > (windowHeight)) {
        isOutOfBoundaries = true;
    }
    if (posX < 0 || posY < 0) {
        isOutOfBoundaries = true;
    }
}

void Pellet::render(SDL_Renderer* renderer, float x, float y, SDL_Texture* texture) {
    SDL_Rect rect{ posX, posY, radius, radius };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Pellet::deleteTexture(SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
}
SDL_Texture* Pellet::getTexture() const {
    return texture;
}


