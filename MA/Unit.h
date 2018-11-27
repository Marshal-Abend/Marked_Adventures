#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

enum State {
	fine,
	changed
};

enum  Direction {
	disabled,
	left,
	top,
	right,
	bottom
};

class Unit {
	float positionX, positionY;
	int pointX, pointY, width, height;
	float scale;
	float directionX, directionY;
	float speed;
	int side;
	Color mask;
	string filePath;
	Image image;
	Texture texture;
	Sprite sprite;
	State state;
public:
	Unit(
		string filePath,
		int x,
		int y,
		int width,
		int height,
		float positionX = 0.0F,
		float positionY = 0.0F,
		float speed = 0.0F,
		Color mask = Color(255, 255, 255),
		int direction = Direction::disabled,
		float scale = 1.0F
	);
	Unit();

	float getPositionX();
	void setPosisionX(float positionX);
	float getPositionY();
	void setPositionY(float positionY);
	void getPosition(float *&positionXY);	//defined array of 2 ints as argument
	void setPosition(float positionX, float positionY);

	int getPointX();
	void setPointX(int pointX);
	int getPointY();
	void setPointY(int pointY);
	void getPoint(int *&pointXY);	//defined array of 2 ints as argument
	void setPoint(int pointX, int pointY);
	int getWidth();
	void setWidth(int width);
	int getHeight();
	void setHeight(int height);
	void getSize(int *&widthAndHeight);	//defined array of 2 ints as argument
	void setSize(int width, int height);
	void getRect(int *&XYWH);	//defined array of 4 ints as argument(X and Y are points, Width and Height are measures)
	void setRect(int pointX, int pointY, int width, int height);

	float getScale();
	void setScale(float scale);

	float getDirectionX();
	void setDirectionX(float directionX);
	float getDirextionY();
	void setDirectionY(float directionY);
	void getDirection(float *&direction); //defined array of 2 ints as argument
	void setDirection(float directionX, float directionY);

	float getSpeed();
	void setSpeed(float speed);

	int getSide();
	void setSide(int side);
	
	void move(int side, float time);



	//load Image->Texture->Sprite
	void loadITS(string filePath, int x, int y, int width, int height, int positionX, int positionY, float speed, Color mask, int direction, float scale);
	Sprite &getSprite();
	void setSprite(Sprite &sprite);
	void draw(RenderWindow &window);

	State getState();
	void setState(State state = State::changed);
	void switchState();

	void update();
};

class Hero : public virtual Unit {
	int health;
	int damage;
public:
	Hero();
	Hero(
		string filePath,
		int x,
		int y,
		int width,
		int height,
		int positionX = 0,
		int positionY = 0,
		float speed = 0.0F,
		Color mask = Color(255, 255, 255),
		int direction = Direction::disabled,
		float scale = 1.0F
	);
	int getHealth();
	void setHealth(int health);
	int getDamage();
	void setDamage(int damage);
	void create(int health, int damage);
};
