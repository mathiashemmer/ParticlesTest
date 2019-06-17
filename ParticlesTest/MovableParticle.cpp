#include "MovableParticle.h"
#include "CImg.h"

extern cimg_library::CImgDisplay *MainWindow;;

void MovableParticle::Update(){
	if (isKinematic)
		return;

	if (MainWindow->is_keyARROWUP()) {
		this->rigidbody->velocity.y -= 100 * DELTA_TIME;
	}
	if (MainWindow->is_keyARROWDOWN()) {
		this->rigidbody->velocity.y += 100 * DELTA_TIME;
	}
	if (MainWindow->is_keyARROWLEFT()) {
		this->rigidbody->velocity.x -= 100 * DELTA_TIME;
	}
	if (MainWindow->is_keyARROWRIGHT()) {
		this->rigidbody->velocity.x += 100 * DELTA_TIME;
	}
}
