#pragma once

#include <SDL.h>

#include "Coord.h"

struct Entity{                          // Class vật chung

    SDL_Texture* texture;               // Pointer đến ảnh

    Coord pos;                          // Tọa độ hiện tại

//************************************************************************************

    Entity( SDL_Texture* _texture, Coord _pos );        // Prototype cho khởi tạo vật

};
