#pragma once
#include <UtH\UtHEngine.hpp>

template<typename T>

class UpdatingText :
	public uth::Text
{
private:
	std::vector<uth::Texture*> textures;
	float size;
	T& obj;
	std::string textBefore;
	std::string textAfter;
public:
	UpdatingText(const std::string& textBefore, T& updateObject, const std::string& textAfter = "", const std::string& fontPath = "8bitoperator.ttf", const int fontSize = 32)
		: uth::Text("8bitoperator.ttf",fontSize),
		obj(updateObject),
		textBefore(textBefore),
		textAfter(textAfter)
	{
		std::ostringstream os;
		os << textBefore << obj << textAfter;
		SetText(os.str());
	}

	void Update(float) override
	{
		std::ostringstream os;
		os << textBefore << obj << textAfter;
		SetText(os.str());
		parent->transform.SetOrigin(7);
	}
};

