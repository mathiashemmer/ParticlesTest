#pragma once
#include <math.h>;
#include <vector>;
#include "RigidBody.h";
#include "CImg.h"

enum GameObjectShape { circle, polygon };

class GameObject {
public:
	GameObject();
	GameObject(Shape* shape);
	GameObject(Shape* shape, int color[3]);
	GameObject(Shape* shape, int color[3], bool kinematic);
	GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity);
	GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity, float gravityScale);
	GameObject(Shape* shape, int color[3], bool kinematic, bool respecGravity, float gravityScale, RigidBody rigidbody);

	Shape *shape;
	unsigned char color[3];
	bool isKinematic = false;
	bool respectGravity = true;
	float GravityScale = 1;

	RigidBody *rigidbody = new RigidBody();

	virtual void Draw(cimg_library_suffixed::CImg<unsigned char> &canvas)=0;
	virtual void Update()=0;
	virtual void UpdateRigidBody()=0;
};

class Shape {
public:
	Shape();
	Shape(GameObjectShape type);
	Shape(GameObjectShape type, float radius);
	Shape(GameObjectShape type, std::vector<float> vertices);

	GameObjectShape shape = GameObjectShape::circle;
	float radius = 1;
	std::vector<float> vertices = { 0 };
};