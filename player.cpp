Player::Player() {
  posX = 600;
  posY = MAP_HEIGHT-TILE_HEIGHT*12;
  mBox.x = posX;
  mBox.y = posY;
  spriteWidth = 28;
  spriteHeight = spriteWidth;
  mBox.w = 20;
  mBox.h = 25;
  interactBox = mBox;
  interactBox.w *= 2;
  speedX = 0.15;
  speedY = 3;
  maxSpeed = 10;
  deccX = 0.15;
  gTexture = &gPlayerTexture;
  gSword = &gSwordTexture;
  canJump = false;
  termVel = 10;
  frames = 8;
  runFrames = 4;
  swordLife = 20;
  for(int i = 0; i < frames; i++)
    gTextureClips[i] = {i*spriteWidth, 0, spriteWidth, spriteHeight};
  swordBox = {0,0,20,16};
  swordOffset = swordBox.w+mBox.w;
  
  createdParticles = false;
  for(int i = 0; i < TOTAL_PARTICLES; i++)
    deallocatedParticle[i] = true;
  particleColors[0][0] = 255;
  particleColors[0][1] = 255;
  particleColors[0][2] = 255;
  
  particleColors[1][0] = 100;
  particleColors[1][1] = 100;
  particleColors[1][2] = 100;
  
  particleColors[2][0] = 150;
  particleColors[2][1] = 50;
  particleColors[2][2] = 0;
}

SDL_Rect Player::getBox() {
  return mBox;
}

void Player::explodeSword(int x, int y)
{
  if(!createdParticles) {
    for(int i = 0; i < TOTAL_PARTICLES/20; i++) {
      if(deallocatedParticle[i]) {
	int randn = rand()%2;
	particles[i] = new Particle(x, y, 2, 2, 3, 2+rand()%5, particleColors[randn][0], particleColors[randn][1], particleColors[randn][2]);
	deallocatedParticle[i] = false;
      }
    }
    createdParticles = true;
  }

  hasExploded = true;
  
  for(int i = 0; i < TOTAL_PARTICLES/20; i++) {
    if(!deallocatedParticle[i]) {
      hasExploded = false;
      if(!particles[i]->isDead()) {
	particles[i]->renderExplode();
      } else {
	delete particles[i];
	deallocatedParticle[i] = true;
      }
    }
  }
}

bool Player::touchesWall(SDL_Rect box, Tile* tiles[], bool getPos)
{
  //Go through the tiles
  for(int i = 0; i < TOTAL_TILES; ++i)
    {
      //If the tile is a wall type tile
      if(tiles[i]->isWall)
        {
	  //If the collision box touches the wall tile
	  if( checkCollision(box, tiles[ i ]->getBox()) )
            {
	      if(getPos) {
		wallPos[0] = tiles[i]->getBox().x;
		wallPos[1] = tiles[i]->getBox().y;
	      }
	      return true;
	    }
	}
    }

  //If no wall tiles were touched
  return false;
}

void Player::handleEvent( SDL_Event& e )
{
  bool upKey, downKey, leftKey, rightKey, zKey, xKey, cKey, lShiftKey, escKey, joystickLeft, joystickRight;
  if(!controller) {
    downKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_Q]|| currentKeyStates[SDL_SCANCODE_KP_8];
    upKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_E] || currentKeyStates[SDL_SCANCODE_KP_2];
    leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_KP_4];
    rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_KP_6];
    zKey = currentKeyStates[SDL_SCANCODE_Z] || currentKeyStates[SDL_SCANCODE_J];
    xKey = currentKeyStates[SDL_SCANCODE_X] || currentKeyStates[SDL_SCANCODE_K];
    //cKey = currentKeyStates[SDL_SCANCODE_C] || currentKeyStates[SDL_SCANCODE_I];
    //lShiftKey = currentKeyStates[SDL_SCANCODE_LSHIFT] || currentKeyStates[SDL_SCANCODE_K];
    escKey = currentKeyStates[SDL_SCANCODE_ESCAPE];
    joystickLeft = false;
    joystickRight = false;
  } else {
    downKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER) || currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_Q] || currentKeyStates[SDL_SCANCODE_KP_8];
    upKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) || currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_E] || currentKeyStates[SDL_SCANCODE_KP_2];
    leftKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT) || currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_KP_4];
    rightKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_KP_6];
    zKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A) || currentKeyStates[SDL_SCANCODE_Z] || currentKeyStates[SDL_SCANCODE_J];
    xKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B) || currentKeyStates[SDL_SCANCODE_X] || currentKeyStates[SDL_SCANCODE_L];
    //cKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y) || currentKeyStates[SDL_SCANCODE_C] || currentKeyStates[SDL_SCANCODE_I];
    //lShiftKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X) || currentKeyStates[SDL_SCANCODE_LSHIFT] || currentKeyStates[SDL_SCANCODE_K];
    escKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START) || currentKeyStates[SDL_SCANCODE_ESCAPE];
    joystickLeft = SDL_JoystickGetAxis(gJoystick, 0) < -JOYSTICK_DEAD_ZONE;
    joystickRight = SDL_JoystickGetAxis(gJoystick, 0) > JOYSTICK_DEAD_ZONE;
  }
  if(zKey) {
    if(!jump) {
      jump = true;
    }
  } else {
    jump = false;
  }
  if(xKey) {
    if(checkCollision(interactBox, hildegarde.mBox) && !isCutscene) {
      isCutscene = true;
    } else {
      if(!pressedAttack && !attack && !isCutscene) {
	pressedAttack = true;
	attack = true;
	swordBox.x = posX;
	swordBox.y = posY+swordBox.h/2;
	swordFlipType = flipType;
	swordAlpha = 255;
	if(swordFlipType == SDL_FLIP_NONE)
	  swordBox.x += mBox.w+swordBox.w/3;
	else
	  swordBox.x -= swordBox.w+swordBox.w/3;
      } else {
	pressedAttack = false;
      }
    }
  }
  if(leftKey) {
    if(!moveTo[0]) {
      moveTo[0] = true;
    }
  } else {
    moveTo[0] = false;
  }
  if(rightKey) {
    if(!moveTo[1]) {
      moveTo[1] = true;
    }
  } else {
    moveTo[1] = false;
  }
}


