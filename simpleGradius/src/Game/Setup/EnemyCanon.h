#ifndef ENEMYCANON_H
#define ENEMYCANON_H

#include "raylib.h"
#include "Player.h"

namespace Juego
{
	extern rocketShip canonBase;

	namespace Gameplay_Section
	{
		void createEnemyCanon();
		void EnemyCanonUpdate();
		void EnemyCanonDraw();
	}
}
#endif // ENEMY_H