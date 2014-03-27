#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Camera.hpp>

using namespace uth;

GameObject::GameObject()
{
	transform.parent = this;
}

GameObject::~GameObject()
{
	RemoveComponents();
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
	component->parent = this;
}

Component* GameObject::GetComponent(const std::string& name)
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		if (components.at(i)->GetName() == name)
		{
			return components.at(i);
		}
	}

	return nullptr;
}

void GameObject::RemoveComponent(Component* component)
{
	for(size_t i = 0; i < components.size(); ++i)
	{
		if(components.at(i) == component)
		{
			delete components.at(i);
			components.erase(components.begin() + i);
		}
	}
}

void GameObject::RemoveComponent(const std::string& name)
{
	for(size_t i = 0; i < components.size(); ++i)
	{
		if(components.at(i)->GetName() == name)
		{
			delete components.at(i);
			components.erase(components.begin() + i);
		}
	}
}

void GameObject::RemoveComponents()
{
	for(size_t i = 0; i < components.size(); ++i)
			delete components.at(i);

	components.clear();
}

void GameObject::Draw(Shader* shader, Camera* camera)
{
	shader->Use();
	shader->SetUniform("unifModel", transform.GetTransform());
	shader->SetUniform("unifProjection", camera->GetProjectionTransform());

	for (auto i = components.begin(); i != components.end(); ++i)
	{
		shader->Use();
		auto component = (*i);
		if (component->IsActive())
			component->Draw(shader, camera);
	}
}

void GameObject::Update(float dt)
{
	for (auto i = components.begin(); i != components.end(); ++i)
	{
		auto component = (*i);
		if (component->IsActive())
			component->Update(dt);
	}
}