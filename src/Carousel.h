#pragma once
#include "Actor.h"

class Carousel : public Actor
{
public:
	Carousel(char* nameP);
	virtual ~Carousel();
	Carousel(const Actor&) = delete;
	Carousel& operator=(const Carousel&) = delete;

	void init()		override;
	void update()	override;
};

