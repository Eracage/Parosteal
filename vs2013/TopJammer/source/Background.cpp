#include "Background.h"
#include <Globals.h>

using namespace uth;

Background::Background()
{
	textures.push_back(uthRS.LoadTexture("Background4.png"));

	size = uthEngine.GetWindow().GetCamera().GetSize().x;

	pmath::Vec2 textureSize = textures[0]->GetSize();

	//create texture objects
	for (int i = 0; i < size * 2 / textureSize.x; i++)
	{
		for (int j = 0; j < size * 2 / textureSize.x; j++)
		{
			auto *o = new GameObject();
			AddChild(o);
			o->transform.SetPosition(-size + i*textureSize.x, -size + j*textureSize.y);
		}
	}
	for (auto& obj : Children()){
		auto o = static_cast<GameObject*>(obj.get());
		o->AddComponent(new Sprite(textures[rand() % textures.size()]));
	}
}

void Background::update(float)
{
	Globals::TILE_MIDDLE = pmath::Vec2(512, 512);

	for (auto& obj : Children())
	{
		auto o = static_cast<GameObject*>(obj.get());

		int x = 0, y = 0;
		if (o->transform.GetPosition().x - Globals::PLAYER_POS.x > size)
			x--;
		else if (o->transform.GetPosition().x - Globals::PLAYER_POS.x < -size)
			x++;
		if (o->transform.GetPosition().y - Globals::PLAYER_POS.y > size)
			y--;
		else if (o->transform.GetPosition().y - Globals::PLAYER_POS.y < -size)
			y++;

		if ((o->transform.GetPosition() - Globals::PLAYER_POS).length() < 256)
			Globals::TILE_MIDDLE = o->transform.GetPosition() + pmath::Vec2(256);

		if (x != 0 || y != 0)
		{
			o->transform.Move(x*size*2, y*size*2);
			o->GetComponent<Sprite>()->SetTexture(textures[rand() % textures.size()]);
		}
	}
}


Background::~Background()
{
}
