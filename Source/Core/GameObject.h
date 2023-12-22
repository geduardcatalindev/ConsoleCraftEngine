#pragma once
#include "../Core.h"
#include "../CoreStructs/Transform.h"
#include <vector>
#include "Component/Component.h"

class GE_API GameObject
{
public:
	GameObject(std::string name, class Scene& scene) : name(name), scene(scene){};
	virtual ~GameObject() 
	{
		for (auto& component : components)
		{
			delete component;
		}
		components.clear();
	}
	std::string name;
	std::vector<std::vector<int>> sprite;

	Transform transform = Transform();
	void Destroy()
	{
		isDestroyedFlag = true;
	}
	int GetWidth() const 
	{ 
		return sprite[0].size(); 
	}
	int GetHeight() const 
	{ 
		return sprite[1].size(); 
	}
	void AddComponent(Component* component)
	{
		components.push_back(component);
	}

	template <typename T>
	T* GetComponent()
	{
		for (auto& component : components)
		{
			
			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr; 
	}

	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	virtual void OnCollided(const GameObject& other) {};
	
	void InitComponents()
	{
		for (auto& component : components)
		{
			component->Init();
		}
	}
	void UpdateComponents(float deltaTime)
	{
		for (auto& component:components)
		{
			component->Update(deltaTime);
		}
	}
	std::string symbol = " ";

	bool isDestroyedFlag = false;
	bool hasClearedFromScreen = false;
	Scene& GetCurrentScene()
	{
		return scene;
	}
protected:
	std::vector<Component*> components;
	Scene& scene;
};