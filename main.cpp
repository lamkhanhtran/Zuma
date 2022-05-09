#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <time.h>
#include <math.h>

#include "Coord.h"
#include "Entity.h"
#include "BezierCurve.h"
#include "Stages.h"
#include "Button.h"
#include "Ball.h"
#include "Frog.h"
#include "LineOfBalls.h"

//************************************************************************

const int SCREEN_WIDTH = 800;           // Độ lớn của cửa sổ
const int SCREEN_HEIGHT = 600;          //

const std::string WINDOW_TITLE = "Zuma";        // Tên của cửa sổ

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

//************************************************************************

void initSDL();                         // Nguyên mẫu của function tạo cửa sổ và xem có bị lỗi không

void logSDLError( std::ostream& os, const std::string &msg, bool fatal = false );     // Nguyên mẫu của function báo lỗi nếu có

void quitSDL();                           // Nguyên mẫu của function kết thúc chương trình

void theGame();

void titleScreen();

void instructionScreen();

void updateEvent();

void updatePhysics();

void updateGraphics();

void checkingGameResult();

//************************************************************************

SDL_Texture* loadTexture( SDL_Renderer* renderer, const char* p_filePath ){         // Khai function tạo ảnh

    SDL_Texture* texture = NULL;
    SDL_Surface* image = SDL_LoadBMP( p_filePath );
	texture = SDL_CreateTextureFromSurface( renderer, image );

	if ( texture == NULL )
        logSDLError( std::cout, "Failed to load texture. Error: ", true );

    SDL_FreeSurface( image );

	return texture;

}

//************************************************************************

SDL_Window* window;                                         // Pointer đến cửa sổ
SDL_Renderer* renderer;                                     // Pointer đến bộ biểu diễn

SDL_Texture* allBallNowTexture;                             // Pointer đến ảnh bóng đang xuất hiện
SDL_Texture* allBallNextTexture;                            // Pointer đến ảnh bóng sẽ xuất hiện
SDL_Texture* allRoadTexture;                                // Pointer đến ảnh đường
SDL_Texture* allMapTexture[12];                             // Pointer đến tất cả các map

SDL_Texture* frogSpriteTexture;                             // Pointer đến ảnh ếch ở trên và ở dưới
SDL_Texture* instructionTexture;                            // Pointer đến ảnh hướng dẫn
SDL_Texture* skullTexture;                                  // Pointer đến ảnh skull cuối đường
SDL_Texture* liveTexture;

SDL_Texture *zumaWordTexture, *zumaShadowTexture;

TTF_Font* smallFont;
TTF_Font* normalFont;
TTF_Font* bigFont;


//************************************************************************

SDL_Rect zumaSrcRect;
SDL_Rect zumaWordRecDest, zumaShadowRecDest;

SDL_Rect screenRect = { 0, 0, 800, 600 };

//************************************************************************

int stateOfGame = 0;                                    // Trạng thái của game

Coord mouse;                                            // Tọa độ con chuột

Button playButton, exitButton, pauseButton;             // Các nút bấm trong game
Button instructionButton, continueButton;               //

bool gameRunning = true;                                // Tình trạng game có đang chạy hay không

int lives;                                              // Số lần có thể chơi

int level;                                              // Bàn thứ

bool gameEnded;                                         // Tình trạng game kết thúc
bool gameWinning;                                       // Tình trạng game thắng hay không
bool gameStop;                                          // Tình trạng game dừng

const float smallestVelocity = 0.25;                    // Tốc độ dịch chuyển không đổi bé nhất trên đường

std::vector<Coord> controlPoints;                               // Bộ điểm của các đường cong Bezier trên map
std::vector<Coord> roadPoints;                                  // Tạo các điểm trên đường để sử dụng cho bộ vẽ
std::vector<Coord> movementPoints;                              // Iterator các vị trí để tạo đoạn mà tạo cảm giác tốc độ constant
std::vector< std::pair<int, int> > blockedMovementPoints;       // Các đoạn mà bóng không được cho phép tiếp xúc

