#include "Pellet.hpp"
#include "Gun.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
extern Gun* gun;
Pellet::~Pellet() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
Pellet::Pellet(float x, float y)
    : posX(x), posY(y) {

}

void Pellet::update(float x, float y, int windowWidth, int windowHeight) {
    posX = x;
    posY = y;

    if (posX > (gun->gunX + 1000) || posY > (gun->gunY + 1000)) {
        isOutOfBoundaries = true;
    }
    if (posX < (gun->gunX - 1000) || posY < (gun->gunY - 1000)) {
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
