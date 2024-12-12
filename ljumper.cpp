#define fps 60
#include "sdlstuff.cpp"
#include "globalvars.h"
#include "tile.h"
#include "physics.h"
#include "renderer.h"
#include "particles.h"
#include "player.h"
#include "media.cpp"
#include "physics.cpp"
#include "renderer.cpp"
#include "tile.cpp"
#include "particles.cpp"
#include "player.cpp"
#include "leveleditor.h"
#include "leveleditor.cpp"
#include "cutscenes.cpp"

int main(int argc, char* args[]) {
  init();
  loadMedia();
  setTiles(tileSet);
  bool quit = false;
  SDL_Event e;
  hildegarde.gTexture = &gHGTexture;
  hildegarde.posX = 864;
  hildegarde.posY = 832;
  hildegarde.defaultPosX = 864;
  hildegarde.defaultPosY = 832;
			      
  while(!quit) {
    Uint32 starting_tick = SDL_GetTicks();

    SDL_Rect bgBox = {0,0,MAP_WIDTH,MAP_HEIGHT};
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
    SDL_SetRenderDrawColor(gRenderer, 25, 50, 70, 255);
    SDL_RenderFillRect(gRenderer, &bgBox);
    
    player.setCamera(camera);
    for(int i = 0; i < TOTAL_TILES; i++) {
      tileSet[i]->render(camera, true);
    }
    hildegarde.moveHG(tileSet);
    hildegarde.render(camera);
    player.move(tileSet);
    player.render(camera);
    for(int i = 0; i < TOTAL_TILES; i++) {
      if(tileSet[i]->renderOver)
	tileSet[i]->render(camera, false);
    }

    levelEditor.select();
    
    while(SDL_PollEvent(&e) != 0){
      //User requests quit
      if(e.type == SDL_QUIT)
	quit = true;
      if(debugMode) {
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
	  if(e.key.keysym.sym == SDLK_b) {
	    if(showHitBoxes)
	      showHitBoxes = false;
	    else
	      showHitBoxes = true;
	  }
	  if(e.key.keysym.sym == SDLK_g) {
	    if(godMode)
	      godMode = false;
	    else
	      godMode = true;
	  }
	}
      }
      player.handleEvent(e);
    }

    if(isCutscene) {
      cutscene.play();
      cutscene.handleEvent(e, false);
    }
    
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
    if( (1000/fps) > SDL_GetTicks() - starting_tick ) {
      SDL_Delay(1000/fps - (SDL_GetTicks() - starting_tick));
    }
  }
  close();
}
