#include "MenuManager.h"

#include "GameData.h"
#include "Player.h"

#include <iostream>


namespace MenuManager
{
	
}


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
	exitPos.y = (screenHeight / 5.0f) * 4.0f -(fontSize / 2.0f);

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

	if (currentSceen == GameSceen::MENU)
	{
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
	}
	else
	{
		if (IsKeyPressed(KEY_ESCAPE))
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
		}
		else if (currentSceen == GameSceen::CREDITS && ((mouseX > gitHubPos.x && mouseX < gitHubPos.x + gitHubSize.x) && (mouseY > gitHubPos.y && mouseY < gitHubPos.y + gitHubSize.y)))
		{		
			DrawTextEx(font, "https://github.com/juandigilio", gitHubPos, fontSize * 0.2f, spacing / 8.0f, GREEN);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				OpenURL("https://github.com/juandigilio");
			}	
		}
		else if (currentSceen == GameSceen::CREDITS && ((mouseX > itchioPos.x && mouseX < itchioPos.x + itchioSize.x) && (mouseY > itchioPos.y && mouseY < itchioPos.y + itchioSize.y)))
		{
			DrawTextEx(font, "https://juandigilio.itch.io", itchioPos, fontSize * 0.2f, spacing / 8.0f, GREEN);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				OpenURL("https://juandigilio.itch.io");
			}
		}
		else
		{
			isClicking = false;
		}
	}

}

static void DrawMain()
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

static void ShowMenu(GameSceen& currentSceen)
{
	DrawMain();

	UpdateMusicStream(menuMusic);

	GetInput(currentSceen);
}

static void DrawInstrucions()
{
	bigWindowPos.x = (screenWidth / 2.0f) - (bigWindow.width / 2.0f);
	bigWindowPos.y = (screenHeight / 2.0f) - (bigWindow.height / 2.0f);

	Vector2 textPos;

	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(bigWindow, bigWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "INSTRUCTIONS", fontSize * 0.85f, spacing / 2.0f).x / 2.0f;
	textPos.y = (screenHeight / 6) - fontSize + 10;
	DrawTextEx(font, "INSTRUCTIONS", textPos, fontSize * 0.85f, spacing / 2.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Press left click once to shoot and get pressed", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y = (screenHeight / 5) + (fontSize) - 20;
	DrawTextEx(font, "Press once left click to shoot and get pressed", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "right click to acelerate, ship will allways follow", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "right click to acelerate, ship will allways follow", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "mouse arrow. Destroy as many asteroids as possible", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "mouse arrow. Destroy as many asteroids as possible", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "and set the new record! Game will end when you", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "and set the new record! Game will end when you", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "loose all your lives, but there is not a win", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "loose all your lives, but there is not a win", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "condition, it's just a highest score comp.", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "condition, it's just a highest score comp.", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "(Press ESC to pause)", fontSize / 3.0f, spacing / 3.0f).x / 2.0f;
	textPos.y += 160;
	DrawTextEx(font, "(Press ESC to pause)", textPos, fontSize / 3.0f, spacing / 3.0f, RAYWHITE);
}

static void ShowInstructions(GameSceen& currentSceen)
{
	DrawInstrucions();

	UpdateMusicStream(menuMusic);

	GetInput(currentSceen);
}



static void GetPausedInput(GameSceen& currentSceen)
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + backButton.width) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + backButton.height))
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
			currentSceen = GameSceen::GAME;
		}
	}
	else if ((mouseX > menuButtonPos.x && mouseX < menuButtonPos.x + menuButton.width) && (mouseY > menuButtonPos.y && mouseY < menuButtonPos.y + menuButton.height))
	{
		DrawTextureV(menuButtonAct, menuButtonPos, WHITE);

		if (!isClicking)
		{
			isClicking = true;

			PlaySound(click);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			PlaySound(clickPressed);
			currentSceen = GameSceen::MENU;
			loading = true;
			StopMusicStream(gameLoopMusic);
			PlayMusicStream(menuMusic);
		}
	}
	else if ((mouseX > exitButtonPos.x && mouseX < exitButtonPos.x + exitButton.width) && (mouseY > exitButtonPos.y && mouseY < exitButtonPos.y + exitButton.height))
	{
		DrawTextureV(exitButtonAct, exitButtonPos, WHITE);

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

}

static void PauseGame(Player player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& currentSceen)
{
	DrawGame(player, asteroids, halfAsteroids, quarterAsteroids);

	smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
	smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f);

	DrawTextureV(smallWindow, smallWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);
	DrawTextureV(menuButton, menuButtonPos, WHITE);
	DrawTextureV(exitButton, exitButtonPos, WHITE);

	Vector2 textPos;

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "PAUSED GAME", fontSize * 0.45f, spacing).x / 2.0f;
	textPos.y = smallWindowPos.y + 45.0f;
	DrawTextEx(font, "PAUSED GAME", textPos, fontSize * 0.45f, spacing, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Press ESC to continue", fontSize * 0.35f, spacing / 8.0f).x / 2.0f;
	textPos.y += 90;
	DrawTextEx(font, "Press ESC to continue", textPos, fontSize * 0.35f, spacing / 8.0f, RAYWHITE);

	GetPausedInput(currentSceen);
}

static void DrawResults(Player player)
{
	Vector2 textPos;

	smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
	smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f);

	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(smallWindow, smallWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "RESULTS", fontSize * 0.6f, spacing / 4.0f).x / 2.0f;
	textPos.y = smallWindowPos.y + 30;
	DrawTextEx(font, "RESULTS", textPos, fontSize * 0.6f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Your score:     ", fontSize * 0.4f, spacing / 8.0f).x / 2.0f;
	textPos.y += 75;
	DrawTextEx(font, "Your score: ", textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);

	textPos.x += MeasureTextEx(font, "Your score: ", fontSize * 0.4f, spacing / 8.0f).x;
	DrawTextEx(font, TextFormat("%01i", player.totalPoints), textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "High score:     ", fontSize * 0.4f, spacing / 8.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "High score: ", textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);

	textPos.x += MeasureTextEx(font, "High score: ", fontSize * 0.4f, spacing / 8.0f).x;
	DrawTextEx(font, TextFormat("%01i", highScore), textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);
}

static void ShowResults(Player& player, GameSceen& currentSceen)
{
	DrawResults(player);

	GetInput(currentSceen);
}

void StartUp()
{
	GameSceen currentSceen = GameSceen::MENU;

	Player player;

	srand(static_cast<unsigned>(time(NULL)));

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "After-Roids");

	InitAudioDevice();

	InitMenu();

	PlayMusicStream(menuMusic);

	while (currentSceen != GameSceen::EXIT)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentSceen)
		{
			case GameSceen::MENU:
			{
				ShowMenu(currentSceen);
				break;
			}
			case GameSceen::GAME:
			{
				//Play(player, asteroids, halfAsteroids, quarterAsteroids, currentSceen);
				break;
			}
			case GameSceen::RESULTS:
			{
				//ShowResults(player, currentSceen);
				break;
			}
			case GameSceen::PAUSE:
			{
				//PauseGame(player, asteroids, halfAsteroids, quarterAsteroids, currentSceen);
				break;
			}
			case GameSceen::INSTRUCTIONS:
			{
				//ShowInstructions(currentSceen);
				break;
			}
			case GameSceen::CREDITS:
			{
				//ShowCredits(currentSceen);
				break;
			}
			case GameSceen::EXIT:
			{
				CloseWindow();

				break;
			}
		}

		EndDrawing();
	}
}