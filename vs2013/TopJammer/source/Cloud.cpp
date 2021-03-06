#include <Cloud.h>
#include <Globals.h>
#include <JamGame.h>

using namespace uth;

Cloud::Cloud()
{
	textures.push_back(uthRS.LoadTexture("StrawberryCloud.png"));
	textures.push_back(uthRS.LoadTexture("PlumCloud.png"));
	textures.push_back(uthRS.LoadTexture("GameCloud.png"));
	textures.push_back(uthRS.LoadTexture("BlueberryCloud.png"));
	textures.push_back(uthRS.LoadTexture("SpinachCloud.png"));

	respawn();
}

void Cloud::Init()
{
	for (int i = 0; i < 6; ++i)
	{
		objects.push_back(parent->AddChild<GameObject>().get());
		rotationSpeeds.push_back(50);
		auto c = new Sprite(nullptr);
		c->SetColor(1, 1, 1, 0.4f);
		objects.back()->AddComponent(c);
	}

	respawn();
}

void Cloud::respawn()
{
	type = rand() % 5;

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->GetComponent<Sprite>()->SetTexture(textures[type]);

		if (i != 0)
			rotationSpeeds[i] = 20 + rand() % 30;
	}

	dir = Randomizer::InsideCircle(Randomizer::GetFloat(30.f,80.f));

	//SetColor(pmath::Vec4((4.0f -  type)/4,0,0,1));
}

void Cloud::Update(float dt)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->transform.Rotate(rotationSpeeds[i] * dt * (i % 2 ? -1 : 1));
	}

	if ((parent->transform.GetPosition() - Globals::PLAYER_POS).length() < 190)
	{
		switch (type)
		{
		case Cloud::Strawberry:
			break;
		case Cloud::Plum:
			break;
		case Cloud::Game:
		{
			JamGame* g;
			parent->Parent()->Parent()->AddChild(g = new JamGame(parent->transform.GetPosition()));
			Globals::JAM_PARTICIPATIONS++;
			randomMove();
			respawn();
			break;
		}
		case Cloud::Blueberry:
			break;
		case Cloud::Spinach:
			break;
		}
		Globals::PLAYER->onCollision(type);
	}

	parent->transform.Move(dir * dt);
}

void Cloud::randomMove()
{
	float angle = rand() % 360;
	pmath::Vec2 pos = pmath::Vec2(pmath::cos(angle), pmath::sin(angle))
		* Randomizer::GetFloat(0.8, 1) * 1500;
	parent->transform.SetPosition(Globals::PLAYER_POS.x + pos.x, Globals::PLAYER_POS.y + pos.y);
	parent->transform.SetRotation(rand() % 360);
}
