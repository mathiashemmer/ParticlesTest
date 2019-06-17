#pragma once
#include "CircleGameObject.h"
class MovableParticle :public CircleGameObject{
	using CircleGameObject::CircleGameObject;
	
	virtual void Update() override;
};

