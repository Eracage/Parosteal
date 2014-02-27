#pragma once
#ifndef COMPONENT_H_UTH
#define COMPONENT_H_UTH

#include <string>
#include <UtH/Core/Shader.hpp>

namespace uth
{
	class GameObject;

	class Component
	{
	public:

		Component(const std::string name); // Should be unique(per gameobject)
		virtual ~Component();

		void SetActive(bool active);
		bool GetActive();

		void SetDrawable(bool drawable);
		bool GetDrawable();

		void SetDynamic(bool dynamic);
		bool GetDynamic();

		void SetName(const std::string name);
		const std::string GetName() const;

		virtual void Draw(Shader* shader){};
		virtual void Update(float dt){};

		GameObject* parent;

	protected:
		Component();

	private:
		std::string m_name;

		bool m_active;
		bool m_draw;
		bool m_dynamic; // false = static
		
	};
}
#endif