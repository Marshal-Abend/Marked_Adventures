#include "Unit.h"
#include "Map.h"
#include "End.h"

//Unit
Unit::Unit() :animation(*this, 20) {
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
	float positionX,
	float positionY,
	float speed,
	Color mask,
	int direction,
	float scale
) :animation(*this, 20)
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

Unit::Unit(const Unit &unit)
{
	animation = unit.animation;
	filePath = unit.filePath;
	pointX = unit.pointX;
	pointY = unit.pointY;
	width = unit.width;
	height = unit.height;
	side = unit.side;
	positionX = unit.positionX;
	positionY = unit.positionY;
	scale = unit.scale;
	directionX = unit.directionX;
	directionY = unit.directionY;
	mask = unit.mask;
	speed = unit.speed;
	state = unit.state;
	texture = unit.texture;
	image = unit.image;
}

Unit &Unit::operator=(const Unit& unit)
{
	animation = unit.animation;
	filePath = unit.filePath;
	pointX = unit.pointX;
	pointY = unit.pointY;
	width = unit.width;
	height = unit.height;
	side = unit.side;
	positionX = unit.positionX;
	positionY = unit.positionY;
	scale = unit.scale;
	directionX = unit.directionX;
	directionY = unit.directionY;
	mask = unit.mask;
	speed = unit.speed;
	state = unit.state;
	texture = unit.texture;
	image = unit.image;
	return *this;
}

float Unit::getPositionX()
{
	return Unit::positionX;
}

void Unit::setPosisionX(float positionX)
{
	Unit::setState();
	Unit::positionX = positionX;
}

float Unit::getPositionY()
{
	return Unit::positionY;
}

void Unit::setPositionY(float positionY)
{
	Unit::setState();
	Unit::positionY = positionY;
}

void Unit::getPosition(float *&positionXY)
{
	positionXY[0] = Unit::directionX;
	positionXY[1] = Unit::directionY;
}

void Unit::setPosition(float positionX, float positionY)
{
	Unit::setState();
	Unit::setPosisionX(positionX);
	Unit::setPositionY(positionY);
}


int Unit::getPointX()
{
	return Unit::pointX;
}

void Unit::setPointX(int pointX)
{
	Unit::setState();
	Unit::pointX = pointX;
}

int Unit::getPointY()
{
	return Unit::pointY;
}

void Unit::setPointY(int pointY)
{
	Unit::setState();
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
	Unit::setState();
	Unit::setPointX(pointX);
	Unit::setPointY(pointY);
}

int Unit::getWidth()
{
	return Unit::width;
}

void Unit::setWidth(int width)
{
	Unit::setState();
	Unit::width = width;
}

int Unit::getHeight()
{
	return Unit::height;
}

void Unit::setHeight(int height)
{
	Unit::setState();
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
	Unit::setState();
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
	Unit::setState();
	Unit::setPoint(pointX, pointY);
	Unit::setSize(width, height);
}

float Unit::getScale()
{
	return Unit::scale;
}

void Unit::setScale(float scale)
{
	Unit::setState();
	Unit::scale = scale;
}

float Unit::getDirectionX()
{
	return Unit::directionX;
}

void Unit::setDirectionX(float directionX)
{
	Unit::setState();
	Unit::directionX = directionX;
}

float Unit::getDirextionY()
{
	return Unit::directionY;
}

void Unit::setDirectionY(float directionY)
{
	Unit::setState();
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
	Unit::setState();
	Unit::setDirectionX(directionX);
	Unit::setDirectionY(directionY);
}

float Unit::getSpeed()
{
	return Unit::speed;
}

void Unit::setSpeed(float speed)
{
	Unit::setState();
	Unit::speed = speed;
}

int Unit::getSide()
{
	return Unit::side;
}

void Unit::setSide(int side)
{
	Unit::setState();
	Unit::side = side;
}

Direction Unit::move(Direction side)
{
	switch (side)
	{

	case Direction::left:
		Unit::setPosition(Unit::getPositionX() - speed*Unit::scale, Unit::getPositionY());
		break;

	case Direction::top:
		Unit::setPosition(Unit::getPositionX(), Unit::getPositionY() - speed*Unit::scale);
		break;

	case Direction::right:
		Unit::setPosition(Unit::getPositionX() + speed*Unit::scale, Unit::getPositionY());
		break;

	case Direction::bottom:
		Unit::setPosition(Unit::getPositionX(), Unit::getPositionY() + speed*Unit::scale);
		break;
	default:
		break;
	}
	return side;
}

