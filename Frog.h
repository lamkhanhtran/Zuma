#pragma once

#include <SDL.h>
#include <vector>

#include "Coord.h"
#include "Entity.h"
#include "Ball.h"

struct Frog : Entity{

    Ball ballNow;
    Ball ballNext;

    float angle;                                // Hướng của vật

    int maxTypeBalls;                           // Tối đa số quả bóng mỗi bàn

    bool shootIt = false;
    bool ballAppear = true;

    int frameShot = 0;

    bool winGame = true;

    Frog( SDL_Texture* _texture = NULL, SDL_Texture* _ballNowTexture = NULL, SDL_Texture* _ballNextTexture = NULL,
          Coord _pos = nullCoord, float _angle = 0, int _maxTypeBalls = -1 );

    void swapBalls();

    Ball shootBalls();

    void update( float _angle, bool _win );

    void drawGraphic( SDL_Renderer* renderer );

};
