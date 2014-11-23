#ifndef GLOBALS_H
#define GLOBALS_H

#include <UtH/UtHEngine.hpp>
#include <Player.h>

class Globals
{
public:
	static int CLOUD_COUNT;
	// Player control
	static Player* PLAYER;

	static pmath::Vec2 PLAYER_POS;
	static pmath::Vec2 PLAYER_TIP;

	static pmath::Vec2 LAST_PARTICLE;

	static float DIFFICULTY;

	static float JAM_PARTICIPATIONS;
	static float MAX_JAM_PARTICIPATIONS;

	static pmath::Vec2 PLAYER_MAX;
	static pmath::Vec2 PLAYER_MIN;

	static float TIMER;

	static std::string LASTHIT;

	static pmath::Vec2 TILE_MIDDLE;

	static void SoftReset();
};

#endif