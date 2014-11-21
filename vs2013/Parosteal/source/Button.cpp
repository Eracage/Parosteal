#include <Button.h>
#include <MenuScene.hpp>
#include <Scenes.hpp>

using namespace uth;

Button::Button(pmath::Vec2 position, pmath::Vec2 size, std::string text, onClick func)
{
	transform.SetPosition(position);
	transform.setSize(size);
	clickFunction = func;

	//create sprite
	AddChild(spriteEdges = new GameObject());
	spriteEdges->AddTags({"Button", "Sprite", "Edges"});
	spriteEdges->AddComponent(new Sprite(pmath::Vec4(0.1, 0.5, 0.1, 1), pmath::Vec2(512, 64)));

	AddChild(spriteMiddle = new GameObject());
	spriteMiddle->AddTags({ "Button", "Sprite", "Middle" });
	spriteMiddle->AddComponent(new Sprite(pmath::Vec4(0, 1, 0, 1), pmath::Vec2(502, 54)));

	//buttonText->AddTags({ "Button", "Text" });
	//buttonText->AddComponent();
}

void Button::update(float)
{
	if (uthInput.Mouse.IsButtonReleased(uth::Mouse::LEFT))
	{
		pmath::Vec2 mousePosition = uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position());
		if (transform.GetGlobalBounds().contains(mousePosition))
		{
			clickFunction();
		}
	}
}

Button::~Button()
{
}
