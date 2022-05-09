#include <iostream>
#include <math.h>
#include <vector>

#include "Coord.h"
#include "Entity.h"
#include "Ball.h"
#include "LineOfBalls.h"

LineOfBalls::LineOfBalls( SDL_Texture* _roadTexture, SDL_Texture* _ballTexture, SDL_Texture* _skullTexture,
                          std::vector<Coord> _movementCoords, std::vector< std::pair<int, int> > _blockedIterator, int _maxTypeBalls, int _targetPops )
    : roadTexture(_roadTexture), ballTexture(_ballTexture), skullTexture(_skullTexture),
      movementCoords(_movementCoords), blockedIterator(_blockedIterator), maxTypeBalls(_maxTypeBalls), targetPops(_targetPops){

    if( !_movementCoords.empty() ){

        Ball a_ball = Ball( _ballTexture, this->movementCoords[0], 40 );
        a_ball.value = randBall( _maxTypeBalls );
        this->balls.push_back( a_ball );
        this->iteratorBalls.push_back( 0 );

        for( int i=0; i<=500; i++ ){
            a_ball = Ball( _ballTexture, nullCoord, 40 );
            a_ball.value = randBall( _maxTypeBalls );
            this->waitingBalls.push_back( a_ball );
        }

    }

}

bool LineOfBalls::checkEnding(){

    if( ( this->winGame && this->ballPops >= this->targetPops ) || !this->winGame ){

        this->endGame = true;
        while( !this->waitingBalls.empty() )
            this->waitingBalls.pop_back();

    }
    if( this->endGame && this->balls.size() == 0 )
        return true;
    return false;

}

void LineOfBalls::moveBalls( int startAt ){

    int numBalls = this->iteratorBalls.size();
    int speed = ( this->winGame ) ? ( ( this->dangerous ) ? 3 : 6 ) : 40;
    this->dangerous = false;

    for(int i = startAt; i < numBalls; i++){

        int temp = this->iteratorBalls[i] + speed;

        if( i != 0 ){

            if( distance( this->movementCoords[ this->iteratorBalls[i] ], this->movementCoords[ this->iteratorBalls[i-1] ] ) >= 40.5 )
                break;

            while( temp < int( this->movementCoords.size() ) &&
                   distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i-1] ] ) < 40 )
                temp++;

            if( temp >= int( this->movementCoords.size() ) ){

                this->balls.erase( this->balls.begin() + i );
                this->iteratorBalls.erase( this->iteratorBalls.begin() + i );
                numBalls = this->iteratorBalls.size();
                i--;
                this->winGame = false;
                continue;

            }

            while( temp >= 0 &&
                   distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i-1] ] ) > 40 )
                temp--;

        }

        if( temp >= int( this->movementCoords.size() ) ){

            this->balls.erase( this->balls.begin() + i );
            this->iteratorBalls.erase( this->iteratorBalls.begin() + i );
            numBalls = this->iteratorBalls.size();
            i--;
            continue;

        }

        if( float( temp + 1 ) / this->movementCoords.size() > 0.6 )
            this->dangerous = true;

        this->iteratorBalls[i] = temp;
        this->balls[i].update( this->movementCoords[ temp ] );

    }

    if ( !this->endGame && distance( this->movementCoords[0], this->movementCoords[ this->iteratorBalls[0] ] ) >= 40 ){

        Ball a_ball = this->waitingBalls.back();
        a_ball.pos = this->movementCoords[0];
        this->balls.insert( this->balls.begin(), a_ball );
        this->iteratorBalls.insert( this->iteratorBalls.begin(), 0 );
        this->waitingBalls.pop_back();

    }

}

