#include <iostream>
#include "Time.h"
#include "Map.h"
#include "Unit.h"
#include "View.h"
#include "Animation.h"

//#include <ctime>


using namespace sf;
using namespace std;

int main()
{

	srand(time(0));
	Hero gg(string("graphics\\gg\\move\\moveTexture.png"), 0, 0, 256, 256);
	Map map(256, 256);
	float currentFrame = 0.0F;
	MA::Timer timer;
	RenderWindow window(VideoMode(1280, 768), "Marked Adventures");
	window.setFramerateLimit(60);
	view.reset(FloatRect(0.0F, 0.0F, 1280.0F, 768.0F));
	gg.setScale(0.35F);
	//map.setScale(0.5F);
	gg.setSpeed(10.0F);
	gg.setPosition((256.0F*1.F) * gg.getScale(), (256.0F*1.F) * gg.getScale());
	Event event;
	bool go = false;
	timer.reset();
	while (window.isOpen())
	{
		

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)go = true;
			if (event.type == Event::MouseMoved)
			{
				continue;
			}
			if (timer.getElapsedTime() < 0.017F)
			{
				sleep(sf::seconds((0.017F - timer.getElapsedTime())));
			}
			timer.reset();
			
			
			if (event.type == Event::Closed)
				window.close();
		}
		//cout << time.getElapsedTime() << endl;
	



		if (go)
		{
			switch (event.key.code)
			{

			case Keyboard::Left:
			case Keyboard::A:
				gg.animate(gg.move(Direction::left));
				break;

			case Keyboard::Up:
			case Keyboard::W:
				gg.animate(gg.move(Direction::top));

				break;

			case Keyboard::Right:
			case Keyboard::D:
				gg.animate(gg.move(Direction::right));
				break;

			case Keyboard::Down:
			case Keyboard::S:
				gg.animate(gg.move(Direction::bottom));
				break;

			default:
				break;
			}



		}

		gg.collision(gg, map);
		getNewView(gg.getPositionX(), gg.getPositionY());
		window.setView(view);
		window.clear(Color(40, 33, 25));
		map.draw(window);
		gg.draw(window);

		window.display();
		if (event.type == Event::KeyReleased)go = false;
	}

	return 0;
}