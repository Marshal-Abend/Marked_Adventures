#include <iostream>
#include <SFML\Audio.hpp>
#include "Time.h"
#include "Map.h"
#include "Unit.h"
#include "View.h"
#include "End.h"

//#include <ctime>


void truePath(RenderWindow & window);
void falseDesires(RenderWindow & window);
void chooseLevel(RenderWindow & window, Level &level);
void game(RenderWindow & window, Level lavel);
Level menu(RenderWindow & window);
void pause(RenderWindow & window);


using namespace sf;
using namespace std;

float scaleX = 1.0F, scaleY = 1.0F;
int prevX, prevY;
GameState gState;


int main()
{
	RenderWindow window(VideoMode(1280, 768), "Marked Adventures", Style::Default);
	window.setFramerateLimit(60);
	prevX = window.getSize().x;
	prevY = window.getSize().y;
	view.setSize(window.getSize().x, window.getSize().y);
	Level level;
	while (gState != GameState::Exit)
	{
		switch (gState)
		{
		case Menu:
			level = menu(window);
			break;
		case OMenu:
			break;
		case MMenu:
			break;
		case Game:
			game(window, level);
			break;
		case Pause:
			break;
		case Exit:
			break;
		default:
			break;
		}
	}
	return 0;
}

void game(RenderWindow & window, Level level)
{
	Music music;
	music.setLoop(true);
	music.openFromFile("play.ogg");
	music.play();

	srand((unsigned int)time(0));
	Hero gg(string("graphics\\gg\\move\\moveTexture.png"), 0, 0, 256, 256);
	gg.setScale(0.1F);
	Map map(256, 256, gg.getScale(), level);
	MA::Timer timer;



//	view.reset(FloatRect(0.0, 0.0, window.getSize().x, window.getSize().y));

	gg.setSpeed(30.0F);
	gg.setPosition((256.0F*1.F) * gg.getScale(), (256.0F*1.F) * gg.getScale());

	Event ev;
	bool go = false;
	timer.reset();

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::KeyPressed)go = true;
			if (timer.getElapsedTime() < 0.017F)
			{
				sleep(sf::seconds((0.017F - timer.getElapsedTime())));
			}
			timer.reset();
			if (ev.type == Event::Resized)
			{
				scaleX = ev.size.width / (float)prevX;
				scaleY = ev.size.height / (float)prevY;
			}

			if (ev.type == Event::Closed)
			{
				window.close();
				gState = GameState::Exit;
				return;
			}


		}

		if (go)
		{
			switch (ev.key.code)
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
			case Keyboard::Add:
				gg.setScale(gg.getScale() + 0.1F);
				map.setScale(map.getScale() + 0.1F);
				break;
			case Keyboard::Subtract:
				gg.setScale(gg.getScale() - 0.1F);
				map.setScale(map.getScale() - 0.1F);
				break;
			case Keyboard::Escape:
				music.pause();
				gState = GameState::Pause;
				pause(window);
				music.play();
				break;
			default:
				break;
			}
		}
		gg.collision(gg, map);
		switch (gState)
		{
		case Menu:
			return;
			break;
		case OMenu:
			music.pause();
			truePath(window);
			return;
			break;
		case MMenu:
			music.pause();
			falseDesires(window);
			return;
			break;
		case Exit:
			return;
			break;
		default:
			break;
		}
		if (gState == GameState::Menu)
		{
			map.clear();
			return;
		}
		getNewView(gg.getPositionX(), gg.getPositionY());
		window.setView(view);
		window.clear(Color(40, 33, 25));
		map.draw(window);
		gg.draw(window);

		window.display();
		if (ev.type == Event::KeyReleased)go = false;
	}

	return;
}

