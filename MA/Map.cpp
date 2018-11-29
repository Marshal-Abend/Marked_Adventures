#include "Map.h"
#include "Unit.h"
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


string *&Map::getMap()
{
	return Map::map;
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

int Map::getBlockWidth()
{
	return Map::blockWidth;
}

void Map::setBlockWidth(int blockWidth)
{
	Map::blockWidth = blockWidth;
}

int Map::getBlockHeight()
{
	return Map::blockHeight;
}

void Map::setBlockHeight(int blockHeight)
{
	Map::blockHeight = blockHeight;
}

//defined array of 2 ints as argument
void Map::getBlock(int *&widthAndHeight)
{
	widthAndHeight[0] = Map::blockWidth;
	widthAndHeight[1] = Map::blockHeight;
}

void Map::setBlock(int width, int height)
{
	setBlockWidth(width);
	setBlockHeight(height);
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
	int height;
	int width;

public:
	Pair()
	{
		width = 0;
		height = 0;
	}

	Pair(int height, int width)
	{
		Pair::height = height;
		Pair::width = width;
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
		return false;
	}
};

bool isEnd(int totalHeight, int totalWidth, int currentHeight, int currentWidth, vector<Pair> &vect)
{
	if (currentHeight <= 0)
	{
		return true;
	}
	else if (currentWidth <= 0)
	{
		return true;
	}
	else if (currentHeight >= totalHeight-1)
	{
		return true;
	}
	else if (currentWidth >= totalWidth-1)
	{
		return true;
	}

	Pair pair(currentHeight, currentWidth);
	for (int n = vect.size() - 1; n > 0; n--)
	{
		if (vect[n] == pair)
		{
			return true;
		}
	}
	return false;
}

Direction randSide()
{
	switch (1 + rand() % 4)
	{
	case Direction::left:
		return Direction::left;
		break;

	case Direction::top:
		return Direction::top;
		break;

	case Direction::right:
		return Direction::right;
		break;

	case Direction::bottom:
		return Direction::bottom;
		break;

	default:
		return Direction::disabled;
		break;
	}
}

Pair getNextPair(Pair prevPair, Direction direction)
{
	switch (direction)
	{
	case Direction::left:
	{
		Pair newPair(prevPair.getHeight(), prevPair.getWidth() - 2);
		return newPair;
		break;
	}

	case Direction::top:
	{
		Pair newPair(prevPair.getHeight() - 2, prevPair.getWidth());
		return newPair;
		break;
	}

	case Direction::right:
	{
		Pair newPair(prevPair.getHeight(), prevPair.getWidth() + 2);
		return newPair;
		break;
	}

	case Direction::bottom:
	{
		Pair newPair(prevPair.getHeight() + 2, prevPair.getWidth());
		return newPair;
		break;
	}

	default:
		break;
	}
	return Pair(-1, -1);
}

void mapInit(string *&map, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		map[i].assign(width, '#');
	}
}

void drawWay(Pair newWay, Direction side, string *&map)
{
	switch (side)
	{

	case Direction::left:
		map[newWay.getHeight()][newWay.getWidth() - 1] = ' ';
		map[newWay.getHeight()][newWay.getWidth() - 2] = ' ';
		break;

	case Direction::top:
		map[newWay.getHeight() - 1][newWay.getWidth()] = ' ';
		map[newWay.getHeight() - 2][newWay.getWidth()] = ' ';
		break;

	case Direction::right:
		map[newWay.getHeight()][newWay.getWidth() + 1] = ' ';
		map[newWay.getHeight()][newWay.getWidth() + 2] = ' ';
		break;

	case Direction::bottom:
		map[newWay.getHeight() + 1][newWay.getWidth()] = ' ';
		map[newWay.getHeight() + 2][newWay.getWidth()] = ' ';
		break;

	default:
		break;
	}

}

bool isVisited(Pair pair, vector<Pair> &visited)
{
	for (int n = visited.size() - 1; n > 0; n--)
	{
		if (visited[n] == pair)
		{
			return true;
		}
	}
	return false;
}

void addVisited(Pair pair, vector<Pair> &visited)
{
	visited.push_back(pair);
}

void setTemplate(string *&map, int height, int width)
{
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
	srand(time(0));
	Map::height = 10 + rand() % 25;
	if (Map::height % 2 == 0)
	{
		Map::height--;
	}
	Map::width = 10 + rand() % 25;
	if (Map::width % 2 == 0)
	{
		Map::width--;
	}
	static string *map = new string[height];
	mapInit(map, Map::height, Map::width);
	vector<Pair> vect;
	vector<Pair> visited;
	vect.push_back(Pair(1, 1));
	while (!vect.empty())
	{
		int n = vect.size();
		int z = visited.size();
		Direction side = randSide();
		Pair pair = getNextPair(vect[vect.size() - 1], side);
		static Pair noWay = vect[vect.size() - 1];
		static int thinkTwice = 10;
		if (isEnd(Map::height, Map::width, pair.getHeight(), pair.getWidth(), vect))
		{
			if (noWay.getHeight() == 0 && noWay.getWidth() == 9)
			{
				int a = 9;
			}
			if (thinkTwice > 0)
			{
				thinkTwice--;
				continue;
			}
			else
			{
				addVisited(vect[vect.size() - 1], visited);
				vect.pop_back();
				if (vect.empty())
				{
					break;
				}
				noWay = vect[vect.size() - 1];
				thinkTwice = 10;
			}
		}
		else
		{
			if (isVisited(pair, visited) || noWay == pair)
			{
				continue;
			}

			drawWay(noWay, side, map);
			noWay = pair;
			vect.push_back(pair);
			thinkTwice = 10;
		}
	}

	//setTemplate(map, height, width);
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