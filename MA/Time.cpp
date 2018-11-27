#include "Time.h"

MA::Time::Time()
{
	MA::Time::time = 0.0F;
}

float MA::Time::getElapsedTime()
{
	return MA::Time::clock.getElapsedTime().asSeconds();
}

void MA::Time::reset()
{
	MA::Time::clock.restart();
}