Level menu(RenderWindow & window) {
	getNewView(window.getSize().x / 2.0F, window.getSize().y / 2.0F);
	window.setView(view);
	Music music;
	music.setLoop(true);
	music.openFromFile("menu//menu.ogg");
	music.play();
	Level level = Level::easy;
	Texture playTexture, menuTexture2, exitTexture, menuBackground;
	playTexture.loadFromFile("menu/play.png");
	exitTexture.loadFromFile("menu/exit.png");
	menuBackground.loadFromFile("menu/bg.jpg");
	Sprite playSprite(playTexture), exitSprite(exitTexture), menuBg(menuBackground);
	menuBg.setScale((float)window.getSize().x / (float)menuBackground.getSize().x, (float)window.getSize().y / (float)menuBackground.getSize().y);
	bool isMenu = 1;
	int menuNum = 0; 
	playSprite.setPosition(100 * scaleX, 30 * scaleY);
	exitSprite.setPosition(100 * scaleX, 90 * scaleY);
	menuBg.setPosition(0, 0);
	Event ev;
	MA::Timer timer;
	timer.reset();
	
	
	while (isMenu)
	{
		while (window.pollEvent(ev))
		{
			if (timer.getElapsedTime() < 0.017F)
			{
				sleep(sf::seconds((0.017F - timer.getElapsedTime())));
			}
			timer.reset();

			if (ev.type == Event::Resized)
			{
				scaleX = ev.size.width / (float)prevX;
				scaleY = ev.size.height / (float)prevY;
			}
			if (ev.type == Event::Closed)
			{
				window.close();
				isMenu = false;
				gState = GameState::Exit;
			}

		}
		playSprite.setColor(Color::White);
		exitSprite.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100* scaleX, 30 * scaleY, 81 * scaleX, 37* scaleY).contains(Mouse::getPosition(window))) { playSprite.setColor(Color(255, 79, 70)); menuNum = 1; }
		else
			if (IntRect(100 * scaleX, 90 * scaleY, 73 * scaleX, 30* scaleY).contains(Mouse::getPosition(window))) { exitSprite.setColor(Color(255, 79, 70)); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
				gState = GameState::Game;
				chooseLevel(window, level);
				if (level == Level::cancel)
				{
					gState = GameState::Menu;
				}
				return level;
			}
			else if (menuNum == 2)
			{
				window.close();
				isMenu = false;
				gState = GameState::Exit;
				return level;
			}

		}

		window.draw(menuBg);
		window.draw(playSprite);
		window.draw(exitSprite);

		window.display();
	}
	return level;
}

void pause(RenderWindow & window)
{
	getNewView(window.getSize().x / 2.0F, window.getSize().y / 2.0F);
	window.setView(view);
	Music music;
	music.setLoop(true);
	music.openFromFile("pause.ogg");
	music.setVolume(75);
	music.play();

	Texture playTexture, menuTexture, menuBackground;
	playTexture.loadFromFile("menu/resume.png");
	menuTexture.loadFromFile("menu/menu.png");
	menuBackground.loadFromFile("menu/bg.jpg");
	Sprite playSprite(playTexture), menuSprite(menuTexture), menuBg(menuBackground);
	menuBg.setScale((float)window.getSize().x / (float)menuBackground.getSize().x, (float)window.getSize().y / (float)menuBackground.getSize().y);
	bool isMenu = 1;
	int menuNum = 0;
	playSprite.setPosition(100 * scaleX, 30 * scaleY);
	menuSprite.setPosition(100 * scaleX, 90 * scaleY);
	menuBg.setPosition(0, 0);
	Event ev;
	MA::Timer timer;
	timer.reset();
	while (isMenu)
	{
		while (window.pollEvent(ev))
		{
			if (timer.getElapsedTime() < 0.017F)
			{
				sleep(sf::seconds((0.017F - timer.getElapsedTime())));
			}
			timer.reset();
			if (ev.type == Event::Resized)
			{
				scaleX = ev.size.width / (float)prevX;
				scaleY = ev.size.height / (float)prevY;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				isMenu = false;
				gState = GameState::Game;
			}
			if (ev.type == Event::Closed)
			{
				window.close();
				isMenu = false;
				gState = GameState::Exit;
				return;
			}

		}
		playSprite.setColor(Color::White);
		menuSprite.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100 * scaleX, 30 * scaleY, 148 * scaleX, 24 * scaleY).contains(Mouse::getPosition(window)))
		{
			playSprite.setColor(Color(255, 79, 70));
			menuNum = 1;
		}
		else if (IntRect(100 * scaleX, 90 * scaleY, 109 * scaleX, 24 * scaleY).contains(Mouse::getPosition(window)))
		{
			menuSprite.setColor(Color(255, 79, 70));
			menuNum = 2;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
				gState = GameState::Game;
			}
			if (menuNum == 2)
			{
				isMenu = false;
				gState = GameState::Menu;
			}

		}

		window.draw(menuBg);
		window.draw(playSprite);
		window.draw(menuSprite);

		window.display();
	}
}

