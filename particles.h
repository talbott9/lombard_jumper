class Particle
{
public:
  //Initialize position and animation
  Particle( int x, int y, int width, int height, double spd, int life, int r, int g, int b );

  //Shows the particle
  void renderSword();
  void renderExplode();
  void renderImplode();
  void renderAbsorb();
  void renderAbsorbOut();
  void moveToXY(double x, double y);
  void moveAngle(double angle, int howFar);

  //Checks if particle is dead
  bool isDead();

  //Offsets
  SDL_Rect mBox;
  int defaultX, defaultY;
  double dx, dy, speed, posX, posY;
  bool shotParticle, reachedTarget;
  int lifeSpan;
  int color[3];

public:
  int mFrame;

  //Type of particle
  LTexture *mTexture;
};
