#include "Animation.h"



Animation::Animation()
{
	timeWalk = 3;
	timeIdle = 3;
	AnimationsImages.push_back("MarioSmallRun.png");
	AnimationsImages.push_back("MarioBigIdle.png");
	AnimationsImages.push_back("MarioSmallJump.png");
}

void Animation::setAnim(gdBody& body, States bo) {
	if (bo == States::WALKING) {
		body.SetImage(AnimationsImages[0]);
		/*if (timeWalk < 0) {
			body.SetImage(AnimationsImages[0]);
			if (timeIdle < 0 ) {
				body.SetImage(AnimationsImages[1]);
				timeWalk = 3;
				timeIdle = 3;
			}
			
		}*/
	}
	if (bo == States::JUMPING) {
		body.SetImage(AnimationsImages[2]);
	}
}


void Animation::setTimer(const float timer) {

	timeWalk -= timer;
	if (timeWalk < timeIdle) {
		timeIdle -= timer;
	}
}

Animation::~Animation()
{
}
