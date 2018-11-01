#include "EnemyCanon.h"

#include "Setup\Game.h"
#include "Screens\settings.h"
#include "Screens\gameplay.h"
#include "Player.h"
#include "PlayerShoot.h"

namespace Juego
{
	rocketShip canonBase;
	rocketShip canonTop;
	Shoot canonShoot;

	static Rectangle enemyCanonBaseSource;
	static Rectangle enemyCanonBaseDestination;
	static Rectangle enemyCanonTopSource;
	static Rectangle enemyCanonTopDestination;

	static Vector2 enemyCanonBaseOrigin;
	static Vector2 enemyCanonTopOrigin;

	Rectangle enemyCanonCollider;

	static Vector2 rotationDirection;

	static float shootTimer=0;
	static float shootSpeed=1000.0f;
	static float rotationAux;

	namespace Gameplay_Section
	{
		void createEnemyCanon()
		{
			if (resolutionNormal)
			{
				canonBase.defaultSpeed =parallaxLayersSpeed[0];
				canonBase.size = {(float) enemyCanonBase.width, (float)enemyCanonBase.height };

				canonTop.defaultSpeed = parallaxLayersSpeed[0];
				canonTop.size = { (float)enemyCanonTop.width, (float)enemyCanonBase.height };
			}
			else if (resolutionSmall)
			{
				canonBase.defaultSpeed = parallaxLayersSpeed[0];
				canonBase.size = { (float)enemyCanonBase.width / resolutionSizeFix, (float)enemyCanonTop.height / resolutionSizeFix };

				canonTop.defaultSpeed = parallaxLayersSpeed[0];
				canonTop.size = { (float)enemyCanonTop.width / resolutionSizeFix, (float)enemyCanonTop.height / resolutionSizeFix };
			}
			canonBase.position.y = GetScreenHeight() / 2 + canonBase.size.y / 2;
			canonBase.position.x = GetScreenWidth() * 2;
			canonBase.isAlive = true;
			canonBase.inputActive = false;
			canonBase.textureTint = { 0, 0, 0, 0 };
			enemyCanonBaseSource = { 0.0f,0.0f,  (float)enemyCanonBase.width, (float)enemyCanonBase.height };
			enemyCanonBaseOrigin = { (float)enemyCanonBase.width / 2,(float)enemyCanonBase.height / 2 };

			canonTop.position.y = canonBase.position.y - canonTop.size.y / 2;
			canonTop.position.x = canonBase.position.x;
			canonTop.isAlive = true;
			canonTop.inputActive = false;
			canonTop.textureTint = { 0, 0, 0, 0 };
			enemyCanonTopSource = { 0.0f,0.0f,  (float)enemyCanonTop.width, (float)enemyCanonTop.height };
			enemyCanonTopOrigin = { (float)enemyCanonTop.width / 2,(float)enemyCanonTop.height/2 + (float)enemyCanonTop.height *0.15f};
			canonTop.rotation = 0.0f;

			canonShoot.position.x = canonTop.position.x;
			canonShoot.position.y = canonTop.position.y;
			if (resolutionNormal)
			{
				canonShoot.size.x = 20;
				canonShoot.size.y = 5;
			}
			else if (resolutionSmall)
			{
				canonShoot.size.x = 20 / resolutionSizeFix;
				canonShoot.size.y = 5 / resolutionSizeFix;
			}
			canonShoot.speed.x = 0;
			canonShoot.speed.y = 0;
			canonShoot.color = BLUE;
			canonShoot.active = false;
		}

