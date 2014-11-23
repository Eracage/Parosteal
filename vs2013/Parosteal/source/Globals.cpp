#include <Globals.h>

int Globals::CLOUD_COUNT = 36;
pmath::Vec2 Globals::LAST_PARTICLE = pmath::Vec2(0, 0);

//Player control
pmath::Vec2 Globals::PLAYER_POS;

pmath::Vec2 Globals::PLAYER_TIP;

pmath::Vec2 Globals::PLAYER_MAX = pmath::Vec2(0, 0);
pmath::Vec2 Globals::PLAYER_MIN = pmath::Vec2(0, 0);

float Globals::DIFFICULTY = 0;

float Globals::JAM_PARTICIPATIONS = 0;
float Globals::MAX_JAM_PARTICIPATIONS = 0;

std::string Globals::LASTHIT = "";

Player* Globals::PLAYER;

float Globals::TIMER = 120;

pmath::Vec2 Globals::TILE_MIDDLE;

void Globals::SoftReset()
{
	CLOUD_COUNT = 36;

	LAST_PARTICLE = pmath::Vec2(0, 0);

	//Player control
	PLAYER_MAX = pmath::Vec2(0, 0);
	PLAYER_MIN = pmath::Vec2(0, 0);

	DIFFICULTY = 0;

	JAM_PARTICIPATIONS = 0;

	TILE_MIDDLE = pmath::Vec2();

	LASTHIT = "";

	TIMER = 2;
}
