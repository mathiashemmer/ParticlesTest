#pragma once
#include <math.h>;
#include "RigidBody.h";
#include "CImg.h"

enum GameObjectShape { circle, polygon };

class GameObject {
public:
	GameObjectShape gameObjectShape;
	unsigned char color[3];
	bool isKinematic = false;
	bool respectGravity = true;

	RigidBody *rigidbody = new RigidBody();

	virtual void Draw(cimg_library_suffixed::CImg<unsigned char> &canvas)=0;
	virtual void Update()=0;
	virtual void UpdateRigidBody()=0;
};