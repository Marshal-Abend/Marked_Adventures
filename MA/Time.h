#pragma once
#include <SFML\Graphics.hpp>
#include <string>


using namespace std;
using namespace sf;

namespace MA
{
	class Timer {
		Clock clock;
		float time;

	public:
		Timer();
		float getElapsedTime();
		void reset();

	};
}

