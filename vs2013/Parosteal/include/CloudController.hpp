#pragma once
#include <UtH\UtHEngine.hpp>
class CloudController :
	public uth::GameObject
{
private:
	std::vector<GameObject*> clouds;
	pmath::Vec2& position;
	float size;
public:
	CloudController(pmath::Vec2& positionVec);
	~CloudController();
	void update(float)override;
};

