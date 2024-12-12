bool setTiles( Tile* tiles[] );
void readTileMap(Tile* tiles[]);
void freeTileSet(Tile* tiles[]);

Tile::Tile( int x, int y, int tileType )
{
  //Get the offsets
  mBox.x = x;
  mBox.y = y;

  //Set the collision box
  mBox.w = TILE_WIDTH;
  mBox.h = TILE_HEIGHT;

  //Get the tile type
  mType = tileType;
  renderOver = false;
  if(tileType >= 2) {
    renderOver = true;
    substituteTileType = 0;
  }
  if(tileType >= 2)
    isWall = true;
  else
    isWall = false;
  if(tileType >= 1)
    isFloor = true;
}

bool setTiles( Tile* tiles[] )
{
  //Success flag
  bool tilesLoaded = true;

  //Open the map
  std::ifstream map0("resources/tiles/map0.map");

  //If the map couldn't be loaded
  if( map0.fail() )
    {
      printf( "Unable to load map file!\n" );
      tilesLoaded = false;
    }
  else
    {
      readTileMap(tileSet);
		
      //Clip the sprite sheet
      if( tilesLoaded )
	{
	  int counter1 = 0;
	  int counter2 = 0;
	  for(int i = 0; i < TOTAL_TILE_SPRITES; i++) {
	    gTileClips[i].x = TILE_WIDTH*counter2;
	    gTileClips[i].y = TILE_HEIGHT*counter1;
	    //printf("#%i %i/%i\n", i, gTileClips[i].x, gTileClips[i].y);
	    gTileClips[i].w = TILE_WIDTH;
	    gTileClips[i].h = TILE_HEIGHT;
	    counter1++;
	    if(counter1 > LENGTH_TILE_TEXTURE_COLUMN) {
	      counter1 =0;
	      counter2++;
	    }
	  }
	 
	}
    }

  //Close the file
  map0.close();

  //If the map was loaded fine
  return tilesLoaded;
}

void readTileMap(Tile* tiles[]) {
  freeTileSet(tileSet);

  //The tile offsets
  int x = 0, y = 0;

  std::ifstream map0("resources/tiles/map0.map");
	
  //Initialize the tiles
  for( int i = 0; i < TOTAL_TILES; i++ )
    {
      //Determines what kind of tile will be made
      int tileType = -1;

      switch(mapID) {
      case 0: map0 >> tileType; break;
      }

      //If the number is a valid tile number
      if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) ) {
	tiles[ i ] = new Tile( x, y, tileType );
      }
      //If we don't recognize the tile type
      else {
	//Stop loading map
	printf( "Error loading map: Invalid tile type at %d!\n", i );
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

  map0.close();
}

void freeTileSet(Tile* tiles[]) {
  for( int i = 0; i < TOTAL_TILES; ++i )
    {
      if( tiles[ i ] != NULL )
	{
	  delete tiles[ i ];
	  tiles[ i ] = NULL;
	}
    }
}

void Tile::render(SDL_Rect& camera, bool useSubstitute)
{
  //If the tile is on screen
  if( checkCollision( camera, mBox ) )
    {
      //Show the tile
      if(useSubstitute && renderOver)
	gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[substituteTileType] );
      else
	gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
  return mType;
}

SDL_Rect Tile::getBox()
{
  return mBox;
}
