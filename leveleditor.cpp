LevelEditor::LevelEditor() {
  int x = 0, y = 0;
  for(int i = 0; i < TOTAL_TILES; i++) {
    tileBoxes[i] = {x-camera.x, y-camera.y, TILE_WIDTH, TILE_HEIGHT};
    
    x += TILE_WIDTH;
    //If we've gone too far
    if( x >= MAP_WIDTH ) {
      //Move back
      x = 0;

      //Move to the next row
      y += TILE_HEIGHT;
    }
    
  }
}

void LevelEditor::readTileMap(Tile* tiles[]) {
  freeTileSet(tileSet);
  int x = 0, y = 0;
  std::ifstream map0("resources/tiles/map0.map");
  std::ofstream newmap("resources/tiles/newlevel.map");
  for(int i = 0; i < TOTAL_TILES; i++) {
    int tileType = -1;

    switch(mapID) {
    case 0: map0 >> tileType; break;
    }
    if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) ) {
      if(selectedTile.x+camera.x == x && selectedTile.y+camera.y == y) {
	tileType = selTileType;
	printf("at %i/%i\n", x,y);
      }
      tiles[i] = new Tile( x, y, tileType );
      newmap << "0"+std::to_string(tileType)+" ";
    } else {
      //Stop loading map
      printf( "Error loading map: Invalid tile type %i at %d!\n", tileType, i);
      break;
    }
    //Move to next tile spot
    x += TILE_WIDTH;
    //If we've gone too far
    if( x >= MAP_WIDTH ) {
      //Move back
      x = 0;

      //Move to the next row
      y += TILE_HEIGHT;
    }
  }
  //remove("resources/tiles/map0.map");
  map0.close();
  newmap.close();
  std::string line;
  std::ifstream ini_file("resources/tiles/newlevel.map");
  std::ofstream out_file("resources/tiles/map0.map"); 
  if(ini_file && out_file) {
    while (getline(ini_file, line)) { 
      out_file << line << "\n"; 
    } 
  }
  ini_file.close(); 
  out_file.close(); 
  //std::ifstream newmap1("resources/tiles/newlevel.map");
  /*std::string mstring;
  while(std::getline(newmap1, mstring)) {
      //Do with temp
      }*/
  //std::ofstream map01("resources/tiles/map0.map");
  //map01 << mstring;
}

void LevelEditor::select() {
  bool mouseLeft, mouseRight, oneKey, twoKey;
  mouseLeft = SDL_GetMouseState(&mouseX, &mouseY) == 1;
  mouseRight = SDL_GetMouseState(&mouseX, &mouseY) == 4;
  oneKey = currentKeyStates[SDL_SCANCODE_1];
  twoKey = currentKeyStates[SDL_SCANCODE_2];
  mouseBox = {mouseX,mouseY,1,1};
  int x = 0, y = 0;
  for(int i = 0; i < TOTAL_TILES; i++) {
    tileBoxes[i] = {x-camera.x, y-camera.y, TILE_WIDTH, TILE_HEIGHT};
    
    x += TILE_WIDTH;
    //If we've gone too far
    if( x >= MAP_WIDTH ) {
      //Move back
      x = 0;

      //Move to the next row
      y += TILE_HEIGHT;
    }
    if(checkCollision(mouseBox,tileBoxes[i])) {
      gTileTexture.render(tileBoxes[i].x, tileBoxes[i].y, &gTileClips[selTileType]);
      SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
      SDL_SetRenderDrawColor(gRenderer, 255, 100, 100, 100);
      SDL_RenderFillRect(gRenderer, &tileBoxes[i]);
      selectedTile = tileBoxes[i];
    }
  }
  if(oneKey) {
    if(!pressedKey[onekey]) {
      pressedKey[onekey] = true;
      selTileType--;
      if(selTileType < 0)
	selTileType = 0;
    }
    pressedKey[onekey] = true;
  } else {
    pressedKey[onekey] = false;
  }
  if(twoKey) {
    if(!pressedKey[twokey]) {
      pressedKey[twokey] = true;
      selTileType++;
      if(selTileType > TOTAL_TILE_SPRITES-1)
	selTileType = TOTAL_TILE_SPRITES-1;
    }
    pressedKey[twokey] = true;
  } else {
    pressedKey[twokey] = false;
  }
  if(mouseLeft) {
    if(!pressedKey[mleftkey]) {
      printf("selected: %i/%i\n", selectedTile.x, selectedTile.y);
      readTileMap(tileSet);
    }
    //pressedKey[mleftkey] = true;
  } else {
    pressedKey[mleftkey] = false;
  }
}
