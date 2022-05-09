#pragma once

struct Coord{ // Tọa độ x, y

    float x, y;

    Coord(); // Đặt x=0, y=0

    Coord( float new_x, float new_y ); // Đặt x = new_x, y = new_y

    Coord operator+( const Coord& _pos );

    Coord operator-( const Coord& _pos );

    Coord operator*( const float& number );

    Coord operator/( const float& number );

    bool operator!=( const Coord& _pos );

    bool operator==( const Coord& _pos );

};

//******************************************************************************************

float distance( Coord point_1, Coord point_2 );

//******************************************************************************************

static Coord nullCoord( -9999, -9999 ); // Tạo 1 tọa độ trống có giá trị -9999, -9999
