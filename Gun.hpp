#ifndef Gun_hpp
#define Gun_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <cmath>
class Game;
class Gun {
public:
    ~Gun();
    Gun();

    void update(int windowWidth, int windowHeight);
    void render(SDL_Renderer* renderer, int windowWidth, int windowHeight);
    void shoot(int windowWidth, int windowHeight);
    void cleanup();
    void createPelletTexture(SDL_Renderer* renderer);
private:
    int width = 200;
    int height = 200;
    int cnt = 0;

    int gunX = 550;
    int gunY = 400;

    int pelletOffsetCorrectionX = 0;
    int pelletOffsetCorrectionY = 0;
    float pelletX = 0;
    float pelletY = 0;
    float tempPelletVelX = 0;
    float tempPelletVelY = 0;
    int gunTipX = 0;
    int gunTipY = 0;
    int rotation = 0;

    float deltaTime;
    float time = 0;

    int mouseX = 0, mouseY = 0;
    int offsetCorrectionX = 0, offsetCorrectionY = 0;
    double rotationAngle = 0;
    double angleOffsetCorrection = 51;

    SDL_Texture* texture = nullptr;
    SDL_Texture* pelletTexture = nullptr;

    bool textureLoaded = false;
    bool clicked = false;
    bool pelletIsVisible = true;

};

#endif // Gun_hpp
