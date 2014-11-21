#include <UtH/UtHEngine.hpp>


class Player : public uth::GameObject
{
public:
	Player();
	void update(float dt) override;
private:
	GameObject* m_base;
	GameObject* m_tip;
};