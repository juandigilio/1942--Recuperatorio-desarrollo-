#include "Pause.h"

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

	static void DrawPause(Player player)
	{
		GameLoop::DrawGame(player);

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
	}

	void ShowPause(Player player, GameSceen& currentSceen)
	{
		DrawPause(player);

		UpdateMusicStream(menuMusic);

		GetPausedInput(currentSceen);
	}
}