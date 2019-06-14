#pragma once
#include "GameObject.h"

extern float GRAVITY_ACC;
extern double DELTA_TIME;

class CircleGameObject : public GameObject{
public:

	float radius;

	///<sumary>
	///<para>Instatiates a new game circle game object</para>
	///<para>Uses default constructor, object will not be visible</para>
	///</sumary>
	CircleGameObject();
	
	///<sumary>
	///<para>Instatiates a new game circle game object</para>
	///<para>radius -> The size of the circle radius</para>
	///</sumary>
	CircleGameObject(float radius);

	///<sumary>
	///<para>Instatiates a new game circle game object</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>(x, y) -> The position of the object </para>
	///</sumary>
	CircleGameObject(float radius, float x, float y);

	///<sumary>
	///<para>Instatiates a new game circle game object</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>(x, y) -> The position of the object </para>
	///<para>color[3] -> The color of the object, represented in RGB 0-255 values</para>
	///</sumary>
	CircleGameObject(float radius, float x, float y, unsigned char color[3]);

	///<sumary>
	///<para>Instatiates a new game circle game object</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>(x, y) -> The position of the object </para>
	///<para>color[3] -> The color of the object, represented in RGB 0-255 values</para>
	///<para>mass -> The mass of the object </para>
	///</sumary>
	CircleGameObject(float radius, float x, float y, unsigned char color[3], float mass);

	///<sumary>
	///<para>Instatiates a new game circle game object</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>(x, y) -> The position of the object </para>
	///<para>color[3] -> The color of the object, represented in RGB 0-255 values</para>
	///<para>mass -> The mass of the object </para>
	///<para>restitution -> The "elasticity" of the object. In collision calculation, the min value from two objects is used</para>
	///</sumary>
	CircleGameObject(float radius, float x, float y, unsigned char color[3], float mass, float restitution);

	///<sumary>
	///<para>Instatiates a new game circle game object</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>radius -> The size of the circle radius</para>
	///<para>(x, y) -> The position of the object </para>
	///<para>rotation -> The rotation of the object </para>
	///<para>color[3] -> The color of the object, represented in RGB 0-255 values</para>
	///<para>mass -> The mass of the object </para>
	///<para>restitution -> The "elasticity" of the object. In collision calculation, the min value from two objects is used</para>
	///</sumary>
	CircleGameObject(float radius, float x, float y, float rotation, unsigned char color[3], float mass, float restitution);

	virtual void Draw(cimg_library_suffixed::CImg<unsigned char>& canvas) override;
	virtual void Update() override;
	virtual void UpdateRigidBody() override;
};

