#pragma once
#include <math.h>;
#include <vector>;
#include "RigidBody.h";
#include "CImg.h"

enum GameObjectShape { circle, polygon };
extern float GRAVITY_ACC;
extern double DELTA_TIME;

class Shape {
public:
	Shape();
	Shape(float radius);
	Shape(std::vector<float> vertices);

	GameObjectShape shapeType = GameObjectShape::circle;
	float radius = 0;
	std::vector<float> vertices = { 0 };
};

class GameObject {
public:
	GameObject();
	GameObject(Shape* shape);
	GameObject(Shape* shape, int color[3]);
	GameObject(Shape* shape, int color[3], bool kinematic);
	GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity);
	GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity, float gravityScale);
	GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity, float gravityScale, RigidBody* rigidbody);
	GameObject(Shape* shape, RigidBody* rigidbody, bool kinematic);

	Shape *shape;
	unsigned char color[3] = { 255,255,255 };
	bool isKinematic = false;
	bool respectGravity = true;
	float gravityScale = 1;

	RigidBody *rigidbody = new RigidBody();

	virtual void Draw(cimg_library_suffixed::CImg<unsigned char> &canvas);
	virtual void Update() {};
	virtual void UpdateRigidBody();
};