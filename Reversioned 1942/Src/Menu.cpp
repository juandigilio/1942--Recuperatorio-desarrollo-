#include "Menu.h"

namespace Menu
{
	Texture2D background{};


	Texture2D instructions{};
	Texture2D credits{};
	Texture2D exit{};
	Texture2D bigWindow{};
	Texture2D smallWindow{};

	Texture2D playContainer{};
	int playContainerFrame = 0;
	bool isPlayContainerSelected = false;

	Texture2D instructionsContainer{};
	int instructionsContainerFrame = 0;
	bool isInstructionsContainerSelected = false;

	Texture2D creditsContainer{};
	int creditsContainerFrame = 0;
	bool isCreditsContainerSelected = false;

	Texture2D exitContainer{};
	int exitContainerFrame = 0;
	bool isExitContainerSelected = false;

	Texture2D backButton{};
	int backButtonFrame = 0;
	bool isBackButtonSelected = false;

	Texture2D menuButton{};
	int menuButtonFrame = 0;
	bool isMenuButtonSelected = false;

	Texture2D exitButton{};
	int exitButtonFrame = 0;
	bool isExitButtonSelected = false;

	Texture2D pauseButton{};
	int pauseButtonFrame = 0;
	bool isPauseButtonSelected = false;




	double lastMenuFrame = 0.0f;

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
	Vector2 pauseButtonPos{};


	bool isClicking = false;

	const float buttonWidth = 50.0f;
	const float buttonHeight = 50.0f;

	static const float playButtonWidth = 450.0f;
	static const float mediumContainerWidth = 384.0f;

	void InitMenu()
	{
		background = LoadTexture("Assets/Images/Menu/background.png");
		playContainer = LoadTexture("Assets/Images/Menu/playContainer.png");
		instructionsContainer = LoadTexture("Assets/Images/Menu/mediumContainer.png");
		creditsContainer = LoadTexture("Assets/Images/Menu/mediumContainer.png");
		exitContainer = LoadTexture("Assets/Images/Menu/mediumContainer.png");

		bigWindow = LoadTexture("Assets/Images/Menu/bigWindow.png");
		smallWindow = LoadTexture("Assets/Images/Menu/smallWindow.png");
		backButton = LoadTexture("Assets/Images/Menu/backBtn.png");
		menuButton = LoadTexture("Assets/Images/Menu/menuBtn.png");
		exitButton = LoadTexture("Assets/Images/Menu/exitBtn.png");
		pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");

		menuMusic = LoadMusicStream("Assets/Sounds/menu.wav");
		menuMusic.looping = true;

		gameLoopMusic = LoadMusicStream("Assets/Sounds/gameLoop.wav");
		gameLoopMusic.looping = true;
		SetMusicVolume(gameLoopMusic, 0.1f);

		click = LoadSound("Assets/Sounds/click.wav");
		clickPressed = LoadSound("Assets/Sounds/clickPressed.wav");

		font = LoadFont("Assets/Fonts/04B_30__.TTF");
		fontSize = font.baseSize * 2.0f;


		playPosContainer.x = (screenWidth / 2.0f) - (playButtonWidth / 2.0f);
		playPosContainer.y = ((screenHeight / 5.0f)) - (playContainer.height / 2.0f);
		playPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Play", fontSize * 1.1f, spacing).x / 2.0f + 8.0f;
		playPos.y = (screenHeight / 5.0f) - (fontSize / 2.0f);

		instructionsPosContainer.x = (screenWidth / 2.0f) - (mediumContainerWidth / 2.0f);
		instructionsPosContainer.y = ((screenHeight / 5.0f) * 2.0f) - (instructionsContainer.height / 2.0f);
		instructionsPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Instructions", fontSize * 0.5f, instrucrtionsSpacing).x / 2.0f + 8.0f;
		instructionsPos.y = ((screenHeight / 5.0f) * 2.0f) - (fontSize / 5.0f) - 5;

		creditsPosContainer.x = (screenWidth / 2.0f) - (mediumContainerWidth / 2.0f);
		creditsPosContainer.y = ((screenHeight / 5.0f) * 3.0f) - (creditsContainer.height / 2.0f);
		creditsPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Credits", fontSize * 0.8f, spacing).x / 2.0f + 20.0f;
		creditsPos.y = ((screenHeight / 5.0f) * 3.0f) - (fontSize / 2.0f);

		exitPosContainer.x = (screenWidth / 2.0f) - (mediumContainerWidth / 2.0f);
		exitPosContainer.y = (screenHeight / 5.0f) * 4.0f - (exitContainer.height / 2.0f);
		exitPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Exit", fontSize, spacing).x / 2.0f + 8.0f;
		exitPos.y = (screenHeight / 5.0f) * 4.0f - (fontSize / 2.0f);

		backButtonPos.x = 15.0f;
		backButtonPos.y = 15.0f;

		pauseButtonPos.x = screenWidth - buttonWidth - 15.0f;
		pauseButtonPos.y = 15.0f;

		menuButtonPos.x = pauseButtonPos.x;
		menuButtonPos.y = 15.0f;

		exitButtonPos.x = menuButtonPos.x - buttonWidth - 15.0f;
		exitButtonPos.y = 15.0f;
	}

