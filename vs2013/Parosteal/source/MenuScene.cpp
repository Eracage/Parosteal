#include <MenuScene.hpp>
#include <Scenes.hpp>
#include <Button.h>

using namespace uth;

uth::Sound* MenuScene::audio = nullptr;

namespace
{
    enum Layers
    {
        Default,
        Other,
		Count
    };
}

void MenuScene::createLayers()
{
	for (int i = 0; i < Count; ++i)
		layers.push_back(AddChild<GameObject>().get());

	//AddChild<GameObject>();

	//AddChild(a = new GameObject(std::vector<std::string>("child", "gameObject")));

	//a->AddTag("child2");
	//a->AddTags({"a","b"});

	//Children("a");

	//FindAll("a");

	//layers[Default]->AddChild<GameObject>();
}

bool MenuScene::Init()
{
	if (audio == nullptr)
		audio = uthRS.LoadSound("Music.wav");
	audio->Loop(true);
	if (!audio->IsPlaying())
	{
		volume = 0;
		audio->SetVolume(volume);
		audio->Play();
	}
	else
		volume = 100;

	createLayers();

	//AddChild(a = new GameObject());
	//a->AddComponent(new Sprite("test.tga"));

	pmath::Vec2 position, size;
	position.x = 0;
	position.y = -256;

	size.w = 512;
	size.h = 64;

	position.y += 80;
	AddChild(a = new Button(position, size, "Start game", [](){uthSceneM.GoToScene(GAME); MenuScene::audio->Stop(); }));
	position.y += 80;
	AddChild(a = new Button(position, size, "Credits", [](){uthSceneM.GoToScene(CREDITS); }));
	position.y += 80;
	AddChild(a = new Button(position, size, "Quit", [](){ uthEngine.Exit(); MenuScene::audio->Stop(); }));

	return true;
}
bool MenuScene::DeInit()
{
	return true;
}

void MenuScene::Update(float dt)
{
	Scene::Update(dt);

	if (volume < 100)
	{	
		volume += 20 * dt;
		audio->SetVolume(volume);

	}
	else
		audio->SetVolume(100);

	//a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
