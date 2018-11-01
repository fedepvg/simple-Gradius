#include "PlayerMissile.h"

#include <cmath>

#include "Setup/Player.h"
#include "Setup/Game.h"
#include "Screens/gameplay.h"
#include "Screens/settings.h"
#include "Setup\Enemy.h"
#include "EnemyCanon.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{

	Shoot missiles[maxMissiles];

	float rapidFireMissileTimer = 0;
	float rapidFireMissileRate = 0.7;

	namespace Gameplay_Section
	{
		void createMissile()
		{
			for (int i = 0; i < maxMissiles; i++)
			{
				missiles[i].position.x = 0;
				missiles[i].position.y = 0;
				if (resolutionNormal)
				{
					missiles[i].size.x = 60;
					missiles[i].size.y = 5;
				}
				else if (resolutionSmall)
				{
					missiles[i].size.x = 60 / resolutionSizeFix;
					missiles[i].size.y = 5 / resolutionSizeFix;
				}

				missiles[i].speed.x = 0;
				missiles[i].speed.y = 0;
				missiles[i].color = RED;
				missiles[i].active = false;
			}
		}

		void missileInput()
		{
			rapidFireMissileTimer += 1 * GetFrameTime();
			// Player missile logic
			if (IsKeyDown(playerKeys[MISSILE]))
			{
				

				for (int i = 0; i < maxMissiles; i++)
				{
					if (rapidFireMissileTimer > rapidFireMissileRate)
					{
						if (!missiles[i].active)
						{
							#ifdef AUDIO
							PlaySound(ship_shoot01);
							#endif
							missiles[i].position = { player.position.x + player.size.x / 2, player.position.y + player.size.y / 2 };


							if (resolutionNormal && !(resolutionBig))
							{
								missiles[i].speed.x = 2.0*player.defaultSpeed*cosf(missileShootAngle*DEG2RAD);
								missiles[i].speed.y = 2.0*player.defaultSpeed*sinf(missileShootAngle*DEG2RAD);
							}
							else if (resolutionSmall)
							{
								missiles[i].speed.x = 1.5*player.defaultSpeed*cosf(missileShootAngle*DEG2RAD);
								missiles[i].speed.y = 1.5*player.defaultSpeed*sinf(missileShootAngle*DEG2RAD);
							}
							else if (resolutionNormal && resolutionBig)
							{
								missiles[i].speed.x = 2.5*player.defaultSpeed*cosf(missileShootAngle*DEG2RAD);
								missiles[i].speed.y = 2.5*player.defaultSpeed*sinf(missileShootAngle*DEG2RAD);
							}

							rapidFireMissileTimer = 0;
							missiles[i].active = true;
							break;
						}
					}
				}
			}
		}

		void missileUpdate()
		{
			// Shot logic
			for (int i = 0; i < maxMissiles; i++)
			{
				if (missiles[i].active)
				{
					// Movement
					missiles[i].position.x += missiles[i].speed.x * GetFrameTime();
					missiles[i].position.y += missiles[i].speed.y * GetFrameTime();

					// Collision logic: missile vs walls
					if (missiles[i].position.x > screenWidth)
					{
						missiles[i].active = false;
					}

					if (missiles[i].position.y > screenHeight)
					{
						missiles[i].active = false;
					}
					else if (missiles[i].position.y < 0)
					{
						missiles[i].active = false;
					}
				}
			}

			// Collision logic: player-missiles vs meteors
			for (int f = 0; f < maxMissiles; f++)
			{
				for (int i = 0; i < maxEnemies; i++)
				{
					if ((missiles[f].active))
					{
						if (CheckCollisionRecs({ missiles[f].position.x,missiles[f].position.y,missiles[f].size.x,missiles[f].size.y }, { enemies[i].position.x,enemies[i].position.y,enemies[i].size.x,enemies[i].size.y }))
						{
							#ifdef AUDIO
							PlaySound(enemy_explode01);
							#endif
							enemies[i].isAlive = false;
							missiles[f].active = false;
							targetsLeft--;
						}
					}
				}
				if ((missiles[f].active))
				{
					if (CheckCollisionRecs({ missiles[f].position.x,missiles[f].position.y,missiles[f].size.x,missiles[f].size.y },enemyCanonCollider ))
					{
#ifdef AUDIO
						PlaySound(enemy_explode01);
#endif
						canonBase.isAlive = false;
						canonTop.isAlive=false;
						missiles[f].active = false;
						targetsLeft--;
					}
				}
			}
		}

		void missileDraw()
		{
			// Draw missile
			for (int i = 0; i < maxMissiles; i++)
			{
				if (missiles[i].active)
					DrawRectangle(missiles[i].position.x, missiles[i].position.y, missiles[i].size.x, missiles[i].size.y, missiles[i].color);
			}
		}
	}
}