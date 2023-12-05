#include "Menu.h"


namespace Menu
{
	extern Texture2D background{};
	extern Texture2D smallContainer{};
	extern Texture2D mediumContainer{};
	extern Texture2D largeContainer{};
	extern Texture2D play{};
	extern Texture2D playSelect{};
	extern Texture2D instructions{};
	extern Texture2D credits{};
	extern Texture2D exit{};

	extern Texture2D bigWindow{};
	extern Texture2D smallWindow{};
	extern Texture2D backButton{};
	extern Texture2D backButtonAct{};
	extern Texture2D menuButton{};
	extern Texture2D menuButtonAct{};
	extern Texture2D exitButton{};
	extern Texture2D exitButtonAct{};

	extern Sound click{};
	extern Sound clickPressed{};

	extern Vector2 playPos{};
	extern Vector2 playPosContainer{};
	extern Vector2 instructionsPos{};
	extern Vector2 instructionsPosContainer{};
	extern Vector2 creditsPos{};
	extern Vector2 creditsPosContainer{};
	extern Vector2 exitPos{};
	extern Vector2 exitPosContainer{};
	extern Vector2 bigWindowPos{};
	extern Vector2 smallWindowPos{};
	extern Vector2 backButtonPos{};
	extern Vector2 menuButtonPos{};
	extern Vector2 exitButtonPos{};

	extern bool isClicking = false;

	void InitMenu()
	{
		background = LoadTexture("Assets/Images/Menu/background.png");
		smallContainer = LoadTexture("Assets/Images/Menu/smallContainer.png");
		mediumContainer = LoadTexture("Assets/Images/Menu/mediumContainer.png");
		largeContainer = LoadTexture("Assets/Images/Menu/largeContainer.png");

		bigWindow = LoadTexture("Assets/Images/Menu/bigWindow.png");
		smallWindow = LoadTexture("Assets/Images/Menu/smallWindow.png");
		backButton = LoadTexture("Assets/Images/Menu/backBtn.png");
		backButtonAct = LoadTexture("Assets/Images/Menu/backBtnAct.png");
		menuButton = LoadTexture("Assets/Images/Menu/menuBtn.png");
		menuButtonAct = LoadTexture("Assets/Images/Menu/menuBtnAct.png");
		exitButton = LoadTexture("Assets/Images/Menu/exitBtn.png");
		exitButtonAct = LoadTexture("Assets/Images/Menu/exitBtnAct.png");

		menuMusic = LoadMusicStream("Assets/Sounds/menu.wav");
		menuMusic.looping = true;

		gameLoopMusic = LoadMusicStream("Assets/Sounds/gameLoop.wav");
		gameLoopMusic.looping = true;
		SetMusicVolume(gameLoopMusic, 0.1f);

		click = LoadSound("Assets/Sounds/click.wav");
		clickPressed = LoadSound("Assets/Sounds/clickPressed.wav");

		font = LoadFont("Assets/Fonts/04B_30__.TTF");
		fontSize = font.baseSize * 2.0f;

		playPosContainer.x = (screenWidth / 2.0f) - (smallContainer.width / 2.0f);
		playPosContainer.y = ((screenHeight / 5.0f)) - (smallContainer.height / 2.0f);
		playPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Play", fontSize, spacing).x / 2.0f + 8.0f;
		playPos.y = (screenHeight / 5.0f) - (fontSize / 2.0f);

		instructionsPosContainer.x = (screenWidth / 2.0f) - (largeContainer.width / 2.0f);
		instructionsPosContainer.y = ((screenHeight / 5.0f) * 2.0f) - (largeContainer.height / 2.0f);
		instructionsPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Instructions", fontSize, instrucrtionsSpacing).x / 2.0f + 8.0f;
		instructionsPos.y = ((screenHeight / 5.0f) * 2.0f) - (fontSize / 2.0f);

		creditsPosContainer.x = (screenWidth / 2.0f) - (mediumContainer.width / 2.0f);
		creditsPosContainer.y = ((screenHeight / 5.0f) * 3.0f) - (mediumContainer.height / 2.0f);
		creditsPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Credits", fontSize, spacing).x / 2.0f + 20.0f;
		creditsPos.y = ((screenHeight / 5.0f) * 3.0f) - (fontSize / 2.0f);

		exitPosContainer.x = (screenWidth / 2.0f) - (smallContainer.width / 2.0f);
		exitPosContainer.y = (screenHeight / 5.0f) * 4.0f - (smallContainer.height / 2.0f);
		exitPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Exit", fontSize, spacing).x / 2.0f + 8.0f;
		exitPos.y = (screenHeight / 5.0f) * 4.0f - (fontSize / 2.0f);

		backButtonPos.x = 15.0f;
		backButtonPos.y = 15.0f;

		exitButtonPos.x = screenWidth - exitButton.width - 15.0f;
		exitButtonPos.y = 15.0f;

		menuButtonPos.x = exitButtonPos.x - (menuButton.width + 15.0f);
		menuButtonPos.y = 15.0f;
	}

