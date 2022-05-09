#pragma once

#include <vector>

#include "Coord.h"


std::vector<Coord> loadMaps( int num_stage ){ // map của 10 bàn zuma

    std::vector<Coord> mapping;

    if ( num_stage == 1 ){ // map của bàn 1 zuma

        mapping.push_back( Coord( 88, 680 ) );
        mapping.push_back( Coord( 88, 600 ) );
        mapping.push_back( Coord( 88, 520 ) );

        mapping.push_back( Coord( 80, 80 ) );
        mapping.push_back( Coord( 420, 80 ) );
        mapping.push_back( Coord( 760, 80 ) );

        mapping.push_back( Coord( 760, 530 ) );
        mapping.push_back( Coord( 440, 530 ) );
        mapping.push_back( Coord( 120, 530 ) );

        mapping.push_back( Coord( 170, 150 ) );
        mapping.push_back( Coord( 420, 150 ) );
        mapping.push_back( Coord( 670, 150 ) );

        mapping.push_back( Coord( 610, 480 ) );
        mapping.push_back( Coord( 430, 450 ) );
        mapping.push_back( Coord( 250, 420 ) );

        mapping.push_back( Coord( 310, 290 ) );
        mapping.push_back( Coord( 340, 280 ) );

    }
    else if ( num_stage == 2 ){ // map của bàn 2 zuma

        mapping.push_back( Coord( 960, 60 ) );
        mapping.push_back( Coord( 800, 60 ) );
        mapping.push_back( Coord( 640, 60 ) );

        mapping.push_back( Coord( 40, -35 ) );
        mapping.push_back( Coord( 40, 300 ) );
        mapping.push_back( Coord( 40, 635 ) );

        mapping.push_back( Coord( 743, 587 ) );
        mapping.push_back( Coord( 722, 473 ) );
        mapping.push_back( Coord( 701, 359 ) );

        mapping.push_back( Coord( 140, 553 ) );
        mapping.push_back( Coord( 140, 316 ) );
        mapping.push_back( Coord( 140, 79 ) );

        mapping.push_back( Coord( 688, 78 ) );
        mapping.push_back( Coord( 693, 180 ) );
        mapping.push_back( Coord( 698, 282 ) );

        mapping.push_back( Coord( 242, 167 ) );
        mapping.push_back( Coord( 242, 297 ) );
        mapping.push_back( Coord( 242, 427 ) );

        mapping.push_back( Coord( 440, 367 ) );
        mapping.push_back( Coord( 490, 351 ) );

    }
    else if ( num_stage == 3 ){ // map của bàn 3 zuma

        mapping.push_back( Coord( 850, 65 ) );
        mapping.push_back( Coord( 800, 65 ) );
        mapping.push_back( Coord( 750, 65 ) );

        mapping.push_back( Coord( 87, 18 ) );
        mapping.push_back( Coord( 84, 143 ) );
        mapping.push_back( Coord( 81, 268 ) );

        mapping.push_back( Coord( 758, -41 ) );
        mapping.push_back( Coord( 756, 276 ) );
        mapping.push_back( Coord( 754, 593 ) );

        mapping.push_back( Coord( -116, 680 ) );
        mapping.push_back( Coord( 73, 392 ) );
        mapping.push_back( Coord( 262, 104 ) );

        mapping.push_back( Coord( 746, 163 ) );
        mapping.push_back( Coord( 615, 357 ) );
        mapping.push_back( Coord( 484, 551 ) );

        mapping.push_back( Coord( 154, 523 ) );
        mapping.push_back( Coord( 130, 450 ) );
        mapping.push_back( Coord( 106, 377 ) );

        mapping.push_back( Coord( 201, 364 ) );
        mapping.push_back( Coord( 296, 387 ) );

    }
    else if ( num_stage == 4 ){ // map của bàn 4 zuma

        mapping.push_back( Coord( 95, 34 ) );
        mapping.push_back( Coord( 252, 138 ) );
        mapping.push_back( Coord( 409, 242 ) );

        mapping.push_back( Coord( 736, 482 ) );
        mapping.push_back( Coord( 736, 310 ) );
        mapping.push_back( Coord( 736, 138 ) );

        mapping.push_back( Coord( 770, 75 ) );
        mapping.push_back( Coord( 468, 75 ) );
        mapping.push_back( Coord( 166, 75 ) );

        mapping.push_back( Coord( 84, 47 ) );
        mapping.push_back( Coord( 98, 128 ) );
        mapping.push_back( Coord( 112, 209 ) );

        mapping.push_back( Coord( 688, 439 ) );
        mapping.push_back( Coord( 702, 519 ) );
        mapping.push_back( Coord( 716, 588 ) );

        mapping.push_back( Coord( 605, 565 ) );
        mapping.push_back( Coord( 347, 565 ) );
        mapping.push_back( Coord( 89, 565 ) );

        mapping.push_back( Coord( 82, 530 ) );
        mapping.push_back( Coord( 82, 361 ) );
        mapping.push_back( Coord( 82, 192 ) );

        mapping.push_back( Coord( 398, 413 ) );
        mapping.push_back( Coord( 524, 486 ) );

    }
    else if ( num_stage == 5 ){ // map của bàn 5 zuma

        mapping.push_back( Coord( 141, -132 ) );
        mapping.push_back( Coord( 202, 0 ) );
        mapping.push_back( Coord( 263, 132 ) );

        mapping.push_back( Coord( 192, 126 ) );
        mapping.push_back( Coord( 106, 251 ) );
        mapping.push_back( Coord( 20, 376 ) );

        mapping.push_back( Coord( 39, 566 ) );
        mapping.push_back( Coord( 156, 546 ) );
        mapping.push_back( Coord( 273, 526 ) );

        mapping.push_back( Coord( 324, -5 ) );
        mapping.push_back( Coord( 587, 48 ) );
        mapping.push_back( Coord( 850, 101 ) );

        mapping.push_back( Coord( 753, 401 ) );
        mapping.push_back( Coord( 564, 515 ) );
        mapping.push_back( Coord( 375, 629 ) );

        mapping.push_back( Coord( 114, 395 ) );
        mapping.push_back( Coord( 160, 306 ) );
        mapping.push_back( Coord( 206, 217 ) );

        mapping.push_back( Coord( 307, 271 ) );
        mapping.push_back( Coord( 397, 419 ) );
        mapping.push_back( Coord( 487, 567 ) );

        mapping.push_back( Coord( 690, 314 ) );
        mapping.push_back( Coord( 678, 208 ) );
        mapping.push_back( Coord( 666, 102 ) );

        mapping.push_back( Coord( 559, 89 ) );
        mapping.push_back( Coord( 470, 198 ) );

    }
    else if ( num_stage == 6 ){ // map của bàn 6 zuma

        mapping.push_back( Coord( 888, -20 ) );
        mapping.push_back( Coord( 798, 0 ) );
        mapping.push_back( Coord( 714, 20 ) );

        mapping.push_back( Coord( 60, 140 ) );
        mapping.push_back( Coord( 46, 254 ) );
        mapping.push_back( Coord( 32, 368 ) );

        mapping.push_back( Coord( 167, 540 ) );
        mapping.push_back( Coord( 295, 557 ) );
        mapping.push_back( Coord( 423, 574 ) );

        mapping.push_back( Coord( 726, 585 ) );
        mapping.push_back( Coord( 737, 390 ) );
        mapping.push_back( Coord( 748, 195 ) );

        mapping.push_back( Coord( 631, 29 ) );
        mapping.push_back( Coord( 314, 37 ) );
        mapping.push_back( Coord( -3, 45 ) );

        mapping.push_back( Coord( 54, 616 ) );
        mapping.push_back( Coord( 623, 437 ) );

    }
    else if ( num_stage == 7 ){ // map của bàn 7 zuma

        mapping.push_back( Coord( 966, 521 ) );
        mapping.push_back( Coord( 798, 517 ) );
        mapping.push_back( Coord( 630, 513 ) );

        mapping.push_back( Coord( 50, 644 ) );
        mapping.push_back( Coord( 50, 334 ) );
        mapping.push_back( Coord( 50, 24 ) );

        mapping.push_back( Coord( 162, 8 ) );
        mapping.push_back( Coord( 181, 251 ) );
        mapping.push_back( Coord( 200, 494 ) );

        mapping.push_back( Coord( 415, 442 ) );
        mapping.push_back( Coord( 492, 380 ) );
        mapping.push_back( Coord( 569, 318 ) );

        mapping.push_back( Coord( 608, 265 ) );
        mapping.push_back( Coord( 629, 163 ) );
        mapping.push_back( Coord( 650, 61 ) );

        mapping.push_back( Coord( 715, 31 ) );
        mapping.push_back( Coord( 740, 227 ) );
        mapping.push_back( Coord( 765, 423 ) );

        mapping.push_back( Coord( 693, 479 ) );
        mapping.push_back( Coord( 507, 456 ) );
        mapping.push_back( Coord( 321, 433 ) );

        mapping.push_back( Coord( 279, 217 ) );
        mapping.push_back( Coord( 257, 82 ) );

    }
    else if ( num_stage == 8 ){ // map của bàn 8 zuma

        mapping.push_back( Coord( 103, 765 ) );
        mapping.push_back( Coord( 94, 599 ) );
        mapping.push_back( Coord( 85, 433 ) );

        mapping.push_back( Coord( 33, 285 ) );
        mapping.push_back( Coord( 173, 163 ) );
        mapping.push_back( Coord( 313, 41 ) );

        mapping.push_back( Coord( 706, 266 ) );
        mapping.push_back( Coord( 737, 145 ) );
        mapping.push_back( Coord( 768, 24 ) );

        mapping.push_back( Coord( 91, -16 ) );
        mapping.push_back( Coord( 67, 161 ) );
        mapping.push_back( Coord( 43, 338 ) );

        mapping.push_back( Coord( 639, 144 ) );
        mapping.push_back( Coord( 719, 303 ) );
        mapping.push_back( Coord( 799, 462 ) );

        mapping.push_back( Coord( 712, 647 ) );
        mapping.push_back( Coord( 602, 490 ) );
        mapping.push_back( Coord( 492, 333 ) );

        mapping.push_back( Coord( 67, 219 ) );
        mapping.push_back( Coord( 191, 550 ) );

    }
    else if ( num_stage == 9 ){ // map của bàn 9 zuma

        mapping.push_back( Coord( -136, 713 ) );
        mapping.push_back( Coord( 5, 593 ) );
        mapping.push_back( Coord( 146, 473 ) );

        mapping.push_back( Coord( 611, 3 ) );
        mapping.push_back( Coord( 292, 48 ) );
        mapping.push_back( Coord( -27, 93 ) );

        mapping.push_back( Coord( 31, 676 ) );
        mapping.push_back( Coord( 249, 550 ) );
        mapping.push_back( Coord( 467, 424 ) );

        mapping.push_back( Coord( 527, -4 ) );
        mapping.push_back( Coord( 688, 105 ) );
        mapping.push_back( Coord( 849, 214 ) );

        mapping.push_back( Coord( 730, 628 ) );
        mapping.push_back( Coord( 647, 554 ) );
        mapping.push_back( Coord( 564, 480 ) );

        mapping.push_back( Coord( 494, 37 ) );
        mapping.push_back( Coord( 212, 211 ) );

    }
    else if ( num_stage == 10 ){ // map của bàn 10 zuma

        mapping.push_back( Coord( -143, -82 ) );
        mapping.push_back( Coord( 0, 0 ) );
        mapping.push_back( Coord( 143, 82 ) );

        mapping.push_back( Coord( 169, 233 ) );
        mapping.push_back( Coord( -32, 185 ) );
        mapping.push_back( Coord( -233, 137 ) );

        mapping.push_back( Coord( -246, 336 ) );
        mapping.push_back( Coord( 4, 300 ) );
        mapping.push_back( Coord( 254, 264 ) );

        mapping.push_back( Coord( 369, 36 ) );
        mapping.push_back( Coord( 589, 36 ) );
        mapping.push_back( Coord( 809, 36 ) );

        mapping.push_back( Coord( 981, 158 ) );
        mapping.push_back( Coord( 795, 215 ) );
        mapping.push_back( Coord( 609, 272 ) );

        mapping.push_back( Coord( 685, 513 ) );
        mapping.push_back( Coord( 627, 597 ) );
        mapping.push_back( Coord( 569, 681 ) );

        mapping.push_back( Coord( 386, 723 ) );
        mapping.push_back( Coord( 388, 599 ) );
        mapping.push_back( Coord( 390, 475 ) );

        mapping.push_back( Coord( 153, 426 ) );
        mapping.push_back( Coord( 2, 531 ) );
        mapping.push_back( Coord( -149, 636 ) );

        mapping.push_back( Coord( -270, 507 ) );
        mapping.push_back( Coord( 0, 410 ) );
        mapping.push_back( Coord( 270, 313 ) );

        mapping.push_back( Coord( 552, 550 ) );
        mapping.push_back( Coord( 624, 233 ) );

    }

    return mapping;

}

