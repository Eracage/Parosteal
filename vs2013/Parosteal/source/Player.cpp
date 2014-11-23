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

Player::Player(Object* map)
	: GameObject("Player"),
	m_map(map)
{
	AddChild(m_topShadow = new GameObject());
	m_topShadow->AddTags({ "Player", "Shadow" });
	m_topShadow->AddComponent(new Sprite("TopBottom.png"));

	AddChild(m_top = new GameObject());
	m_top->AddTags({ "Player", "Base" });
	m_top->AddComponent(new Sprite("TopTop.png"));

	AddChild(m_tip = new GameObject());
	m_tip->AddTags({ "Player", "Tip" });
	m_tip->AddComponent(new Sprite("PlayerTip.png"));



	Globals::SCORE = 0;
}

void Player::update(float dt)
{
	static int movementType = 1;

	setDifficulty();

	//Globals::DIFFICULTY += 0.1f * dt;

	Transform& tipT = m_tip->transform;

	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key1))
		Globals::DIFFICULTY = 1;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key2))
		Globals::DIFFICULTY = 2;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key3))
		Globals::DIFFICULTY = 3;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key4))
		Globals::DIFFICULTY = 4;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key5))
		Globals::DIFFICULTY = 5;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key6))
		Globals::DIFFICULTY = 6;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key7))
		Globals::DIFFICULTY = 7;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key8))
		Globals::DIFFICULTY = 8;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key9))
		Globals::DIFFICULTY = 9;
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Key0))
	{
		Globals::DIFFICULTY = 0;

		setDifficulty();

		PlayerPos = pmath::Vec2();
		tipT.SetPosition(pmath::Vec2());
		m_top->transform.SetPosition(pmath::Vec2());

		Globals::PLAYER_POS = pmath::Vec2();
	}

	const pmath::Vec2 tipPos = tipT.GetPosition();


	tipT.Move(pmath::Mat2::createRotation(180) * control() * dt * 80);


	// Making tip make random movement, more the further it is from base
	tipT.Move(
		(tipPos/15 + uth::Randomizer::InsideCircle(
			(450 + pow(tipPos.length(), 1.8f)) / 5)) 
		* m_tipRandomMovementMultiplier * dt);

	// Move Player
	PlayerPos += pmath::Mat2::createRotation(90)
		* tipT.GetPosition()
		* (m_speed + pow(tipT.GetPosition().length(), 0.7)) * dt * m_speedMultiplier;


	// Keep spinning
	const float SpinAmount = (1 + pow(tipT.GetPosition().lengthSquared(), m_spinPow))
		* dt * m_spinMultiplier;

	tipT.SetPosition(pmath::Mat2::createRotation(SpinAmount) * tipT.GetPosition());

	m_top->transform.Rotate(SpinAmount)

	// Keep tip in rational range
	if (tipT.GetPosition().lengthSquared() > 12000)
		tipT.SetPosition(tipT.GetPosition().normalized() * 109);

	// Keep top in opposite direction of tip
	m_baseTargetPos = -tipT.GetPosition();
	m_top->transform.Move((m_baseTargetPos - m_top->transform.GetPosition()) * dt * 3);
	m_topShadow->transform.SetPosition(m_top->transform.GetPosition() * 0.90);


	//float rotation = dt * (tipPos.length() + 100);
	//m_map->transform.Rotate(rotation);
	//tipT.SetPosition(pmath::Mat2::createRotation(-rotation) * tipT.GetPosition());


	Globals::PLAYER_POS = PlayerPos - m_tip->transform.GetPosition();
	Globals::PLAYER_TIP = tipT.GetPosition();

	m_map->transform.SetOrigin(Globals::PLAYER_POS);
}

void Player::setDifficulty()
{
	const float dif = Globals::DIFFICULTY;
	const float difSqrt = sqrt(dif);

	m_tipRandomMovementMultiplier = 1;
	m_spinMultiplier = 9;
	m_spinPow = 0.45f;
	m_speed = 3;
	m_speedMultiplier = 0.5;

	m_tipRandomMovementMultiplier += difSqrt * 0.01f;
	m_spinMultiplier += difSqrt * sin(dif) * 0.01;
	m_spinPow += difSqrt * 0.01f;
	m_speed += difSqrt * 0.1;
	m_speedMultiplier += 0.05 * difSqrt;

}
