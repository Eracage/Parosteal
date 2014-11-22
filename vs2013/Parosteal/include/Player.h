#include <UtH/UtHEngine.hpp>


class Player : public uth::GameObject
{
public:
	Player();
	void update(float dt) override;

	pmath::Vec2 PlayerPos;
private:
	GameObject* m_top;
	GameObject* m_tip;


	float m_movementMultiplier;
	pmath::Vec2 m_baseTargetPos;

	float m_spinMultiplier;
};
