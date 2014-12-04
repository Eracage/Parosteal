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

	AddChild(m_topDude = new GameObject());
	m_topDude->AddTags({ "Player", "Dude" });
	m_topDude->AddComponent(new Sprite("TopDude.png"));

	AddChild(m_tip = new GameObject());
	m_tip->AddTags({ "Player", "Tip" });
	m_tip->AddComponent(new Sprite("PlayerTip.png"));

	defaults();
}

void Player::update(float dt)
{
	static int movementType = 1;

	m_tipRandomMovementMultiplier = 1 + ((m_tipRandomMovementMultiplier - 1) * (1 - dt));

	m_speedMultiplier = 0.5 + ((m_speedMultiplier - 0.5) * (1 - dt));

	m_bonusSpin = m_bonusSpin * (1 - dt/2);

	Transform& tipT = m_tip->transform;

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

	static float time = 0;
	time += dt;

	m_top->transform.Rotate(m_bonusSpin * 50 + 45 * dt + SpinAmount);
	m_topDude->transform.Rotate(m_bonusSpin * -50 + 45 * dt + 30 * sin(time) * dt + SpinAmount);

	// Keep tip in rational range
	if (tipT.GetPosition().lengthSquared() > 12000)
		tipT.SetPosition(tipT.GetPosition().normalized() * 109);

	// Keep top in opposite direction of tip
	m_baseTargetPos = -tipT.GetPosition();
	m_top->transform.Move((m_baseTargetPos - m_top->transform.GetPosition()) * dt * 3);

	m_topShadow->transform.SetPosition(m_top->transform.GetPosition() * 0.90);
	m_topDude->transform.SetPosition(m_top->transform.GetPosition() * 1.05);


	//float rotation = dt * (tipPos.length() + 100);
	//m_map->transform.Rotate(rotation);
	//tipT.SetPosition(pmath::Mat2::createRotation(-rotation) * tipT.GetPosition());


	Globals::PLAYER_POS = pmath::Vec2i(PlayerPos);
	Globals::PLAYER_TIP = pmath::Vec2i(PlayerPos + tipT.GetPosition());

	m_map->transform.SetOrigin(Globals::PLAYER_POS);

	//check if outside max/min coordinated
	if (Globals::PLAYER_POS.x > Globals::PLAYER_MAX.x)
		Globals::PLAYER_MAX.x = Globals::PLAYER_POS.x;
	else if (Globals::PLAYER_POS.x < Globals::PLAYER_MIN.x)
		Globals::PLAYER_MIN.x = Globals::PLAYER_POS.x;

	if (Globals::PLAYER_POS.y > Globals::PLAYER_MAX.y)
		Globals::PLAYER_MAX.y = Globals::PLAYER_POS.y;
	else if (Globals::PLAYER_POS.y < Globals::PLAYER_MIN.y)
		Globals::PLAYER_MIN.y = Globals::PLAYER_POS.y;
}

void Player::defaults()
{
	const float dif = Globals::DIFFICULTY;
	const float difSqrt = sqrt(dif);

	m_tipRandomMovementMultiplier = 1;
	m_spinMultiplier = 9;
	m_spinPow = 0.45f;
	m_bonusSpin = 0;
	m_speed = 3;
	m_speedMultiplier = 0.5;
}

void Player::onCollision(int cloudType){
	switch (cloudType)
	{
	case 0: //Strawberry
		m_speedMultiplier = 1;
		break;
	case 1: //Plum
		m_tipRandomMovementMultiplier = 4;
		break;
	case 2: //Game
		break;
	case 3: //Blueberry
		m_tip->transform.SetPosition(pmath::Mat2::createRotation(rand()) * m_tip->transform.GetPosition());
		break;
	case 4: //Spinach
		m_bonusSpin = 10;
		break;
	default:
		break;
	}
}
