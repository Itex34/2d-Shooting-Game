#include "Ball.hpp"
#include <cmath>

Ball::Ball() {}

void Ball::update(int windowWidth, int windowHeight, float deltaTime) {

    double deltaX = velocityX * deltaTime * 200;
    double deltaY = velocityY * deltaTime * 200;

    offsetCorrectionX = width / 2;
    offsetCorrectionY = height / 2;

    time += deltaTime;

    ballY += deltaX;
}

void Ball::render(SDL_Renderer* renderer, int x, int y) {
    if(isHit == false)
    {
        x += ballX;
        y += ballY;
        if (x < 0) {
            isOutOfBoundaries = true;
        }
        if (texture == nullptr) {
            SDL_Surface* imageSurface = IMG_Load("ball.png");
            if (imageSurface == NULL) {
                printf("Unable to load image: %s\n", IMG_GetError());
                return;
            }
            texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
            SDL_FreeSurface(imageSurface);
        }

        // Check if texture is valid
        if (texture == nullptr) {
            printf("Failed to create texture: %s\n", SDL_GetError());
            return;
        }

        // Render ball
        SDL_Rect rect{ x, y, width, height };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}

SDL_Texture* Ball::getTexture() const {
    return texture;
}

void Ball::deleteTexture(SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
}
