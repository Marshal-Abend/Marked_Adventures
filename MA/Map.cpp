#include "Map.h"
#include "Unit.h"
#include <vector>
#include <iostream>

using namespace std;

Map::Map()
{
	Map::blockWidth = 0;
	Map::blockHeight = 0;
	Map::scale = 0.0F;
}

Map::Map(int blockWidth, int blockHeight, float scale, Level level, string monolitPath, string osozPath, string wallPath, string wayPath)
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



	Map::map = Map::generateMap(level);
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
	Map::way.setScale(Map::scale, Map::scale);
	Map::wall.setScale(Map::scale, Map::scale);
	Map::osoz.setScale(Map::scale, Map::scale);
	Map::monolit.setScale(Map::scale, Map::scale);
}

void Map::clear()
{
	delete[] Map::map;
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

bool isVisited(Pair pair, vector<Pair> &visited)
{
	for (int n = visited.size() - 1; n >= 0; n--)
	{
		if (visited[n] == pair)
		{
			return true;
		}
	}
	return false;
}

bool isVisited(Direction pair, vector<Direction> &visited)
{
	for (int n = visited.size() - 1; n >= 0; n--)
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

void addVisited(Direction pair, vector<Direction> &visited)
{
	visited.push_back(pair);
}


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
	else if (currentHeight >= totalHeight - 1)
	{
		return true;
	}
	else if (currentWidth >= totalWidth - 1)
	{
		return true;
	}

	Pair pair(currentHeight, currentWidth);
	if (isVisited(pair, vect))return true;
	return false;
}

Direction randSide(vector<Direction> &random)
{
	srand((unsigned int)rand());
	Direction pureRandom = Direction(rand() % 4);


	if (random.size() == 4)
	{
		random.clear();
	}
	while (isVisited(pureRandom, random))
	{
		pureRandom = Direction(rand() % 4);

	}

	switch (pureRandom)
	{
	case Direction::left:
		addVisited(Direction::left, random);
		return Direction::left;
		break;

	case Direction::top:
		addVisited(Direction::top, random);
		return Direction::top;
		break;

	case Direction::right:
		addVisited(Direction::right, random);
		return Direction::right;
		break;

	case Direction::bottom:
		addVisited(Direction::bottom, random);
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
		return Pair(-1, -1);
		break;
	}

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


bool fullStuck(string *&map, Direction side, Pair pair)
{
	unsigned char block = 0;
	if (map[pair.getHeight() - 1][pair.getWidth()] == '#') block++;
	if (map[pair.getHeight()][pair.getWidth() - 1] == '#') block++;
	if (map[pair.getHeight() + 1][pair.getWidth()] == '#') block++;
	if (map[pair.getHeight()][pair.getWidth() + 1] == '#') block++;
	if (block == 3) return true;
	return false;
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

string *&Map::generateMap(Level level)
{
	srand((unsigned int)rand());
	int base;
	switch (level)
	{
	case Level::easy:
		base = 10;
		break;
	case Level::normal:
		base = 18;
		break;
	case Level::hard:
		base = 28;
		break;
	case Level::expert:
		base = 50;
		break;
	default:
		break;
	}
	Map::height = base + rand() % 10;
	if (Map::height % 2 == 0)
	{
		Map::height--;
	}
	Map::width = base + rand() % 10;
	if (Map::width % 2 == 0)
	{
		Map::width--;
	}
	static string *mapl;
	mapl = new string[height];
	mapInit(mapl, Map::height, Map::width);
	vector<Pair> vect;
	vector<Direction> random;
	vector<Pair> visited;
	vector<Pair> stucked;
	mapl[1][1] = ' ';
	vect.push_back(Pair(1, 1));
	Pair noWay = vect[vect.size() - 1];
	int thinkTwice = 4;
	while (!vect.empty())
	{
		Direction side = randSide(random);
		Pair pair = getNextPair(vect[vect.size() - 1], side);
		if (isEnd(Map::height, Map::width, pair.getHeight(), pair.getWidth(), vect) || isVisited(pair, visited))
		{
			if (thinkTwice > 0)
			{
				thinkTwice--;
				continue;
			}
			else
			{
				if (vect.empty())
				{
					break;
				}
				else
				{
					addVisited(vect[vect.size() - 1], visited);
					cout << "pop " << vect.size() << "\t" << vect[vect.size() - 1].getHeight() << "   " << vect[vect.size() - 1].getWidth() << endl;
					if (fullStuck(mapl, side, vect[vect.size() - 1]))
					{
						addVisited(vect[vect.size() - 1], stucked);
					}
					vect.pop_back();
					if (vect.empty())
					{
						break;
					}
					noWay = vect[vect.size() - 1];

					thinkTwice = 4;
				}

			}
		}
		else
		{
			drawWay(noWay, side, mapl);
			cout << "add " << vect.size() << "\t" << pair.getHeight() << "   " << pair.getWidth() << endl;
			random.clear();
			noWay = pair;
			addVisited(pair, vect);
			thinkTwice = 4;
		}
	}


	int randomEnds;
	if (stucked.size() > 2)
	{
		randomEnds = rand() % stucked.size();
		while (stucked[randomEnds].getHeight() < Map::height / 2 && stucked[randomEnds].getWidth() < Map::width / 2)
		{
			randomEnds = rand() % stucked.size();
		}
		mapl[stucked[randomEnds].getHeight()][stucked[randomEnds].getWidth()] = 'O';
	}
	else
	{
		randomEnds = rand() % visited.size();
		while (visited[randomEnds].getHeight() < Map::height / 2 && visited[randomEnds].getWidth() < Map::width / 2)
		{
			randomEnds = rand() % visited.size();
		}
		mapl[visited[randomEnds].getHeight()][visited[randomEnds].getWidth()] = 'O';
	}






	int randomSecondEnds;
	if (stucked.size() > 2)
	{
		randomSecondEnds = rand() % stucked.size();
		while (randomEnds == randomSecondEnds || stucked[randomSecondEnds].getHeight() < Map::height / 2 && stucked[randomSecondEnds].getWidth() < Map::width / 2)
		{
			randomSecondEnds = rand() % stucked.size();
		}
		mapl[stucked[randomSecondEnds].getHeight()][stucked[randomSecondEnds].getWidth()] = 'M';
	}
	else
	{
		randomSecondEnds = rand() % visited.size();
		while (randomEnds == randomSecondEnds)
		{
			randomSecondEnds = rand() % visited.size();
		}
		mapl[visited[randomSecondEnds].getHeight()][visited[randomSecondEnds].getWidth()] = 'M';
	}


	//setTemplate(map, height, width);
	return mapl;
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