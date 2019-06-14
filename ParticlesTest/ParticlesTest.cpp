#include <iostream>
#include "CImg.h"
#include "GameObject.h"
#include <list>
#include <chrono>
#include "Vector2.h"
#include <string>
#include "CollisionHandler.h"

using namespace cimg_library;
using namespace std::chrono;

//Definition of some constants and global objects used in the simulation
const nanoseconds FRAMETIME(16666666);		// 1/60 sec or 1666666.10^-9
float GRAVITY_ACC = 9.81;
double DELTA_TIME = (double)1/(double)60;

int main()
{
	//Aplication window settings
	unsigned int winHeight = 720;
	unsigned int winWidth = 1200;
	CImgDisplay main_disp(winWidth, winHeight, "Particle Simulator");
	main_disp.move(305, 20);
	CImgDisplay config_disp(300, 300, "Configuration Window");
	config_disp.move(0, 20);
	bool hasClicked = false;
	bool multiBrush = false;
	bool multiBrush_togle = true;
	bool simulate = false;
	bool simulate_toggle = true;

	//Object settings
	float _radius = 25;
	float _mass = 1;
	float _restitution = 1;

	//Simulation objects and settings
	std::list<GameObject*> objPool;
	Manifold manifold;

	using clock = high_resolution_clock;
	nanoseconds accumulator(0ns);
	auto timeSinceLastFrame	= clock::now();
	auto timeNow			= clock::now();

	while (!main_disp.is_closed()){
		// Game update tick 
		timeNow = clock::now();							// Current frame time
		auto deltaTime = timeNow - timeSinceLastFrame;	// Time between frames = last frame time - current frame time
		timeSinceLastFrame = timeNow;					// Update time from last frame.
		if (simulate) {
			accumulator += deltaTime;						// Get how much time has passed since last frame;
		}
		

		CImg<unsigned char> img(winWidth, winHeight, 1, 3, 0);
		CImg<unsigned char> config_img(300, 300, 1, 3, 0);

		// Update the game 60 times per second. Sometimes the frame may lag from last time, so the logic keeps going until the delta time has
		//passed. This maintein the 60 update calls.
		while (accumulator >= FRAMETIME && simulate)
		{
			// Loop every object in the pool
			for (GameObject* self : objPool) {
				// For every object, loop over every other object in the pool to calculate colision detection and forces.
				for (GameObject* other : objPool) {
					if (self != other) {
						manifold.A = self;
						manifold.B = other;
						if (self->gameObjectShape == GameObjectShape::circle && other->gameObjectShape == GameObjectShape::circle) {
							if (CircleVsCricle(&manifold)) ResolveCollision(manifold);
						}
					}
				}
			}
			// Updates the object after all colisions have been calculated. This is done due the fact that appling the forces right after
			//calculating them may make other objects ignore a colision, even though they should not.
			for (GameObject* self : objPool) {
				self->UpdateRigidBody();
			}
			accumulator -= FRAMETIME;
		}

		//Draw frame loop
		for (GameObject* o : objPool) {
			o->Draw(img);
		}

		if (main_disp.button() && main_disp.mouse_y() >= 0 && (!hasClicked || multiBrush)) {
			float x = main_disp.mouse_x();
			float y = main_disp.mouse_y();

			unsigned char color[3] = { 255, 255, 255 };

			GameObject* newObj = new CircleGameObject(_radius, x, y, color, _mass, _restitution);
			newObj->Draw(img);
			objPool.push_front(newObj);
			hasClicked = true;
		}
		else {
			if (hasClicked && !main_disp.button()) { hasClicked = false; }
		}

		if (main_disp.key(0) == main_disp.keycode("R")) {
			objPool.clear();
		}

		// RADIUS
		if (main_disp.key(0) == main_disp.keycode("Q")) {
			_radius += 10.0f * DELTA_TIME;
		}
		else if (main_disp.key(0) == main_disp.keycode("A")) {
			_radius -= 10.0f * DELTA_TIME;
		}

		// MASS
		if (main_disp.key(0) == main_disp.keycode("W")) {
			_mass += 10.0f * DELTA_TIME;
		}
		if (main_disp.key(0) == main_disp.keycode("S")) {
			_mass -= 10.0f * DELTA_TIME;
		}
		if (main_disp.key(0) == main_disp.keycode("X")) {
			_mass = 0;
		}

		// RESTITUTION
		if (main_disp.key(0) == main_disp.keycode("E")) {
			_restitution += 1.0f * DELTA_TIME;
			if (_restitution >= 1) _restitution = 1;
		}
		if (main_disp.key(0) == main_disp.keycode("D")) {
			_restitution -= 1.0f * DELTA_TIME;
			if (_restitution <= 0) _restitution = 0;
		}

		if (main_disp.key(0) == main_disp.keycode("F") && multiBrush_togle) {
			multiBrush = !multiBrush;
			multiBrush_togle = false;
		
		}
		if (!multiBrush_togle && main_disp.released_key() != 0) {
			multiBrush_togle = true;
		}

		if (main_disp.key(0) == cimg::keySPACE && simulate_toggle) {
			simulate = !simulate;
			simulate_toggle = false;

		}
		if (!simulate_toggle && main_disp.released_key() != 0) {
			simulate_toggle = true;
		}

		auto str = "(Q,A)Radius: " + std::to_string(_radius);
		str += "\n(W,S,X)Mass: " + std::to_string(_mass);
		str += "\n(E,D)Resitution: " + std::to_string(_restitution);
		str += "\n(R)Reset Object Pool";
		str += "\n(F)MultiBrush: ";
		str += multiBrush ? "true" : "false";
		str += "\n"+std::to_string(deltaTime.count() / (double)1000000000);
		str += "\nFPS: " + std::to_string((int)(1 / (deltaTime.count() / (double)1000000000)));

		int mx = main_disp.mouse_x();
		int my = main_disp.mouse_y();
		str += "\n(" + std::to_string(mx) + "," + std::to_string(my) + ")";

		str += "\n(SPACE)Simulate: ";
		str += simulate ? "true" : "false";
		unsigned char color[3] = { 255, 255, 255};
		config_img.draw_text(0, 0, str.c_str(), color, 0, 1, 20);
		config_disp.display(config_img);
		main_disp.display(img);
	}
}

void Update() {

}