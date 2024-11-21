class LevelEditor {
 public:
  LevelEditor();
  int mouseX, mouseY;
  SDL_Rect mouseBox;
  void select();
  SDL_Rect tileBoxes[TOTAL_TILES];
  int tileCoords[TOTAL_TILES][2];
  int rows,columns;
  int selTileType;
  bool pressedKey[100];
  SDL_Rect selectedTile;
  void readTileMap(Tile* tiles[]);
};

LevelEditor levelEditor;
