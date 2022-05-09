#include <math.h>

#include "Coord.h"

Coord::Coord() : x( 0.0 ), y( 0.0 ) {} // Đặt x=0, y=0

Coord::Coord( float new_x, float new_y ) : x( new_x ), y( new_y ) {} // Đặt x = new_x, y = new_y

Coord Coord::operator+( const Coord& _pos ){ // Cộng tọa độ

    return Coord( this->x + _pos.x ,
                  this->y + _pos.y );

}

Coord Coord::operator-( const Coord& _pos ){ // Trừ tọa độ

    return Coord( this->x - _pos.x ,
                  this->y - _pos.y );

}

Coord Coord::operator*( const float& number ){ // Nhân tọa độ với số

    return Coord( this->x * number ,
                  this->y * number );

}

Coord Coord::operator/( const float& number ){ // Chia tọa độ với số

    if ( number == 0 )
        return Coord( 0, 0 );

    return Coord( this->x / number ,
                  this->y / number );

}

bool Coord::operator!=( const Coord& _pos ){ // So sánh tọa độ với nhau

    return ( ( this->x == _pos.x && this->y == _pos.y ) ? false : true );

}

bool Coord::operator==( const Coord& _pos ){ // So sánh tọa độ với nhau

    return ( ( this->x == _pos.x && this->y == _pos.y ) ? true : false );

}

float distance( Coord point_1, Coord point_2 ){             // Tính khoảng cách giữa 2 điểm

    return sqrt( pow( point_2.x - point_1.x , 2 ) + pow( point_2.y - point_1.y, 2 ) );

}
