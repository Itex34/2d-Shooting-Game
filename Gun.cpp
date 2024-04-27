#include "Gun.hpp"
#include "Pellet.hpp"
#include "Game.hpp"
#include <cmath>
Pellet* pellet = nullptr;
extern Game* game;
Gun::Gun() {}

void Gun::update(int windowWidth, int windowHeight) {

    Uint32 prevTicks = SDL_GetTicks();
    Uint32 currentTicks = SDL_GetTicks();
    deltaTime = (currentTicks - prevTicks) / 1000.0f;
    prevTicks = currentTicks;

    gunX = windowWidth / 2;
    gunY = windowHeight / 2 + 230;

    SDL_GetMouseState(&mouseX, &mouseY);

    double dx = mouseX - gunX;
    double dy = mouseY - gunY;

    rotationAngle = atan2(dy, dx) * 180 / M_PI;
    rotationAngle += angleOffsetCorrection;



} 

void Gun::render(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    float pelletSpeed = 3.0f;
    float pelletVelX = pelletSpeed * cos((rotationAngle - 40.1) * M_PI / 180);
    float pelletVelY = pelletSpeed * sin((rotationAngle - 40.1) * M_PI / 180);
    //pelletX = 50;
    //pelletY = 50;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
        pelletX += pelletVelX;
        pelletY += pelletVelY;
    }
    if (game != nullptr)
    {
        delete pellet;
        pellet = new Pellet(pelletX, pelletY, pelletVelX, pelletVelY);
    }
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


    pellet->render(game->getRenderer(), pelletX, pelletY);//here i access the game that is defined in the main.cpp file 
    pellet->update(pelletX, pelletY);

    SDL_Rect rect{ renderX, renderY, width, height };

    // render the rotated texture
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotationAngle, nullptr, SDL_FLIP_NONE);

}
void Gun::shoot(int windowWidth, int windowHeight) {
        pellet->render(game->getRenderer(), pelletX, pelletY);//here i access the game that is defined in the main.cpp file 
        pellet->update(pelletX, pelletY);
}

void Gun::cleanup() {
    if (pellet != nullptr) {
        delete pellet;
        pellet = nullptr;
    }
    if (game != nullptr) {
        delete game;
        game = nullptr;
    }
}