		void EnemyCanonUpdate()
		{
			
			if (shootTimer >= 2.0f)
			{
				shootTimer = 0.0f;
				if (canonBase.position.x < GetScreenWidth()) 
				{
					canonShoot.position.x = canonTop.position.x;
					canonShoot.position.y =canonTop.position.y;
					canonShoot.speed.x = sin((canonTop.rotation+180)*DEG2RAD)*shootSpeed;
					canonShoot.speed.y = cos(canonTop.rotation*DEG2RAD)*shootSpeed;
					rotationAux = (canonTop.rotation+180)*DEG2RAD;
					canonShoot.active = true;
				}
			}

			if (canonShoot.active) 
			{
				canonShoot.speed.x = sin(rotationAux)*shootSpeed;
				canonShoot.speed.y = cos(rotationAux)*shootSpeed;
				canonShoot.position.x -= canonShoot.speed.x*GetFrameTime();
				canonShoot.position.y += canonShoot.speed.y*GetFrameTime();
			}

			shootTimer += GetFrameTime();

			if (player.position.y > canonTop.position.y + canonTop.size.y) 
			{
				canonTop.rotation = -115.0f;
			}
			else if (player.position.y < canonTop.position.y - canonTop.size.y) 
			{
				canonTop.rotation = -75.0f;
			}
			else
			{
				canonTop.rotation =-90.0f;
			}

			canonBase.position.x -= canonBase.defaultSpeed * GetFrameTime();

			canonTop.position.x -= canonTop.defaultSpeed * GetFrameTime();

			if (canonBase.position.x < 0 - canonBase.size.x || !canonBase.isAlive)
			{
				canonBase.isAlive = true;
				canonBase.position.x = GetRandomValue((float)screenWidth + canonBase.size.x, (float)screenWidth + (canonBase.size.x * 10));
			}

			if (canonTop.position.x < 0 - canonTop.size.x || !canonTop.isAlive)
			{
				canonTop.isAlive = true;
				canonTop.position.x = canonBase.position.x;
			}

			enemyCanonCollider.x = canonBase.position.x-canonBase.size.x/2;
			enemyCanonCollider.y = canonTop.position.y-canonTop.size.y/2;
			enemyCanonCollider.width = canonBase.size.x;
			enemyCanonCollider.height = canonTop.size.y+canonBase.size.y/2;
		}

		void EnemyCanonDraw()
		{
			if (resolutionNormal)
			{
				enemyCanonBaseSource = { 0.0f,0.0f, (float)enemyCanonBase.width,(float)enemyCanonBase.height};
				enemyCanonBaseDestination = { canonBase.position.x,canonBase.position.y, (float)enemyCanonBase.width,(float)enemyCanonBase.height};

				enemyCanonTopSource = { 0.0f,0.0f, (float)enemyCanonTop.width,(float)enemyCanonTop.height };
				enemyCanonTopDestination = { canonTop.position.x,canonTop.position.y, (float)enemyCanonTop.width,(float)enemyCanonTop.height };
			}
			else if (resolutionSmall)
			{
				enemyCanonBaseSource = { 0.0f,0.0f, enemyCanonBase.width / resolutionSizeFix,enemyCanonBase.height / resolutionSizeFix };
				enemyCanonBaseDestination = { canonBase.position.x,canonBase.position.y, enemyCanonBase.width / resolutionSizeFix,enemyCanonBase.height / resolutionSizeFix };

				enemyCanonTopSource = { 0.0f,0.0f,(float)enemyCanonTop.width / resolutionSizeFix,(float)enemyCanonTop.height / resolutionSizeFix };
				enemyCanonTopDestination = { canonTop.position.x,canonTop.position.y, (float)enemyCanonTop.width / resolutionSizeFix,(float)enemyCanonTop.height / resolutionSizeFix };

			}
			
			DrawRectangleRec(enemyCanonCollider, BLANK);
			if (canonShoot.active) {
				DrawRectangle(canonShoot.position.x, canonShoot.position.y, canonShoot.size.x, canonShoot.size.y, canonShoot.color);
			}

			if (canonBase.isAlive)
			{
				DrawRectangle(canonBase.position.x, canonBase.position.y, canonBase.size.x, canonBase.size.y, BLANK);
				DrawTexturePro(enemyCanonBase, enemyCanonBaseSource, enemyCanonBaseDestination, enemyCanonBaseOrigin, 0, WHITE);
			}

			if (canonTop.isAlive)
			{
				DrawRectangle(canonTop.position.x, canonTop.position.y, canonTop.size.x, canonTop.size.y, BLANK);
				DrawTexturePro(enemyCanonTop, enemyCanonTopSource, enemyCanonTopDestination, enemyCanonTopOrigin, canonTop.rotation, WHITE);
			}	
			
		}

	}
}