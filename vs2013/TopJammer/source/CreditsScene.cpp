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


	auto logo = new GameObject;
	logo->AddComponent(new Sprite("logo.png"));
	logo->transform.SetPosition(0, -300);
	logo->transform.SetOrigin(8);
	logo->transform.ScaleToSize(230, 105);
	AddChild(logo);

	{
		GameObject* go = new GameObject();
		Text* txt = new Text("8bitoperator.ttf", 32, "Text", pmath::Vec4(0.1, 1.0, 0.1, 1.0));
		go->AddComponent(txt);
		txt->AddText("Esko Haila - Coding, Sound Editing");
		go->transform.SetOrigin(4);
		go->transform.SetPosition(-420, -100);
		AddChild(go);
	}
	{
		GameObject* go = new GameObject();
		Text* txt = new Text("8bitoperator.ttf", 32, "Text", pmath::Vec4(0.1, 1.0, 0.1, 1.0));
		go->AddComponent(txt);
		txt->AddText("Olli Salminen - Coding, Graphics");
		go->transform.SetOrigin(4);
		go->transform.SetPosition(-420, -20);
		AddChild(go);
	}
	{
		GameObject* go = new GameObject();
		Text* txt = new Text("8bitoperator.ttf", 32, "Text", pmath::Vec4(0.1, 1.0, 0.1, 1.0));
		go->AddComponent(txt);
		txt->AddText("Mikael Immonen - Sounds");
		go->transform.SetOrigin(4);
		go->transform.SetPosition(-420, 60);
		AddChild(go);
	}
	{
		GameObject* go = new GameObject();
		Text* txt = new Text("8bitoperator.ttf", 32, "Text", pmath::Vec4(0.1, 1.0, 0.1, 1.0));
		go->AddComponent(txt);
		txt->AddText("Peetu Rimmi - Graphics, Google's assistant");
		go->transform.SetOrigin(4);
		go->transform.SetPosition(-420, 140);
		AddChild(go);
	}
	{
		GameObject* go = new GameObject();
		Text* txt = new Text("8bitoperator.ttf", 32, "Text", pmath::Vec4(0.1, 1.0, 0.1, 1.0));
		go->AddComponent(txt);
		txt->AddText("Google - Producer, Designer");
		go->transform.SetOrigin(4);
		go->transform.SetPosition(-420, 220);
		AddChild(go);
	}

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

	AddChild(a = new Button({ 522, 300 }, { 172, 64 }, "Back", [](){uthSceneM.GoToScene(MENU); }));




	return true;
}
bool CreditsScene::DeInit()
{
	return true;
}

void CreditsScene::Update(float dt)
{
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Escape))
		uthSceneM.GoToScene(SceneName::MENU);

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