void chooseLevel(RenderWindow & window, Level &level)
{
	getNewView(window.getSize().x / 2.0F, window.getSize().y / 2.0F);
	window.setView(view);
	Texture easyTexture, normalTexture, hardTexture, expertTexture, menuTexture, menuBackground;
	easyTexture.loadFromFile("level/easy.png");
	normalTexture.loadFromFile("level/normal.png");
	hardTexture.loadFromFile("level/hard.png");
	expertTexture.loadFromFile("level/expert.png");
	menuTexture.loadFromFile("level/menu.png");
	menuBackground.loadFromFile("level/bg.jpg");

	Sprite easySprite(easyTexture), normalSprite(normalTexture), hardSprite(hardTexture), expertSprite(expertTexture), menuSprite(menuTexture), menuBg(menuBackground);
	menuBg.setScale((float)window.getSize().x / (float)menuBackground.getSize().x, (float)window.getSize().y / (float)menuBackground.getSize().y);
	bool isMenu = 1;
	int menuNum = 0;

	easySprite.setPosition(100 * scaleX, 30 * scaleY);
	normalSprite.setPosition(100 * scaleX, 80 * scaleY);
	hardSprite.setPosition(100 * scaleX, 140 * scaleY);
	expertSprite.setPosition(100 * scaleX, 200 * scaleY);
	menuSprite.setPosition(100 * scaleX, 260 * scaleY);
	menuBg.setPosition(0, 0);

	Event ev;
	MA::Timer timer;
	timer.reset();
	while (isMenu)
	{
		while (window.pollEvent(ev))
		{
			if (timer.getElapsedTime() < 0.017F)
			{
				sleep(sf::seconds((0.017F - timer.getElapsedTime())));
			}
			timer.reset();
			if (ev.type == Event::Resized)
			{
				scaleX = ev.size.width / (float)prevX;
				scaleY = ev.size.height / (float)prevY;
			}

			if (ev.type == Event::Closed)
			{
				window.close();
				isMenu = false;
				gState = GameState::Exit;
				return;
			}
		}
		easySprite.setColor(Color::White);
		normalSprite.setColor(Color::White);
		hardSprite.setColor(Color::White);
		expertSprite.setColor(Color::White);
		menuSprite.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100 * scaleX, 30 * scaleY, 92 * scaleX, 31 * scaleY).contains(Mouse::getPosition(window)))
		{
			easySprite.setColor(Color(255, 79, 70));
			menuNum = 1;
		}
		else if (IntRect(100 * scaleX, 80 * scaleY, 137 * scaleX, 30 * scaleY).contains(Mouse::getPosition(window)))
		{
			normalSprite.setColor(Color(255, 79, 70));
			menuNum = 2;
		}
		else if (IntRect(100 * scaleX, 140 * scaleY, 89 * scaleX, 30 * scaleY).contains(Mouse::getPosition(window)))
		{
			hardSprite.setColor(Color(255, 79, 70));
			menuNum = 3;
		}
		else if (IntRect(100 * scaleX, 200 * scaleY, 129 * scaleX, 39 * scaleY).contains(Mouse::getPosition(window)))
		{
			expertSprite.setColor(Color(255, 79, 70));
			menuNum = 4;
		}
		else if (IntRect(100 * scaleX, 260 * scaleY, 109 * scaleX, 24 * scaleY).contains(Mouse::getPosition(window)))
		{
			menuSprite.setColor(Color(255, 79, 70));
			menuNum = 5;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
				level = Level::easy;
			}
			else if (menuNum == 2)
			{
				isMenu = false;
				level = Level::normal;
			}
			else if (menuNum == 3)
			{
				isMenu = false;
				level = Level::hard;
			}
			else if (menuNum == 4)
			{
				isMenu = false;
				level = Level::expert;
			}
			else if (menuNum == 5)
			{
				isMenu = false;
				level = Level::cancel;
			}

		}

		window.draw(menuBg);
		window.draw(easySprite);
		window.draw(normalSprite);
		window.draw(hardSprite);
		window.draw(expertSprite);
		window.draw(menuSprite);

		window.display();
	}
}

