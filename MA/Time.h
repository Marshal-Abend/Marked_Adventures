#pragma once
#include <SFML\Graphics.hpp>
#include <string>


using namespace std;
using namespace sf;

namespace MA
{
	class Time {
		Clock clock;
		float time;

	public:
		Time();
		float getElapsedTime();
		void reset();

	};
}

