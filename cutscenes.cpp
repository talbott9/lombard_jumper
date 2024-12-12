#include "cutscenes.h"
#include "scripts.cpp"
Cutscene cutscene;

Cutscene::Cutscene() {
  textbox = {camera.x + camera.w/7, camera.h - camera.h/4, camera.w - camera.w/7*2, camera.h/5};
  wrpBnd = textbox.w - textbox.w/6*2;
  textX = textbox.x + textbox.w/6;
  textY = textbox.y + textbox.h/8;
  gTextFont = &gFont;
  scriptLine.clear();
  scriptLine.resize(NUM_SCRIPT_LINES);
  talking.clear();
  talking.resize(NUM_SCRIPT_LINES);
  heroTalking.clear();
  heroTalking.resize(NUM_SCRIPT_LINES);
}

void Cutscene::resetCutscene() {
  textWritten = "";
  canAdvance = false;
  isCutscene = false;
  hasIndexedScript = false;
  lineNumber = 0;
}

void Cutscene::handleEvent(SDL_Event& e, bool controller) {
  bool isRepeat, upKey, downKey, leftKey, rightKey, zKey, xKey, cKey, lShiftKey, escKey, lCtrlKey;
  if(!controller) {
    zKey = currentKeyStates[SDL_SCANCODE_Z] || currentKeyStates[SDL_SCANCODE_J] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER];
    xKey = currentKeyStates[SDL_SCANCODE_X] || currentKeyStates[SDL_SCANCODE_K];
  } else {
    zKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A) || currentKeyStates[SDL_SCANCODE_Z]  || currentKeyStates[SDL_SCANCODE_J] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER];
    xKey = SDL_GameControllerGetButton(gGameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B) || currentKeyStates[SDL_SCANCODE_X];
  }
  if(xKey) {
    if(!advancedDialogue) {
      if(charCount < scriptLine[lineNumber].size()) {
	doNotType = 1;
      } else {
	doNotType = 0;
	charCount = 0;
	gText.free();
	textWritten = "";
	lineNumber++;
      }
    }
    advancedDialogue = true;
  } else {
    advancedDialogue = false;
  }
}


void Cutscene::drawDialogueText(std::string s, LTexture* gText) {
  //drawTicks++;
  if(!doNotType) {
    if(!pause) {
      if(charCount < scriptLine[lineNumber].size()) {
	if(s[charCount] != '\\') {
	  textWritten += s[charCount]; charCount++;
	} else {
	  textWritten += "\n           "; charCount++;
	}
      }
    }
    gText->loadFromRenderedText(textWritten, White, wrpBnd, *gTextFont);
    gText->render(textX, textY);
	
  } else {
    if(!pause) {
      while(charCount < scriptLine[lineNumber].size()) {
	if(s[charCount] != '\\') {
	  textWritten += s[charCount]; charCount++;
	} else {
	  textWritten += "\n           "; charCount++;
	}
      }
    }
    gText->loadFromRenderedText(textWritten, White, wrpBnd, *gTextFont);
    gText->render(textX, textY);
  }
}

void Cutscene::skipText() {
  if(lineNumber == totalNumberOfLines-1) {
  } else {
    skipTextTicks++;
    if(skipTextTicks%3 == 0) {
      doNotType = 0;
      charCount = 0;
      gText.free();
      textWritten = "";
      lineNumber++;
    } else {
      doNotType = 1;
    }
  }
}

void Cutscene::play() {
  SDL_RenderFillRect(gRenderer, &textbox);
  indexScript();
  if(!(lineNumber >= totalNumberOfLines))
    drawDialogueText(scriptLine[lineNumber], &gText);
  else {
    isCutscene = false;
    resetCutscene();
  }
}