void truePath(RenderWindow & window)
{
	getNewView(window.getSize().x / 2.0F, window.getSize().y / 2.0F);
	window.setView(view);
	Texture yesTexture, nolTexture, welcomeTexture, menuBackground;
	yesTexture.loadFromFile("truePath/yes.png");
	nolTexture.loadFromFile("truePath/no.png");
	welcomeTexture.loadFromFile("truePath/welcome.png");
	menuBackground.loadFromFile("truePath/bg.png");

	Sprite yesSprite(yesTexture), noSprite(nolTexture), welcomeSprite(welcomeTexture), menuBg(menuBackground);
	menuBg.setScale((float)window.getSize().x / (float)menuBackground.getSize().x, (float)window.getSize().y / (float)menuBackground.getSize().y);
	bool isMenu = 1;
	int menuNum = 0;

	welcomeSprite.setPosition(100 * scaleX, 30 * scaleY);
	yesSprite.setPosition(100 * scaleX, 105 * scaleY);
	noSprite.setPosition(100 * scaleX, 170 * scaleY);
	menuBg.setPosition(0, 0);

	Event ev;
	MA::Timer timer;
	timer.reset();
	while (isMenu)
	{
		while (window.pollEvent(ev))
		{
			if (timer.getElapsedTime() < 0.017F)
			{
				sleep(sf::seconds((0.017F - timer.getElapsedTime())));
			}
			timer.reset();
			if (ev.type == Event::Resized)
			{
				scaleX = ev.size.width / (float)prevX;
				scaleY = ev.size.height / (float)prevY;
			}

			if (ev.type == Event::Closed)
			{
				window.close();
				isMenu = false;
				gState = GameState::Exit;
				return;
			}
		}
		welcomeSprite.setColor(Color::Green);
		yesSprite.setColor(Color::Green);
		noSprite.setColor(Color::Green);
		menuNum = 0;
		window.clear(Color(85, 230, 101));

		if (IntRect(100 * scaleX, 105 * scaleY, 449 * scaleX, 39 * scaleY).contains(Mouse::getPosition(window)))
		{
			yesSprite.setColor(Color(0, 0, 255));
			menuNum = 1;
		}
		else if (IntRect(100 * scaleX, 170 * scaleY, 343 * scaleX, 36 * scaleY).contains(Mouse::getPosition(window)))
		{
			noSprite.setColor(Color(0, 0, 255));
			menuNum = 2;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
				playEnd(EndType::welcome, window);
				gState = GameState::Menu;
				return;
			}
			else if (menuNum == 2)
			{
				isMenu = false;
				playEnd(EndType::truth, window);
				gState = GameState::Menu;
				return;
			}
		}

		window.draw(menuBg);
		window.draw(welcomeSprite);
		window.draw(yesSprite);
		window.draw(noSprite);

		window.display();
	}
}

