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

float GRAVITY_ACC = 9.81;
double DELTA_TIME = (float)1/(float)18;

int main()
{
	const nanoseconds FRAMETIME(16666666);		// 1/60 sec or 1666666.10^-9
	using clock = high_resolution_clock;	
	nanoseconds accumulator(0ns);

	unsigned int winHeight = 720;
	unsigned int winWidth = 1280;

	bool hasClicked = false;
	bool zeroMass;
	float rad = 25;

	std::list<GameObject*> objPool;

	CImgDisplay main_disp(winWidth, winHeight, "Particle Simulator");
	auto lastFramStartTime = clock::now();

	while (!main_disp.is_closed()){
		auto timeNow = clock::now();					// Get current time
		auto deltaTime = timeNow - lastFramStartTime;	// Find the DeltaTime between frames
		lastFramStartTime = timeNow;					// Uptade the 
		accumulator += duration_cast<nanoseconds>(deltaTime);
		CImg<unsigned char> img(winWidth, winHeight, 1, 3, 0);

		while (accumulator >= FRAMETIME)
		{
			Manifold manifold;

			for (GameObject* self : objPool) {
				for (GameObject* other : objPool) {
					if (self != other) {
						manifold.A = self;
						manifold.B = other;

						if (self->gameObjectShape == GameObjectShape::circle && other->gameObjectShape == GameObjectShape::circle) {
							if (CircleVsCricle(&manifold)) ResolveCollision(manifold);
						}
					}
				}
				self->UpdateRigidBody();
			}
			accumulator -= FRAMETIME;
		}

		//Draw frame loop
		for (GameObject* o : objPool) {
			o->Draw(img);
		}

		if (main_disp.button() && main_disp.mouse_y() >= 0 && !hasClicked) {
			float x = main_disp.mouse_x();
			float y = main_disp.mouse_y();

			unsigned char color[3] = { 255, 255, 255 };

			float mass = rad >= 25 ? rad : 0;

			GameObject* newObj = new CircleGameObject(rad, x, y, color, mass);
			newObj->Draw(img);
			objPool.push_front(newObj);
			hasClicked = true;
		}
		else if (hasClicked && !main_disp.button()) {
			hasClicked = false;
		}

		if (main_disp.key(0) == main_disp.keycode("W")) {
			rad += 10.0f * DELTA_TIME;
		}
		else if (main_disp.key(0) == main_disp.keycode("S")) {
			rad -= 10.0f * DELTA_TIME;
		}

		main_disp.display(img);
	}
}

void Update() {

}