#include <Player.h>
#include <Globals.h>

using namespace uth;

Player::Player()
	: GameObject("Player")
{
	AddChild(m_base = new GameObject());
	m_base->AddTags({ "Player", "Base" });
	m_base->AddComponent(new Sprite("PlayerBase.png"));

	AddChild(m_tip = new GameObject());
	m_tip->AddTags({ "Player", "Tip" });
	m_tip->AddComponent(new Sprite("PlayerTip.png"));


	Globals::SCORE = 0;
}

void Player::update(float dt)
{
	pmath::Vec2 tipPos = m_tip->transform.GetPosition();
	m_tip->transform.Move((tipPos + uth::Randomizer::InsideCircle((1 + tipPos.length())/10)) * dt);

	transform.Move(pmath::Mat2::createRotation(90) * tipPos * dt);
}
