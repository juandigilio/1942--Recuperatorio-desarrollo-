#include "Pause.h"

#include <iostream>

#include "raylib.h"

#include "Menu.h"
#include "GameLoop.h"


using namespace Menu;

namespace Pause
{
	static void GetPausedInput(GameSceen& currentSceen)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		SetExitKey(KEY_Q);

		if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + buttonWidth) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + buttonHeight))
		{
			isBackButtonSelected = true;

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
		else if ((mouseX > menuButtonPos.x && mouseX < menuButtonPos.x + buttonWidth) && (mouseY > menuButtonPos.y && mouseY < menuButtonPos.y + buttonHeight))
		{
			isMenuButtonSelected = true;

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
		else if ((mouseX > exitButtonPos.x && mouseX < exitButtonPos.x + buttonWidth) && (mouseY > exitButtonPos.y && mouseY < exitButtonPos.y + buttonHeight))
		{
			isExitButtonSelected = true;

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
			isBackButtonSelected = false;
			isMenuButtonSelected = false;
			isExitButtonSelected = false;
			isClicking = false;
		}

		if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::GAME;
			pauseTimer = GetTime();
		}

	}

	static void DrawPause(Player player, vector<Enemy> enemies, GameSceen& currentSceen)
	{
		GameLoop::DrawGame(player, enemies, currentSceen);

		smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
		smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f);

		DrawTextureV(smallWindow, smallWindowPos, WHITE);
		DrawBackButton();
		DrawMenuButton();
		DrawExitButton();

		Vector2 textPos;

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "PAUSED GAME", fontSize * 0.45f, spacing).x / 2.0f;
		textPos.y = smallWindowPos.y + 45.0f;
		DrawTextEx(font, "PAUSED GAME", textPos, fontSize * 0.45f, spacing, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Press ESC to continue", fontSize * 0.35f, spacing / 8.0f).x / 2.0f;
		textPos.y += 90;
		DrawTextEx(font, "Press ESC to continue", textPos, fontSize * 0.35f, spacing / 8.0f, RAYWHITE);
	}

	void ShowPause(Player player, vector<Enemy> enemies, GameSceen& currentSceen)
	{
		DrawPause(player, enemies, currentSceen);

		UpdateMusicStream(menuMusic);

		GetPausedInput(currentSceen);
	}
}