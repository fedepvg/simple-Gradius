#ifndef PLAYERMISSILE_H
#define PLAYERMISSILE_H

#include "raylib.h"
#include "PlayerShoot.h"

namespace Juego 
{
	const int maxMissiles = 4;
	const int missileShootAngle = 60;

	extern Shoot missiles[maxMissiles];

	extern float rapidFireMissileTimer;
	extern float rapidFireMissileRate;

	namespace Gameplay_Section
	{
		void createMissile();
		void missileInput();
		void missileUpdate();
		void missileDraw();
	}
}

#endif