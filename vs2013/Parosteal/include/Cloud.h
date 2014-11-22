#ifndef CLOUD_H
#define CLOUD_H

#include <UtH\UtHEngine.hpp>
class Cloud :
	public uth::Sprite
{
private:
	std::vector<uth::Texture*> textures;
	int type;
public:
	enum Cloudtype{
		Strawberry,
		Plum,
		Game,
		Blueberry,
		Spinach
	};
	Cloud();
	void respawn();
};

#endif