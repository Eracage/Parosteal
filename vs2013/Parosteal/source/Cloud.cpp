#include <Cloud.h>

using namespace uth;

Cloud::Cloud()
	: Sprite(nullptr)
{
	textures.push_back(uthRS.LoadTexture("StrawberryCloud.png"));
	textures.push_back(uthRS.LoadTexture("PlumCloud.png"));
	textures.push_back(uthRS.LoadTexture("GameCloud.png"));
	textures.push_back(uthRS.LoadTexture("BlueberryCloud.png"));
	textures.push_back(uthRS.LoadTexture("SpinachCloud.png"));

	respawn();
}

void Cloud::respawn()
{
	type = rand() % 5;
	SetTexture(textures[type]);
	//SetColor(pmath::Vec4((4.0f -  type)/4,0,0,1));
}