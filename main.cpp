#include "Game.hpp"
#include "Ball.hpp"
#include "Gun.hpp"
#include "SDL2/SDL.h"
#include "Pellet.hpp"
#include "windows.h"
#include <cstdlib>
#include <random>
#include <vector>

Game* game = nullptr;
Gun* gun = nullptr;
std::vector<Ball*> balls;
std::vector<int> ballPositionX;
std::vector<int> ballPositionY;
int main(int argc, char* argv[])
{
    const float targetFPS = 60.0f;
    const float maxFrameTime = 1.0f / targetFPS; 
    Uint32 prevTicks = SDL_GetTicks();
    const float dt = 1000.0f / targetFPS;
    int windowWidth = 1300;
    int windowHeight = 700;

    game = new Game();
    gun = new Gun();

    game->init("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, false);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> ballX(100, windowWidth - 100);
    std::uniform_int_distribution<> ballY(0, 50);
    std::uniform_int_distribution<> ballCount(2, 10);

    // create multiple balls and add them to the vector
    for (int i = 0; i < ballCount(gen); ++i) {
        Ball* ball = new Ball();
        balls.push_back(ball);
        ballPositionX.push_back(ballX(gen));
        ballPositionY.push_back(ballY(gen));
    }

    while (game->running() == true)
    {
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - prevTicks) / 1000.0f;
        prevTicks = currentTicks;

        game->handleEvents();
        game->update();

        for (auto ball : balls) {
            ball->update(windowWidth, windowHeight, deltaTime);
        }

        gun->update(windowWidth, windowHeight);

        // check for collisions and render balls
        for (size_t i = 0; i < balls.size(); ++i) {
            Ball* ball = balls[i];
            if (gun->pelletX <= ball->ballX + 100 || gun->pelletY <= ball->ballY + 100) {
                ball->isHit = true;
                break;
            }
            if (gun->pelletX <= ball->ballX - 100 || gun->pelletY <= ball->ballY - 100) {
                ball->isHit = true;
                break;
            }
            //render balls if there is no collision
            if (ball->isHit == false) {
                ball->render(game->getRenderer(), ballPositionX[i], ballPositionY[i]);
            }
        }

        gun->render(game->getRenderer(), windowWidth, windowHeight);
        SDL_RenderPresent(game->getRenderer());

        game->render();

        Uint32 frameTicks = SDL_GetTicks() - currentTicks;
        if (frameTicks < maxFrameTime * 1000.0f) {
            SDL_Delay((Uint32)((maxFrameTime * 1000.0f) - frameTicks));
        }

        // check for balls out of boundaries
        for (auto it = balls.begin(); it != balls.end();) {
            if ((*it)->isOutOfBoundaries == true) {
                (*it)->deleteTexture((*it)->getTexture());
                delete* it;
                it = balls.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    gun->cleanup();
    game->clean();

    // clean up all balls
    for (auto ball : balls) {
        ball->deleteTexture(ball->getTexture());
        delete ball;
    }

    delete gun;
    delete game;

    return 0;
}
