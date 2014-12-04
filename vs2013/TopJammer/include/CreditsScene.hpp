#pragma once
#ifndef CREDITSSCENE_H_UTH
#define CREDITSSCENE_H_UTH

#include <UtH/UtHEngine.hpp>

class CreditsScene : public uth::Scene
{
	void createLayers();
public:
	CreditsScene(){}
	~CreditsScene() override{}
	
	bool Init() override;
	bool DeInit() override;
	
	void Update(float dt) override;
	//void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;
	uth::GameObject* a;
	std::vector<uth::Layer*> layers;
};

#endif
