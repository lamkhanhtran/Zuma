#include <iostream>
#include <math.h>
#include <SDL.h>

#include "Coord.h"
#include "Entity.h"
#include "Ball.h"

int randBall( int _maxTypeBalls ){

    return ( rand() % _maxTypeBalls );

}

Ball::Ball( SDL_Texture* _texture, Coord _pos, int _ballSize ) : Entity( _texture, _pos ) {

    this->ballSize = _ballSize;

}

Ball::Ball( const Ball& _ball ) : Entity( _ball.texture, _ball.pos ){

    this->value = _ball.value;

    this->ballSize = _ball.ballSize;

    this->nextPos = _ball.nextPos;

}

void Ball::update( Coord nextPos ){

    this->pos = nextPos;

}

void Ball::drawGraphic( SDL_Renderer* renderer ){

    SDL_Rect recDest = { int(this->pos.x) - this->ballSize / 2, int(this->pos.y) - this->ballSize / 2, this->ballSize, this->ballSize };
    SDL_Rect srcRect = { this->ballSize * this->value, 0, this->ballSize, this->ballSize };

    // Địa chỉ ảnh cắt từ texture

    SDL_RenderCopy( renderer, this->texture, &srcRect, &recDest );

}
