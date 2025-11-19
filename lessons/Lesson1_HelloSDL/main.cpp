#include <SDL2/SDL.h>
#include <iostream>

namespace Lesson1_HelloSDL{
    //Screen dimemnsion constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;


    int run_Lesson1_HelloSDL(int argc, char* args[]) {
        
        //Window that we render to
        SDL_Window* window = NULL;

        //Surface that is contained by the window
        SDL_Surface* screenSurface = NULL;

        //Initializing SDL
        // Required for SDL functions to work
        //only initializing SDL video subsystem for now
        //SDL returns -1 if error
        if (SDL_Init(SDL_INIT_VIDEO) <0 ){
            std::cout << "SDL could not initialize, ERROR: " << SDL_GetError();
            return 1;
        }
        else{
            //create the window
            window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == NULL){
                std::cout << "Window could not be created: " << SDL_GetError();
                return 1;
            }
            else{
                //GEtting window surface
                screenSurface = SDL_GetWindowSurface(window);

                //Filling it with white
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));

                //updating window surface
                //AFTER DRAWING NEED TO UPDATE **
                SDL_UpdateWindowSurface(window);

                //getting window to stay up
                // HACK NOT USED LATER ON
                SDL_Event e;
                bool quit = false;
                while (quit == false)
                {
                    while (SDL_PollEvent(&e))
                    {
                        if (e.type == SDL_QUIT){
                            quit = true;
                        }
                    }
                    
                }
                
                //Destroying window and quitting sdl
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;

            }
        }
    }
}