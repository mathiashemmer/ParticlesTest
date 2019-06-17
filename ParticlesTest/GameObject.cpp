#include "GameObject.h"

GameObject::GameObject(){}

GameObject::GameObject(Shape* shape){
	this->shape = shape;
}

GameObject::GameObject(Shape* shape, int color[3]){
	this->shape = shape;
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
}

GameObject::GameObject(Shape* shape, int color[3], bool kinematic){
	this->shape = shape;
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
	this->isKinematic = kinematic;
}

GameObject::GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity){
	this->shape = shape;
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
	this->isKinematic = kinematic;
	this->respectGravity = respecGravity;
}

GameObject::GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity, float gravityScale){
	this->shape = shape;
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
	this->isKinematic = kinematic;
	this->respectGravity = respecGravity;
	this->gravityScale = gravityScale;
}

GameObject::GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity, float gravityScale, RigidBody* rigidbody){
	this->shape = shape;
	this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2];
	this->isKinematic = kinematic;
	this->respectGravity = respecGravity;
	this->gravityScale = gravityScale;
	this->rigidbody = rigidbody;
}

GameObject::GameObject(Shape* shape, RigidBody* rigidbody, bool kinematic){
	this->shape = shape;
	this->rigidbody = rigidbody;
	this->isKinematic = kinematic;
}

void GameObject::Draw(cimg_library_suffixed::CImg<unsigned char>& canvas){
	if (this->shape->shapeType == GameObjectShape::circle) {
		canvas.draw_circle(this->rigidbody->position.x, this->rigidbody->position.y, this->shape->radius, this->color, 1);
	}
}

void GameObject::UpdateRigidBody(){
	this->rigidbody->position += this->rigidbody->velocity;
	if (this->respectGravity)
		this->rigidbody->velocity += Vector2(0, gravityScale * 9.81) * (1.0f/60.0f) * this->rigidbody->mass;

	if (this->rigidbody->position.y >= 720) {
		this->rigidbody->velocity.y *= -1;
		this->rigidbody->position.y -= 2;
	}
		

	if(this->rigidbody->position.x <= 0 || this->rigidbody->position.x >= 1280)
		this->rigidbody->velocity.x *= -1;
}

Shape::Shape() {}

Shape::Shape(float radius){
	this->shapeType = GameObjectShape::circle;
	this->radius = radius;
}

Shape::Shape(std::vector<float> vertices){
	this->shapeType = GameObjectShape::polygon;
	this->vertices = vertices;
}
