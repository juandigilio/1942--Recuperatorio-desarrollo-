#include "GameLoop.h"

#include "raymath.h"

#include "Bullet.h"
#include "Parallax.h"


using namespace PlayerUtilities;
using namespace EnemyUtilities;
using namespace ParallaxUtilities;

namespace GameLoop
{
	Sound crash{};

	Texture2D pauseButton{};
	Texture2D pauseButtonAct{};
	
	Vector2 pauseButtonPos{};

	static void LoadGame()
	{
		pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
		pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

		crash = LoadSound("Assets/Sounds/crash.wav");

		pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
		pauseButtonPos.y = 15.0f;
	}

	static void PlayerCollides(Player& player, GameSceen& currentSceen)
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
			currentSceen = GameSceen::RESULTS;
		}
	}

	static void CheckCollisions(Player& player, vector<Enemy>& enemies, GameSceen& currentSceen)
	{
		for (auto& object : enemies)
		{
			float actualDistance;
			float minDistance;

			for (int i = 0; i < maxBulletsQnty; i++)
			{
				if (player.bullets[i].isAlive)
				{
					actualDistance = Vector2Distance(player.bullets[i].GetCenter(), object.GetCenter());
					minDistance = player.bullets[i].radius + object.radius;

					if (actualDistance <= minDistance)
					{
						object.isAlive = false;

					}
				}
			}

			if (object.isAlive)
			{
				actualDistance = Vector2Distance(player.GetCenter(), object.GetCenter());
				minDistance = player.radius + object.radius;

				if (actualDistance <= minDistance)
				{
					PlayerCollides(player, currentSceen);
				}
			}
		}

		enemies.erase(remove_if(enemies.begin(), enemies.end(),[](const Enemy& enemy) { return !enemy.isAlive; }), enemies.end());
	}

	static void UpdateAll(Player& player, vector<Enemy>& enemies, GameSceen& currentSceen)
	{	
		UpdateParallax();

		UpdatePlayer(player);

		UpdateEnemies(enemies);

		CheckCollisions(player, enemies, currentSceen);
		
		UpdateMusicStream(gameLoopMusic);
	}

	static void RestartAllEntities(Player& player, vector<Enemy>& enemies)
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
		}

		enemies.clear();
	}

	static void ShowCrash(Player& player, vector<Enemy>& enemies)
	{
		player.rotation += 1000.0f * GetFrameTime();

		if (player.rotation >= 360.0f)
		{
			player.rotation = 0.0f;
		}

		if (GetTime() - player.lastCollide > 2.0f)
		{
			player.isColliding = false;

			RestartAllEntities(player, enemies);
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

	void DrawGame(Player player, vector<Enemy> enemies)
	{
		DrawParallax();

		DrawPlayer(player);

		DrawEnemies(enemies);

		DrawHUD(player);
	}

	static void GameLoop(Player& player, vector<Enemy>& enemies, GameSceen& currentSceen)
	{
		if (!player.isColliding)
		{
			GetPlayerInput(player, currentSceen);

			UpdateAll(player, enemies, currentSceen);
		}
		else
		{
			ShowCrash(player, enemies);
		}

		DrawGame(player, enemies);

		GetHUDInput(currentSceen);
	}

	void Play(Player& player, vector<Enemy>& enemies, GameSceen& currentSceen)
	{
		if (loading)
		{
			LoadGame();
			LoadPlayer(player);
			
			RestartAllEntities(player, enemies);
			loading = false;
		}

		GameLoop(player, enemies, currentSceen);
	}
}