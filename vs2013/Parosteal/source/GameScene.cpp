#include <GameScene.hpp>
#include <Scenes.hpp>
#include <uth/Platform/JavaFunctions.hpp>
#include <Player.h>
#include <Background.h>
#include <CloudController.hpp>
#include <Globals.h>


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

	layers[LMap]->AddChild(new Background());

	layers[LPlayer]->AddChild(new Player(layers[LMap]));

	ParticleTemplate pt;
	pt.SetLifetime(-1.f);
	pt.SetSpeed(0);
	pt.SetTexture(uthRS.LoadTexture("particle.png"));

	auto ps = layers[LMap]->AddChild(new ParticleSystem(3000));
	ps->SetTemplate(pt);

	Affector* aff = new Affector();
	aff->SetParticleInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
	{
		float angle = rand() % 360;
		particle.direction = pmath::Vec2(pmath::cos(angle), pmath::sin(angle));
		particle.SetGlobalPosition(Globals::PLAYER_TIP);
	});

	aff->SetParticleUpdateFunc([](Particle& part, const ParticleTemplate& ptemp, float dt)
	{
		//part.color = pmath::Vec4(0, 0, 0, 1);
	});

	ps->AddAffector(aff);
	ps->SetEmitProperties(true, 0.1f, 0.1f, 1, 1);

	layers[LMap]->AddChild(new CloudController());

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

	transform.SetScale(scale);

	//a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
