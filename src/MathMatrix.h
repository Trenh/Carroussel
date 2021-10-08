#pragma once
#include <math.h>
#include "Quaternion.h"

namespace mathMatrix
{
	inline void translate(float* matrix, float x, float y, float z) {
		matrix[12] = x;
		matrix[13] = y;
		matrix[14] = z;
		matrix[15] = 1.0;
	}

	inline void scale(float* matrix, float sx, float sy, float sz) {
		matrix[0] = matrix[0] * sx;
		matrix[1] = matrix[1] * sx;
		matrix[2] = matrix[2] * sx;
		matrix[3] = 0;

		matrix[4] = matrix[4] * sy;
		matrix[5] = matrix[5] * sy;
		matrix[6] = matrix[6] * sy;
		matrix[7] = 0;

		matrix[8] = matrix[8] * sz;
		matrix[9] = matrix[9] * sz;
		matrix[10] = matrix[10] * sz;
		matrix[11] = 0;

		matrix[15] = 1.0;
	}

	inline void rotate(float* matrix, float rx, float ry, float rz) {
		const float sx = sin(rx);
		const float cx = cos(rx);
		const float sy = sin(ry);
		const float cy = cos(ry);
		const float sz = sin(rz);
		const float cz = cos(rz);

		matrix[0] = cy * cz;
		matrix[1] = -cy * sz;
		matrix[2] = sy;

		matrix[4] = cz * sx * sy + cx * sz;
		matrix[5] = cx * cz - sx * sy * sz;
		matrix[6] = -cy * sx;

		matrix[8] = -cx * cz * sy + sx * sz;
		matrix[9] = cz * sx + cx * sy * sz;
		matrix[10] = cx * cy;

		matrix[15] = 1.0;
	}

	inline void createFromQuaternion(float* matrix, const Quaternion& q) {
		matrix[0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
		matrix[1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
		matrix[2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
		matrix[3] = 0.0f;

		matrix[4] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
		matrix[5] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
		matrix[6] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
		matrix[7] = 0.0f;

		matrix[8] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
		matrix[9] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		matrix[10] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
		matrix[11] = 0.0f;

		matrix[12] = 0.0f;
		matrix[13] = 0.0f;
		matrix[14] = 0.0f;
		matrix[15] = 1.0f;
	}
	
	inline float* calculPositionWithCenterRotationAndRayon(float* centerP, float* rotationP, float* rayonP) {
		float PositionX = rayonP[0];
		float PositionY = rayonP[1];
		float PositionZ = rayonP[2];

		float worldRotationX = Maths::toRadians(rotationP[0]);
		float worldRotationY = Maths::toRadians(rotationP[1]);
		float worldRotationZ = Maths::toRadians(rotationP[2]);

		float positionY = PositionY * Maths::cos(worldRotationX) - PositionZ * Maths::sin(worldRotationX);
		float positionZ = PositionZ * Maths::cos(worldRotationX) + PositionY * Maths::sin(worldRotationX);
		float positionX = PositionX * Maths::cos(worldRotationY) + positionZ * Maths::sin(worldRotationY);
		positionZ = positionZ * Maths::cos(worldRotationY) - PositionX * Maths::sin(worldRotationY);

		float tempPosX = positionX;
		float tempPosY = positionY;

		positionX = tempPosX * Maths::cos(worldRotationZ) - tempPosY * Maths::sin(worldRotationZ);
		positionY = tempPosY * Maths::cos(worldRotationZ) + tempPosX * Maths::sin(worldRotationZ);

		positionX += centerP[0];
		positionY += centerP[1];
		positionZ += centerP[2];

		float position[3] = {positionX, positionY, positionZ };
		return position;
	}
}
