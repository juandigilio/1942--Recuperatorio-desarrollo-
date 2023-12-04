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
		DrawTextureV(backButton, backButtonPos, WHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Created by Juan Digilio", fontSize * 0.6f, spacing / 4.0f).x / 2.0f;
		textPos.y = smallWindowPos.y - 130;
		DrawTextEx(font, "Created by Juan Digilio", textPos, fontSize * 0.6f, spacing / 4.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Assets author:	MattWalkden", fontSize * 0.3f, spacing / 8.0f).x / 2.0f;
		textPos.y += 55;
		DrawTextEx(font, "Assets author: MattWalkden", textPos, fontSize * 0.3f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Downloaded from craftpix.net", fontSize * 0.3f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "Downloaded from craftpix.net", textPos, fontSize * 0.3f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "This is remake of the classic", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 90;
		DrawTextEx(font, "This is remake of the classic", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Asteroids game made in raylib for my", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "Asteroids game made in raylib for my", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "coursing at Image-Campus in my first", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "coursing at Image-Campus in my first", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "year of video games development.", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "year of video games development.", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "The code is open source and you", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 40;
		DrawTextEx(font, "The code is open source and you", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "can find it in my GitHub", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
		textPos.y += 20;
		DrawTextEx(font, "can find it in my GitHub", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		gitHubSize = MeasureTextEx(font, "https://github.com/juandigilio", fontSize * 0.2f, spacing / 8.0f);
		itchioSize = MeasureTextEx(font, "https://juandigilio.itch.io/", fontSize * 0.2f, spacing / 8.0f);

		gitHubPos.x = (screenWidth / 2) - gitHubSize.x / 2.0f;
		gitHubPos.y = textPos.y + 30;
		DrawTextEx(font, "https://github.com/juandigilio", gitHubPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

		itchioPos.x = (screenWidth / 2) - itchioSize.x / 2.0f;
		itchioPos.y = gitHubPos.y + 20;
		DrawTextEx(font, "https://juandigilio.itch.io", itchioPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);
	}

	static void GetCreditsInput(GameSceen& currentSceen)
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
		}
	}

	void ShowCredits(GameSceen& currentSceen)
	{
		DrawCredits();

		UpdateMusicStream(menuMusic);

		GetCreditsInput(currentSceen);
	}
}