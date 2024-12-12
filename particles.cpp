Particle::Particle( int x, int y, int width, int height, double spd, int life, int r, int g, int b )
{
  //Set offsets
  mBox.x = x - 3 + ( rand() % 13 );
  posX = mBox.x;
  mBox.y = y - 3 + ( rand() % 13 );
  posY = mBox.y;
  defaultX = x;
  defaultY = y;
  mBox.w = width;
  mBox.h = height;

  dx = 0;
  dy = 0;
  speed = spd;

  //Initialize animation
  mFrame = rand() % 5;
  lifeSpan = life;

  shotParticle = false;
  reachedTarget = false;

  //Set type
  //switch( rand() % 3 )
  // {
  //   case 0: mTexture = &gRedTexture; break;
  //  case 1: mTexture = &gGreenTexture; break;
  //  case 2: mTexture = &gBlueTexture; break;
  //}
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

void Particle::moveToXY(double x, double y)
{
  if(!shotParticle) {
    double side1 = y - posY;
    double side2 = posX - x;
    double r = sqrt(side1 * side1 + side2 * side2);
    double sinAngle = (side1/r);
    double cosAngle = (side2/r);
    if(posX > x)
      dx = -speed*cosAngle;
    else {
      cosAngle = -cosAngle;
      dx = speed*cosAngle;
    }
    if(posY < y)
      dy = speed*sinAngle;
    else {
      sinAngle = -sinAngle;
      dy = -speed*sinAngle;
    }
    shotParticle = true;
    reachedTarget = false;
  }
  double distanceX = posX - defaultX;
  double distanceY = defaultY - posY;
  // std::cout << distanceX << "/" << dx << std::endl;
  //std::cout << distanceY << "/" << dy << std::endl;
  if(abs(distanceX-dx) > 20 || abs(distanceY-dy) > 20) {
  } else {
    reachedTarget = true;
  }
  posX += dx;
  posY += dy;
  mBox.x = posX;
  mBox.y = posY;
}

void Particle::renderExplode()
{
  if(!pause)
    moveToXY(posX + -10 + rand()%15, posY + -10 + rand()%15);

  SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], 255);

  //Show shimmer
  if(mFrame % 2 == 0) {
    if(!pause) {
      SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], 192);
    }
  }

  SDL_RenderFillRect(gRenderer, &mBox);

  if(!pause)
    mFrame++;
}


void Particle::renderImplode()
{
  if(!pause) 
    moveToXY(defaultX, defaultY);

  SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

  //Show shimmer
  if(mFrame % 2 == 0) {
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 192);
  }

  SDL_RenderFillRect(gRenderer, &mBox);

  if(!pause) 
    mFrame++;
}

void Particle::renderSword()
{

  if(!pause) {
    mBox.x -= speed;
    mBox.y -= speed;
  }
  
  //SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(gRenderer, 205, 205, 205, 255);

  //Show shimmer
  if(mFrame % 2 == 0) {
    if(!pause) 
      SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
  }

  SDL_RenderFillRect(gRenderer, &mBox);

  if(!pause)
    mFrame++;
}

bool Particle::isDead()
{
    return mFrame > lifeSpan;
}

void Particle::moveAngle(double angle, int howFar) {
    double sinAngle = std::sin(angle*PI/180.0);
    double cosAngle = std::cos(angle*PI/180.0);

    posX = defaultX;
    posY = defaultY;
    dx = speed*cosAngle;
    dy = speed*sinAngle;
    posX += dx*howFar;
    posY += dy*howFar;
    mBox.x = posX;
    mBox.y = posY;
    dx = -dx;
    dy = -dy;
    shotParticle = true;
}
