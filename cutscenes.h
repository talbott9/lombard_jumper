class Cutscene {
 public:
  Cutscene();
  void render(SDL_Rect& camera);
  void handleEvent(SDL_Event& e, std::string s);
  void indexScript();
  void handleEvent(SDL_Event& e, bool controller);
  void drawDialogueText(std::string s, LTexture* gText);
  void skipText();
  void blur();
  void resetCutscene();
  void gameOverScreen();
  void play();
  
  std::vector<std::string> scriptLine;
  std::vector<bool> heroTalking;
  std::vector<int> talking;
  std::string textWritten;
  TTF_Font** gTextFont;
  SDL_Rect textbox;
  
  bool endScene, hasEndedScene, tobasu, isPost, finishedShowPostStage;
  int skipTextTicks, blurTicks, blurTicks2, blurTicks4, blurRows, blurY, blurY2, blurX, showPostStageTicks;
  bool blurYeah, blurYeah2;
  bool createdScoreThing;
  SDL_Rect scoreThing;
  float scoreX, scoreY;
  int highScoreTicks;
  std::string scoreString[8];
  std::string tip[10];
  bool loadedTip;
  int randn;
  bool advancedDialogue, canAdvance, hasTobasu;
  int cutsceneTicks;
  LTexture* gBossPortrait;
 private:
  std::string s;
  char c;
  int i, charCount, lineNumber, totalNumberOfLines, wrpBnd, textX, textY;
  bool doNotType, hasIndexedScript;
};
