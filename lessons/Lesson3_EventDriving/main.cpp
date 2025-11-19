#include <SDL2/SDL.h>
#include <iostream>

namespace Lesson3_EventDriving{
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
    SDL_Surface* gXout = NULL;

    int run_Lesson3_EventDriving(int argc, char* args[]) {
        if (!init()){
            cout << "Failed to initialize";
            return 1;
        }
        if (!loadMedia()){
            cout << "Failed to load media";
            return 1;
        }


        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While application is running; MAIN LOOP
        while (!quit)
        {

            //Handle events on queue
            // PLACED AT TOP OF MAIN LOOP
            // KEEPS POLLING FFROM THE EVENT QUEUE
            //RETURNS 0 WHEN THERE ARE NO MORE EVENTS LEFT TO HANDLE (queue is empty)
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT){
                    quit = true;
                }
            }


            //Copying image from surface 1(laoded image) tp surface 3 (window surafce)
            SDL_BlitSurface(gXout, NULL, gScreenSurface, NULL);

            //updating window surafce
            SDL_UpdateWindowSurface(gWindow);


            
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
        gXout = SDL_LoadBMP("lessons/Lesson3_EventDriving/x.bmp");
        if (gXout == NULL){
            cout << "Unable to load image x.bmp, Error: " << SDL_GetError();
            success = false;
        }
        return success;

    }

    void close(){
        //Deallocate Surface
        SDL_FreeSurface(gXout);
        gXout = NULL;

        //Destroy Window
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;

        //Quit systems
        SDL_Quit();
    }
}