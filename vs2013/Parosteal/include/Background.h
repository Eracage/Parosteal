#pragma once
#include <UtH\UtHEngine.hpp>
class Background :
	public uth::GameObject
{
private:
	std::vector<uth::Texture*> textures;
	float size;
public:
	Background();
	~Background();
	void update(float)override;
};

