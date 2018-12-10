#include "View.h"

View view;

View &getNewView(float x, float y)
{
	float scale = 0.1;
	if (x < (256 * 7 + 36) * scale)
	{
		x = (256 * 7 + 36)*scale;
	}
	if (y < (256 * 4 + 75) * scale)
	{
		y = (256 * 4 + 75)*scale;
	}
	view.setCenter(x, y);

	return view;
}