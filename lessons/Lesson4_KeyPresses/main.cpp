#include <iostream>
#include <SDL2/SDL.h>
namespace Lesson4_KeyPresses{
using namespace std;

    //Creating Enum for all the different keypresses
    //Key presses surfaces constants
    enum KeyPressSurfaces{
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //Starts up SDL and creates window
    bool init();

    //loads media
    bool loadMedia();

    //Frees media and shuts down SDL
    void close();

    //Loads individual image
    SDL_Surface* loadSurface(string path);

    //Rendering window
    SDL_Window* gWindow = NULL;

    //Window surface
    // SURFACES are image data types that render pixels to the screen this uses CPU TO RENDER
    SDL_Surface* gScreenSurface = NULL;

    //Images that correspond to a keypress
    SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

    //Current displayed surface
    SDL_Surface* gCurrentSurface = NULL;

    int run_Lesson4_KeyPresses(int argc, char* args[]) {
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

        //Setting default surface
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

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

                //User presses key
                else if (e.type == SDL_KEYDOWN){

                    //Select surfaces based on key press
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_UP:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    
                    default:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                    }

                }
            }


            //Copying image from surface 1(laoded image) tp surface 3 (window surafce)
            SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

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

        //load default surface
        gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("lessons/Lesson4_KeyPresses/press.bmp");
        if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
            cout << "Filed to load default image";
            success = false;
        }

        // Load up surface
        gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("lessons/Lesson4_KeyPresses/up.bmp");
        if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL){
            cout << "Filed to load up image";
            success = false;
        }

        gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("lessons/Lesson4_KeyPresses/down.bmp");
        if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL){
            cout << "Filed to load down image";
            success = false;
        }


        gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("lessons/Lesson4_KeyPresses/left.bmp");
        if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
            cout << "Filed to load left image";
            success = false;
        }


        gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("lessons/Lesson4_KeyPresses/right.bmp");
        if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL){
            cout << "Filed to load right image";
            success = false;
        }

        return success;

    }

    void close(){

        //Deallocate array surfaces
        for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i ++){
            SDL_FreeSurface(gKeyPressSurfaces[i]);
            gKeyPressSurfaces[i] = NULL;
        }

        //Destroy Window
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;

        //Quit systems
        SDL_Quit();
    }

    SDL_Surface* loadSurface(string path){
        //load image at specified file
        SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
        if (loadedSurface == NULL){
            cout << "Unable to load image, " << path.c_str() << " Error: " << SDL_GetError();
        }

        return loadedSurface;
    }

}
