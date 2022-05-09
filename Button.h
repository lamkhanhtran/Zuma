#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Coord.h"
#include "Entity.h"

struct Button{

    SDL_Texture *wordTexture, *shadowTexture;

    SDL_Rect srcRect;

    SDL_Color BLACK_COLOR = { 0, 0, 0 };
    SDL_Color GRAY_COLOR = { 104, 104, 104 };

    Coord pos;

    Button();

    void setButton( SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color, Coord pos );

    bool update( const Coord& mouse );

    void drawGraphic( SDL_Renderer* renderer );

};
