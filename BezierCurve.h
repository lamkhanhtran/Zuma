#pragma once

#include <SDL.h>
#include <vector>
#include <math.h>

#include "Coord.h"

//***********************************************************************************

// làm hàm vẽ đường cong bezier 4 điểm

Coord lerp( Coord point_1, Coord point_2, float percent ){              // nội suy tuyến tính (linear interpolation)

    return ( point_2 - point_1 ) * percent + point_1;

}

Coord quadBezier( Coord point_1, Coord point_2,
                  Coord point_3, float percent ){                       // hàm bậc 2 bezier (quadratic bezier)

    Coord tempPoint_1 = lerp( point_1, point_2, percent );
    Coord tempPoint_2 = lerp( point_2, point_3, percent );

    return ( tempPoint_2 - tempPoint_1 ) * percent + tempPoint_1;

}

Coord cubBezier( Coord point_1, Coord point_2,
                 Coord point_3, Coord point_4, float percent ){          // hàm bậc 3 bezier (cubic bezier)

    Coord tempPoint_1 = quadBezier( point_1, point_2, point_3, percent );
    Coord tempPoint_2 = quadBezier( point_2, point_3, point_4, percent );

    return ( tempPoint_2 - tempPoint_1 ) * percent + tempPoint_1;

}

Coord tangentCubic( Coord point_1, Coord point_2,
                    Coord point_3, Coord point_4, float percent ){       // đạo hàm hàm bậc 3 bezier (cubic bezier)

    return point_1 * ( -3 * pow( percent, 2 ) + 6 * percent - 3 ) +
           point_2 * ( 9 * pow( percent, 2 ) - 12 * percent + 3 ) +
           point_3 * ( -9 * pow( percent, 2 ) + 6 * percent ) +
           point_4 * ( 3 * pow( percent, 2 ) );

}

Coord offsetCoord( Coord tangent, float offset ){                        // đạo hàm hàm bậc 3 bezier (cubic bezier)

    Coord normal( -tangent.y, tangent.x );
    float distant = sqrt( pow( normal.x, 2 ) + pow( normal.y, 2 ) );

    normal = ( normal / distant ) * offset;

    return normal;

}

std::vector<Coord> loadRoad( std::vector<Coord> controlPoints ){      // hàm vẽ điểm lerp của 1 dãy các điểm

    std::vector<Coord> roadPoints;

    for(int i = 1, n = controlPoints.size(); i < n - 1; i += 3 ){

        for(float t = 0; t < 2000; t += 1){

            Coord current = cubBezier( controlPoints[ i ], controlPoints[ i + 1 ],
                                       controlPoints[ i + 2 ], controlPoints[ i + 3 ], ( t / 2000 ) );
            roadPoints.push_back(current);

        }
    }

    return roadPoints;
}

std::vector<Coord> loadMovement( std::vector<Coord> roadPoints, float velocity ){

    std::vector<Coord> movementPoints;

    Coord diff = roadPoints[1] - roadPoints[0];
    diff = ( diff / distance( roadPoints[1], roadPoints[0] ) );
    for(float i=15;i>=0;i-=velocity)
        movementPoints.push_back( roadPoints[0] - diff * i );

    float totalDis = 0.0;

    for(int i = 1, n = roadPoints.size(); i < n; i++ ){

        float currentDis = distance( roadPoints[i], roadPoints[i-1] );
        totalDis += currentDis;
        if( totalDis > velocity ){
            movementPoints.push_back( roadPoints[i] );
            totalDis = 0.0;
        }
        //std::cout << totalDis << '\n';

    }
    return movementPoints;

}
