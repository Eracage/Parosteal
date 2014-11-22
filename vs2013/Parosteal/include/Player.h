#include <UtH/UtHEngine.hpp>


class Player : public uth::GameObject
{
public:
	Player(Object* map);
	void update(float dt) override;

	void setDifficulty();
	pmath::Vec2 PlayerPos;
private:
	GameObject* m_top;
	GameObject* m_tip;

	Object* m_map;

	pmath::Vec2 m_baseTargetPos;

	// Difficulty controls

	float m_tipRandomMovementMultiplier;
	float m_spinMultiplier;
	float m_spinPow;
	float m_speed;
	float m_speedMultiplier;


};
