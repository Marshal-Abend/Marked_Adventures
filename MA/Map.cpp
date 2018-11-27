#include "Map.h"
#include <vector>

Map::Map()
{
	Map::blockWidth = 0;
	Map::blockHeight = 0;
	Map::scale = 0.0F;
}

Map::Map(int blockWidth, int blockHeight, string monolitPath, string osozPath, string wallPath, string wayPath, float scale)
{
	Map::blockWidth = blockWidth;
	Map::blockHeight = blockHeight;
	Map::scale = scale;


	Imonolit.loadFromFile(monolitPath);
	Tmonolit.loadFromImage(Imonolit);
	Map::monolit.setTexture(Tmonolit);
	Map::monolit.setScale(Map::scale, Map::scale);

	static Image Iosoz;
	static Texture Tosoz;
	Iosoz.loadFromFile(osozPath);
	Tosoz.loadFromImage(Iosoz);
	Map::osoz.setTexture(Tosoz);
	Map::osoz.setScale(Map::scale, Map::scale);

	static Image Iwall;
	static Texture Twall;
	Iwall.loadFromFile(wallPath);
	Twall.loadFromImage(Iwall);
	Map::wall.setTexture(Twall);
	Map::wall.setScale(Map::scale, Map::scale);

	static Image Iway;
	static Texture Tway;
	Iway.loadFromFile(wayPath);
	Tway.loadFromImage(Iway);
	Map::way.setTexture(Tway);
	Map::way.setScale(Map::scale, Map::scale);



	Map::map = Map::generateMap();
}


int Map::getWidth()
{
	return Map::width;
}

void Map::setWidth(int width)
{
	Map::width = width;
}

int Map::getHeight()
{
	return Map::height;
}

void Map::setHeight(int height)
{
	Map::height = height;
}

void Map::getSize(int *&widthAndHeight)	//defined array of 2 ints as argumen
{
	widthAndHeight[0] = Map::width;
	widthAndHeight[1] = Map::height;
}

void Map::setSize(int width, int height)
{
	Map::setWidth(width);
	Map::setHeight(height);
}

float Map::getScale()
{
	return Map::scale;
}

void Map::setScale(float scale)
{
	Map::scale = scale;
}


class Pair {
	int width;
	int height;
public:
	Pair()
	{
		width = 0;
		height = 0;
	}

	Pair(int width, int height)
	{
		Pair::width = width;
		Pair::height = height;
	}

	int getWidth()
	{
		return width;
	}

	void setWidth(int width)
	{
		Pair::width = width;
	}

	int getHeight()
	{
		return height;
	}

	void setHeight(int height)
	{
		Pair::height = height;
	}


	void set(int width, int height)
	{
		setWidth(width);
		setHeight(height);
	}

	bool operator==(Pair second)
	{
		if (this->width == second.width && this->height == second.height)
		{
			return true;
		}
	}
};

bool isEnd(int totalWidth, int totalHeight, int currentWidth, int currentHeight, vector<Pair> &vect)
{
	if (currentWidth < 0)
	{
		return true;
	}
	else if (currentHeight < 0)
	{
		return true;
	}
	else if (currentWidth >= totalWidth)
	{
		return true;
	}
	else if (currentHeight >= totalHeight)
	{
		return true;
	}

	Pair pair(currentWidth, currentHeight);
	for (int n = vect.size(); n > 0; n--)
	{
		if (vect[n] == pair)
		{
			return true;
		}
	}
	return false;
}



void mapInit(string *&map, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		map[i].assign(width, ' ');
	}

	for (int i = 0; i < width; i++)
	{
		map[0][i] = '#';
	}

	for (int i = 0; i < width; i++)
	{
		map[height - 1][i] = '#';
	}

	for (int i = 0; i < height; i++)
	{
		map[i][0] = '#';
	}

	for (int i = 0; i < height; i++)
	{
		map[i][width - 1] = '#';
	}
}

string *&Map::generateMap()
{
	Map::width = 5 + rand() % 25;
	Map::height = 5 + rand() % 25;
	static string *map = new string[height];
	mapInit(map, Map::width, Map::height);
	vector<Pair> vect;
	vect.push_back(Pair(width / 2, height / 2));
	map[7][7] = 'O';
	map[9][9] = 'M';
	return map;
}

void Map::draw(RenderWindow &window)
{
	for (int i = 0; i < Map::height; i++)
	{
		for (int l = 0; l < Map::width; l++)
		{
			switch (Map::map[i][l])
			{
			case '#':
				Map::wall.setPosition((float)i*(float)Map::blockWidth*Map::scale, (float)l*(float)Map::blockHeight*Map::scale);
				window.draw(Map::wall);
				break;
			case ' ':
				Map::way.setPosition((float)i*(float)Map::blockWidth*Map::scale, (float)l*(float)Map::blockHeight*Map::scale);
				window.draw(Map::way);
				break;
			case 'M':
				Map::monolit.setPosition((float)i*(float)Map::blockWidth*Map::scale, (float)l*(float)Map::blockHeight*Map::scale);
				window.draw(Map::monolit);
				break;
			case 'O':
				Map::osoz.setPosition((float)i*(float)Map::blockWidth*Map::scale, (float)l*(float)Map::blockHeight*Map::scale);
				window.draw(Map::osoz);
			default:
				break;
			}


		}

	}
}