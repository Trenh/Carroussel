#pragma once
#include "bgfx/bgfx.h"
#include "Actor.h"
#include "Quaternion.h"

class Component
{
public:
	Component(Actor* ownerP, char* nameP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	virtual void init()		{ isInit = true;		}
	virtual void update()	{ computeTransform();	}
	virtual void destroy();

	void setName	(char* nameP);
	void setPosition(float* pos);
	void setPosition(float x, float y, float z);
	void setScale	(float* scl);
	void setScale	(float x, float y, float z);
	void setRotation(float* rot);
	void setRotation(float x, float y, float z);

	char*	getName()				{ return name;			}
	float*	getPosition()			{ return m_position;	}
	float*	getScale()				{ return m_scale;		}
	float*	getRotation()			{ return m_rotation;	}
	int		getUpdateOrder() const	{ return updateOrder;	}

	bool isTheComponent(char* nameP);

protected:
	Actor&						owner;
	int							updateOrder;
	bgfx::VertexBufferHandle	m_vbh;
	bgfx::IndexBufferHandle		m_ibh;
	bgfx::ProgramHandle			m_program;
	float						m_matrix[16];

private:
	void computeTransform();

	char		name[20];
	float		m_position[3] = { 0, 0, 0 };
	float		m_scale[3] =	{ 1, 1, 1 };
	float		m_rotation[3] = { 0, 0, 0 }; // angle in degrees
	Quaternion	m_rotation_by_quaternion;
	bool		isInit = false;
};