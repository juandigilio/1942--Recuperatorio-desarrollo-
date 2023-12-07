#include "Instructions.h"

#include "raylib.h"

#include "Menu.h"

using namespace Menu;

namespace Instructions
{
	static void GetInput(GameSceen& currentSceen)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		SetExitKey(KEY_Q);

		if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;
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
			}
		}
		else
		{
			isBackButtonSelected = false;
			isClicking = false;
		}
	}

	static void DrawInstrucions()
	{
		float instructionsSize = fontSize / 3.0f;

		bigWindowPos.x = (screenWidth / 2.0f) - (bigWindow.width / 2.0f);
		bigWindowPos.y = (screenHeight / 2.0f) - (bigWindow.height / 2.0f);

		Vector2 textPos;

		DrawTexture(background, 0, 0, WHITE);
		DrawTextureV(bigWindow, bigWindowPos, WHITE);
		DrawBackButton();

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "INSTRUCTIONS", fontSize * 0.85f, spacing / 2.0f).x / 2.0f;
		textPos.y = (screenHeight / 6) - fontSize + 10;
		DrawTextEx(font, "INSTRUCTIONS", textPos, fontSize * 0.85f, spacing / 2.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Press left mouse button to shoot", instructionsSize, spacing / 4.0f).x / 2.0f;
		textPos.y = (screenHeight / 5) + (fontSize)-20;
		DrawTextEx(font, "Press left mouse button to shoot", textPos, instructionsSize, spacing / 4.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "where the cursor is positioned", instructionsSize, spacing / 4.0f).x / 2.0f;
		textPos.y += 40;
		DrawTextEx(font, "where the cursor is positioned", textPos, instructionsSize, spacing / 4.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Use keyboard arrows to move", instructionsSize, spacing / 4.0f).x / 2.0f;
		textPos.y += 70;
		DrawTextEx(font, "Use keyboard arrows to move", textPos, instructionsSize, spacing / 4.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "if you crash you lose!", instructionsSize, spacing / 4.0f).x / 2.0f;
		textPos.y += 40;
		DrawTextEx(font, "if you crash you lose!", textPos, instructionsSize, spacing / 4.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Destroy as many UFOS as possible and", instructionsSize, spacing / 4.0f).x / 2.0f;
		textPos.y += 70;
		DrawTextEx(font, "Destroy as many UFOS as possible and", textPos, instructionsSize, spacing / 4.0f, RAYWHITE);

		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "don't let them take over our planet!", instructionsSize, spacing / 4.0f).x / 2.0f;
		textPos.y += 40;
		DrawTextEx(font, "don't let them take over our planet!", textPos, instructionsSize, spacing / 4.0f, RAYWHITE);
		
		textPos.x = (screenWidth / 2) - MeasureTextEx(font, "(ESC is always the answer)", fontSize / 3.0f, spacing / 3.0f).x / 2.0f;
		textPos.y += 160;
		DrawTextEx(font, "(ESC is always the answer)", textPos, fontSize / 3.0f, spacing / 3.0f, RAYWHITE);
	}

	void ShowInstructions(GameSceen& currentSceen)
	{
		DrawInstrucions();

		UpdateMusicStream(menuMusic);

		GetInput(currentSceen);
	}
}