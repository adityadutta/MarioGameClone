#ifndef ANIMATION_H
#define ANIMATION_H

#include<vector>
#include"gdBody.h"

enum class States{
	WALKING,
	JUMPING
};
class Animation
{
public:
	Animation();
	~Animation();
	std::vector<char*> AnimationsImages;
	void setAnim(gdBody& body, States bo);
	void setTimer(const float timer);
	float timeWalk;
	float timeIdle;

};
#endif

