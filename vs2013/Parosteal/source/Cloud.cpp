#include <Cloud.h>

using namespace uth;

Cloud::Cloud()
	: Sprite(nullptr)
{
	textures.push_back(uthRS.LoadTexture("DefaultCloud.png"));
	textures.push_back(uthRS.LoadTexture("DefaultCloud.png"));
	textures.push_back(uthRS.LoadTexture("DefaultCloud.png"));
	textures.push_back(uthRS.LoadTexture("DefaultCloud.png"));
	textures.push_back(uthRS.LoadTexture("DefaultCloud.png"));

	respawn();
}

void Cloud::respawn()
{
	type = rand() % 5;
	SetTexture(textures[type]);
}