void Player::moveHG(Tile *tiles[]) {
  mVelY += G;
  if(mVelY > 10)
    mVelY = 10;
  posY += mVelY;
  mBox.y = posY;
  posX += mVelX;
  mBox.x = posX;
  if(touchesWall(mBox, tiles)) {
    if(touchesWall(mBox, tiles, true) && posY < wallPos[1]) {
      if(!jump)
	canJump = true;
      mVelY = 0;
      posY = wallPos[1]-mBox.h;
      mBox.y = posY;
    } else {
      //Move back
      posY -= mVelY;
      mBox.y = posY;
      mVelY = 0;
    }
  }
  if(hgMoveTicks % 120 == 0) {
    int randn = rand()%10;
    if((randn > 4 && posX + 2*30 < defaultPosX + 200) || posX - 2*30 < defaultPosX - 380)
      mVelX += 2;
    else
      mVelX -= 2;
  }
  if(hgMoveTicks % 150 == 0) {
    mVelX = 0;
    hgMoveTicks = 0;
  }

  hgMoveTicks++;
}

void Player::move( Tile *tiles[] )
{
  mVelY += G;
  if(mVelY > 10)
    mVelY = 10;
  if(!attack || airborne) {
    if(moveTo[0] && mVelX >= -maxSpeed) {
      mVelX -= speedX;
      if(mVelX < -maxSpeed)
	mVelX = -maxSpeed;
    } else if(moveTo[1] && mVelX <= maxSpeed) {
      mVelX += speedX;
      if(mVelX > maxSpeed)
	mVelX = maxSpeed;
    }
  }
  if(attack) {
    attackTicks++;
    if(attackTicks > swordLife) {
      attackTicks = 0;
      attack = false;
    }
    if(touchesWall(swordBox,tiles, true)) {
      if(mBox.x > wallPos[0]) {
	mVelX = 5;
	swordExplodeXY[0] = wallPos[0]+TILE_WIDTH-camera.x;
      } else {
	mVelX = -5;
	swordExplodeXY[0] = wallPos[0]-camera.x;
      }
      swordExplodeXY[1] = swordBox.y+swordBox.h/2-camera.y;
      swordBox.x = -BIG_NUMBER;
      swordBox.y = -BIG_NUMBER;
      mVelY -= 2;
      hitWall = true;
      canJump = false;
    }
  }
  if(hitWall) {
    explodeSword(swordExplodeXY[0], swordExplodeXY[1]);
    if(hasExploded) {
      hitWall = false;
      createdParticles = false;
    }
  }

  if(mVelX > 0 && (!moveTo[1] || (attack && !airborne))) {
    mVelX -= deccX;
    if(mVelX < 0)
      mVelX = 0;
  }
  else if(mVelX < 0 && (!moveTo[0] || (attack && !airborne))) {
    mVelX += deccX;
    if(mVelX > 0)
      mVelX = 0;
  }

  //if(mVelX > 0 && mVelX < 1)
  //  posX += 1;
  posX += mVelX;
  mBox.x = posX;

  if(canJump && jump && !airborne) {
    canJump = false;
    jumpCycle = true;
    mVelY -= speedY;
    if(moveTo[0])
      mVelX -= speedX*3;
    else if(moveTo[1])
      mVelX += speedX*3;
  }
  
  //If the dot went too far to the left or right
  if( ( posX < 0 ) || ( posX + spriteWidth > MAP_WIDTH ) || touchesWall(mBox, tiles) )
    {
      //Move back
      posX -= mVelX;
      mBox.x = posX;
      mVelX = 0;
    }

  if(!canJump) {
    if(jumpCycle) {
      if(jump)
	jumpTicks++;
      else
	jumpCycle = false;
      if(jumpTicks < 10)
	mVelY -= jumpTicks*0.1;
    }
  } else {
    jumpTicks = 0;
  }
  posY += mVelY;
  mBox.y = posY;

  if(touchesWall(mBox, tiles)) {
    if(touchesWall(mBox, tiles, true) && posY < wallPos[1]) {
      if(!jump)
	canJump = true;
      mVelY = 0;
      posY = wallPos[1]-mBox.h;
      mBox.y = posY;
    } else {
      //Move back
      posY -= mVelY;
      mBox.y = posY;
      mVelY = 0;
    }
  }
  if(mVelY != 0)
    airborne = true;
  else
    airborne = false;
  if(mBox.y == wallPos[1]-mBox.h)
    airborne = false;

  interactBox.x = mBox.x - (interactBox.w-mBox.w)/2;
  interactBox.y = mBox.y - (interactBox.h-mBox.h)/2;
}

