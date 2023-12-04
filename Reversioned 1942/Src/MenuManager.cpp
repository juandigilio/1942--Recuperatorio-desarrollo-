#include "MenuManager.h"

#include "GameData.h"
#include "Player.h"

#include <iostream>


namespace MenuManager
{
	
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