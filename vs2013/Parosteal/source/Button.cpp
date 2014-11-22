#include <Button.h>
#include <MenuScene.hpp>
#include <Scenes.hpp>

using namespace uth;

Button::Button(pmath::Vec2 position, pmath::Vec2 size, std::string text, onClick func)
{
	transform.SetPosition(position);
	clickFunction = func;
	transform.setSize(size);

	//create sprite
	AddChild(spriteEdges = new GameObject());
	spriteEdges->AddTags({"Button", "Sprite", "Edges"});
	spriteEdges->AddComponent(new Sprite(pmath::Vec4(0.1, 0.5, 0.1, 1), pmath::Vec2(size.x, size.y)));

	AddChild(spriteMiddle = new GameObject());
	spriteMiddle->AddTags({ "Button", "Sprite", "Middle" });
	spriteMiddle->AddComponent(new Sprite(pmath::Vec4(0, 1, 0, 1), pmath::Vec2(size.x-10, size.y-10)));

	Text* newText;
	AddChild(buttonText = new GameObject());
	buttonText->AddTags({ "Button", "Text" });
	buttonText->AddComponent(newText = new Text("8bitoperator.ttf", size.y - 20));
	newText->SetColor(pmath::Vec4(0, 0, 0.5, 1));
	newText->SetText(text);
	buttonText->transform.SetPosition(0, -4);

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
