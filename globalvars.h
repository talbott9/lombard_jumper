#define G 0.2
#define BIG_NUMBER 999999
#define TOTAL_PARTICLES 500
#define PI 3.14159265
#define NUM_SCRIPT_LINES 200

int mapID = 0;

enum pressedKeysEnum {mleftkey, mrightkey, onekey, twokey};
enum sceneIDEnum {hg1, hg2, hg3};
sceneIDEnum sceneID = hg1;
bool isCutscene = false;

bool showHitBoxes = false;
bool debugMode = true;
bool godMode = false;
bool pause = false;
