#ifndef Ball_hpp
#define Ball_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>

class Ball {
public:

    Ball();

    void update(int windowWidth, int windowHeight, float deltaTime);

    void render(SDL_Renderer* renderer, int x, int y);

    SDL_Texture* getTexture() const;

    void deleteTexture(SDL_Texture* texture);

    bool isOutOfBoundaries = false;
    bool isHit = false;
    int ballX = 200;
    int ballY = 43;
    float radius = 100;
private:
    float deltaTime;
    int width = radius;
    int height = radius;


    int velocityX = 2;
    int velocityY = 2;

    float time = 0;

    int mouseX = 0, mouseY = 0;
    int offsetCorrectionX = 0, offsetCorrectionY = 0;

    SDL_Texture* texture = nullptr;
};

#endif // Ball_hpp
