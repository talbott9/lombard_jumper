class Player {
 public:
  //Initializes the variables
  Player();

  //Takes key presses
  void handleEvent(SDL_Event& e);

  //Moves the player
  void move(Tile *tiles[]);
  void moveHG(Tile *tiles[]);
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
  void explodeSword(int x, int y);
  //Collision box of the player
  SDL_Rect mBox, interactBox;

  //X-Y coordinates
  float posX, posY, defaultPosX, defaultPosY;

  int hgMoveTicks;
  
private:
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
  Particle* particles[TOTAL_PARTICLES];
  bool deallocatedParticle[TOTAL_PARTICLES];
  bool createdParticles, hasExploded, hitWall;
  int swordExplodeXY[2];
  int particleColors[5][3];
};

Player player, hildegarde;
