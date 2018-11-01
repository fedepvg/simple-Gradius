#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace Juego
{
	enum gameplayOptions 
	{
		buttonContinue = 20,
		buttonRestart,
		buttonGameOver,
		buttonQuitToMenu
	};

	enum playerKeysNumber
	{
		UP = 8,
		DOWN,
		SHOOT,
		MISSILE,
		MAX
	};

	extern bool gameON;
	extern int playerKeys[MAX];

	const int maxLayers = 6;
	extern Texture2D backgroundLayers[maxLayers];

	extern float parallaxLayersSpeed[maxLayers];

	extern Texture2D ship;
	extern Texture2D enemyShip;
	extern Texture2D enemyCanonBase;
	extern Texture2D enemyCanonTop;

	namespace Gameplay_Section
	{
		void InitGameplayVariables();
		void InitGameplayParallax();
		void InitGameplayScreen();
		void UpdateGameplayScreen();
		void DrawGameplay();
		void RestartPhase();
		bool FinishGameplayScreen();
		void DeInitGameplayParallax();
		void DeInitGameplayResources();
	}
}
#endif // GAMEPLAY_H