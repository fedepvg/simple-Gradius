#ifndef ENEMYCANON_H
#define ENEMYCANON_H

#include "raylib.h"
#include "Player.h"
#include "PlayerShoot.h"

namespace Juego
{
	extern rocketShip canonBase;
	extern rocketShip canonTop;
	extern Rectangle enemyCanonCollider;
	extern Shoot canonShoot;

	namespace Gameplay_Section
	{
		void createEnemyCanon();
		void EnemyCanonUpdate();
		void EnemyCanonDraw();
	}
}
#endif // ENEMY_H