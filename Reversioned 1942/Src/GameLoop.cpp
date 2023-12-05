#include "GameLoop.h"

#include "raymath.h"


using namespace PlayerUtilities;

namespace GameLoop
{
	Sound crash{};

	Texture2D pauseButton{};
	Texture2D pauseButtonAct{};
	Texture2D gamePlayBacground{};
	Vector2 pauseButtonPos{};

	static void LoadGame()
	{
		gamePlayBacground = LoadTexture("Assets/Images/background.png");
		pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
		pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

		crash = LoadSound("Assets/Sounds/crash.wav");

		pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
		pauseButtonPos.y = 15.0f;
	}

	static void PlayerCollides(Player& player, GameSceen& gamseSceen)
	{
		player.isColliding = true;
		player.lastCollide = static_cast<float>(GetTime());
		player.availableLives--;
		PlaySound(crash);

		if (player.totalPoints > highScore)
		{
			highScore = player.totalPoints;
		}

		if (player.availableLives == 0)
		{
			gamseSceen = GameSceen::RESULTS;
		}
	}

	static bool CheckCircleCircleCollision(float radius1, float radius2, Vector2 position1, Vector2 position2)
	{
		float actualDistance = Vector2Distance(position1, position2);
		float minDistance = radius1 + radius2;

		if (actualDistance <= minDistance)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static void UpdateAll(Player& player, GameSceen& gamseSceen)
	{
		
		UpdatePlayer(player);
		
		UpdateMusicStream(gameLoopMusic);
	}

	static void RestartAllEntities(Player& player)
	{
		player.position.x = screenCenter.x - (player.texture.width / 2);
		player.position.y = screenCenter.y - (player.texture.height / 2);
		player.velocity = { 0, 0 };
		player.speed = 0;
		player.totalPoints = 0;
		player.thousandCouner = 0;

		for (int i = 0; i < maxBulletsQnty; i++)
		{
			player.bullets[i].isAlive = false;
			player.bullets[i].firstCrossing = true;
		}
	}

	static void ShowCrash(Player& player)
	{
		player.rotation += 0.6f;

		if (player.rotation >= 360.0f)
		{
			player.rotation = 0.0f;
		}

		if (GetTime() - player.lastCollide > 2.0f)
		{
			player.isColliding = false;

			RestartAllEntities(player);
		}
	}

	static void GetHUDInput(GameSceen& currentSceen)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if (currentSceen == GameSceen::GAME)
		{
			if ((mouseX > pauseButtonPos.x && mouseX < pauseButtonPos.x + pauseButton.width) && (mouseY > pauseButtonPos.y && mouseY < pauseButtonPos.y + pauseButton.height))
			{
				DrawTextureEx(pauseButtonAct, pauseButtonPos, 0, 1.0, WHITE);

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					currentSceen = GameSceen::PAUSE;
				}
			}
		}
	}

	static void DrawHUD(Player player)
	{
		Vector2 textPos;

		textPos.x = 15;
		textPos.y = screenHeight - fontSize;
		DrawTextEx(font, "Score: ", textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

		textPos.x += MeasureTextEx(font, "Score: ", fontSize * 0.25f, spacing / 8.0f).x;
		DrawTextEx(font, TextFormat("%01i", player.totalPoints), textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

		textPos.x = 15;
		textPos.y += 20;
		DrawTextEx(font, "High score: ", textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

		textPos.x += MeasureTextEx(font, "High score: ", fontSize * 0.25f, spacing / 8.0f).x;
		DrawTextEx(font, TextFormat("%01i", highScore), textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

		DrawTextureEx(pauseButton, pauseButtonPos, 0, 1.0, WHITE);
	}

	void DrawGame(Player player)
	{
		DrawTextureV(gamePlayBacground, { 0, 0 }, RAYWHITE);
		DrawPlayer(player);
		DrawHUD(player);
	}

	static void GameLoop(Player& player, GameSceen& currentSceen)
	{
		if (!player.isColliding)
		{
			GetPlayerInput(player, currentSceen);

			UpdateAll(player, currentSceen);
		}
		else
		{
			ShowCrash(player);
		}

		DrawGame(player);

		GetHUDInput(currentSceen);
	}

	void Play(Player& player, GameSceen& currentSceen)
	{
		if (loading)
		{
			LoadGame();
			LoadPlayer(player);
			
			RestartAllEntities(player);
			loading = false;
		}

		GameLoop(player, currentSceen);
	}
}