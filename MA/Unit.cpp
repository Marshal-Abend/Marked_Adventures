#include "Unit.h"

Unit::Unit() {
	Unit::pointX = 0.0F;
	Unit::pointY = 0.0F;
	Unit::width = 0.0F;
	Unit::height = 0.0F;
	Unit::directionX = 0.0F;
	Unit::directionY = 0.0F;
	Unit::speed = 0.0F;
	Unit::direction = Direction::disabled;
}

Unit::Unit(string filePath, int x, int y, int width, int height, int positionX = 0, int positionY = 0, float speed = 0.0F, Color mask = Color(255, 255, 255), int direction = Direction::disabled, float scale = 1.0F)
{
	Unit::filePath = filePath;
	Unit::pointX = x;
	Unit::pointY = y;
	Unit::width = width;
	Unit::height = height;
	Unit::direction = direction;
	Unit::positionX = positionX;
	Unit::positionY = positionY;
	Unit::scale = scale;
	Unit::directionX = 0.0F;
	Unit::directionY = 0.0F;
	Unit::mask = mask;

	Unit::image.loadFromFile(Unit::filePath);
	Unit::image.createMaskFromColor(Unit::mask);

	Unit::texture.loadFromImage(Unit::image);

	Unit::sprite.setTexture(Unit::texture);
	Unit::sprite.setPosition(Unit::positionX, Unit::positionY);
	Unit::sprite.setScale(Unit::scale, Unit::scale);
	Unit::sprite.setTextureRect(IntRect(Unit::pointX, Unit::pointY, Unit::width, Unit::height));
}