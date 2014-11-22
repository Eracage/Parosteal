#pragma once
#ifndef GAMESCENE_H_UTH
#define GAMESCENE_H_UTH

#include <UtH/UtHEngine.hpp>

class GameScene : public uth::Scene
{
	void createLayers();
public:
	GameScene(){}
	~GameScene() override{}
	
	bool Init() override;
	bool DeInit() override;
	
	void Update(float dt) override;
	//void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;
	uth::GameObject* a;
	std::vector<uth::Layer*> layers;

	pmath::Vec2 position;
};

#endif
