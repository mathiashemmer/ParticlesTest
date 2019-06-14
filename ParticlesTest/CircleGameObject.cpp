#include "CircleGameObject.h"


CircleGameObject::CircleGameObject(){
	this->gameObjectShape = GameObjectShape::circle;
	this->radius = 1;
}

CircleGameObject::CircleGameObject(float radius){
	this->gameObjectShape = GameObjectShape::circle;
	this->radius = radius;
}

CircleGameObject::CircleGameObject(float radius, float x, float y){
	this->gameObjectShape = GameObjectShape::circle;
	this->radius = radius;
	this->rigidbody->position = Vector2(x, y);
}

CircleGameObject::CircleGameObject(float radius, float x, float y, unsigned char color[3]){
	this->gameObjectShape = GameObjectShape::circle;
	this->radius = radius;
	this->rigidbody->position = Vector2(x, y);
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
}

CircleGameObject::CircleGameObject(float radius, float x, float y, unsigned char color[3], float mass){
	this->gameObjectShape = GameObjectShape::circle;
	this->radius = radius;
	this->rigidbody->position = Vector2(x, y);
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
	this->rigidbody->mass = mass;
}

CircleGameObject::CircleGameObject(float radius, float x, float y, unsigned char color[3], float mass, float restitution){
	this->gameObjectShape = GameObjectShape::circle;
	this->radius = radius;
	this->rigidbody->position = Vector2(x, y);
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
	this->rigidbody->mass = mass;
	this->rigidbody->restitution = restitution;
}

CircleGameObject::CircleGameObject(float radius, float x, float y, float rotation, unsigned char color[3], float mass, float restitution) {
	this->gameObjectShape = GameObjectShape::circle;
	this->radius = radius;
	this->rigidbody->position = Vector2(x, y);
	this->rigidbody->rotation = rotation;
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
	this->rigidbody->mass = mass;
	this->rigidbody->restitution = restitution;
}

void CircleGameObject::Draw(cimg_library_suffixed::CImg<unsigned char>& canvas){
	canvas.draw_circle(this->rigidbody->position.x, this->rigidbody->position.y, this->radius, this->color);
}

void CircleGameObject::Update(){
}

void CircleGameObject::UpdateRigidBody(){
	if(!isKinematic)
		this->rigidbody->position += this->rigidbody->velocity * (float)DELTA_TIME;
	if (respectGravity)
		this->rigidbody->velocity.y += GRAVITY_ACC * DELTA_TIME;

	if (this->rigidbody->position.y + this->radius > 715) {
		this->rigidbody->velocity.y = 0;
	}
}
