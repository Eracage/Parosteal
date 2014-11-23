#include <CreditsScene.hpp>
#include <Scenes.hpp>
#include <Button.h>
#include <MenuScene.hpp>

using namespace uth;


namespace
{
    enum Layers
    {
        Default,
        Other,
		Count
    };
}

void CreditsScene::createLayers()
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

bool CreditsScene::Init()
{
	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);

	createLayers();

	AddChild(a = new Button({ 540, 300 }, { 128, 64 }, "Back", [](){uthSceneM.GoToScene(MENU); }));




	return true;
}
bool CreditsScene::DeInit()
{
	return true;
}

void CreditsScene::Update(float dt)
{
	if (MenuScene::volume < 100)
	{
		MenuScene::volume += 20 * dt;
		MenuScene::audio->SetVolume(MenuScene::volume);

	}
	else
		MenuScene::audio->SetVolume(100);

	Scene::Update(dt);
}

//void CreditsScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
