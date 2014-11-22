#pragma once
#include <UtH\UtHEngine.hpp>
class Background :
	public uth::GameObject
{
private:
	std::vector<uth::Texture*> textures;
	pmath::Vec2& position;
	float size;
public:
	Background(pmath::Vec2& positionVec);
	~Background();
	void update(float)override;
};

