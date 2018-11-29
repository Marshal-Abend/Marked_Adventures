#include "Time.h"

MA::Timer::Timer()
{
	MA::Timer::time = 0.0F;
}

float MA::Timer::getElapsedTime()
{
	return MA::Timer::clock.getElapsedTime().asSeconds();
}

void MA::Timer::reset()
{
	MA::Timer::clock.restart();
}