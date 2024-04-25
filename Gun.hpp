#ifndef Gun_hpp
#define Gun_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

class Gun {
public:
    ~Gun();

    Gun();
    void update(int windowWidth, int windowHeight,Game* game);
    void render(SDL_Renderer* renderer);
    void shoot(Game* game);
    void cleanup(Game* game);

private:
    int width = 200;
    int height = 200;
    int cnt = 0;

    int gunX = 550;
    int gunY = 400;

    int rotation = 0;
    float deltaTime;
    float time = 0;      // Current time

    int mouseX = 0, mouseY = 0;
    int offsetCorrectionX = 0, offsetCorrectionY = 0;
    double rotationAngle;
    double angleOffsetCorrection = 51;

    SDL_Texture* texture = nullptr;


    bool textureLoaded = false;


};

#endif // Gun_hpp
