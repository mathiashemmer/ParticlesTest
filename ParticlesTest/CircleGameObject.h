#pragma once
#include "GameObject.h"

extern float GRAVITY_ACC;
extern double DELTA_TIME;

class CircleGameObject : public GameObject{
public:

	float radius;

	///<summary>
	///Instatiates a new game circle game object. Uses default constructor, object will not be visible
	///</summary>
	CircleGameObject();
	
	///<sumary>
	///Instatiates a new game circle game object
	///</sumary>
	///<param name="radius">The size of the circle radius</param>
	CircleGameObject(float radius);

	///<summary>
	///Instatiates a new game circle game object
	///</summary>
	///<param name="radius">The size of the circle radius</param>
	///<param name="x">The x position of the object </param>
	///<param name="y">The y position of the object </param>
	CircleGameObject(float radius, float x, float y);

	///<summary>
	///Instatiates a new game circle game object
	///</summary>
	///<param name="radius">The size of the circle radius</param>
	///<param name="x">The x position of the object </param>
	///<param name="y">The y position of the object </param>
	///<param name="color">The color of the object, represented in RGB 0-255 values</param>
	CircleGameObject(float radius, float x, float y, unsigned char color[3]);

	///<summary>
	///Instatiates a new game circle game object
	///</summary>
	///<param name="radius">The size of the circle radius</param>
	///<param name="x">The x position of the object </param>
	///<param name="y">The y position of the object </param>
	///<param name="color">The color of the object, represented in RGB 0-255 values</param>
	///<param name="mass">The mass of the object</param>
	CircleGameObject(float radius, float x, float y, unsigned char color[3], float mass);

	///<summary>
	///Instatiates a new game circle game object
	///</summary>
	///<param name="radius">The size of the circle radius</param>
	///<param name="x">The x position of the object </param>
	///<param name="y">The y position of the object </param>
	///<param name="color">The color of the object, represented in RGB 0-255 values</param>
	///<param name="mass">The mass of the object</param>
	///<param name="restitution">The "elasticity" of the object. In collision calculation, the min value from two objects is used</param>
	CircleGameObject(float radius, float x, float y, unsigned char color[3], float mass, float restitution);

	///<summary>
	///Instatiates a new game circle game object
	///</summary>
	///<param name="radius">The size of the circle radius</param>
	///<param name="x">The x position of the object </param>
	///<param name="y">The y position of the object </param>
	///<param name="rotation">The rotation of the object in radians</param>
	///<param name="color">The color of the object, represented in RGB 0-255 values</param>
	///<param name="mass">The mass of the object</param>
	///<param name="restitution">The "elasticity" of the object. In collision calculation, the min value from two objects is used</param>
	CircleGameObject(float radius, float x, float y, float rotation, unsigned char color[3], float mass, float restitution);

	virtual void Draw(cimg_library_suffixed::CImg<unsigned char>& canvas) override;
	virtual void Update() {};
	virtual void UpdateRigidBody() override;
};

