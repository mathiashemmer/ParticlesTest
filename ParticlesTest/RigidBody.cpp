#include "RigidBody.h"

RigidBody::RigidBody(){
	this->Reset();
}

RigidBody::RigidBody(float x, float y){
	this->Reset();
	this->position = Vector2(x, y);
}

RigidBody::RigidBody(float x, float y, float mass){
	this->Reset();
	this->position = Vector2(x, y);
	this->mass = mass;
}

RigidBody::RigidBody(float x, float y, float mass, float restitution){
	this->Reset();
	this->position = Vector2(x, y);
	this->mass = mass;
	this->restitution = restitution;
}

RigidBody::RigidBody(float x, float y, float mass, float restitution, float rotation){
	this->Reset();
	this->position = Vector2(x, y);
	this->mass = mass;
	this->restitution = restitution;
	this->rotation = rotation;
}

void RigidBody::Reset(){
	this->position = Vector2(0, 0);
	this->velocity = Vector2(0, 0);
	this->mass = 1;
	this->restitution = 1;
	this->angularVelocity = 0;
	this->rotation = 0;
}

void RigidBody::Stall(){
	this->velocity = Vector2(0, 0);
	this->angularVelocity = 0;
}
