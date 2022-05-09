#pragma once

#include <SDL.h>

#include "Coord.h"
#include "Entity.h"

int randBall( int _maxTypeBalls );

struct Ball : Entity{                           // Bóng

    int value;                                  // Giá trị màu quả bóng

    int ballSize;                               // Kích cỡ quả bóng

    Coord nextPos;                              // Tọa độ tiếp theo của bóng

    Ball( SDL_Texture* _texture = NULL, Coord _pos = nullCoord, int _ballSize = 0 );

    Ball( const Ball& _ball );

    void update( Coord nextPos );

    void drawGraphic( SDL_Renderer* renderer );

};
