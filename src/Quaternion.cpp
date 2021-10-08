#include "Quaternion.h"

const Quaternion Quaternion::identity(0, 0, 0, 1);


Quaternion::Quaternion(float xP, float yP, float zP, float wP) {
	set(xP, yP, zP, wP);
}

Quaternion::Quaternion(const float* axis, float angle)
{
	float scalar = Maths::sin(angle / 2.0f);
	x = axis[0] * scalar;
	y = axis[1] * scalar;
	z = axis[2] * scalar;
	w = Maths::cos(angle / 2.0f);
}

void Quaternion::set(float inX, float inY, float inZ, float inW) {
	x = inX;
	y = inY;
	z = inZ;
	w = inW;
}

void Quaternion::conjugate() {
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}

void Quaternion::normalize() {
	float len = length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}