LineOfBalls ballList = LineOfBalls( NULL, NULL, NULL, movementPoints, blockedMovementPoints, -1, 0 ); // Đường bóng ( cả path lẫn bóng ở trên đường )

Coord frogSitting;                                      // Vị trí ếch ngồi
float angle;                                            // Hướng của ếch nhắm
Frog froggie;                                           // Cả con ếch

Ball shotBall;                                          // Bóng bị bắn ra
float angleShot;                                        // Hướng di chuyển của bóng bị bắn
int posShotDistFromTop = -1;                            // Vị trí bóng chạm xét từ bóng gần lỗ nhất
int posConnect = -1;                                    // Kiểm tra nổ bóng cùng màu và kết nối các quả bóng lại

bool ballShotTouch = false;                             // Tình trạng bóng bắn bị chạm
bool ballInLineConnect = false;                         // Tình trạng bóng dồn sau khi có bóng cùng màu
std::vector<int> pushBack;                              // Các vị trí tính từ bóng gần lỗ nhất đang dồn về

//************************************************************************

/**void createCircle( SDL_Renderer* renderer, Coord pos, float radius ){

    float centerX = pos.x;
    float centerY = pos.y;
    int dx = radius;
    int dy = 0;
    int err = 0;

    while (dx >= dy) {

        SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
        SDL_RenderDrawPoint(renderer, centerX + dy, centerY + dx);
        SDL_RenderDrawPoint(renderer, centerX - dy, centerY + dx);
        SDL_RenderDrawPoint(renderer, centerX - dx, centerY + dy);
        SDL_RenderDrawPoint(renderer, centerX - dx, centerY - dy);
        SDL_RenderDrawPoint(renderer, centerX - dy, centerY - dx);
        SDL_RenderDrawPoint(renderer, centerX + dy, centerY - dx);
        SDL_RenderDrawPoint(renderer, centerX + dx, centerY - dy);

        if (err <= 0) {
            dy += 1;
            err += 2*dy + 1;
        }

        if (err > 0) {
            dx -= 1;
            err -= 2*dx + 1;
        }
    } // while
} // createCircle()
**/
int main(int argc, char *argv[]){


    srand(time(0));                                                                 // Tạo ra sự random

    initSDL();                                                                      // Khởi tạo window

    frogSpriteTexture = loadTexture( renderer, "Resource/gfx/frogSprite.bmp");      // Load các ảnh của ếch
    allRoadTexture = loadTexture( renderer, "Resource/gfx/roadSkin.bmp");           // Load các ảnh của đường bóng
    allBallNowTexture = loadTexture( renderer, "Resource/gfx/ballNow.bmp");         // Load các ảnh của b
    allBallNextTexture = loadTexture( renderer, "Resource/gfx/ballNext.bmp");       // Load các ảnh của bóng nhỏ
    instructionTexture = loadTexture( renderer, "Resource/gfx/instruction.bmp");    // Load ảnh đuôi đường đi
    skullTexture = loadTexture( renderer, "Resource/gfx/skull.bmp");                // Load ảnh đuôi đường đi

    for(int i=1; i<11; i++){
        std::string path = "Resource/gfx/map_" + std::to_string(i) + ".bmp";
        allMapTexture[i] = loadTexture( renderer, path.c_str() );
    }

    liveTexture = loadTexture( renderer, "Resource/gfx/live.bmp");


    smallFont = TTF_OpenFont( "Resource/font/OrelegaOne-Regular.ttf", 12 );         // Load font chữ nhỏ
    normalFont = TTF_OpenFont( "Resource/font/OrelegaOne-Regular.ttf", 40 );        // Load font chữ vừa
    bigFont = TTF_OpenFont( "Resource/font/OrelegaOne-Regular.ttf", 80 );           // Load font chữ to



    SDL_Surface* surfaceMessage1 = TTF_RenderText_Blended( bigFont, "ZUMA", YELLOW_COLOR );     // Tạo chữ zuma
    SDL_Surface* surfaceMessage2 = TTF_RenderText_Blended( bigFont, "ZUMA", BLACK_COLOR );      // Tạo bóng zuma

    zumaWordTexture = SDL_CreateTextureFromSurface( renderer, surfaceMessage1 );                // Biến chữ thành texture
    zumaShadowTexture = SDL_CreateTextureFromSurface( renderer, surfaceMessage2 );              // Biến bóng thành texture

    zumaSrcRect = { 0, 0, surfaceMessage1->w, surfaceMessage1->h };                                                                                 // Lấy hình zuma
    zumaWordRecDest = { 400 - (surfaceMessage1->w / 2) - 1, 100 - (surfaceMessage1->h / 2) - 1, surfaceMessage1->w, surfaceMessage1->h };           // Lấy vị trí in hình zuma
    zumaShadowRecDest = { 400 - (surfaceMessage1->w / 2) + 1, 100 - (surfaceMessage1->h / 2) + 1, surfaceMessage1->w, surfaceMessage1->h };         // Lấy vị trí in bóng zuma

    SDL_FreeSurface( surfaceMessage1 );             // Xóa tạo chữ
    SDL_FreeSurface( surfaceMessage2 );             // Xóa tạo bóng

    playButton.setButton( renderer, "PLAY", normalFont, YELLOW_COLOR, Coord( 400, 400 ) );              // Setup nút chơi
    exitButton.setButton( renderer, "EXIT", normalFont, YELLOW_COLOR, Coord( 400, 500 ) );              // Setup nút thoát
    pauseButton.setButton( renderer, "I I", normalFont, YELLOW_COLOR, Coord( 20, 20 ) );                // Setup nút dừng
    instructionButton.setButton( renderer, "INSTRUCTION", normalFont, YELLOW_COLOR, Coord( 400, 450 ) );// Setup nút dừng
    continueButton.setButton( renderer, "CONTINUE", normalFont, YELLOW_COLOR, Coord( 400, 250 ) );      // Setup nút tiếp tục

//*******************************************************************************************************************************

    SDL_Event e;

    mouse = Coord( e.button.x, e.button.y );

    lives = 3;

    level = 0;

    frogSitting = loadFrogs(level);                       // Vị trí của ếch trên map
    angle = SDL_atan2( mouse.y - frogSitting.y, mouse.x - frogSitting.x);// * ( 180 / M_PI );

    froggie = Frog( frogSpriteTexture, allBallNowTexture, allBallNextTexture, frogSitting, angle, loadNumBalls(level) );

	Uint32 totalFrameTicks = 0;
	Uint32 totalFrames = 0;

//*************************************************************************************************************************

    while(gameRunning){

        totalFrames++;
		Uint32 startTicks = SDL_GetTicks();
		Uint64 startPerf = SDL_GetPerformanceCounter();

        theGame();

        SDL_Delay(10);



        Uint32 endTicks = SDL_GetTicks();
		Uint64 endPerf = SDL_GetPerformanceCounter();
		Uint64 framePerf = endPerf - startPerf;
		float frameTime = (endTicks - startTicks) / 1000.0f;
		totalFrameTicks += endTicks - startTicks;

		// Strings to display
		std::string fps = "Current FPS: " + std::to_string(1.0f / frameTime);
		std::string avg = "Average FPS: " + std::to_string(1000.0f / ((float)totalFrameTicks / totalFrames));
		std::string perf = "Current Perf: " + std::to_string(framePerf);

		std::cout << fps << '\n' << avg << '\n' << perf << '\n';


    }

    quitSDL();

    return 0;
}

