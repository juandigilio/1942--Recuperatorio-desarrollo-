#include "GameLoop.h"

#include "raymath.h"

#include "Bullet.h"
#include "Parallax.h"
#include "Menu.h"


using namespace PlayerUtilities;
using namespace EnemyUtilities;
using namespace ParallaxUtilities;
using namespace Menu;

namespace GameLoop
{
	Sound crash{};

	

	static void LoadGame()
	{
		crash = LoadSound("Assets/Sounds/crash.wav");
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
						player.totalPoints += 100;
						player.bullets[i].isAlive = false;
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
		player.position.x = screenCenter.x - player.texture.width / 2;
		player.position.y = static_cast<float>(screenHeight - player.texture.height);
		player.velocity = { 0, 0 };
		player.totalPoints = 0;
		player.thousandCouner = 0;
		player.frame = 0;
		player.explosionFrame = 0;
		player.lastFrame = 0.0f;

		ResetParallax();

		enemySpeedHardnes = enemyBaseSpeed;
		spawnRateHardnes = spawnRateBase;

		for (int i = 0; i < maxBulletsQnty; i++)
		{
			player.bullets[i].isAlive = false;
		}

		enemies.clear();
	}

	static void GetHUDInput(GameSceen& currentSceen)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if (currentSceen == GameSceen::GAME)
		{
			if ((mouseX > pauseButtonPos.x && mouseX < pauseButtonPos.x + buttonWidth) && (mouseY > pauseButtonPos.y && mouseY < pauseButtonPos.y + buttonHeight))
			{
				isPauseButtonSelected = true;

				if (!isClicking)
				{
					isClicking = true;

					PlaySound(click);
				}

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					PlaySound(clickPressed);
					currentSceen = GameSceen::PAUSE;
				}
			}
			else
			{
				isPauseButtonSelected = false;
				isClicking = false;
			}
		}
	}

	static void DrawHUD(Player player, GameSceen& currentSceen)
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

		if (currentSceen != GameSceen::PAUSE)
		{
			DrawPauseButton();
		}
	}

	void DrawGame(Player& player, vector<Enemy>& enemies, GameSceen& currentSceen)
	{
		DrawParallax();

		DrawEnemies(enemies);

		if (!player.isColliding)
		{
			DrawPlayer(player);
		}
		else
		{
			if (ShowExplosion(player))
			{
				RestartAllEntities(player, enemies);
			}
		}

		DrawHUD(player, currentSceen);
	}

	static void GameLoop(Player& player, vector<Enemy>& enemies, GameSceen& currentSceen)
	{
		if (!player.isColliding)
		{
			GetPlayerInput(player, currentSceen);

			UpdateAll(player, enemies, currentSceen);
		}

		DrawGame(player, enemies, currentSceen);

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

	void UnloadGameLoopTextures()
	{
		UnloadTexture(pauseButton);
		UnloadSound(crash);
	}
}