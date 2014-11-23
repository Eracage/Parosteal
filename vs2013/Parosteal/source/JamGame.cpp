#include<JamGame.h>

JamGame::JamGame(pmath::Vec2 pos)
{
	textures.push_back(uthRS.LoadTexture("Game1.png"));
	textures.push_back(uthRS.LoadTexture("Game2.png"));
	textures.push_back(uthRS.LoadTexture("Game3.png"));
	textures.push_back(uthRS.LoadTexture("Game4.png"));
	textures.push_back(uthRS.LoadTexture("Game5.png"));

	uth::GameObject* go;
	AddChild(go = new uth::GameObject());
	go->AddComponent(new uth::Sprite(textures[rand() % textures.size()]));

	transform.SetPosition(pos);
}

JamGame::~JamGame()
{
}

//void JamGame::update(float dt)
//{
//	timer -= dt;
//	if (timer < 0)
//	{
//		Remove();
//	}
//}