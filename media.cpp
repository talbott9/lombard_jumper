LTexture gSwordTexture;
bool loadMedia() {
  bool success = true;
  gPlayerTexture.loadFromFile("resources/player/player.png");
  gTileTexture.loadFromFile("resources/tiles/tiles1.png");
  gSwordTexture.loadFromFile("resources/player/playersword.png");
  return success;
}
