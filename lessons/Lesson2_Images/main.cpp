#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Rendering window
SDL_Window* gWindow = NULL;

//Window surface
// SURFACES are image data types that render pixels to the screen this uses CPU TO RENDER
SDL_Surface* gScreenSurface = NULL;

//Image that we load and show on the screen
SDL_Surface* gHelloWorld = NULL;

int run_Lesson2_Images(int argc, char* args[]) {
    if (!init()){
        cout << "Failed to initialize";
    }
    else{
        if (!loadMedia()){
            cout << "Failed to load media";
        }
        else{
            //Copying image from surface 1(laoded image) tp surface 3 (window surafce)
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            //updating window surafce
            SDL_UpdateWindowSurface(gWindow);

            //window hack
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
        }
    }
    
    //free resources and close
    close();
    return 0;
}


bool init(){
    // INIT flag
    bool success = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Could not be initialized erorr: " << SDL_GetError();
        success = false;
    }
    else{
        //create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL){
            cout << "Window could not be created, Error: " << SDL_GetError();
            success = false;
        }
        else{
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}



bool loadMedia(){
    //flag
    bool success = true;

    //load splash image
    gHelloWorld = SDL_LoadBMP("lessons/Lesson2_Images/hello_world.bmp");
    if (gHelloWorld == NULL){
        cout << "Unable to load image hello_world.bmp, Error: " << SDL_GetError();
        success = false;
    }
    return success;

}

void close(){
    //Deallocate Surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //Destroy Window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit systems
    SDL_Quit();
}
