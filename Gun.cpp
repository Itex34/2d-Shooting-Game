#include "Gun.hpp"
#include "Pellet.hpp"
#include "Game.hpp"
#include <cmath>
Pellet* pellet = nullptr;

Gun::Gun() {}

void Gun::update(int windowWidth, int windowHeight) {
    Uint32 prevTicks = SDL_GetTicks();
    Uint32 currentTicks = SDL_GetTicks();
    deltaTime = (currentTicks - prevTicks) / 1000.0f;
    prevTicks = currentTicks;
    // adjust gun position
    gunX = windowWidth / 2;
    gunY = windowHeight / 2 + 230;


        // get mouse position
    SDL_GetMouseState(&mouseX, &mouseY);

    // calculate angle between gun and mouse
    double dx = mouseX - gunX;
    double dy = mouseY - gunY;
    rotationAngle = atan2(dy, dx) * 180 / M_PI;

    // adjust for offset
    rotationAngle += angleOffsetCorrection;
    //shoot if clicked
    if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        shoot();
        std::cout << "click!" << std::endl;
    }

}

void Gun::render(SDL_Renderer* renderer) {
    if (texture == nullptr) {
        SDL_Surface* imageSurface = IMG_Load("shotgun.png");
        if (imageSurface == nullptr) {
            printf("Unable to load image: %s\n", IMG_GetError());
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if (texture == nullptr) {
            printf("Failed to create texture: %s\n", SDL_GetError());
            SDL_FreeSurface(imageSurface);
            return;
        }
        SDL_FreeSurface(imageSurface);
    }


    // calculate rendering position
    int renderX = gunX - width / 2;
    int renderY = gunY - height / 2;

    SDL_Rect rect{ renderX, renderY, width, height };

    // render the rotated texture
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotationAngle, nullptr, SDL_FLIP_NONE);

}
void Gun::shoot() {

    float pelletSpeed = 10.0f;
    float pelletVelX = pelletSpeed * cos(rotationAngle * M_PI / 180);
    float pelletVelY = pelletSpeed * sin(rotationAngle * M_PI / 180);

    delete pellet;
    pellet = new Pellet(gunX, gunY, pelletVelX, pelletVelY);

    SDL_RenderPresent(game->getRenderer());//here i need to access the game that i defined in the main.cpp file
    pellet->render(game->getRenderer());// here sa well

}

void Gun::cleanup() {
    if (pellet != nullptr) {
        delete pellet;
        pellet = nullptr;
    }
    if (gameTwo != nullptr) {
        delete gameTwo;
        gameTwo = nullptr;
    }
}
