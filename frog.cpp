#include <iostream>
#include <math.h>
#include <SDL.h>

#include "Coord.h"
#include "Entity.h"
#include "Ball.h"
#include "Frog.h"


Frog::Frog( SDL_Texture* _texture, SDL_Texture* _ballNowTexture, SDL_Texture* _ballNextTexture,
            Coord _pos, float _angle, int _maxTypeBalls )
    : Entity( _texture, _pos ), maxTypeBalls(_maxTypeBalls) {

    float xAddOn = cos( this->angle );
    float yAddOn = sin( this->angle );

    Coord temp = Coord( _pos.x - xAddOn * 23, _pos.y - yAddOn * 23 );
    this->ballNext = Ball( _ballNextTexture, temp, 14 );
    this->ballNext.value = randBall( this->maxTypeBalls );

    temp = Coord( _pos.x + xAddOn * 23, _pos.y + yAddOn * 23 );
    this->ballNow = Ball( _ballNowTexture, temp, 40 );
    this->ballNow.value = randBall( this->maxTypeBalls );

}

void Frog::swapBalls(){

    if( this->ballAppear ){

        int temp = this->ballNow.value;
        this->ballNow.value = this->ballNext.value;
        this->ballNext.value = temp;

    }

}

Ball Frog::shootBalls(){

    this->shootIt = true;
    this->ballAppear = false;

    Ball ballShoot = this->ballNow ;
    this->ballNow = Ball( ballShoot );

    this->ballNow.value = this->ballNext.value;
    this->ballNext.value = randBall( this->maxTypeBalls );

    return ballShoot;

}

void Frog::update( float _angle, bool _win ){

    this->winGame = _win;

    if( this->shootIt || this->frameShot!=0){

        this->shootIt = false;
        this->frameShot = (this->frameShot + 1) % 16;

        if(this->frameShot==12)
            this->ballAppear = true;

    }

    if( !this->winGame )
        return;

    this->angle = _angle;

    float xAddOn = cos( this->angle );
    float yAddOn = sin( this->angle );

    Coord temp = Coord( this->pos.x - xAddOn * 23, this->pos.y - yAddOn * 23 );

    this->ballNext.update( temp );

    temp = Coord( this->pos.x + xAddOn * 23, this->pos.y + yAddOn * 23 );

    this->ballNow.update( temp );

}

void Frog::drawGraphic( SDL_Renderer* renderer ){

    SDL_Rect frogSprite[8] = {
        { 0, 360, 132, 120 },
        { 0, 240, 132, 120 },
        { 0, 120, 132, 120 },
        { 0, 0, 132, 120 },
        { 132, 360, 132, 120 },
        { 132, 240, 132, 120 },
        { 132, 120, 132, 120 },
        { 132, 0, 132, 120 }
    };

    SDL_Rect recDest = { int(this->pos.x) - 72, int(this->pos.y) - 60, 132, 120 };

    SDL_Point centerFrog = {72, 60};

    SDL_RenderCopyEx( renderer, this->texture, &frogSprite[ this->frameShot / 4 ], &recDest, ( this->angle * (180 / M_PI) ), &centerFrog, SDL_FLIP_NONE );

    if( this->ballAppear )
        this->ballNow.drawGraphic( renderer );

    this->ballNext.drawGraphic( renderer );

    SDL_RenderCopyEx( renderer, this->texture, &frogSprite[ ( this->frameShot / 4 ) + 4 ], &recDest, ( this->angle * ( 180 / M_PI ) ), &centerFrog, SDL_FLIP_NONE );

}
