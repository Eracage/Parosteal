#include <CloudController.hpp>
#include <Globals.h>
#include <Cloud.h>

using namespace uth;

CloudController::CloudController(pmath::Vec2& positionVec)
	:position(positionVec)
{
	size = uthEngine.GetWindow().GetCamera().GetSize().x;
	
	for (int i = 0; i < Globals::CLOUD_COUNT; i++)
	{
		auto *o = new GameObject();
		AddChild(o);
		float angle = rand() % 360;
		float x = 2000 * pmath::cos(angle);
		float y = 2000 * pmath::sin(angle);
		o->transform.SetPosition(position.x + x, position.y + y);
		o->transform.SetRotation(rand() % 360);
		o->AddComponent(new Cloud());
		
	}
}

void CloudController::update(float)
{
	//check clouds' distance from player and move to somewhere else
	for (auto& obj : Children())
	{
		auto o = static_cast<GameObject*>(obj.get());
		pmath::Vec2 posVector = o->transform.GetPosition();

		double distance = posVector.distance(posVector, position);

		if (distance > 2048)
		{
			float angle = rand() % 360;
			float x = 2000 * pmath::cos(angle);
			float y = 2000 * pmath::sin(angle);
			o->transform.SetRotation(rand() % 360);
			o->transform.SetPosition(position.x + x, position.y + y);
			o->GetComponent<Cloud>()->respawn();
		}
	}
}

CloudController::~CloudController()
{}