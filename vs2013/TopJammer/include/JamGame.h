#ifndef JAM_GAME_H
#define JAM_GAME_H

#include <UtH\UtHEngine.hpp>
class JamGame
	: public uth::GameObject
{
public:
	JamGame(pmath::Vec2 pos);
	~JamGame();
	//void update(float dt)override;

private:
	std::vector<uth::Texture*> textures;
	//float timer = 300;
};


#endif