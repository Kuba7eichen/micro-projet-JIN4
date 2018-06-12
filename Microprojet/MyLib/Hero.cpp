#include "stdafx.h"

#include "Hero.h"
#include <Windows.h>

Hero::Hero(double x, double y)
	:Entity{ x,y },
	velocityX(0),
	velocityY(0),
	jumpingVelocity(5),
	maxWalkingSpeed(5)
{

	fsm.add_transitions({
		{ States::Standing, States::Jumping, 'up', nullptr, [&] {jump(); } },
		});
	fsm.add_transitions({
		{ States::Jumping, States::SlidingLeft, 'jl', nullptr,  nullptr },
		});
	fsm.add_transitions({
		{ States::Jumping, States::SlidingRight, 'jr', nullptr, nullptr },
		});
	fsm.add_transitions({
		{ States::Jumping, States::Standing, 'down', nullptr, nullptr },
		});
	fsm.add_transitions({
		{ States::SlidingRight, States::Jumping, 'up', nullptr, [&] {wallJump(-1); } },
		});
	fsm.add_transitions({
		{ States::SlidingLeft, States::Jumping, 'up', nullptr, [&] {wallJump(1); } },
		});
	fsm.add_transitions({
		{ States::SlidingRight, States::Jumping, 'wl', nullptr, nullptr },
		});
	fsm.add_transitions({
		{ States::SlidingLeft, States::Jumping, 'wr', nullptr, nullptr },
		});
}

void Hero::handleInput() 
{
	if (GetKeyState(VK_UP) & 0x8000)
		fsm.execute('up');
	if (GetKeyState(VK_LEFT) & 0x8000)
		velocityX = -maxWalkingSpeed;
	if (GetKeyState(VK_RIGHT) & 0x8000)
		velocityX = maxWalkingSpeed;
}

void Hero::jump()
{
	velocityY = jumpingVelocity;
}
void Hero::wallJump(int direction)
{
	velocityY = jumpingVelocity;
	
	velocityX = maxWalkingSpeed * direction;
}
void Hero::update(double elapsed)
{
	pos_x += velocityX * elapsed;
	pos_y += velocityY * elapsed;
}
