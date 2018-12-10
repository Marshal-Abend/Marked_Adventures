#pragma once
#include <SFML\Graphics.hpp>
#include <string>


enum Level {
	easy,
	normal,
	hard,
	expert,
	cancel
};

using namespace std;
using namespace sf;

class Map {
	int blockWidth, blockHeight;
	int width, height;
	string* map;

	Image Imonolit;
	Texture Tmonolit;
	Sprite monolit;

	Image Iosoz;
	Texture Tosoz;
	Sprite osoz;

	Image Iwall;
	Texture Twall;
	Sprite wall;

	Image Iway;
	Texture Tway;
	Sprite way;
	float scale;
public:
	Map();
	Map(int width, int height, float scale = 0.35F,Level level = Level::easy, string monolitPath = "graphics\\map\\monolit.png", string osozPath = "graphics\\map\\osoz.png", string wallPath = "graphics\\map\\wall-adapted.png", string wayPath = "graphics\\map\\way.png");

	string *&getMap();

	int getWidth();
	void setWidth(int width);
	int getHeight();
	void setHeight(int height);
	void getSize(int *&widthAndHeight);	//defined array of 2 ints as argument
	void setSize(int width, int height);

	int getBlockWidth();
	void setBlockWidth(int blockWidth);
	int getBlockHeight();
	void setBlockHeight(int blockHeight);

	void getBlock(int *&widthAndHeight);	//defined array of 2 ints as argument
	void setBlock(int width, int height);

	float getScale();
	void setScale(float scale);

	string *&generateMap(Level level);

	void draw(RenderWindow &window);

	void clear();
};
