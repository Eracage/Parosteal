#include <CloudController.hpp>
#include <Globals.h>
#include <Cloud.h>

using namespace uth;

CloudController::CloudController()
{
	size = uthEngine.GetWindow().GetCamera().GetSize().x;
	
	for (int i = 0; i < Globals::CLOUD_COUNT; i++)
	{
		auto *o = new GameObject();
		AddChild(o);

		float angle = rand() % 360;
		pmath::Vec2 pos = pmath::Vec2(pmath::cos(angle), pmath::sin(angle))
			* Randomizer::GetFloat(0.3, 1) * 1500;
		o->transform.SetPosition(Globals::PLAYER_POS.x + pos.x, Globals::PLAYER_POS.y + pos.y);
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

		double distance = posVector.distance(posVector, Globals::PLAYER_POS);

		if (distance > 1600)
		{
			o->GetComponent<Cloud>()->randomMove();
			o->GetComponent<Cloud>()->respawn();
		}
	}
}

CloudController::~CloudController()
{}