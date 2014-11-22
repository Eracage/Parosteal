#include <MenuScene.hpp>
#include <Scenes.hpp>
#include <Button.h>

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
	createLayers();

	//AddChild(a = new GameObject());
	//a->AddComponent(new Sprite("test.tga"));

	pmath::Vec2 position, size;
	position.x = 0;
	position.y = -256;

	size.w = 512;
	size.h = 64;

	position.y += 80;
	AddChild(a = new Button(position, size, "Start game", [](){uthSceneM.GoToScene(GAME); }));
	position.y += 80;
	AddChild(a = new Button(position, size, "Credits", [](){uthSceneM.GoToScene(CREDITS); }));
	position.y += 80;
	AddChild(a = new Button(position, size, "Quit", [](){ uthEngine.Exit(); }));

	return true;
}
bool MenuScene::DeInit()
{
	return true;
}

void MenuScene::Update(float dt)
{
	Scene::Update(dt);

	//a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
