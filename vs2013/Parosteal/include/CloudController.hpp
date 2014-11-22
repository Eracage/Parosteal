#pragma once
#include <UtH\UtHEngine.hpp>
class CloudController :
	public uth::GameObject
{
private:
	std::vector<GameObject*> clouds;
	float size;
public:
	CloudController();
	~CloudController();
	void update(float)override;
};