	static void GetInput(GameSceen& currentSceen)
	{
		SetExitKey(KEY_ESCAPE);

		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if ((mouseX > playPosContainer.x && mouseX < playPosContainer.x + playButtonWidth) && (mouseY > playPosContainer.y && mouseY < playPosContainer.y + playContainer.height))
		{
			isPlayContainerSelected = true;

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
		else if ((mouseX > instructionsPosContainer.x && mouseX < instructionsPosContainer.x + mediumContainerWidth) && (mouseY > instructionsPosContainer.y && mouseY < instructionsPosContainer.y + instructionsContainer.height))
		{
			isInstructionsContainerSelected = true;

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
		else if ((mouseX > creditsPosContainer.x && mouseX < creditsPosContainer.x + mediumContainerWidth) && (mouseY > creditsPosContainer.y && mouseY < creditsPosContainer.y + creditsContainer.height))
		{
			isCreditsContainerSelected = true;

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
		else if ((mouseX > exitPosContainer.x && mouseX < exitPosContainer.x + mediumContainerWidth) && (mouseY > exitPosContainer.y && mouseY < exitPosContainer.y + exitContainer.height))
		{
			isExitContainerSelected = true;

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
			isPlayContainerSelected = false;
			isInstructionsContainerSelected = false;
			isCreditsContainerSelected = false;
			isCreditsContainerSelected = false;
			isExitContainerSelected = false;
			isClicking = false;
		}
	}

	void DrawBackButton()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { backButtonPos.x, backButtonPos.y, buttonWidth, buttonHeight };
		Rectangle source = { buttonWidth * backButtonFrame, 0.0f, buttonWidth, buttonHeight };

		if (isBackButtonSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				backButtonFrame++;

				lastMenuFrame = GetTime();

				if (backButtonFrame > 2)
				{
					backButtonFrame = 1;
				}
			}
		}
		else
		{
			backButtonFrame = 0;
		}

		DrawTexturePro(backButton, source, dest, origin, 0.0f, RAYWHITE);
	}

	void DrawExitButton()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { exitButtonPos.x, exitButtonPos.y, buttonWidth, buttonHeight };
		Rectangle source = { buttonWidth * exitButtonFrame, 0.0f, buttonWidth, buttonHeight };

		if (isExitButtonSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				exitButtonFrame++;

				lastMenuFrame = GetTime();

				if (exitButtonFrame > 2)
				{
					exitButtonFrame = 1;
				}
			}
		}
		else
		{
			exitButtonFrame = 0;
		}

