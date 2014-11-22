#include <GameScene.hpp>
#include <Scenes.hpp>
#include <uth/Platform/JavaFunctions.hpp>
#include <Player.h>
#include <Background.h>
#include <CloudController.hpp>


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
	layers[LMap]->AddChild(new CloudController(position));

	layers[LPlayer]->AddChild<Player>();

	//a->AddComponent(new Sprite("test.tga"));

	


	return true;
}
bool GameScene::DeInit()
{
	return true;
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);

	layers[LMap]->transform.SetOrigin(position); 
	static float scale = 1;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::LocalPlus)){
		scale += 0.1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::LocalMinus)){
		scale -= 0.1;
	}
	layers[LMap]->transform.SetScale(scale);

	position += uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position())/100;

	//a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
