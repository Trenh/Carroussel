#include "Actor.h"
#include "Component.h"
#include "Game.h"

Actor::Actor(char* nameP) :
	game(Game::instance())
{
	game.addActor(this);
	setName(nameP);
}

Actor::~Actor() {
	destroy();
}

void Actor::setName(char* nameP)
{
	for (int i = 0; i < sizeof(name) / sizeof(char); i++) {
		name[i] = nameP[i];
		if (nameP[i] == '\0') {
			break;
		}
	}
}

void Actor::setWorldPosition(float* pos) {
	for (int i = 0; i < sizeof(m_WorldPosition) / sizeof(float); i++) {
		m_WorldPosition[i] = pos[i];
	}
}

void Actor::setWorldPosition(float x, float y, float z) {
	m_WorldPosition[0] = x;
	m_WorldPosition[1] = y;
	m_WorldPosition[2] = z;
}

void Actor::setWorldRotation(float* rot) {
	for (int i = 0; i < sizeof(m_WorldRotation) / sizeof(float); i++) {
		m_WorldRotation[i] = rot[i];
	}
}

void Actor::setWorldRotation(float x, float y, float z) {
	m_WorldRotation[0] = x;
	m_WorldRotation[1] = y;
	m_WorldRotation[2] = z;
}

void Actor::setWorldScale(float* scl) {
	for (int i = 0; i < sizeof(m_WorldScale) / sizeof(float); i++) {
		m_WorldScale[i] = scl[i];
	}
}

void Actor::setWorldScale(float x, float y, float z) {
	m_WorldScale[0] = x;
	m_WorldScale[1] = y;
	m_WorldScale[2] = z;
}

void Actor::init() {
	for (auto c : components) {
		c->init();
	}
}

void Actor::update() {
	for (auto c : components) {
		c->update();
	}
}

void Actor::destroy() {
	components.clear();
}

void Actor::addComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}

Component* Actor::searchComponent(char* componentName)
{
	for (auto c : components) {
		if (c->isTheComponent(componentName)) { 
			return c;
		}
	}
	return nullptr;
}

bool Actor::isTheActor(char* nameP)
{
	for (int i = 0; i < sizeof(name) / sizeof(char); ++i) {
		if (name[i] != nameP[i]) { return false; }
		if (name[i] == '\0' && nameP[i] != '\0') { return false; }
		if (name[i] != '\0' && nameP[i] == '\0') { return false; }
		if (name[i] == '\0' && nameP[i] == '\0') { break; }
	}
	return true;
}
