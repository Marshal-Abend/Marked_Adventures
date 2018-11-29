#include "View.h"

View view;

View &getNewView(float x, float y)
{
	view.setCenter(x, y);
	
	return view;
}