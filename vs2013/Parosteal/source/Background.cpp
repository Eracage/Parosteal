#include "Background.h"

using namespace uth;

Background::Background(pmath::Vec2& positionVec)
	: position(positionVec)
{
	textures.push_back(uthRS.LoadTexture("Background1.png"));
	textures.push_back(uthRS.LoadTexture("Background2.png"));
	textures.push_back(uthRS.LoadTexture("Background3.png"));

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
	position += pmath::Vec2(0.2);

	for (auto& obj : Children())
	{
		auto o = static_cast<GameObject*>(obj.get());

		int x = 0, y = 0;
		if (o->transform.GetPosition().x - position.x > size)
			x--;
		else if (o->transform.GetPosition().x - position.x < -size)
			x++;
		if (o->transform.GetPosition().y - position.y > size)
			y--;
		else if (o->transform.GetPosition().y - position.y < -size)
			y++;

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
