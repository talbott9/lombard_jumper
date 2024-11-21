class Player {
 public:
  //Initializes the variables
  Player();

  //Takes key presses
  void handleEvent(SDL_Event& e);

  //Moves the player
  void move(Tile *tiles[]);
  bool touchesWall(SDL_Rect box, Tile* tiles[], bool getPos = false);
	
  //Centers the camera over the player
  void setCamera(SDL_Rect& camera);

  SDL_Rect getBox();

  //Renders the player
  LTexture* gTexture;
  LTexture* gSword;
  int frames, runFrames, runLoop;
  float frameTicks;
  SDL_Rect gTextureClips[100];
  SDL_Rect* currentClip;
  int spriteWidth, spriteHeight;
  SDL_RendererFlip flipType = SDL_FLIP_NONE;
  SDL_RendererFlip swordFlipType = SDL_FLIP_NONE;
  void render(SDL_Rect& camera);

  float speedX, speedY;
 private:
  //Collision box of the player
  SDL_Rect mBox;

  //X-Y coordinates
  float posX, posY;
  
  //The velocity of the dot
  float mVelX, mVelY, deccX;
  bool jump, canJump, jumpCycle, airborne;
  bool moveTo[2];
  float maxSpeed;
  float termVel;
  int wallPos[2];
  int jumpTicks;
  bool attack, pressedAttack;
  int attackTicks, swordAlpha, swordLife, swordOffset;
  SDL_Rect swordBox;
};

Player player;
