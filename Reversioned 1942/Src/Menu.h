#pragma once

#include "raylib.h"

#include "GameData.h"


using namespace GameData;

namespace Menu
{
	extern Texture2D background;
	extern Texture2D playContainer;
	extern Texture2D playSelect;
	extern Texture2D instructions;
	extern Texture2D credits;
	extern Texture2D exit;

	extern Texture2D bigWindow;
	extern Texture2D smallWindow;

	extern Texture2D backButton;	
	extern bool isBackButtonSelected;

	extern Texture2D menuButton;
	extern bool isMenuButtonSelected;
	
	extern Texture2D exitButton;
	extern bool isExitButtonSelected;

	extern Texture2D pauseButton;
	extern bool isPauseButtonSelected;


	extern Sound click;
	extern Sound clickPressed;

	extern Vector2 playPos;
	extern Vector2 playPosContainer;
	extern Vector2 instructionsPos;
	extern Vector2 instructionsPosContainer;
	extern Vector2 creditsPos;
	extern Vector2 creditsPosContainer;
	extern Vector2 exitPos;
	extern Vector2 exitPosContainer;
	extern Vector2 bigWindowPos;
	extern Vector2 smallWindowPos;
	extern Vector2 backButtonPos;
	extern Vector2 menuButtonPos;
	extern Vector2 exitButtonPos;
	extern Vector2 pauseButtonPos;

	extern bool isClicking;

	extern const float buttonWidth;
	extern const float buttonHeight;

	extern void ShowMenu(GameSceen& currentSceen);

	extern void InitMenu();

	extern void DrawBackButton();

	extern void DrawExitButton();

	extern void DrawMenuButton();

	extern void DrawPauseButton();

	extern void UnloadMenuTextures();
}