#pragma once
#include "Entity.h"
#include "fsm.h"
#include <complex>
#include <chrono>


class Hero : public Entity
{
public:
	Hero(double x, double y);
	void handleInput();
	void jump();
	void wallJump(int direction);
	void update(double elapsed) override;
	

private:
	enum class States { Standing, Jumping, SlidingRight, SlidingLeft };
	FSM::Fsm<States, States::Standing, int> fsm;
	double velocityX;
	double velocityY;
	double maxWalkingSpeed;
	double jumpingVelocity;

};
