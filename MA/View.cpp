#include "View.h"

View view;

View &getNewView(float x, float y)
{
	float scale = 0.35;
	if (x < (256 * 7 + 36) * scale)
	{
		x = (256 * 7 + 36)*scale;
	}
	/*if (y < 25)
	{

	}*/
	view.setCenter(x, y);

	return view;
}