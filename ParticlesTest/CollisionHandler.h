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

	if(inverseMassA != 0 && !A->isKinematic)
		A->rigidbody->velocity -= inverseMassA * impulse;
	if (inverseMassB != 0 && !B->isKinematic)
		B->rigidbody->velocity += inverseMassB * impulse;
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
		m->penetration = totalRadiusSquared - directionLenght;
		m->normal = direction.Normalized();					
	}
	else {
		m->penetration = A->radius;
		m->normal = Vector2(0, 1);
	}

	return true;
}