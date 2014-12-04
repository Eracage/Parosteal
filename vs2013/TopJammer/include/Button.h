#ifndef BUTTON_H
#define BUTTON_H

#include <UtH\Engine\GameObject.hpp>
#include <functional>

class Button : public uth::GameObject
{
private:
	typedef std::function<void()> onClick;
	onClick clickFunction;
	GameObject* spriteEdges;
	GameObject* spriteMiddle;
	GameObject* buttonText;
public:
	Button(pmath::Vec2 position, pmath::Vec2 size, std::string text, onClick func);
	~Button();
	void update(float)override;
};
#endif
