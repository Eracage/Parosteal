#ifndef CLOUD_H
#define CLOUD_H

#include <UtH\UtHEngine.hpp>
class Cloud :
	public uth::Component
{
private:
	std::vector<uth::GameObject*> objects;
	std::vector<float> rotationSpeeds;
	std::vector<uth::Texture*> textures;
	int type;

	pmath::Vec2 dir;
public:
	enum Cloudtype{
		Strawberry,
		Plum,
		Game,
		Blueberry,
		Spinach
	};
	Cloud();

	void randomMove();
	void Init();
	void respawn();
	void Update(float dt) override;
};

#endif