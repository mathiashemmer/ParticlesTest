#pragma once
#include "Vector2.h"

class RigidBody {

public:
	Vector2 position;
	float rotation;
	Vector2 velocity;
	float angularVelocity;

	float mass;					
	float restitution;		// "Boucyness" coeficient -> Determines how much distortion the object suffers on colision.

	RigidBody();
	RigidBody(float x, float y);
	RigidBody(float x, float y, float mass);
	RigidBody(float x, float y, float mass, float restitution);
	RigidBody(float x, float y, float mass, float restitution, float rotation);

	void Reset();
	void Stall();

};