int LineOfBalls::collisionDetect( const Ball& shotBall ){

    int connect = -1;

    for( int i = 0, n = this->iteratorBalls.size(); i < n; i++ ){

        bool collisionInTunnel = false;

        for( int j = 0, m = this->blockedIterator.size(); j < m; j++ ){

            if( this->blockedIterator[j].first <= this->iteratorBalls[i] &&
                this->blockedIterator[j].second >= this->iteratorBalls[i] ){

                collisionInTunnel = true;
                break;

            }

        }

        if( collisionInTunnel )
            continue;

        float nowDist = distance( this->movementCoords[ this->iteratorBalls[i] ], shotBall.pos );

        if( nowDist < 40 ){

            if( this->iteratorBalls[i] + ( ( this->dangerous ) ? 3 : 6 ) >= int( this->movementCoords.size() ) )
                continue;

            float nextDist = distance( this->movementCoords[ this->iteratorBalls[i] + ( ( this->dangerous ) ? 3 : 6 ) ],
                                       shotBall.pos );

            if( nowDist < nextDist ){

                if( ( i == 0 && this->endGame ) ||
                    ( i != 0 && distance( this->movementCoords[ this->iteratorBalls[i] ], this->movementCoords[ this->iteratorBalls[i-1] ] ) >= 40.5 ) ){

                    int temp = this->iteratorBalls[i] - 1;

                    if( temp < 0 ) continue;

                    while( temp >= 0 &&
                           distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i] ] ) < 40 )
                        temp--;

                    if( temp < 0 ) continue;

                    while( temp < int( this->movementCoords.size() )  &&
                           distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i] ] ) > 40 )
                        temp++;

                    Ball a_ball = Ball( shotBall );
                    a_ball.update( this->movementCoords[ temp ] );

                    this->balls.insert( this->balls.begin() + i, a_ball );
                    this->iteratorBalls.insert( this->iteratorBalls.begin() + i, temp );
                    this->moveBalls( i );
                    connect = int( this->iteratorBalls.size() - 1 ) - i;

                }
                else{

                    Ball a_ball = Ball( shotBall );
                    a_ball.update( this->movementCoords[ this->iteratorBalls[i] ] );

                    this->balls.insert( this->balls.begin() + i, a_ball );
                    this->iteratorBalls.insert( this->iteratorBalls.begin() + i, this->iteratorBalls[i] );
                    this->moveBalls( i + 1 );
                    connect = int( this->iteratorBalls.size() - 1 ) - i;

                }
            }
            else{

                Ball a_ball = Ball( shotBall );
                a_ball.update( this->movementCoords[ this->iteratorBalls[i] ] );

                this->balls.insert( this->balls.begin() + i + 1, a_ball );
                this->iteratorBalls.insert( this->iteratorBalls.begin() + i + 1, this->iteratorBalls[i] );
                this->moveBalls( i + 1 );
                connect = int( this->iteratorBalls.size() - 1 ) - i - 1;

            }

            break;
        }
    }

    return connect;
}

int LineOfBalls::deleteSameBallsIfPossible( int ballPosFromTop ){

    int realBallPos = this->iteratorBalls.size() - 1 - ballPosFromTop;
    int ballBefore = 0, ballAfter = 0, value = this->balls[ realBallPos ].value;
    int next = realBallPos + 1, prev = realBallPos - 1;


    while( ( next < int( this->iteratorBalls.size() ) ) && ( this->balls[ next ].value == value ) &&
           ( distance( this->balls[ next ].pos, this->balls[ next - 1 ].pos ) < 40.5 ) ){
        next++;
        ballAfter++;
    }

    while( ( prev >= 0 ) && ( this->balls[ prev ].value == value ) &&
           ( distance( this->balls[ prev ].pos, this->balls[ prev + 1 ].pos ) < 40.5 ) ){
        prev--;
        ballBefore++;
    }

    prev++;

    if( ( ballBefore + ballAfter >= 2 ) ){

        this->balls.erase( this->balls.begin() + prev, this->balls.begin() + next );
        this->iteratorBalls.erase( this->iteratorBalls.begin() + prev, this->iteratorBalls.begin() + next );
        realBallPos = prev;
        this->ballPops += ( ballBefore + ballAfter + 1 );

    }

    if( realBallPos != 0 && this->balls[ realBallPos ].value == this->balls[ realBallPos - 1 ].value &&
        distance( this->balls[ realBallPos ].pos, this->balls[ realBallPos - 1 ].pos ) > 40.5) return this->iteratorBalls.size() - 1 - realBallPos;

    else if( realBallPos != int( this->iteratorBalls.size() - 1 ) && this->balls[ realBallPos ].value == this->balls[ realBallPos + 1 ].value &&
             distance( this->balls[ realBallPos ].pos, this->balls[ realBallPos + 1 ].pos ) > 40.5) return this->iteratorBalls.size() - 1 - ( realBallPos + 1 );

    return -1;

}