void Player::setCamera( SDL_Rect& camera )
{
  //Center the camera over the dot
  camera.x = ( posX + spriteWidth / 2 ) - SCREEN_WIDTH / 2;
  camera.y = ( posY + spriteHeight / 2 ) - SCREEN_HEIGHT / 2;

  if(!godMode) {
    //Keep the camera in bounds
    if( camera.x < TILE_WIDTH )
      { 
	camera.x = TILE_WIDTH;
      }
    if( camera.y < 0 )
      {
	camera.y = 0;
      }
    if( camera.x > MAP_WIDTH - camera.w - TILE_WIDTH )
      {
	camera.x = MAP_WIDTH - camera.w - TILE_WIDTH;
      }
    if( camera.y > MAP_HEIGHT - camera.h )
      {
	camera.y = MAP_HEIGHT - camera.h;
      }
  }
}

void Player::render(SDL_Rect& camera) {
  gTexture->mWidth = spriteWidth;
  gTexture->mHeight = spriteHeight;
  int frame = frameTicks;
  currentClip = &gTextureClips[frame];
  if(mVelX > 0) {
    if(frameTicks == 0 && runLoop == 0)
      frameTicks = 1;
    frameTicks += 0.05*mVelX;
    flipType = SDL_FLIP_NONE;
  }
  else if(mVelX < 0) {
    if(frameTicks == 0 && runLoop == 0)
      frameTicks = 1;
    frameTicks += 0.05*-mVelX;
    flipType = SDL_FLIP_HORIZONTAL;
  } else {
    frameTicks = 0;
    runLoop = 0;
  }
  if(frameTicks >= runFrames) {
    frameTicks = 0;
    runLoop++;
  }

  if(airborne) {
    if(mVelY > 0) 
      currentClip = &gTextureClips[5];
    else
      currentClip = &gTextureClips[4];
  }

  if(attack) {
    if(airborne)
      currentClip = &gTextureClips[7];
    else
      currentClip = &gTextureClips[6];
  }
  
  gTexture->render(posX - (spriteWidth- mBox.w)/2 - camera.x, posY - spriteHeight/2 + mBox.h/2 - camera.y, currentClip, 0, NULL, flipType);
  if(showHitBoxes) {
    SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
    SDL_Rect box = {mBox.x-camera.x, mBox.y-camera.y, mBox.w, mBox.h};
    SDL_RenderFillRect(gRenderer, &box);
  }
  if(attack) {
    int renderX = swordBox.x-swordBox.w/2-camera.x;
    if(swordFlipType == SDL_FLIP_HORIZONTAL)
      renderX = swordBox.x-camera.x;
    int renderY = swordBox.y-swordBox.h/2-camera.y;
    swordAlpha -= 255/swordLife;
    gSword->setAlpha(swordAlpha);
    gSword->render(renderX, renderY, NULL, 0, NULL, swordFlipType);
    if(showHitBoxes) {
      SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
      SDL_Rect swordBox1 = {swordBox.x-camera.x, swordBox.y-camera.y, swordBox.w, swordBox.h};
      SDL_RenderFillRect(gRenderer, &swordBox1);
    }
  }
  //SDL_RenderFillRect(gRenderer, &mBox);
}
