#include <SDL.h>

#include "Coord.h"
#include "Entity.h"

Entity::Entity( SDL_Texture* _texture, Coord _pos )
    : texture(_texture), pos(_pos){

}
