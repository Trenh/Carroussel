#include "Carousel.h"
#include "Cube.h"
#include "Maths.h"
#include "MathMatrix.h"
#include "Timer.h"

Carousel::Carousel(char* nameP) :
	Actor(nameP)
{}

Carousel::~Carousel() {}

void Carousel::init()
{
	Cube* base1 = new Cube(this, "base1");
	base1->setScale(5.0f, 0.1f, 0.5f);
	base1->setPosition(5.0f, 0.0f, 0.0f);

	Cube* base2 = new Cube(this, "base2");
	base2->setScale(4.0f, 0.05f, 0.5f);
	base2->setRotation(0.0f, 90, 0.0f);
	base2->setPosition(6.0f, 0.0f, 0.0f);

	Cube* arm1 = new Cube(this, "Arm1");
	arm1->setScale(2.0f, 0.1f, 0.5f);
	arm1->setPosition(6.0f, 0.1f, 3.5f);

	Cube* arm2 = new Cube(this, "Arm2");
	arm2->setScale(2.0f, 0.1f, 0.5f);
	arm2->setPosition(6.0f, 0.1f, -3.5);

	Cube* arm3 = new Cube(this, "Arm3");
	arm3->setScale(2.0f, 0.1f, 0.5f);
	arm3->setPosition(9.0f, 0.1f, 0.0f);

	Cube* tasse1 = new Cube(this, "tasse1");
	tasse1->setScale(0.5f, 0.5f, 0.5f);
	tasse1->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tasse2 = new Cube(this, "tasse2");
	tasse2->setScale(0.5f, 0.5f, 0.5f);
	tasse2->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tasse3 = new Cube(this, "tasse3");
	tasse3->setScale(0.5f, 0.5f, 0.5f);
	tasse3->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tasse4 = new Cube(this, "tasse4");
	tasse4->setScale(0.8f, 0.3f, 0.5f);
	tasse4->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tasse5 = new Cube(this, "tasse5");
	tasse5->setScale(0.5f, 0.5f, 0.5f);
	tasse5->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tasse6 = new Cube(this, "tasse6");
	tasse6->setScale(0.5f, 0.5f, 0.5f);
	tasse6->setPosition(0.0f, 0.7f, 0.0f);

	Actor::init(); // Imperatively after the creation of the component
}

void Carousel::update()
{
	float rayon[3] = { 1.5f, 0.0f, 0.0f };
	float rayonInv[3] = { -1.5f, 0.0f, 0.0f };
	float time = Timer::getTime();

	Component* arm1 = searchComponent("Arm1");

	arm1->setRotation(0, time * 45, 0);

	Component* arm2 = searchComponent("Arm2");

	arm2->setRotation(0, time *- 45, 0);

	Component* arm3 = searchComponent("Arm3");

	arm3->setRotation(time*0, time * 90,time* 0);

	Component* tasse1 = searchComponent("tasse1");

	float* armPosition = arm1->getPosition();
	float* armRotation = arm1->getRotation();

	float* calculPositiontasse = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition, armRotation, rayon);

	tasse1->setRotation(0, -time * 45 * 2, 0);
	tasse1->setPosition(calculPositiontasse[0], tasse1->getPosition()[1], calculPositiontasse[2]);

	Component* tasse2 = searchComponent("tasse2");

	float* calculPositiontasse2 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition, armRotation, rayonInv);

	tasse2->setRotation(0, -time * 45 * 2, 0);
	tasse2->setPosition(calculPositiontasse2[0], tasse2->getPosition()[1], calculPositiontasse2[2]);

	Component* tasse3 = searchComponent("tasse3");

	float* armPosition2 = arm2->getPosition();
	float* armRotation2 = arm2->getRotation();

	float* calculPositiontasse3 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition2, armRotation2, rayon);

	tasse3->setRotation(0, -time * 45 * 2, 0);
	tasse3->setPosition(calculPositiontasse[0], tasse3->getPosition()[1], calculPositiontasse[2]);

	Component* tasse4 = searchComponent("tasse4");

	float* calculPositiontasse4 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition2, armRotation2, rayonInv);

	tasse4->setRotation(0, -time * 45 * 2, 0);
	tasse4->setPosition(calculPositiontasse2[0], tasse4->getPosition()[1], calculPositiontasse2[2]);

	Component* tasse5 = searchComponent("tasse5");

	float* armPosition3 = arm3->getPosition();
	float* armRotation3 = arm3->getRotation();

	float* calculPositiontasse5 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition3, armRotation3, rayon);

	tasse5->setRotation(0, 0, -time * 45 * 2);
	tasse5->setPosition(calculPositiontasse[0], tasse5->getPosition()[1], calculPositiontasse[2]);

	Component* tasse6 = searchComponent("tasse6");

	float* calculPositiontasse6 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition3, armRotation3, rayonInv);

	tasse6->setRotation(0, time * 45 * 5, 0);
	tasse6->setPosition(calculPositiontasse2[0], tasse6->getPosition()[1], calculPositiontasse2[2]);

	Actor::update(); // Imperatively after the modification
}
