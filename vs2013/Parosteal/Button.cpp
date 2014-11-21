#include "Button.h"
#include "MenuScene.hpp"
#include "Scenes.hpp"

Button::Button(pmath::Vec2 position, pmath::Vec2 size, std::string text, onClick func)
{
	transform.SetPosition(position);
	transform.SetSize(size);
	clickFunction = func;
}

void Button::update(float)
{
	if (uthInput.Mouse.IsButtonReleased(uth::Mouse::LEFT))
	{
		pmath::Vec2 mousePosition = uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position());
		
	}
}

Button::~Button()
{
}
