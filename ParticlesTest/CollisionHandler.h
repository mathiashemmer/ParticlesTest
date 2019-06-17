#pragma once
#include "GameObject.h"
#include "CircleGameObject.h"

class Manifold {
public:
	GameObject* A;
	GameObject* B;
	float penetration;
	Vector2 normal;
};

void PositionalCorrection(Manifold m)
{
	const float percent = 0.8; // usually 20% to 80%
	const float slop = 0.01; // usually 0.01 to 0.1

	float inverseMassA = (m.A->rigidbody->mass != 0 ? 1 / m.A->rigidbody->mass : 0);
	float inverseMassB = (m.B->rigidbody->mass != 0 ? 1 / m.B->rigidbody->mass : 0);

	Vector2 correction = (std::max(m.penetration - slop, 0.0f) / (inverseMassA + inverseMassB)) * percent * m.normal;
	m.A->rigidbody->position -= inverseMassA * correction;
	m.B->rigidbody->position += inverseMassB * correction;
}

void ResolveCollision(Manifold manifold) {
	GameObject* A = manifold.A;
	GameObject* B = manifold.B;
	float inverseMassA = (A->rigidbody->mass != 0 ? 1 / A->rigidbody->mass : 0);
	float inverseMassB = (B->rigidbody->mass != 0 ? 1 / B->rigidbody->mass : 0);

	Vector2 relativeVelocity = B->rigidbody->velocity - A->rigidbody->velocity;
	float normalVelocity = Vector2().DotProduct(relativeVelocity, manifold.normal);

	if (normalVelocity > 0) return;

	float e = std::min(A->rigidbody->restitution, B->rigidbody->restitution);
	float j = -(1 + e) * normalVelocity;
	j /= (inverseMassA + inverseMassB) != 0 ? (inverseMassA + inverseMassB) : 0;

	Vector2 impulse = manifold.normal * j;
<<<<<<< HEAD
	
	if (inverseMassA != 0) 
=======

	if(inverseMassA != 0 && !A->isKinematic)
>>>>>>> ControlableRigidbody
		A->rigidbody->velocity -= inverseMassA * impulse;
	if (inverseMassB != 0 && !B->isKinematic)
		B->rigidbody->velocity += inverseMassB * impulse;

	PositionalCorrection(manifold);
}

bool CircleVsCricle(Manifold *m) {
	CircleGameObject* A = (CircleGameObject*)m->A;
	CircleGameObject* B = (CircleGameObject*)m->B;

	Vector2 direction = B->rigidbody->position - A->rigidbody->position;
	float totalRadius = A->radius + B->radius;
	float totalRadiusSquared = totalRadius * totalRadius;
	
	float lensqr = direction.LenghtSquared();
	if (lensqr > totalRadiusSquared) return false;

	float directionLenght = direction.Lenght();

	if (directionLenght != 0) {
		m->penetration = totalRadius - directionLenght;
		m->normal = direction.Normalized();					
	}
	else {
		m->penetration = A->radius;
		m->normal = Vector2(1, 0);
	}

	return true;
}

void AABBvsAABB(Manifold manifold) {

}