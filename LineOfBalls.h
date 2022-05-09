#pragma once

#include <SDL.h>
#include <vector>

#include "Coord.h"
#include "Entity.h"
#include "Ball.h"

struct LineOfBalls{

    SDL_Texture* roadTexture;
    SDL_Texture* ballTexture;
    SDL_Texture* skullTexture;

    std::vector<Coord> movementCoords;

    std::vector<Ball> balls;
    std::vector<int> iteratorBalls;
    std::vector< std::pair<int, int> > blockedIterator;

    std::vector<Ball> waitingBalls;

    float normalVelocity = 1.5;
    float dangerVelocity = 0.75;
    float deathVelocity = 10;

    int maxTypeBalls;

    int ballPops = 0;
    int targetPops;

    bool winGame = true;
    bool endGame = false;

    bool dangerous = false;

    LineOfBalls( SDL_Texture* _roadTexture, SDL_Texture* _ballTexture, SDL_Texture* _skullTexture,
                 std::vector<Coord> _movementCoords, std::vector< std::pair<int, int> > _blockedIterator, int _maxTypeBalls, int _targetPops );

    bool checkEnding();

    void moveBalls( int startAt );

    int collisionDetect( const Ball& shotBall );

    int deleteSameBallsIfPossible( int ballPosFromTop );

    bool returnDisconnectBalls( int ballPosFromTop );

    void drawGraphic( SDL_Renderer* renderer, int num_stage );

};