std::vector< std::pair<int, int> > loadBlockedRoad( int num_stage ){

    std::vector< std::pair<int, int> > blockedPath;

    if( num_stage == 5 ){

        blockedPath.push_back( std::pair<int, int>( 2170, 2860 ) );

    }
    else if( num_stage == 6 ){

        blockedPath.push_back( std::pair<int, int>( 450, 960 ) );
        blockedPath.push_back( std::pair<int, int>( 1350, 2130 ) );

    }
    else if( num_stage == 7 ){

        blockedPath.push_back( std::pair<int, int>( 7330, 8000 ) );

    }
    else if( num_stage == 8 ){

        blockedPath.push_back( std::pair<int, int>( 4290, 5300 ) );

    }
    else if( num_stage == 9 ){

        blockedPath.push_back( std::pair<int, int>( 1080, 1840 ) );
        blockedPath.push_back( std::pair<int, int>( 3070, 3700 ) );
        blockedPath.push_back( std::pair<int, int>( 4640, 5060 ) );

    }

    return blockedPath;

}

Coord loadFrogs( int num_stage ){

    if ( num_stage == 1 ) return Coord( 470, 300 );         // tọa độ ếch ở map 1
    else if ( num_stage == 2 ) return Coord( 678, 322 );    // tọa độ ếch ở map 2
    else if ( num_stage == 3 ) return Coord( 470, 320 );    // tọa độ ếch ở map 3
    else if ( num_stage == 4 ) return Coord( 207, 428 );    // tọa độ ếch ở map 4
    else if ( num_stage == 5 ) return Coord( 492, 344 );    // tọa độ ếch ở map 5
    else if ( num_stage == 6 ) return Coord( 392, 295 );    // tọa độ ếch ở map 6
    else if ( num_stage == 7 ) return Coord( 451, 168 );    // tọa độ ếch ở map 7
    else if ( num_stage == 8 ) return Coord( 337, 477 );    // tọa độ ếch ở map 8
    else if ( num_stage == 9 ) return Coord( 473, 488 );    // tọa độ ếch ở map 9
    else if ( num_stage == 10 ) return Coord( 453, 256 );   // tọa độ ếch ở map 10

    return Coord( 400, 300 );

}

int loadNumBalls( int num_stage ){

    if ( num_stage <= 4 ) return 4;                 // số loại bóng ở map 1, 2, 3, 4
    else if ( num_stage <= 7 ) return 5;            // số loại bóng ở map 5, 6, 7
    else if ( num_stage <= 10 ) return 6;           // số loại bóng ở map 8, 9, 10

    return 0;

}

int loadTargetNumber( int num_stage ){

    if ( num_stage <= 3 ) return 50;
    else if ( num_stage <= 6 ) return 60;
    else if ( num_stage <= 9 ) return 70;

    return 80;

}
