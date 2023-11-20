#include "Timer.h"

Timer::Timer( float amountTime , int amount )
{
	this->amountTime = amountTime;
	this->amount = amount;
}

Timer::Timer( float amountTime )
{
	this->amountTime = amountTime;
}

bool Timer::checkTime( ) const
{
	return time > amountTime;
}

bool Timer::getState( ) const
{
	return state;
}

int Timer::getAmount( ) const
{
	return amount;
}

void Timer::update( float dt_ )
{
	time += dt_;
}

void Timer::reset( )
{
	time = 0.0f;
	amount = 0;
}

void Timer::setState( bool in )
{
	state = in;
}

float Timer::getTime( ) const
{
	return time;
}

float Timer::getMaxTime( ) const
{
	return amountTime;
}
