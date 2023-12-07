#include "Credits.h"

#include "Menu.h"


using namespace Menu;

namespace Credits
{
	Vector2 gitHubPos{};
	Vector2 gitHubSize{};
	Vector2 itchioPos{};
	Vector2 itchioSize{};

	static void DrawCredits()
	{
		Vector2 textPos;

		smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
		smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f) + 10.0f;

		DrawTexture(background, 0, 0, WHITE);
		DrawTextureV(smallWindow, smallWindowPos, WHITE);

		DrawBackButton();

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Created by Juan Digilio", fontSize * 0.65f, spacing / 4.0f).x / 2.0f;
		textPos.y = smallWindowPos.y - 150;
		DrawTextEx(font, "Created by Juan Digilio", textPos, fontSize * 0.65f, spacing / 4.0f, BLACK);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Game art by Juan Digilio", fontSize * 0.4f, spacing / 8.0f).x / 2.0f;
		textPos.y += 55;
		DrawTextEx(font, "Game art by Juan Digilio", textPos, fontSize * 0.4f, spacing / 8.0f, BLACK);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Menu assets by MattWalkden", fontSize * 0.25f, spacing / 8.0f).x / 2.0f;
		textPos.y += 35;
		DrawTextEx(font, "Menu assets by MattWalkden", textPos, fontSize * 0.25f, spacing / 8.0f, BLACK);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Downloaded from craftpix.net", fontSize * 0.25f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "Downloaded from craftpix.net", textPos, fontSize * 0.25f, spacing / 8.0f, BLACK);
		///////
		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Special thanks to Image-Campus", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 60;
		DrawTextEx(font, "Special thanks to Image-Campus", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Sergio Baretto and", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "Sergio Baretto and", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Stefano Juan Cvitanich", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "Stefano Juan Cvitanich", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "for the support along this year", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "for the support along this year", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "The code is open source and you", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 40;
		DrawTextEx(font, "The code is open source and you", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "can find it on my GitHub", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "can find it on my GitHub", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		gitHubSize = MeasureTextEx(font, "https://github.com/juandigilio", fontSize * 0.2f, spacing / 8.0f);
		itchioSize = MeasureTextEx(font, "https://juandigilio.itch.io/", fontSize * 0.2f, spacing / 8.0f);

		gitHubPos.x = (screenWidth / 2) - gitHubSize.x / 2.0f;
		gitHubPos.y = textPos.y + 25;
		DrawTextEx(font, "https://github.com/juandigilio", gitHubPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		itchioPos.x = (screenWidth / 2) - itchioSize.x / 2.0f;
		itchioPos.y = gitHubPos.y + 20;
		DrawTextEx(font, "https://juandigilio.itch.io", itchioPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);
	}

	static void GetCreditsInput(GameSceen& currentSceen)
	{
		SetExitKey(KEY_Q);

		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

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
				currentSceen = GameSceen::MENU;
			}
		}
		else if ((mouseX > gitHubPos.x && mouseX < gitHubPos.x + gitHubSize.x) && (mouseY > gitHubPos.y && mouseY < gitHubPos.y + gitHubSize.y))
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
		else if ((mouseX > itchioPos.x && mouseX < itchioPos.x + itchioSize.x) && (mouseY > itchioPos.y && mouseY < itchioPos.y + itchioSize.y))
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
			isBackButtonSelected = false;
		}

		if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;
		}
	}

	void ShowCredits(GameSceen& currentSceen)
	{
		DrawCredits();

		UpdateMusicStream(menuMusic);

		GetCreditsInput(currentSceen);
	}
}