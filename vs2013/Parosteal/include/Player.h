#ifndef PLAYER_H
#define PLAYER_H

#include <UtH/UtHEngine.hpp>


class Player : public uth::GameObject
{
public:
	Player(Object* map);
	void update(float dt) override;

	void defaults();
	pmath::Vec2 PlayerPos;

	void onCollision(int cloudType);
private:
	GameObject* m_top;
	GameObject* m_topShadow;
	GameObject* m_topDude;
	GameObject* m_tip;

	Object* m_map;

	pmath::Vec2 m_baseTargetPos;

	// Difficulty controls

	float m_tipRandomMovementMultiplier;
	float m_spinMultiplier;
	float m_spinPow;
	float m_bonusSpin;
	float m_speed;
	float m_speedMultiplier;

};

#endif
