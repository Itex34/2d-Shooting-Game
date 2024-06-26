#ifndef Gun_hpp
#define Gun_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
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
    void cleanup();
    void createPelletTexture(SDL_Renderer* renderer);
    float pelletVelX(float rotationOffset);
    float pelletVelY(float rotationOffset);


    int gunX = 550;
    int gunY = 400;


    int width = 200;
    int height = 200;

    int pelletOffsetCorrectionX = 0;
    int pelletOffsetCorrectionY = 0;

    float pelletSpeed = 40.0f;

    float pelletX = 200000;
    float pelletY = 200000;
    float pelletRadius = 20.0f;


    float timeLimit = 0;
    int gunTipX = 0;
    int gunTipY = 0;
    int rotation = 0;

    float deltaTime = 0;
    float time = 0;

    int mouseX = 0, mouseY = 0;
    int offsetCorrectionX = 0, offsetCorrectionY = 0;
    double rotationAngle = 0;
    double initialRotationAngle;
    double angleOffsetCorrection = 51;



    bool textureLoaded = false;
    bool clicked = false;
    bool pelletIsVisible = true;
private:
    SDL_Texture* texture = nullptr;
    SDL_Texture* pelletTexture = nullptr;

};

#endif // Gun_hpp
