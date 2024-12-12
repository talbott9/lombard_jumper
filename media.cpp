LTexture gSwordTexture, gHGTexture, gText;
bool loadMedia() {
  bool success = true;
  gPlayerTexture.loadFromFile("resources/player/player.png");
  gHGTexture.loadFromFile("resources/npc/hildegarde.png");
  gTileTexture.loadFromFile("resources/tiles/tiles1.png");
  gSwordTexture.loadFromFile("resources/player/playersword.png");
  gFont= TTF_OpenFont("resources/fonts/battlefont.otf", 20);
  return success;
}