bool LineOfBalls::returnDisconnectBalls( int ballPosFromTop ){

    int realBallPos = this->iteratorBalls.size() - 1 - ballPosFromTop;
    int numBalls = this->iteratorBalls.size();
    int furthestBallConnect = realBallPos + 1;
    int backwardSpeed = 12;


    while( ( furthestBallConnect < numBalls ) &&
           ( distance( this->balls[ furthestBallConnect ].pos, this->balls[ furthestBallConnect - 1 ].pos ) < 40 ) ){
        furthestBallConnect++;
    }
    furthestBallConnect--;

    for( int i = furthestBallConnect; i >= realBallPos; i-- ){

        int temp = this->iteratorBalls[i] - backwardSpeed;

        if(i != furthestBallConnect){

            if( distance( this->movementCoords[ this->iteratorBalls[i] ], this->movementCoords[ this->iteratorBalls[i+1] ] ) >= 40.5 )
                break;

            while( temp >= 0 &&
                   distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i+1] ] ) < 40 )
                temp--;

            while( temp < int( this->movementCoords.size() ) &&
                   distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i+1] ] ) > 40 )
                temp++;

        }

        if( temp < 0 ){

            this->waitingBalls.push_back( this->balls[i] );
            this->balls.erase( this->balls.begin() + i );
            this->iteratorBalls.erase( this->iteratorBalls.begin() + i );
            numBalls = this->iteratorBalls.size();
            continue;

        }

        this->iteratorBalls[i] = temp;
        this->balls[i].update( this->movementCoords[ temp ] );

    }


    if( distance( this->balls[ realBallPos ].pos, this->balls[ realBallPos - 1 ].pos ) < 40 ){

        for( int i = furthestBallConnect; i >= 0; i-- ){

            int temp = this->iteratorBalls[i] - backwardSpeed - 30;

            if(i != furthestBallConnect){

                if( distance( this->movementCoords[ this->iteratorBalls[i] ], this->movementCoords[ this->iteratorBalls[i+1] ] ) >= 40.5 )
                    break;

                while( temp >= 0 &&
                       distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i+1] ] ) < 40 )
                    temp--;

                if( temp < 0 ){

                    this->waitingBalls.push_back( this->balls[i] );
                    this->balls.erase( this->balls.begin() + i );
                    this->iteratorBalls.erase( this->iteratorBalls.begin() + i );
                    numBalls--;
                    continue;

                }

                while( temp < int( this->movementCoords.size() ) &&
                       distance( this->movementCoords[ temp ], this->movementCoords[ this->iteratorBalls[i+1] ] ) > 40 )
                    temp++;

            }

            if( temp < 0 ){

                this->waitingBalls.push_back( this->balls[i] );
                this->balls.erase( this->balls.begin() + i );
                this->iteratorBalls.erase( this->iteratorBalls.begin() + i );
                numBalls--;
                continue;

            }

            this->iteratorBalls[i] = temp;
            this->balls[i].update( this->movementCoords[ temp ] );

        }
        return true;

    }

    return false;
}

void LineOfBalls::drawGraphic( SDL_Renderer* renderer, int num_stage ){

    SDL_Rect srcRect = { (num_stage - 1) * 2, 0, 2, 41 };
    SDL_Rect recDest;
    SDL_Point center = { 0, 20 };

    float angle;

    for(int i = 0, iterate = 0, n = this->movementCoords.size(); i < n-1; i++ ){

        if( iterate < int( this->blockedIterator.size() ) ){
            int currentTarget = this->blockedIterator[ iterate ].first;
            if( i == currentTarget ){
                i = this->blockedIterator[ iterate ].second;
                iterate++;
                continue;
            }
        }
        recDest = { int( this->movementCoords[i].x ), int( this->movementCoords[i].y ) - 20, 2, 41 };

        angle = SDL_atan2( this->movementCoords[ i + 1 ].y - this->movementCoords[ i ].y,
                           this->movementCoords[ i + 1 ].x - this->movementCoords[ i ].x ) ;

        SDL_RenderCopyEx( renderer, this->roadTexture, &srcRect, &recDest, (angle * (180 / M_PI)), &center, SDL_FLIP_NONE );

    }

    srcRect = { 0, 0, 107, 107 };
    recDest = { int(this->movementCoords[ this->movementCoords.size()-1 ].x) - 53, int(this->movementCoords[ this->movementCoords.size()-1 ].y) - 53, 107, 107 };

    SDL_RenderCopy( renderer, this->skullTexture, &srcRect, &recDest );

    for(int i = 0, n = this->balls.size(); i < n; i++){

        bool hideBalls = false;
        for( int j = 0, m = this->blockedIterator.size(); j < m; j++ ){
            if( this->blockedIterator[j].first <= this->iteratorBalls[i] &&
                this->blockedIterator[j].second >= this->iteratorBalls[i] ){
                hideBalls = true;
                break;
            }
        }
        if( !hideBalls )
            this->balls[i].drawGraphic( renderer );

    }

}
