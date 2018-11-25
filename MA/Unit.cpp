#include "Unit.h"
//Unit
Unit::Unit() {
	Unit::pointX = 0.0;
	Unit::pointY = 0.0;
	Unit::width = 0.0;
	Unit::height = 0.0;
	Unit::directionX = 0.0F;
	Unit::directionY = 0.0F;
	Unit::speed = 0.0F;
	Unit::side = Direction::disabled;
}

Unit::Unit(
	string filePath,
	int x,
	int y,
	int width,
	int height,
	int positionX,
	int positionY,
	float speed,
	Color mask,
	int direction,
	float scale
)
{
	Unit::filePath = filePath;
	Unit::pointX = x;
	Unit::pointY = y;
	Unit::width = width;
	Unit::height = height;
	Unit::side = direction;
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
	Unit::sprite.setPosition((float)Unit::positionX, (float)Unit::positionY);
	Unit::sprite.setScale(Unit::scale, Unit::scale);
	Unit::sprite.setTextureRect(IntRect(Unit::pointX, Unit::pointY, Unit::width, Unit::height));
}

int Unit::getPositionX()
{
	return Unit::positionX;
}

void Unit::setPosisionX(int positionX)
{
	Unit::positionX = positionX;
}

int Unit::getPositionY()
{
	return Unit::positionY;
}

void Unit::setPositionY(int positionY)
{
	Unit::positionY = positionY;
}

void Unit::getPosition(int *&positionXY)
{
	positionXY[0] = Unit::directionX;
	positionXY[1] = Unit::directionY;
}

void Unit::setPosition(int positionX, int positionY)
{
	Unit::setPosisionX(positionX);
	Unit::setPositionY(positionY);
}


int Unit::getPointX()
{
	return Unit::pointX;
}

void Unit::setPointX(int pointX)
{
	Unit::pointX = pointX;
}

int Unit::getPointY()
{
	return Unit::pointY;
}

void Unit::setPointY(int pointY)
{
	Unit::pointY = pointY;
}

//defined array of 2 ints as argument
void Unit::getPoint(int *&pointXY)
{
	pointXY[0] = Unit::pointX;
	pointXY[1] = Unit::pointY;
}

void Unit::setPoint(int pointX, int pointY)
{
	Unit::setPointX(pointX);
	Unit::setPointY(pointY);
}

int Unit::getWidth()
{
	return Unit::width;
}

void Unit::setWidth(int width)
{
	Unit::width = width;
}

int Unit::getHeight()
{
	return Unit::height;
}

void Unit::setHeight(int height)
{
	Unit::height = height;
}

//defined array of 2 ints as argument
void Unit::getSize(int *&widthAndHeight)
{
	widthAndHeight[0] = Unit::width;
	widthAndHeight[1] = Unit::height;
}

void Unit::setSize(int width, int height)
{
	Unit::setWidth(width);
	Unit::setHeight(height);
}

//defined array of 4 ints as argument(X and Y are points, Width and Height are measures)
void Unit::getRect(int *&XYWH)
{
	XYWH[0] = Unit::pointX;
	XYWH[1] = Unit::pointY;
	XYWH[2] = Unit::width;
	XYWH[3] = Unit::height;
}

void Unit::setRect(int pointX, int pointY, int width, int height)
{
	Unit::setPoint(pointX, pointY);
	Unit::setSize(width, height);
}

float Unit::getScale()
{
	return Unit::scale;
}

void Unit::setScale(float scale)
{
	Unit::scale = scale;
}

float Unit::getDirectionX()
{
	return Unit::directionX;
}

void Unit::setDirectionX(float directionX)
{
	Unit::directionX = directionX;
}

float Unit::getDirextionY()
{
	return Unit::directionY;
}

void Unit::setDirectionY(float directionY)
{
	Unit::directionY = directionY;
}

//defined array of 2 ints as argument
void Unit::getDirection(float *&direction)
{
	direction[0] = directionX;
	direction[1] = directionY;
}

void Unit::setDirection(float directionX, float directionY)
{
	Unit::setDirectionX(directionX);
	Unit::setDirectionY(directionY);
}

float Unit::getSpeed()
{
	return Unit::speed;
}

void Unit::setSpeed(float speed)
{
	Unit::speed = speed;
}

int Unit::getSide()
{
	return Unit::side;
}

void Unit::setSide(int side)
{
	Unit::side = side;
}

//load Image->Texture->Sprite
void Unit::loadITS(string filePath, int x, int y, int width, int height, int positionX, int positionY, float speed, Color mask, int direction, float scale)
{
	Unit::filePath = filePath;
	Unit::pointX = x;
	Unit::pointY = y;
	Unit::width = width;
	Unit::height = height;
	Unit::side = direction;
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
	Unit::sprite.setPosition((float)Unit::positionX, (float)Unit::positionY);
	Unit::sprite.setScale(Unit::scale, Unit::scale);
	Unit::sprite.setTextureRect(IntRect(Unit::pointX, Unit::pointY, Unit::width, Unit::height));
}

Sprite &Unit::getSprite()
{
	return Unit::sprite;
}

void Unit::setSprite(Sprite &sprite)
{
	Unit::sprite = sprite;
}

void Unit::draw(RenderWindow &window)
{
	window.draw(Unit::getSprite());
}

//Hero
Hero::Hero() : Unit::Unit()
{
	Hero::health = 0;
	Hero::damage = 0;
}

Hero::Hero(
	string filePath,
	int x,
	int y,
	int width,
	int height,
	int positionX,
	int positionY,
	float speed,
	Color mask,
	int direction,
	float scale) 
	:
	Unit::Unit(
		filePath,
		x,
		y,
		width,
		height,
		positionX,
		positionY,
		speed,
		mask,
		direction,
		scale)
{
	
}

int Hero::getHealth()
{
	return Hero::health;
}

void Hero::setHealth(int health)
{
	Hero::health = health;
}

int Hero::getDamage()
{
	return Hero::damage;
}

void Hero::setDamage(int damage)
{
	Hero::damage = damage;
}

void Hero::create(int health, int damage)
{
	setHealth(health);
	setDamage(damage);
}