//************************************************************************

void initSDL(){

    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
        logSDLError( std::cout, "SDL_Init", true );

    if ( TTF_Init() )
		logSDLError( std::cout, "TTF_Init", true );

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if(window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);
    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if(renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

//**************************************************************************

void logSDLError(std::ostream& os, const std::string &msg, bool fatal){ // Khai function báo lỗi nếu có

    os << msg << " Error: " << SDL_GetError() << std::endl;

    if ( fatal ){
        SDL_Quit();
        exit(1);
    }

}

//**************************************************************************

void quitSDL(){

    SDL_DestroyTexture( allBallNowTexture );                             // Xóa pointer đến ảnh bóng đang xuất hiện
    SDL_DestroyTexture( allBallNextTexture );                            // Xóa pointer đến ảnh bóng sẽ xuất hiện
    SDL_DestroyTexture( allRoadTexture );                                // Xóa pointer đến ảnh đường

    SDL_DestroyTexture( frogSpriteTexture );                             // Xóa pointer đến ảnh ếch ở trên và ở dưới
    SDL_DestroyTexture( instructionTexture );                            // Xóa pointer đến ảnh hướng dẫn
    SDL_DestroyTexture( skullTexture );                                  // Xóa pointer đến ảnh skull cuối đường
    SDL_DestroyTexture( liveTexture );                                   // Xóa pointer đến ảnh mạng

    SDL_DestroyTexture( zumaWordTexture );                               // Xóa pointer đến ảnh word zuma
    SDL_DestroyTexture( zumaShadowTexture );                             // Xóa pointer đến ảnh shadow zuma

    for(int i=1; i<11; i++)
        SDL_DestroyTexture( allMapTexture[i] );                          // Xóa pointer đến ảnh các map

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

}

//**************************************************************************

void theGame(){

    if( stateOfGame == 0 )
        titleScreen();
    else if( stateOfGame == 1 )
        instructionScreen();
    else if( stateOfGame == 2 ){
        updateEvent();
        if( !gameStop )
            updatePhysics();
        updateGraphics();
    }
    else if( stateOfGame == 3 )
        checkingGameResult();

}

//**************************************************************************

void titleScreen(){


    SDL_Event e;

    while( SDL_PollEvent(&e) != 0 ){
        switch(e.type){

        case SDL_QUIT:
            gameRunning = false;
            break;

        case SDL_MOUSEMOTION:
            mouse = Coord( e.button.x, e.button.y );
            angle = SDL_atan2( mouse.y - frogSitting.y, mouse.x - frogSitting.x);
            break;

        case SDL_MOUSEBUTTONUP:
            if ( e.button.button == SDL_BUTTON_LEFT ){

                if( playButton.update( mouse ) ){

                    exitButton.pos = Coord( 400, 300 );

                    level = 1;

                    stateOfGame = 2;

                    gameEnded = false;
                    gameWinning = true;
                    gameStop = false;

                    controlPoints = loadMaps( level );
                    roadPoints = loadRoad( controlPoints );
                    movementPoints = loadMovement( roadPoints, smallestVelocity );
                    blockedMovementPoints = loadBlockedRoad( level );

                    shotBall = Ball();
                    angleShot = 0;

                    frogSitting = loadFrogs(level);
                    angle = SDL_atan2( mouse.y - frogSitting.y, mouse.x - frogSitting.x);

                    froggie = Frog( frogSpriteTexture, allBallNowTexture, allBallNextTexture, frogSitting, angle, loadNumBalls(level) );

                    ballList = LineOfBalls( allRoadTexture, allBallNowTexture, skullTexture, movementPoints, blockedMovementPoints, loadNumBalls(level), loadTargetNumber(level) );

                }
                else if( instructionButton.update( mouse ) ){

                    continueButton.pos = Coord( 700, 575 );

                    stateOfGame = 1;

                }
                else if( exitButton.update( mouse ) )
                    gameRunning = false;

            }
            break;

        }
    }

    froggie.update( angle, true );

    SDL_SetRenderDrawColor( renderer, WHITE_COLOR.r, WHITE_COLOR.g, WHITE_COLOR.b, WHITE_COLOR.a );
    SDL_RenderClear( renderer );

    SDL_RenderCopy( renderer, zumaShadowTexture, &zumaSrcRect, &zumaShadowRecDest );
    SDL_RenderCopy( renderer, zumaWordTexture, &zumaSrcRect, &zumaWordRecDest );

    froggie.drawGraphic( renderer );

    playButton.drawGraphic( renderer );
    instructionButton.drawGraphic( renderer );
    exitButton.drawGraphic( renderer );

    SDL_RenderPresent( renderer );


}

//**************************************************************************

void instructionScreen(){

    SDL_Event e;

    while( SDL_PollEvent(&e) != 0 ){
        switch(e.type){

        case SDL_QUIT:
            gameRunning = false;
            break;

        case SDL_MOUSEMOTION:
            mouse = Coord( e.button.x, e.button.y );
            break;

        case SDL_MOUSEBUTTONUP:
            if ( e.button.button == SDL_BUTTON_LEFT ){

                if( continueButton.update( mouse ) ){

                    continueButton.pos = Coord( 400, 250 );

                    stateOfGame = 0;

                }

            }
            break;

        }
    }

    SDL_RenderCopy( renderer, instructionTexture, &screenRect, &screenRect );

    continueButton.drawGraphic( renderer );

    SDL_RenderPresent( renderer );

}

//**************************************************************************

void updateEvent(){

    SDL_Event e;

    while( SDL_PollEvent(&e) != 0 ){
        switch(e.type){

        case SDL_QUIT:
            gameRunning = false;
            break;

        case SDL_MOUSEMOTION:
            mouse = Coord( e.button.x, e.button.y );
            angle = SDL_atan2( mouse.y - frogSitting.y, mouse.x - frogSitting.x);
            break;

        case SDL_MOUSEBUTTONUP:
            if ( e.button.button == SDL_BUTTON_RIGHT && !gameEnded && gameWinning ){

                /**if ( level < 10)
                    level++;
                else
                    level = 1;

                controlPoints = loadMaps( level );
                roadPoints = loadRoad( controlPoints );
                movementPoints = loadMovement( roadPoints, smallestVelocity );
                blockedMovementPoints = loadBlockedRoad( level );

                if( shotBall.pos != nullCoord ){
                    shotBall = Ball();
                    angleShot = 0;
                }

                frogSitting = loadFrogs(level);                                     // Vị trí của ếch trên map
                angle = SDL_atan2( mouse.y - frogSitting.y, mouse.x - frogSitting.x);

                froggie = Frog( frogSpriteTexture, allBallNowTexture, allBallNextTexture, frogSitting, angle, loadNumBalls(level) );

                ballList = LineOfBalls( allRoadTexture, allBallNowTexture, skullTexture,
                                        movementPoints, blockedMovementPoints, loadNumBalls(level), loadTargetNumber(level) ); */

                froggie.swapBalls();

            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if( e.button.button == SDL_BUTTON_LEFT && !gameEnded && gameWinning ){

                if( gameStop && continueButton.update( mouse ) )
                    gameStop = false;
                else if( gameStop && exitButton.update( mouse ) ){

                    exitButton.pos = Coord( 400, 500 );

                    stateOfGame = 0;

                    mouse = Coord( e.button.x, e.button.y );

                    gameStop = false;

                    lives = 3;

                    level = 0;

                    frogSitting = loadFrogs(level);
                    angle = SDL_atan2( mouse.y - frogSitting.y, mouse.x - frogSitting.x);

                    froggie = Frog( frogSpriteTexture, allBallNowTexture, allBallNextTexture, frogSitting, angle, loadNumBalls(level) );

                }
                else if( pauseButton.update( mouse ) )
                    gameStop = true;
                else if( shotBall.pos == nullCoord && froggie.frameShot == 0){

                    shotBall = froggie.shootBalls();
                    angleShot = froggie.angle;

                }

            }
            break;

        }
    }

}

//**************************************************************************

void updatePhysics(){

    froggie.update( angle, gameWinning );

    if( posConnect != -1 ){

        pushBack.push_back( posConnect );
        posConnect = -1;

    }

    for( int i = pushBack.size()-1, n = 0; i>=n; i-- ){

        bool ballTouch = ballList.returnDisconnectBalls( pushBack[i] );
        if( ballTouch ){

            int posBall = ballList.deleteSameBallsIfPossible( pushBack[i] );
            pushBack.erase( pushBack.begin() + i );
            if( posBall != -1 )
                pushBack.push_back( posBall );

        }

    }

    if( pushBack.empty() )
        ballInLineConnect = false;

    if( ballShotTouch ){

        posConnect = ballList.deleteSameBallsIfPossible( posShotDistFromTop );
        ballShotTouch = false;
        ballInLineConnect = true;

    }

    if( shotBall.pos != nullCoord ){

        posShotDistFromTop = ballList.collisionDetect( shotBall );
        if( posShotDistFromTop != -1 ){

            shotBall = Ball();
            angleShot = 0;
            ballShotTouch = true;

        }
        else{

            float dx = cos( angleShot ) * 15;
            float dy = sin( angleShot ) * 15;
            shotBall.update( shotBall.pos + Coord(dx, dy) );
            if( shotBall.pos.x > 820 || shotBall.pos.x < -20 || shotBall.pos.y > 620 || shotBall.pos.y < -20 ){

                shotBall = Ball();
                angleShot = 0;

            }

        }

    }

    if( !ballInLineConnect )
        ballList.moveBalls(0);

    gameEnded = ballList.checkEnding();
    gameWinning = ballList.winGame;

    if( gameEnded )
        stateOfGame = 3;

}

//**************************************************************************

void updateGraphics(){

    SDL_RenderClear( renderer );
    SDL_RenderCopy( renderer, allMapTexture[ level ], &screenRect, &screenRect );

    ballList.drawGraphic( renderer, level );

    froggie.drawGraphic( renderer );

    if( shotBall.pos != nullCoord )
        shotBall.drawGraphic( renderer );

    pauseButton.drawGraphic( renderer );
    SDL_Rect liveSrcRect = { 0, 0, 23, 23 }, livesRect = { 42, 0, 76, 25 };
    SDL_RenderFillRect( renderer, &livesRect );
    for(int i=0; i<lives; i++){
        SDL_Rect liveRecDest = { 43 + i*25, 1, 23, 23};
        SDL_RenderCopy( renderer, liveTexture, &liveSrcRect, &liveRecDest );
    }

    if( gameStop ){
        SDL_SetRenderDrawColor( renderer, 104, 104, 104, 104 );
        SDL_Rect pauseRect = { 250, 200, 300, 150 };
        SDL_RenderFillRect( renderer, &pauseRect );
        continueButton.drawGraphic( renderer );
        exitButton.drawGraphic( renderer );
    }

    SDL_RenderPresent(renderer);

}

void checkingGameResult(){

    if( gameWinning ){

        level++;
        if ( level > 10 ){
            stateOfGame = 0;
            return;
        }

    }
    else{

        lives--;
        if( !lives ){
            level = 1;
            lives = 3;
        }

    }

    stateOfGame = 2;

    gameEnded = false;
    gameWinning = true;
    gameStop = false;

    controlPoints = loadMaps( level );
    roadPoints = loadRoad( controlPoints );
    movementPoints = loadMovement( roadPoints, smallestVelocity );
    blockedMovementPoints = loadBlockedRoad( level );

    shotBall = Ball();
    angleShot = 0;

    frogSitting = loadFrogs(level);                                             // Vị trí của ếch trên map
    angle = SDL_atan2( mouse.y - frogSitting.y, mouse.x - frogSitting.x);

    froggie = Frog( frogSpriteTexture, allBallNowTexture, allBallNextTexture, frogSitting, angle, loadNumBalls(level) );

    ballList = LineOfBalls( allRoadTexture, allBallNowTexture, skullTexture, movementPoints, blockedMovementPoints, loadNumBalls(level), loadTargetNumber(level) );

}
