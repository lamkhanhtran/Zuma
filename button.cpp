#include <SDL.h>
#include <SDL_ttf.h>

#include "Coord.h"
#include "Entity.h"
#include "Button.h"

Button::Button(){

}

void Button::setButton( SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color, Coord _pos ){

    this->pos = _pos;

    SDL_Surface* surfaceMessage1 = TTF_RenderText_Blended( font, text, color );
    SDL_Surface* surfaceMessage2 = TTF_RenderText_Blended( font, text, BLACK_COLOR );

    this->wordTexture = SDL_CreateTextureFromSurface( renderer, surfaceMessage1 );
    this->shadowTexture = SDL_CreateTextureFromSurface( renderer, surfaceMessage2 );

    this->srcRect.x = 0;
    this->srcRect.y = 0;
    this->srcRect.w = surfaceMessage1->w;
    this->srcRect.h = surfaceMessage1->h;

    SDL_FreeSurface(surfaceMessage1);
    SDL_FreeSurface(surfaceMessage2);

}

bool Button::update( const Coord& mouse ){

    int diff_x = mouse.x - int(this->pos.x);
    int diff_y = mouse.y - int(this->pos.y);

    if( abs( diff_x ) <= ( this->srcRect.w / 2 ) && abs( diff_y ) <= ( this->srcRect.h / 2 ) )
        return true;

    return false;

}

void Button::drawGraphic( SDL_Renderer* renderer ){

    SDL_Rect wordRecDest = { int( this->pos.x ) - ( this->srcRect.w / 2 ) - 1, int( this->pos.y ) - ( this->srcRect.h / 2 ) - 1, this->srcRect.w, this->srcRect.h };

    SDL_Rect shadowRecDest = { int( this->pos.x ) - ( this->srcRect.w / 2 ) + 1, int( this->pos.y ) - ( this->srcRect.h / 2 ) + 1, this->srcRect.w, this->srcRect.h };

    SDL_SetRenderDrawColor( renderer, this->GRAY_COLOR.r - 40, this->GRAY_COLOR.g - 40, this->GRAY_COLOR.b - 40, this->GRAY_COLOR.a );
    SDL_RenderFillRect( renderer, &shadowRecDest );

    SDL_SetRenderDrawColor( renderer, this->GRAY_COLOR.r, this->GRAY_COLOR.g, this->GRAY_COLOR.b, this->GRAY_COLOR.a );
    SDL_RenderFillRect( renderer, &wordRecDest );

    SDL_RenderCopy( renderer, this->shadowTexture, &this->srcRect, &shadowRecDest );
    SDL_RenderCopy( renderer, this->wordTexture, &this->srcRect, &wordRecDest );

}
