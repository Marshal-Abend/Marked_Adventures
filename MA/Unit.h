#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

enum  Direction {
	disabled,
	left,
	top,
	right,
	bottom
};

class Unit {
	int positionX, positionY;
	int pointX, pointY, width, height;
	float scale;
	float directionX, directionY, speed;
	int direction;
	Color mask;
	string filePath;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Unit(string filePath, int x, int y, int width, int height, int positionX, int positionY, float speed, Color mask, int direction, float scale);
	Unit();
	

};

class Hero : virtual Unit {

	Hero() : Unit() {};
};
