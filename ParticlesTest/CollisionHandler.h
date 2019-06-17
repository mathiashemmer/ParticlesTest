#pragma once
#include "GameObject.h"

class Manifold {
public:
	GameObject* A;
	GameObject* B;
	float penetration;
	Vector2 normal;
};

void PositionalCorrection(Manifold* m)
{
	const float percent = 0.8;
	const float slop = 0.01;

	float inverseMassA = (m->A->rigidbody->mass != 0 ? 1 / m->A->rigidbody->mass : 0);
	float inverseMassB = (m->B->rigidbody->mass != 0 ? 1 / m->B->rigidbody->mass : 0);

	Vector2 correction = (std::max(m->penetration - slop, 0.0f) / (inverseMassA + inverseMassB)) * percent * m->normal;
	m->A->rigidbody->position -= inverseMassA * correction;
	m->B->rigidbody->position += inverseMassB * correction;
}

void ResolveCollision(Manifold *m) {
	GameObject* A = m->A;
	GameObject* B = m->B;
	float inverseMassA = (A->rigidbody->mass != 0 ? 1 / A->rigidbody->mass : 0);
	float inverseMassB = (B->rigidbody->mass != 0 ? 1 / B->rigidbody->mass : 0);

	Vector2 relativeVelocity = B->rigidbody->velocity - A->rigidbody->velocity;
	float normalVelocity = Vector2().DotProduct(relativeVelocity, m->normal);

	if (normalVelocity > 0) return;

	float e = std::min(A->rigidbody->restitution, B->rigidbody->restitution);
	float j = -(1 + e) * normalVelocity;
	j /= (inverseMassA + inverseMassB) != 0 ? (inverseMassA + inverseMassB) : 0;

	Vector2 impulse = m->normal * j;
	
	if(inverseMassA != 0 && !A->isKinematic)
		A->rigidbody->velocity -= inverseMassA * impulse;
	if (inverseMassB != 0 && !B->isKinematic)
		B->rigidbody->velocity += inverseMassB * impulse;

	PositionalCorrection(m);
}

bool CircleVsCricle(Manifold* m) {
	GameObject* A = m->A;
	GameObject* B = m->B;

	Vector2 direction = B->rigidbody->position - A->rigidbody->position;
	float totalRadius = A->shape->radius + B->shape->radius;
	float totalRadiusSquared = totalRadius * totalRadius;
	
	float lensqr = direction.LenghtSquared();
	if (lensqr > totalRadiusSquared) return false;

	float directionLenght = direction.Lenght();

	if (directionLenght != 0) {
		m->penetration = totalRadius - directionLenght;
		m->normal = direction.Normalized();					
	}
	else {
		m->penetration = A->shape->radius;
		m->normal = Vector2(1, 0);
	}
	return true;
}

bool DetectColision(Manifold *m) {
	if (m->A->shape->shapeType == GameObjectShape::circle && m->B->shape->shapeType == GameObjectShape::circle)
		if (CircleVsCricle(m))
			ResolveCollision(m);
	return false;
}