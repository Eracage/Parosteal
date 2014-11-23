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
	soundTimer = 0;
	sounds.push_back(uthRS.LoadSound("Beat1.wav"));
	sounds.push_back(uthRS.LoadSound("Beat2.wav"));
	sounds.push_back(uthRS.LoadSound("Beat3.wav"));
	sounds.push_back(uthRS.LoadSound("Beat4.wav"));
	sounds.push_back(uthRS.LoadSound("Beat5.wav"));
	sounds[rand() % sounds.size()]->Play();

	createLayers();

	layers[LMap]->AddChild(new Background());

	layers[LPlayer]->AddChild(Globals::PLAYER = new Player(layers[LMap]));

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
		particle.SetRotation((Globals::PLAYER_TIP - Globals::LAST_PARTICLE).angle());
		particle.SetPosition(Globals::LAST_PARTICLE);
		//Globals::LAST_PARTICLE = Globals::PLAYER_TIP;
	});

	aff->SetParticleUpdateFunc([](Particle& part, const ParticleTemplate& ptemp, float dt)
	{
		//part.color = pmath::Vec4(0, 0, 0, 1);
	});

	particleSystem->AddAffector(aff);
	particleSystem->SetEmitProperties(true, 100.0f, 100.0f, 1, 1);

	Globals::TIMER = 120;
	Globals::JAM_PARTICIPATIONS = 0;

	layers[LMap]->AddChild(new CloudController());

	{
		GameObject* bg = new GameObject();
		bg->AddComponent(new Sprite("UI.png"));
		bg->transform.SetPosition(-686, -366);
		bg->transform.SetOrigin(7);
		layers[LUi]->AddChild(bg);

		GameObject* go = new GameObject();
		go->AddComponent(new UpdatingText<float>("Attended ", Globals::JAM_PARTICIPATIONS, " Game Jams"));
		go->transform.SetPosition(-634, -354);
		go->transform.SetOrigin(7);
		layers[LUi]->AddChild(go);

		GameObject* go2 = new GameObject();
		go2->AddComponent(new UpdatingText<float>("Time left: ", Globals::TIMER, "s"));
		go2->transform.SetPosition(-634, -300);
		go2->transform.SetOrigin(7);
		layers[LUi]->AddChild(go2);
	}

	return true;
}
bool GameScene::DeInit()
{
	if (Globals::MAX_JAM_PARTICIPATIONS < Globals::JAM_PARTICIPATIONS)
		Globals::MAX_JAM_PARTICIPATIONS = Globals::JAM_PARTICIPATIONS;
	return true;
}

void GameScene::Update(float dt)
{
	soundTimer += dt;
	if (soundTimer > 8)
	{
		soundTimer -= 8;
		sounds[rand() % sounds.size()]->Play(soundTimer);
	}
	//create particles
	pmath::Vec2 difference = Globals::PLAYER_TIP - Globals::LAST_PARTICLE;
	while(difference.length() > 24)
	{
		pmath::Vec2 newPos = difference.unitVector()*24;
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

	//timer
	Globals::TIMER -= dt;
	if (Globals::TIMER < 0){
		uthSceneM.GoToScene(MENU);
	}

	//a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
