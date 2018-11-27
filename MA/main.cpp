#include <iostream>
#include "Time.h"
#include "Unit.h"
#include "Map.h"
#include "View.h"


using namespace sf;
using namespace std;

int main()
{


	Hero gg(string("graphics\\gg\\move\\moveTexture.png"), 0, 0, 256, 256);
	Map map(256, 256);
	float currentFrame = 0.0F;
	MA::Time time;
	RenderWindow window(VideoMode(1024, 768), "Marked Adventures");
	view.reset(FloatRect(0.0F, 0.0F, 1024.0F, 768.0F));
	gg.setScale(0.1F);
	gg.setSpeed(10.0F);
	gg.setPosition(256.0F, 256.0F);
	Event event;
	time.reset();
	while (window.isOpen())
	{

		//cout << time.getElapsedTime() << endl;
		if (time.getElapsedTime() < 0.017F)
		{
			continue;
		}
		time.reset();



		if (event.type == Event::KeyPressed)
		{
			switch (event.key.code)
			{

			case Keyboard::Left:
			case Keyboard::A:
				gg.move(Direction::left, time.getElapsedTime());
				break;

			case Keyboard::Up:
			case Keyboard::W:
				gg.move(Direction::top, time.getElapsedTime());

				break;

			case Keyboard::Right:
			case Keyboard::D:
				gg.move(Direction::right, time.getElapsedTime());
				break;

			case Keyboard::Down:
			case Keyboard::S:
				gg.move(Direction::bottom, time.getElapsedTime());
				break;

			default:
				break;
			}



		}

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		
		

		/*		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
				{
					gg.move(Direction::left, time.getElapsedTime());
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
				{
					gg.move(Direction::top, time.getElapsedTime());
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
				{
					gg.move(Direction::right, time.getElapsedTime());
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
				{
					gg.move(Direction::bottom, time.getElapsedTime());
				}
		*/
		//getNewView(gg.getPositionX(), gg.getPositionY());
//		window.setView(view);
		window.clear(Color(40, 33, 25));
		map.draw(window);
		gg.draw(window);

		window.display();
	}

	return 0;
}