		DrawTexturePro(exitButton, source, dest, origin, 0.0f, RAYWHITE);
	}

	void DrawMenuButton()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { menuButtonPos.x, menuButtonPos.y, buttonWidth, buttonHeight };
		Rectangle source = { buttonWidth * menuButtonFrame, 0.0f, buttonWidth, buttonHeight };

		if (isMenuButtonSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				menuButtonFrame++;

				lastMenuFrame = GetTime();

				if (menuButtonFrame > 2)
				{
					menuButtonFrame = 1;
				}
			}
		}
		else
		{
			menuButtonFrame = 0;
		}

		DrawTexturePro(menuButton, source, dest, origin, 0.0f, RAYWHITE);
	}

	void DrawPauseButton()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { pauseButtonPos.x, pauseButtonPos.y, buttonWidth, buttonHeight };
		Rectangle source = { buttonWidth * pauseButtonFrame, 0.0f, buttonWidth, buttonHeight };

		if (isPauseButtonSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				pauseButtonFrame++;

				lastMenuFrame = GetTime();

				if (pauseButtonFrame > 2)
				{
					pauseButtonFrame = 1;
				}
			}
		}
		else
		{
			pauseButtonFrame = 0;
		}

		DrawTexturePro(pauseButton, source, dest, origin, 0.0f, RAYWHITE);
	}

	static void DrawPlayContainer()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { playPosContainer.x, playPosContainer.y, playButtonWidth, static_cast<float>(playContainer.height) };
		Rectangle source = { playButtonWidth * playContainerFrame, 0.0f, playButtonWidth, static_cast<float>(playContainer.height) };

		if (isPlayContainerSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				playContainerFrame++;

				lastMenuFrame = GetTime();

				if (playContainerFrame > 2)
				{
					playContainerFrame = 1;
				}
			}
		}
		else
		{
			playContainerFrame = 0;
		}

		DrawTexturePro(playContainer, source, dest, origin, 0.0f, RAYWHITE);
	}

	static void DrawInstructionsContainer()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { instructionsPosContainer.x, instructionsPosContainer.y, mediumContainerWidth, static_cast<float>(instructionsContainer.height) };
		Rectangle source = { mediumContainerWidth * instructionsContainerFrame, 0.0f, mediumContainerWidth, static_cast<float>(instructionsContainer.height) };

		if (isInstructionsContainerSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				instructionsContainerFrame++;

				lastMenuFrame = GetTime();

				if (instructionsContainerFrame > 2)
				{
					instructionsContainerFrame = 1;
				}
			}
		}
		else
		{
			instructionsContainerFrame = 0;
		}

		DrawTexturePro(instructionsContainer, source, dest, origin, 0.0f, RAYWHITE);
	}

	static void DrawCreditsContainer()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { creditsPosContainer.x, creditsPosContainer.y, mediumContainerWidth, static_cast<float>(creditsContainer.height) };
		Rectangle source = { mediumContainerWidth * creditsContainerFrame, 0.0f, mediumContainerWidth, static_cast<float>(creditsContainer.height) };

		if (isCreditsContainerSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				creditsContainerFrame++;

				lastMenuFrame = GetTime();

				if (creditsContainerFrame > 2)
				{
					creditsContainerFrame = 1;
				}
			}
		}
		else
		{
			creditsContainerFrame = 0;
		}

		DrawTexturePro(creditsContainer, source, dest, origin, 0.0f, RAYWHITE);
	}

	static void DrawExitContainer()
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { exitPosContainer.x, exitPosContainer.y, mediumContainerWidth, static_cast<float>(exitContainer.height) };
		Rectangle source = { mediumContainerWidth * exitContainerFrame, 0.0f, mediumContainerWidth, static_cast<float>(exitContainer.height) };

		if (isExitContainerSelected)
		{
			double elapsedTime = GetTime() - lastMenuFrame;

			if (elapsedTime > 0.4f)
			{
				exitContainerFrame++;

				lastMenuFrame = GetTime();

				if (exitContainerFrame > 2)
				{
					exitContainerFrame = 1;
				}
			}
		}
		else
		{
			exitContainerFrame = 0;
		}

		DrawTexturePro(exitContainer, source, dest, origin, 0.0f, RAYWHITE);
	}

	static void DrawMenu()
	{
		DrawTexture(background, 0, 0, WHITE);
		DrawPlayContainer();
		DrawInstructionsContainer();
		DrawCreditsContainer();
		DrawExitContainer();

		DrawTextEx(font, "Play", playPos, fontSize * 1.1f, spacing, BLACK);
		DrawTextEx(font, "Instructions", instructionsPos, fontSize * 0.5f, instrucrtionsSpacing, BLACK);
		DrawTextEx(font, "Credits", creditsPos, fontSize * 0.8f, 3, BLACK);
		DrawTextEx(font, "Exit", exitPos, fontSize, spacing, BLACK);
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
		UnloadTexture(playContainer);
		UnloadTexture(instructionsContainer);
		UnloadTexture(creditsContainer);
		UnloadTexture(exitContainer);
		UnloadTexture(bigWindow);
		UnloadTexture(smallWindow);
		UnloadTexture(backButton);
		UnloadTexture(menuButton);
		UnloadTexture(exitButton);

		UnloadMusicStream(menuMusic);
		UnloadMusicStream(gameLoopMusic);

		UnloadSound(click);
		UnloadSound(clickPressed);

		UnloadFont(font);
	}
}