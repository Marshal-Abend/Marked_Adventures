#pragma once
#include "Unit.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <sfeMovie\Movie.hpp>

#define DURATION_BLIND 64.00F
#define DURATION_HD 81.00F;
#define DURATION_IMMORTALITY 60.00F
#define DURATION_MONEY	82.00F
#define DURATION_POWER 56.00F
#define DURATION_WELCOME 65.00F
#define DURATION_TRUE 112.00F

#define VIDEO_BLIND "ends\\blind.mp4"
#define VIDEO_HD "ends\\hd.mp4"
#define VIDEO_IMMORTALITY "ends\\immortality.mp4"
#define VIDEO_MONEY	"ends\\money.mp4"
#define VIDEO_POWER "ends\\power.mp4"
#define VIDEO_WELCOME "ends\\welcome.mp4"
#define VIDEO_TRUE "ends\\truth.mp4"

extern GameState gState;


enum EndType {
	blind,
	hd,
	immortality,
	money,
	power,
	welcome,
	truth
};




using namespace std;
using namespace sfe;
using namespace sf;

void playEnd(EndType endType, RenderWindow &window);