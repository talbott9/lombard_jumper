#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>

SDL_Window* gWindow = NULL;
SDL_GameController* gGameController = NULL;
SDL_Joystick* gJoystick = NULL;
const int JOYSTICK_DEAD_ZONE = 8000;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
SDL_Renderer* gRenderer = NULL;
const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
bool controller;

bool init()
{
  //Initialization flag
  bool success = true;

  srand(time(NULL));

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    if(SDL_NumJoysticks() >= 1) {
      gGameController = SDL_GameControllerOpen(0);
      gJoystick = SDL_GameControllerGetJoystick(gGameController);
      if(gGameController == NULL)  {
	printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
      }
      if(gJoystick == NULL)  {
	printf( "Warning: Unable to open joystick! SDL Error: %s\n", SDL_GetError() );
      }
    }
    //Set texture filtering to linear
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 	{
      printf("Warning: Linear texture filtering not enabled!");
    }

    //Create window
    gWindow = SDL_CreateWindow("Lombard Jumper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      //Create vsynced renderer for window
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if(gRenderer == NULL)	{
	printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	success = false;
      } else {
	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init( imgFlags ) & imgFlags)) {
	  printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	  success = false;
	}

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
	  printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	  success = false;
	}

	if( Mix_AllocateChannels(10) < 0 )
	  {
	    fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
	    exit(-1);
	  }

	//Initialize SDL_ttf
	if(TTF_Init() == -1)  {
	  printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	  success = false;
	}
      }
    }
  }
  return success;
}

void close() {
  //Destroy window	
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  SDL_GameControllerClose( gGameController );
  gGameController = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  Mix_Quit();
  SDL_Quit();
}