void falseDesires(RenderWindow & window)
{
	getNewView(window.getSize().x / 2.0F, window.getSize().y / 2.0F);
	window.setView(view);
	Texture blingTexture, hdTexture, immortalityTexture, moneyTexture, powerTexture, wishTexture, menuBackground;
	blingTexture.loadFromFile("falseDesires/blind.png");
	hdTexture.loadFromFile("falseDesires/hd.png");
	immortalityTexture.loadFromFile("falseDesires/immortality.png");
	moneyTexture.loadFromFile("falseDesires/money.png");
	powerTexture.loadFromFile("falseDesires/power.png");
	wishTexture.loadFromFile("falseDesires/wish.png");
	menuBackground.loadFromFile("falseDesires/bg.png");

	Sprite blingSprite(blingTexture), hdSprite(hdTexture), immortalitySprite(immortalityTexture), moneySprite(moneyTexture), powerSprite(powerTexture), wishSprite(wishTexture), menuBg(menuBackground);
	menuBg.setScale((float)window.getSize().x / (float)menuBackground.getSize().x, (float)window.getSize().y / (float)menuBackground.getSize().y);
	bool isMenu = 1;
	int menuNum = 0;

	wishSprite.setPosition(100 * scaleX, 30 * scaleY);
	blingSprite.setPosition(100 * scaleX, 120 * scaleY);
	hdSprite.setPosition(100 * scaleX, 180 * scaleY);
	immortalitySprite.setPosition(100 * scaleX, 240 * scaleY);
	moneySprite.setPosition(100 * scaleX, 300 * scaleY);
	powerSprite.setPosition(100 * scaleX, 360 * scaleY);
	menuBg.setPosition(0, 0);

	Event ev;
	MA::Timer timer;
	timer.reset();
	while (isMenu)
	{
		while (window.pollEvent(ev))
		{
			if (timer.getElapsedTime() < 0.017F)
			{
				sleep(sf::seconds((0.017F - timer.getElapsedTime())));
			}
			timer.reset();
			if (ev.type == Event::Resized)
			{
				scaleX = ev.size.width / (float)prevX;
				scaleY = ev.size.height / (float)prevY;
			}

			if (ev.type == Event::Closed)
			{
				window.close();
				isMenu = false;
				gState = GameState::Exit;
				return;
			}
		}
		wishSprite.setColor(Color::White);
		blingSprite.setColor(Color::White);
		hdSprite.setColor(Color::White);
		immortalitySprite.setColor(Color::White);
		moneySprite.setColor(Color::White);
		powerSprite.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(85, 230, 101));

		if (IntRect(100 * scaleX, 120 * scaleY, 406 * scaleX, 39 * scaleY).contains(Mouse::getPosition(window)))
		{
			blingSprite.setColor(Color(50, 0, 230));
			menuNum = 1;
		}
		else if (IntRect(100 * scaleX, 180 * scaleY, 423 * scaleX, 39 * scaleY).contains(Mouse::getPosition(window)))
		{
			hdSprite.setColor(Color(50, 0, 230));
			menuNum = 2;
		}
		else if (IntRect(100 * scaleX, 240 * scaleY, 224 * scaleX, 39 * scaleY).contains(Mouse::getPosition(window)))
		{
			immortalitySprite.setColor(Color(50, 0, 230));
			menuNum = 3;
		}
		else if (IntRect(100 * scaleX, 300 * scaleY, 129 * scaleX, 30 * scaleY).contains(Mouse::getPosition(window)))
		{
			moneySprite.setColor(Color(50, 0, 230));
			menuNum = 4;
		}
		else if (IntRect(100 * scaleX, 360 * scaleY, 126 * scaleX, 31 * scaleY).contains(Mouse::getPosition(window)))
		{
			powerSprite.setColor(Color(50, 0, 230));
			menuNum = 5;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
				playEnd(EndType::blind, window);
				gState = GameState::Menu;
				return;
			}
			else if (menuNum == 2)
			{
				isMenu = false;
				playEnd(EndType::hd, window);
				gState = GameState::Menu;
				return;
			}
			else if (menuNum == 3)
			{
				isMenu = false;
				playEnd(EndType::immortality, window);
				gState = GameState::Menu;
				return;
			}
			else if (menuNum == 4)
			{
				isMenu = false;
				playEnd(EndType::money, window);
				gState = GameState::Menu;
				return;
			}
			else if (menuNum == 5)
			{
				isMenu = false;
				playEnd(EndType::power, window);
				gState = GameState::Menu;
				return;
			}
		}

		window.draw(menuBg);
		window.draw(wishSprite);
		window.draw(blingSprite);
		window.draw(hdSprite);
		window.draw(immortalitySprite);
		window.draw(moneySprite);
		window.draw(powerSprite);

		window.display();
	}
}