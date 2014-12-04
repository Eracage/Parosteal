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
	uthEngine.SetClearColor(0.94f, 0.68f, 0.40);
	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);
	soundTimer = 0;
	sounds.push_back(uthRS.LoadSound("Beat1.wav"));
	sounds.push_back(uthRS.LoadSound("Beat2.wav"));
	sounds.push_back(uthRS.LoadSound("Beat3.wav"));
	sounds.push_back(uthRS.LoadSound("Beat4.wav"));
	sounds.push_back(uthRS.LoadSound("Beat5.wav"));
	sounds[0]->SetVolume(70);
	sounds[1]->SetVolume(70);
	sounds[2]->SetVolume(80);
	sounds[3]->SetVolume(60);
	sounds[4]->SetVolume(6);
	sounds[rand() % sounds.size()]->Play();

	Globals::SoftReset();

	createLayers();
	finished = false;
	targetScale = 1;
	scale = 1;
	endTime = 0;

	{
		GameObject* go = new GameObject("BGTILES");
		go->AddComponent(new Sprite("bg100.png"));
		go->transform.ScaleToSize(pmath::Vec2(51200));
		layers[Layers::LMap]->AddChild(go);

		GameObject* go2 = new GameObject("BGTILES");
		go2->AddComponent(new Sprite("bg10.png"));
		go2->transform.ScaleToSize(pmath::Vec2(5120));
		layers[Layers::LMap]->AddChild(go2);
	}

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
	});

	particleSystem->AddAffector(aff);
	particleSystem->SetEmitProperties(true, 100.0f, 100.0f, 1, 1);

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
	for (auto s : sounds)
		s->Stop();

	uthEngine.SetClearColor(0, 0, 0);
	if (Globals::MAX_JAM_PARTICIPATIONS < Globals::JAM_PARTICIPATIONS)
		Globals::MAX_JAM_PARTICIPATIONS = Globals::JAM_PARTICIPATIONS;


	return true;
}

void GameScene::Update(float dt)
{
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Escape))
	{
		uthSceneM.GoToScene(SceneName::MENU);
	}

	soundTimer += dt;
	if (soundTimer > 8)
	{
		soundTimer -= 8;
		sounds[rand() % sounds.size()]->Play(soundTimer);
	}

	if (dt > 0.1)
		dt = 0.1;

	if (!finished)
	{

		Scene::Update(dt);


		//create particles
		pmath::Vec2 difference = Globals::PLAYER_TIP - Globals::LAST_PARTICLE;
		while (difference.length() > 24)
		{
			pmath::Vec2 newPos = difference.unitVector() * 24;
			Globals::LAST_PARTICLE += newPos;
			particleSystem->Emit(1);
			difference = Globals::PLAYER_TIP - Globals::LAST_PARTICLE;
		}




		if (uthInput.Keyboard.IsKeyDown(Keyboard::NumpadAdd))
			scale *= 1 + dt;
		if (uthInput.Keyboard.IsKeyDown(Keyboard::NumpadSubtract))
			scale *= 1 - dt;

		transform.SetScale(scale);

		//timer
		Globals::TIMER -= dt;
		if (Globals::TIMER < 0)
		{
			Globals::TIMER = 0;

			for (auto o : FindAll("BGTILES"))
			{
				o->transform.SetPosition(Globals::TILE_MIDDLE);
			}

			pmath::Vec2 tScale;
			tScale = (Globals::PLAYER_MAX - Globals::PLAYER_MIN) * 1.5f;

			tScale.scale(1 / 1280.f, 1 / 720.f);
			targetScale = 1/(tScale.x > tScale.y ? tScale.x : tScale.y);


			finished = true;
		}
	}
	else
	{
		if (scale > targetScale || (((Globals::PLAYER_MAX + Globals::PLAYER_MIN) / 2)
			- layers[LMap]->transform.GetOrigin()).length() > 2)
		{
			if (scale > targetScale)
				scale *= 1 - dt;

			layers[LMap]->transform.SetScale(scale);
			layers[LPlayer]->transform.SetScale(scale);

			layers[LMap]->transform.SetOrigin(
				layers[LMap]->transform.GetOrigin()
				+ (((Globals::PLAYER_MAX + Globals::PLAYER_MIN) / 2)
				- layers[LMap]->transform.GetOrigin()) * dt
				);
		}
		else if (endTime > 4)
			uthSceneM.GoToScene(SceneName::MENU);
		else
			endTime += dt;
	}

	//a->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
