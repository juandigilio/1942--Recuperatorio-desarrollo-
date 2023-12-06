#include "Menu.h"

namespace Menu
{
	Texture2D background{};
	Texture2D smallContainer{};
	Texture2D mediumContainer{};
	Texture2D largeContainer{};
	Texture2D play{};
	Texture2D playSelect{};
	Texture2D instructions{};
	Texture2D credits{};
	Texture2D exit{};

	Texture2D bigWindow{};
	Texture2D smallWindow{};
	Texture2D backButton{};
	Texture2D backButtonAct{};
	Texture2D menuButton{};
	Texture2D menuButtonAct{};
	Texture2D exitButton{};
	Texture2D exitButtonAct{};

	Sound click{};
	Sound clickPressed{};

	Vector2 playPos{};
	Vector2 playPosContainer{};
	Vector2 instructionsPos{};
	Vector2 instructionsPosContainer{};
	Vector2 creditsPos{};
	Vector2 creditsPosContainer{};
	Vector2 exitPos{};
	Vector2 exitPosContainer{};
	Vector2 bigWindowPos{};
	Vector2 smallWindowPos{};
	Vector2 backButtonPos{};
	Vector2 menuButtonPos{};
	Vector2 exitButtonPos{};

	bool isClicking = false;

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
		SetExitKey(KEY_ESCAPE);

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
		else if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;
		}
		else
		{
			isClicking = false;
		}
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

	void UnloadMenuTextures()
	{
		UnloadTexture(background);
		UnloadTexture(smallContainer);
		UnloadTexture(mediumContainer);
		UnloadTexture(largeContainer);
		UnloadTexture(bigWindow);
		UnloadTexture(smallWindow);
		UnloadTexture(backButton);
		UnloadTexture(backButtonAct);
		UnloadTexture(menuButton);
		UnloadTexture(menuButtonAct);
		UnloadTexture(exitButton);
		UnloadTexture(exitButtonAct);

		UnloadMusicStream(menuMusic);
		UnloadMusicStream(gameLoopMusic);

		UnloadSound(click);
		UnloadSound(clickPressed);

		UnloadFont(font);
	}
}