#include "FinalResults.h"

#include "Menu.h"

using namespace Menu;

namespace FinalResults
{
	static void DrawResults(Player player)
	{
		Vector2 textPos;

		smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
		smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f);

		DrawTexture(background, 0, 0, WHITE);
		DrawTextureV(smallWindow, smallWindowPos, WHITE);
		DrawBackButton();

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

	static void GetInput(Player player, GameSceen& currentSceen)
	{
		SetExitKey(KEY_Q);

		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;

			if (player.totalPoints > highScore)
			{
				highScore = player.totalPoints;
			}
		}
		else if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + buttonWidth) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + buttonHeight))
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
				currentSceen = GameSceen::MENU;

				if (player.totalPoints > highScore)
				{
					highScore = player.totalPoints;
				}
			}
		}
		else
		{
			isBackButtonSelected = false;
			isClicking = false;
		}
	}

	void ShowResults(Player& player, GameSceen& currentSceen)
	{
		DrawResults(player);

		UpdateMusicStream(menuMusic);

		GetInput(player, currentSceen);
	}
}