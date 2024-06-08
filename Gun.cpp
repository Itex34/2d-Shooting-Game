#include "Gun.hpp"
#include "Pellet.hpp"
#include "Game.hpp"
#include <cmath>
#include <memory>

Pellet* pellet = nullptr;
extern Game* game;
Gun::Gun() {}
Gun::~Gun() {}

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




    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    gunTipX = gunX + cos((rotationAngle - 60) * M_PI / 180) * 100;
    gunTipY = gunY + sin((rotationAngle - 60) * M_PI / 180) * 100;


    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (pellet == nullptr) {
            pelletIsVisible = false;

            pelletX = gunTipX;
            pelletY = gunTipY;

            initialRotationAngle = rotationAngle;
        }
    }


    if (game != nullptr)
    {
        if (pellet == nullptr)
        {
            pelletIsVisible = true;
            delete pellet;
            pellet = new Pellet(pelletX, pelletY);
        }

        if (pellet->isOutOfBoundaries == false)
        {
            createPelletTexture(renderer);
            pellet->render(game->getRenderer(), pelletX, pelletY, pelletTexture);
            pellet->update(pelletX, pelletY, windowWidth, windowHeight);

            pellet->render(game->getRenderer(), pelletX + (pelletVelX(80) - pelletVelX(47)), pelletY + (pelletVelY(80) - pelletVelY(47)), pelletTexture);
            pellet->update(pelletX + (pelletVelX(80) - pelletVelX(47)), pelletY + (pelletVelY(80) - pelletVelY(47)), windowWidth, windowHeight);

            pellet->render(game->getRenderer(), pelletX + (pelletVelX(10) - pelletVelX(47)), pelletY + (pelletVelY(10) - pelletVelY(47)), pelletTexture);
            pellet->update(pelletX + (pelletVelX(10) - pelletVelX(47)), pelletY + (pelletVelY(10) - pelletVelY(47)), windowWidth, windowHeight);

            pelletX += pelletVelX(47);
            pelletY += pelletVelY(47);

        }
        else {
            pelletIsVisible = false;
        }

    }


    int renderX = gunX - width / 2;
    int renderY = gunY - height / 2;


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


    else if (pellet != nullptr && pellet->isOutOfBoundaries == true) {
        pellet->deleteTexture(pellet->getTexture());
        delete pellet;
        pellet = nullptr;
    }


    SDL_Rect rect{ renderX, renderY, width, height };
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotationAngle, nullptr, SDL_FLIP_NONE);
}


void Gun::cleanup() {
    if (pellet != nullptr) {
        delete pellet;
        pellet = nullptr;
    }
}

void Gun::createPelletTexture(SDL_Renderer* renderer) {
    if (pelletIsVisible == true && pelletTexture == nullptr) {
        SDL_Surface* imageSurface = IMG_Load("ball.png");
        if (imageSurface == NULL) {
            printf("Unable to load image: %s\n", IMG_GetError());
            return;
        }
        pelletTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
    }

    if (pelletTexture == nullptr) {
        printf("Failed to create pellet texture: %s\n", SDL_GetError());
        return;
    }
}


float Gun::pelletVelX(float rotationOffset) {
    return pelletSpeed * cos((initialRotationAngle - rotationOffset) * M_PI / 180);
}
float Gun::pelletVelY(float rotationOffset) {
    return pelletSpeed * sin((initialRotationAngle - rotationOffset) * M_PI / 180);
}
