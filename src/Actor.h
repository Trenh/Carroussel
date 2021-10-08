#pragma once
#include <vector>

class Game;
class Component;

class Actor
{
public:
	Actor(char* nameP);
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	void setName			(char* nameP);
	void setWorldPosition	(float* pos);
	void setWorldPosition	(float x, float y, float z);
	void setWorldRotation	(float* rot);
	void setWorldRotation	(float x, float y, float z);
	void setWorldScale		(float* scl);
	void setWorldScale		(float x, float y, float z);

	char*	getName()			{ return name;				}
	float*	getWorldPosition()	{ return m_WorldPosition;	}
	float*	getWorldRotation()	{ return m_WorldRotation;	}
	float*	getWorldScale()		{ return m_WorldScale;		}

	void		addComponent	(Component* component);
	void		removeComponent	(Component* component);
	Component*	searchComponent	(char* componentName);

	bool isTheActor(char* nameP);

	virtual void	init();
	virtual void	update();
	void			destroy();

private:
	Game&					game;
	char					name[20];
	std::vector<Component*> components;
	float					m_WorldPosition[3]		= { 0, 0, 0 };
	float					m_WorldScale[3]			= { 1, 1, 1 };
	float					m_WorldRotation[3]		= { 0, 0, 0 }; // angle in degrees
};