//AABB collision
void  Unit::collision(Unit &unit, Map &map)
{
	static Unit previousState = unit;
	static string* lmap;
	lmap = map.getMap();
	for (int i = 0; i < map.getHeight(); i++)
	{
		for (int l = 0; l < map.getWidth(); l++)
		{
			switch (lmap[i][l])
			{
			case '#':
			{
				float deltaX = (unit.getPositionX() + unit.getWidth()* unit.getScale()) - (float)(i * map.getBlockWidth() + map.getBlockWidth()) * unit.getScale();
				float deltaY = (unit.getPositionY() + unit.getHeight()* unit.getScale()) - (float)(l * map.getBlockHeight() + map.getBlockHeight()) * unit.getScale();
				float colX = abs(deltaX) - (map.getBlockWidth() - 32.0F)* unit.getScale();
				float colY = abs(deltaY) - (map.getBlockHeight() - 32.0F)* unit.getScale();
				if (colX < 0.0F && colY < 0.0F)
				{
					unit = previousState;
					return;
				}
				break;
			}

			case 'O':
			{
				float deltaX = (unit.getPositionX() + unit.getWidth()* unit.getScale()) - (float)(i * map.getBlockWidth() + map.getBlockWidth()) * unit.getScale();
				float deltaY = (unit.getPositionY() + unit.getHeight()* unit.getScale()) - (float)(l * map.getBlockHeight() + map.getBlockHeight()) * unit.getScale();
				float colX = abs(deltaX) - (map.getBlockWidth() - 32.0F)* unit.getScale();
				float colY = abs(deltaY) - (map.getBlockHeight() - 32.0F)* unit.getScale();
				if (colX < 0.0F && colY < 0.0F)
				{
					gState = GameState::OMenu;
					return;
				}
				break;
			}

			case 'M':
			{
				float deltaX = (unit.getPositionX() + unit.getWidth()* unit.getScale()) - (float)(i * map.getBlockWidth() + map.getBlockWidth()) * unit.getScale();
				float deltaY = (unit.getPositionY() + unit.getHeight()* unit.getScale()) - (float)(l * map.getBlockHeight() + map.getBlockHeight()) * unit.getScale();
				float colX = abs(deltaX) - (map.getBlockWidth() - 32.0F)* unit.getScale();
				float colY = abs(deltaY) - (map.getBlockHeight() - 32.0F)* unit.getScale();
				if (colX < 0.0F && colY < 0.0F)
				{
					gState = GameState::MMenu;
					return;
				}
				break;
			}
			default:
				break;
			}
		}

	}
	previousState = unit;
}

void Unit::animate(Direction side)
{
	animation.animate(side);
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
	Unit::setState();

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
	Unit::setState();
	Unit::sprite = sprite;
}

void Unit::draw(RenderWindow &window)
{
	/*	if (Unit::state == State::changed)
		{
			Unit::update();
			Unit::state = State::fine;
		}*/
	Unit::update();
	window.draw(Unit::sprite);
}

State Unit::getState()
{
	return Unit::state;
}

void Unit::setState(State state)
{
	Unit::state = state;
}

void Unit::switchState()
{
	if (Unit::state == State::changed)
	{
		Unit::state = State::fine;
	}
	else
	{
		Unit::state = State::changed;
	}
}

void Unit::update()
{
	Unit::sprite.setPosition(Unit::positionX, Unit::positionY);
	Unit::sprite.setTextureRect(IntRect(Unit::pointX, Unit::pointY, Unit::width, Unit::height));
	Unit::sprite.setScale(Unit::scale, Unit::scale);
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



//Animation

Animation::Animation()
{
	target = NULL;
	totalFrames = 0;
	currentFrame = 0.0F;
	frameWidth = 0;
	frameHeight = 0;
	speed = 0.0F;
	frameOffset = 0.0F;
}

Animation::Animation(Unit &unit, int totalFrames, float currentFrame, int frameWidth, int frameHeight, float speed, float frameOffset)
{
	Animation::target = &unit;
	Animation::totalFrames = totalFrames;
	Animation::currentFrame = currentFrame;
	Animation::frameWidth = frameWidth;
	Animation::frameHeight = frameHeight;
	Animation::speed = speed;
	Animation::frameOffset = frameOffset;
}

void Animation::animate(Direction side)
{
	static Direction prevSide = side;
	switch (side)
	{
	case Direction::left:
		if (side == prevSide && Animation::currentFrame < Animation::totalFrames - 1)
		{
			Animation::currentFrame += Animation::speed;

		}
		else
		{
			Animation::currentFrame = 0.F;
			prevSide = Direction::left;
		}
		break;
	case Direction::top:
		if (side == prevSide && Animation::currentFrame < Animation::totalFrames - 1)
		{
			Animation::currentFrame += Animation::speed;
		}
		else
		{
			Animation::currentFrame = 0.F;
			prevSide = Direction::top;
		}
		break;
	case Direction::right:
		if (side == prevSide && Animation::currentFrame < Animation::totalFrames - 1)
		{
			Animation::currentFrame += Animation::speed;
		}
		else
		{
			Animation::currentFrame = 0.F;
			prevSide = Direction::right;
		}
		break;
	case Direction::bottom:
		if (side == prevSide && Animation::currentFrame < Animation::totalFrames - 1)
		{
			Animation::currentFrame += Animation::speed;
		}
		else
		{
			Animation::currentFrame = 0.F;
			prevSide = Direction::bottom;
		}
		break;
	default:
		break;
	}
	Animation::target->setRect(target->getWidth()*(int)currentFrame, target->getHeight()*side, target->getWidth(), target->getHeight());
}

Animation &Animation::operator=(const Animation& obj)
{
	Animation::totalFrames = obj.totalFrames;
	Animation::currentFrame = obj.currentFrame;
	Animation::frameWidth = obj.frameWidth;
	Animation::frameHeight = obj.frameHeight;
	Animation::speed = obj.speed;
	Animation::frameOffset = obj.frameOffset;
	return *this;
}
