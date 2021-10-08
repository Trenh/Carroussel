#pragma once
#include "EngineUtils.h"
#include "Window.h"
#include <vector>
#include "Actor.h"

struct MouseButton
{
	enum Enum
	{
		None,
		Left,
		Middle,
		Right,

		Count
	};
};

struct MouseState
{
	MouseState()
		: m_mx(0)
		, m_my(0)
		, m_mz(0)
	{
		for (uint32_t ii = 0; ii < MouseButton::Count; ++ii)
		{
			m_buttons[ii] = MouseButton::None;
		}
	}

	int32_t m_mx;
	int32_t m_my;
	int32_t m_mz;
	uint8_t m_buttons[MouseButton::Count];
};

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() {}
public:

	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void	addActor(Actor* actor);
	void	removeActor(Actor* actor);
	Actor*	searchActor(char* actorName);

private:
	Window window;
	MouseState mouseState;

	std::vector<Actor*> actors;
	std::vector<Actor*> pendingActors;
};

