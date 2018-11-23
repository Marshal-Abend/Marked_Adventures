#include <SFML\Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1024, 768), "Marked Adventures");

	Image ggImage;
	ggImage.loadFromFile("graphics\\gg\\move\\moveTexture.png");
	ggImage.createMaskFromColor(Color(255, 255, 255));

	Texture ggTexture;
	ggTexture.loadFromImage(ggImage);

	Sprite ggSprite;
	ggSprite.setTexture(ggTexture);
	ggSprite.setPosition(50, 20);
	ggSprite.setScale(0.3F, 0.3F);
	ggSprite.setTextureRect(IntRect(0, 0, 256, 256));

	float currentFrame = 0.0F;
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
			currentFrame += 0.038*time;
			if (currentFrame > 20) currentFrame = 0;

			ggSprite.setTextureRect(IntRect(256 * int(currentFrame), 0, 256, 256));
			ggSprite.move(-0.1F*time, 0.0F);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			currentFrame += 0.038*time;
			if (currentFrame > 20) currentFrame = 0;
			ggSprite.setTextureRect(IntRect(256 * int(currentFrame), 256, 256, 256));
			ggSprite.move(0.0F, -0.1F*time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) 
		{
			currentFrame += 0.038*time;
			if (currentFrame > 20) currentFrame = 0;
			ggSprite.setTextureRect(IntRect(256 * int(currentFrame), 512, 256, 256));
			ggSprite.move(0.1F*time, 0.0F); 
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) 
		{
			currentFrame += 0.038*time;
			if (currentFrame > 20) currentFrame = 0;
			ggSprite.setTextureRect(IntRect(256 * int(currentFrame), 768, 256, 256));
			ggSprite.move(0.0F, 0.1F*time);
		}

		window.clear(Color(255, 255, 255));
		window.draw(ggSprite);
		window.display();
	}

	return 0;
}