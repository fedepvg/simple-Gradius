#include "EnemyCanon.h"

#include "Setup\Game.h"
#include "Screens\settings.h"
#include "Screens\gameplay.h"

namespace Juego
{
	rocketShip canonBase;
	rocketShip canonTop;

	static Rectangle enemyCanonBaseSource;
	static Rectangle enemyCanonBaseDestination;
	static Rectangle enemyCanonTopSource;
	static Rectangle enemyCanonTopDestination;

	static Vector2 enemyCanonBaseOrigin;
	static Vector2 enemyCanonTopOrigin;

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
			enemyCanonTopOrigin = { (float)enemyCanonTop.width / 2,(float)enemyCanonTop.height / 2 };
		}

		void EnemyCanonUpdate()
		{
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
			
			if (canonTop.isAlive)
			{
				DrawRectangle(canonTop.position.x, canonTop.position.y, canonTop.size.x, canonTop.size.y, BLANK);
				DrawTexturePro(enemyCanonTop, enemyCanonTopSource, enemyCanonTopDestination, enemyCanonTopOrigin, 0, WHITE);
			}

			if (canonBase.isAlive)
			{
				DrawRectangle(canonBase.position.x, canonBase.position.y, canonBase.size.x, canonBase.size.y,BLANK);
				DrawTexturePro(enemyCanonBase, enemyCanonBaseSource, enemyCanonBaseDestination, enemyCanonBaseOrigin, 0, WHITE);
			}
		}

	}
}