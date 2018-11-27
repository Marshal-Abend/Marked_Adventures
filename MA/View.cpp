#include "View.h"

View view;

View &getNewView(float x, float y)
{
	view.setCenter(x*0.1F, y*0.1F);
	return view;
}