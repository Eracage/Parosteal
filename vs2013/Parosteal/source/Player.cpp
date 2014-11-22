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
	: GameObject("Player"),
	m_movementMultiplier(1)
{
	AddChild(m_top = new GameObject());
	m_top->AddTags({ "Player", "Base" });
	m_top->AddComponent(new Sprite("PlayerBase.png"));

	AddChild(m_tip = new GameObject());
	m_tip->AddTags({ "Player", "Tip" });
	m_tip->AddComponent(new Sprite("PlayerTip.png"));


	Globals::SCORE = 0;
}

void Player::update(float dt)
{
	static int movementType = 1;

	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key1))
		movementType = 1;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key2))
		movementType = 2;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key3))
		movementType = 3;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key4))
		movementType = 4;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key5))
		movementType = 5;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key6))
		movementType = 6;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key7))
		movementType = 7;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key8))
		movementType = 8;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key9))
		movementType = 9;

	Transform& tipT = m_tip->transform;
	const pmath::Vec2 tipPos = tipT.GetPosition();


	tipT.Move(pmath::Mat2::createRotation(180) * control() * dt * 80);

	switch (movementType)
	{
	case 1:
		// Making tip make random movement, more the further it is from base
		tipT.Move(
			(tipPos/30 + uth::Randomizer::InsideCircle(
				(550 + pow(tipPos.length(), 1.6)) / 5)) 
			* m_movementMultiplier * dt);

		PlayerPos += pmath::Mat2::createRotation(90) 
			* tipT.GetPosition()
			* sqrt(tipT.GetPosition().length()) * dt * 0.8f;

		break;
	case 2:
		tipT.Move((uth::Randomizer::InsideCircle((20 + pow(tipPos.length(), 1.8)) / 9)) * m_movementMultiplier  * dt);
		break;
	case 3:
		tipT.Move((/*tipPos +*/ uth::Randomizer::InsideCircle((5 + pow(tipPos.length(), 0.1)) / 10)) * dt);

		{
			pmath::Vec2 movement = pmath::Mat2::createRotation(90) * tipT.GetPosition() * sqrt(tipT.GetPosition().length()) * dt * 0.8f;
			tipT.Move(movement);
			transform.Move(-movement * 0.2);
		}
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	}

	// Keep spinning
	tipT.SetPosition(
		pmath::Mat2::createRotation(
			pow(tipT.GetPosition().lengthSquared(), Globals::PLAYER_SPIN_POW)
			* dt * Globals::PLAYER_SPIN_MULTIPLIER)
		* tipT.GetPosition());

	// Keep tip in rational range
	if (tipT.GetPosition().lengthSquared() > 8000)
		tipT.SetPosition(tipT.GetPosition() * 0.99);

	// Keep top in opposite direction of tip
	m_baseTargetPos = -tipT.GetPosition();
	m_top->transform.Move((m_baseTargetPos - m_top->transform.GetPosition()) * dt * 3);
}
