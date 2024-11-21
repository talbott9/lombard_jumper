SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

TTF_Font* gFont = NULL;
TTF_Font* gBattleFont = NULL;

//Color RGBs
SDL_Color White = {255, 255, 255};
SDL_Color Grey = {200, 200, 255};
SDL_Color Blue1 = {0, 105, 255};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close( Tile* tiles[] );


//Texture wrapper class
class LTexture
{
public:
  //Initializes variables
  LTexture();

  //Deallocates memory
  ~LTexture();

  //Loads image at specified path
  bool loadFromFile( std::string path );

  bool loadFromRenderedText( std::string textureText, SDL_Color textColor, int wrapBoundary, TTF_Font* gFont);

  //Deallocates texture
  void free();

  //Set color modulation
  void setColor( Uint8 red, Uint8 green, Uint8 blue );

  //Set blending
  void setBlendMode( SDL_BlendMode blending );

  //Set alpha modulation
  void setAlpha( Uint8 alpha );
		
  //Renders texture at given point
  void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  //Image dimensions
  int mWidth;
  int mHeight;

  //Gets image dimensions
  int getWidth();
  int getHeight();

  SDL_Rect getBox();
private:
  //The actual hardware texture
  SDL_Texture* mTexture;

  SDL_Rect mBox;
};

LTexture gTileTexture, gPlayerTexture;
