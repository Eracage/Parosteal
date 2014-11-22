#include <Player.h>
#include <Globals.h>

using namespace uth;

pmath::Vec2 control()
{
	pmath::Vec2 retVal;

	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad1))
	{
		retVal.x -= 1;
		retVal.y += 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad2) || uthInput.Keyboard.IsKeyDown(Keyboard::Down))
	{
		retVal.y += 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad3))
	{
		retVal.x += 1;
		retVal.y += 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad4) || uthInput.Keyboard.IsKeyDown(Keyboard::Left))
	{
		retVal.x -= 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad6) || uthInput.Keyboard.IsKeyDown(Keyboard::Right))
	{
		retVal.x += 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad7))
	{
		retVal.x -= 1;
		retVal.y -= 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad8) || uthInput.Keyboard.IsKeyDown(Keyboard::Up))
	{
		retVal.y -= 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Numpad9))
	{
		retVal.y -= 1;
		retVal.x += 1;
	}
	if (retVal != pmath::Vec2())
		return retVal.normalize();
	return retVal;
}

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
	const pmath::Vec2 tipPos = m_tip->transform.GetPosition();
	m_tip->transform.Move((/*tipPos +*/ uth::Randomizer::InsideCircle((5 + pow(tipPos.length(),0.1))/10)) * dt);

	m_tip->transform.Move(control() * dt * 80);

	pmath::Vec2 movement = pmath::Mat2::createRotation(90) * m_tip->transform.GetPosition() * sqrt(m_tip->transform.GetPosition().length()) * dt * 0.8f;
	m_tip->transform.Move(movement);
	transform.Move(-movement * 0.2);
}
