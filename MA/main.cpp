#include "Unit.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1024, 768), "Marked Adventures");

	Hero gg(string("D:\\Course Project\\MA\\MA\\graphics\\gg\\move\\moveTexture.png"), 0, 0, 256, 256);

	float currentFrame = 0.0F;
	Clock clock;

	while (window.isOpen())
	{
		float time = (float)clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;
		Event event;
		gg.setScale(0.1F);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color(255, 255, 255));
		gg.draw(window);
		
		window.display();
	}

	return 0;
}