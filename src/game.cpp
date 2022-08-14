#include <headers/games.h>
#include <headers/window.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer *Game::ren = nullptr;
TTF_Font * ourFont;
Game::Game(){
    window = nullptr;
    screenHeight = 600;
    screenWidth = 1024;
    gameState = GameState::PLAY;

};
Game::~Game(){};

void Game::run(){
    init("Bricks Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,screenWidth, screenHeight ,SDL_WINDOW_SHOWN);
    gameLoop();
}

SDL_Rect rect = { 830, 0, 215, 215};

void Game::init(const char *title, int x, int y, int w, int h, Uint32 flags){
    SDL_Init(SDL_INIT_EVERYTHING); //initialize sdl

    //create a window
    window = SDL_CreateWindow(title, x, y, w, h,flags);
    if(window==NULL){
        std::cout<<"There was error initialzing the window"<<std::endl;
        std::cout<<SDL_GetError()<<std::endl;
    }

    //render window
    SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    
    //initialize image
    int imgFlags = IMG_INIT_PNG;
    int initstatus = IMG_Init(imgFlags);
    if((initstatus & flags)!=flags){
        std::cout<<"Failed to initialize SDL_image"<<std::endl;
    }

    //load image
    SDL_Surface *image,*button;
    image = IMG_Load("images/unnamed.png");
    if(!image){
        std::cout<<"Image not loaded"<<std::endl;
    }
    button = IMG_Load("images/playbutton.png");
    if(!button){
        std::cout<<"button not loaded"<<std::endl;
    }

    //rectangle image background
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 850;
    rectangle.h = 600;

    //rectangle for menu background
    SDL_Rect rect1;
    rect1.x = 800;
    rect1.y = 0;
    rect1.h = 900;
    rect1.w = 500;


    //render iamge
    SDL_Texture * ourPNG = SDL_CreateTextureFromSurface(ren,image);
    SDL_Texture *play = SDL_CreateTextureFromSurface(ren,button);
    SDL_SetRenderDrawColor(ren, 0, 130, 127, 127);
    SDL_RenderFillRect(ren, &rect1);
    SDL_RenderCopy(ren, ourPNG, NULL,&rectangle);
    SDL_RenderCopy(ren, play, NULL, &rect);
    

    SDL_RenderPresent(ren);
}

void Game::gameLoop(){

    while(gameState != GameState::EXIT){
        handleEvents();
    }
    
}

void Game::handleEvents(){
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        if (evnt.type == SDL_QUIT)
        { 
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(ren);
            SDL_Quit();
            TTF_Quit();
        }
    

        if(SDL_MOUSEBUTTONDOWN == evnt.type)
        {
            SDL_Point mousePosition;
            // Mouse click coords from event handler
            mousePosition.x = evnt.motion.x; 
            mousePosition.y = evnt.motion.y;

            if (SDL_PointInRect(&mousePosition, &rect)) {
                std::cout<<"mouse is pressed"<<std::endl;
                SDL_DestroyWindow(window);
                Window window;
                window.run();

            }
        
        }
    }

}