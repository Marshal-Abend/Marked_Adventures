#include "End.h"

void playEnd(EndType endType, RenderWindow &window)
{
	Movie movie;
	float duration;
	string movieName;
	Clock clock;

	switch (endType)
	{
	case EndType::blind:
		movieName = VIDEO_BLIND;
		duration = DURATION_BLIND;
		break;
	case EndType::hd:
		movieName = VIDEO_HD;
		duration = DURATION_HD;
		break;
	case EndType::immortality:
		movieName = VIDEO_IMMORTALITY;
		duration = DURATION_IMMORTALITY;
		break;
	case EndType::money:
		movieName = VIDEO_MONEY;
		duration = DURATION_MONEY;
		break;
	case EndType::power:
		movieName = VIDEO_POWER;
		duration = DURATION_POWER;
		break;
	case EndType::welcome:
		movieName = VIDEO_WELCOME;
		duration = DURATION_WELCOME;
		break;
	case EndType::truth:
		movieName = VIDEO_TRUE;
		duration = DURATION_TRUE;
		break;
	default:
		break;
	}
	if (!movie.openFromFile(movieName))
		return;

	Vector2u prevSize = window.getSize();
	window.create(VideoMode::getDesktopMode(), "", Style::Fullscreen);
	window.setMouseCursorVisible(false);
	movie.fit(0, 0, window.getSize().x, window.getSize().y);

	//window.create(VideoMode::getDesktopMode(), "sfeMovie Player", Style::Fullscreen);
	//movie.update();
	Event ev;
	window.setFramerateLimit(60);
	movie.play();
	clock.restart();
	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed) 
			{
				window.close();
				gState = GameState::Exit;
				return;
			}
				
		}


		window.clear();
		movie.update();
		window.draw(movie);
		window.display();


		if (clock.getElapsedTime().asSeconds() >= duration)
		{
			window.create(VideoMode(prevSize.x, prevSize.y), "Marked Adventures", Style::Default);
			window.setMouseCursorVisible(true);
			return;
		}
	}

	return;
}