	static void GetInput(GameSceen& currentSceen)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if ((mouseX > playPosContainer.x && mouseX < playPosContainer.x + smallContainer.width) && (mouseY > playPosContainer.y && mouseY < playPosContainer.y + smallContainer.height))
		{
			DrawTextEx(font, "Play", playPos, fontSize, spacing, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				StopMusicStream(menuMusic);
				PlayMusicStream(gameLoopMusic);
				currentSceen = GameSceen::GAME;
			}
		}
		else if ((mouseX > instructionsPosContainer.x && mouseX < instructionsPosContainer.x + largeContainer.width) && (mouseY > instructionsPosContainer.y && mouseY < instructionsPosContainer.y + largeContainer.height))
		{
			DrawTextEx(font, "Instructions", instructionsPos, fontSize, instrucrtionsSpacing, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::INSTRUCTIONS;
			}
		}
		else if ((mouseX > creditsPosContainer.x && mouseX < creditsPosContainer.x + mediumContainer.width) && (mouseY > creditsPosContainer.y && mouseY < creditsPosContainer.y + mediumContainer.height))
		{
			DrawTextEx(font, "Credits", creditsPos, fontSize, 3, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::CREDITS;
			}
		}
		else if ((mouseX > exitPosContainer.x && mouseX < exitPosContainer.x + smallContainer.width) && (mouseY > exitPosContainer.y && mouseY < exitPosContainer.y + smallContainer.height))
		{
			DrawTextEx(font, "Exit", exitPos, fontSize, spacing, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::EXIT;
			}
		}
		else
		{
			isClicking = false;
		}

		////////
		/*if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;
		}
		else if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + backButton.width) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + backButton.height))
		{
			DrawTextureV(backButtonAct, backButtonPos, WHITE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::MENU;
			}
		}*/
	}

	static void DrawMenu()
	{
		DrawTexture(background, 0, 0, WHITE);
		DrawTextureEx(smallContainer, playPosContainer, 0, 1.0, WHITE);
		DrawTextureEx(largeContainer, instructionsPosContainer, 0, 1.0, WHITE);
		DrawTextureEx(mediumContainer, creditsPosContainer, 0, 1.0, WHITE);
		DrawTextureEx(smallContainer, exitPosContainer, 0, 1.0, WHITE);

		DrawTextEx(font, "Play", playPos, fontSize, spacing, RAYWHITE);
		DrawTextEx(font, "Instructions", instructionsPos, fontSize, instrucrtionsSpacing, RAYWHITE);
		DrawTextEx(font, "Credits", creditsPos, fontSize, 3, RAYWHITE);
		DrawTextEx(font, "Exit", exitPos, fontSize, spacing, RAYWHITE);
	}

	void ShowMenu(GameSceen& currentSceen)
	{
		DrawMenu();

		UpdateMusicStream(menuMusic);

		GetInput(currentSceen);
	}
}