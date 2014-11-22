#include <GameScene.hpp>
#include <Scenes.hpp>
#include <uth/Platform/JavaFunctions.hpp>
#include <Player.h>
#include <Background.h>

using namespace uth;


namespace
{
    enum Layers
    {
        LMap,
		LPlayer,
		LUi,
		LCount
    };
}

void GameScene::createLayers()
{
	for (int i = 0; i < LCount; ++i)
		layers.push_back(AddChild<GameObject>().get());

	//AddChild<GameObject>();

	//AddChild(a = new GameObject(std::vector<std::string>("child", "gameObject")));

	//a->AddTag("child2");
	//a->AddTags({"a","b"});

	//Children("a");

	//FindAll("a");

	//layers[Default]->AddChild<GameObject>();
}

bool GameScene::Init()
{
	createLayers();

	layers[LMap]->AddChild(new Background(position));

	layers[LPlayer]->AddChild(new Player(layers[LMap],position));

	//a->AddComponent(new Sprite("test.tga"));

	


	return true;
}
bool GameScene::DeInit()
{
	return true;
}

void GameScene::Update(float dt)
{
	if (dt > 0.1)
		dt = 0.1;
	Scene::Update(dt);

	static float scale = 1;

	if (uthInput.Keyboard.IsKeyDown(Keyboard::NumpadAdd))
		scale *= 1 + dt;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::NumpadSubtract))
		scale *= 1 - dt;

	layers[LMap]->transform.SetScale(scale);

	//a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
