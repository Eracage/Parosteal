#include <CreditsScene.hpp>
#include <Scenes.hpp>

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
	createLayers();

	AddChild(a = new GameObject());
	a->AddComponent(new Sprite("test.tga"));



	return true;
}
bool CreditsScene::DeInit()
{
	return true;
}

void CreditsScene::Update(float dt)
{
	Scene::Update(dt);

	a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void CreditsScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
