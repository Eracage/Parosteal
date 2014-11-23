#include <GameScene.hpp>
#include <Scenes.hpp>
#include <uth/Platform/JavaFunctions.hpp>
#include <Player.h>
#include <Background.h>
#include <CloudController.hpp>
#include <Globals.h>
#include <UpdatingText.h>


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
	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);

	createLayers();

	layers[LMap]->AddChild(new Background());

	layers[LPlayer]->AddChild(new Player(layers[LMap]));

	ParticleTemplate pt;
	pt.SetLifetime(-1.f);
	pt.SetSpeed(0);
	pt.SetTexture(uthRS.LoadTexture("particle.png"));

	layers[LMap]->AddChild(particleSystem = new ParticleSystem(300000));
	particleSystem->SetTemplate(pt);

	Affector* aff = new Affector();
	aff->SetParticleInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
	{
		float angle = rand() % 360;
		particle.direction = pmath::Vec2(pmath::cos(angle), pmath::sin(angle));
		particle.SetPosition(Globals::LAST_PARTICLE);
		//Globals::LAST_PARTICLE = Globals::PLAYER_TIP;
	});

	aff->SetParticleUpdateFunc([](Particle& part, const ParticleTemplate& ptemp, float dt)
	{
		//part.color = pmath::Vec4(0, 0, 0, 1);
	});

	particleSystem->AddAffector(aff);
	particleSystem->SetEmitProperties(true, 100.0f, 100.0f, 1, 1);
	particleSystem->AddTag("PS");

	layers[LMap]->AddChild(new CloudController());

	{
		GameObject* go = new GameObject();
		go->AddComponent(new UpdatingText<float>("Attended ", Globals::JAM_PARTICIPATIONS, " Game Jams"));
		go->transform.SetPosition(-640, -360);
		go->transform.SetOrigin(7);
		layers[LUi]->AddChild(go);
	}

	return true;
}
bool GameScene::DeInit()
{
	return true;
}

void GameScene::Update(float dt)
{
	//create particles
	pmath::Vec2 difference = Globals::PLAYER_TIP - Globals::LAST_PARTICLE;
	while(difference.length() > 32)
	{
		pmath::Vec2 newPos = difference.unitVector()*32;
		Globals::LAST_PARTICLE += newPos;
		particleSystem->Emit(1);
		difference = Globals::PLAYER_TIP - Globals::LAST_PARTICLE;
	}

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
